
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>


int WINAPI wWinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPWSTR lpCmdLine,
        int nCmdShow
        ) {
    fprintf(stdout, "Hello Windows. %d\n", nCmdShow);
    fprintf(stdout, "%ws\n", lpCmdLine);
    fprintf(stdout, "%p %p\n", hInstance, hPrevInstance);

    // create a "Hello World" message box using MessageBox()
    MessageBoxExW(NULL,
               L"Hello World!",
               L"Just another Hello World program!",
               MB_ICONEXCLAMATION | MB_OKCANCEL,
               0
               );

    return 0;
}
