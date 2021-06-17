#include "Injector.h"

int Sorokin::Injector::Inject( const WCHAR* const proc_name, const char* const dll_name ) noexcept( true )
{
    DWORD proc_id = 0;
    while ( proc_id == 0 )
    {
        proc_id = GetProcId( proc_name );
        Sleep( 100 );
    }

    auto proc_ptr = OpenProcess( PROCESS_ALL_ACCESS, 0, proc_id );
    if ( proc_ptr && proc_ptr != INVALID_HANDLE_VALUE )
    {
        auto alloced_mem = VirtualAllocEx( proc_ptr, nullptr, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
        if ( alloced_mem != 0 )
        {
            WriteProcessMemory( proc_ptr, alloced_mem, dll_name, strlen( dll_name ) + 1, 0 );
            auto thread_ptr = CreateRemoteThread( proc_ptr, 0, 0,
                reinterpret_cast<LPTHREAD_START_ROUTINE>( LoadLibraryA ), alloced_mem, 0, 0 );
            if ( thread_ptr )
            {
                CloseHandle( thread_ptr );
            }
        }
        CloseHandle( proc_ptr );
    }

    return 0;
}

DWORD Sorokin::Injector::GetProcId( const WCHAR* const proc_name ) noexcept( true )
{
    DWORD result = 0;
    auto proc_snap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if ( proc_snap != INVALID_HANDLE_VALUE )
    {
        PROCESSENTRY32 proc_entry;
        proc_entry.dwSize = sizeof( proc_entry );
        if ( Process32First( proc_snap, &proc_entry ) )
        {
            do
            {
                if ( wcscmp( proc_entry.szExeFile, proc_name ) == 0 )
                {
                    result = proc_entry.th32ProcessID;
                    break;
                }
            } while ( Process32Next( proc_snap, &proc_entry ) );
        }
    }
    CloseHandle( proc_snap );
    return result;
}