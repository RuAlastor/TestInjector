#include <iostream>
#include <Windows.h>

int main( int argc, char* argv[] )
{
    volatile bool check = true;
    std::string printing_string = "Dummy process string.";
    while ( check )
    {
        std::cout << printing_string << '\n';
        Sleep( 1000 );
    }

    return 0;
}