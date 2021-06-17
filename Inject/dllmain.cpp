// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

int parasite_proc() noexcept( true )
{
    while ( true )
    {
        std::cout << "External proc string." << '\n';
        Sleep( 1000 );
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch ( ul_reason_for_call )
    {
        case DLL_PROCESS_ATTACH:
        {
            parasite_proc();
            break;
        }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

