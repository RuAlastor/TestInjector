#pragma once

#include <Windows.h>
#include <TlHelp32.h>

#include <string>

namespace Sorokin
{
    class Injector
    {
    public:
        Injector() = default;
        ~Injector() = default;

        Injector( const Injector& )             = delete;
        Injector& operator=( const Injector& )  = delete;
        Injector( Injector&& )                  = delete;
        Injector& operator=( Injector&& )       = delete;

        int Inject( const WCHAR* const proc_name, const char* const dll_name ) noexcept( true );

    public:
        static DWORD GetProcId( const WCHAR* const proc_name ) noexcept( true );
    };
}