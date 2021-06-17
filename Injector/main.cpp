#include <Windows.h>
#include <TlHelp32.h>

#include "Injector.h"

int main( int argc, char* argv[] )
{
    WCHAR proc_name[] = L"DummyProcess.exe";
    const char* dll_name = "C:\\Kappa\\Workspace\\CPlusPlus\\Injector\\Debug\\Inject.dll";

    Sorokin::Injector injector;
    injector.Inject( proc_name, dll_name );

    return 0;
}