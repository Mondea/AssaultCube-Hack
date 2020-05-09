// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "memory.h"
#include "Hook.h"

typedef int(_stdcall* twglSwapBuffers) (HDC hDc);

twglSwapBuffers owglSwapBuffers;

 int _stdcall hookFunc(HDC hDc) {
     std::cout << "Hooked\n";
    return owglSwapBuffers(hDc);
}

DWORD WINAPI HackThread(HMODULE hModule) {

    // Create Console for debugging/Writing
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "HOOKED BRO\n";


    //Test
    Hook wglSwapBuffersHook("wglSwapBuffers",L"opengl32.dll", (uintptr_t*)hookFunc, (uintptr_t*)&owglSwapBuffers, 5);
    wglSwapBuffersHook.Enable();
    Sleep(10000);
    wglSwapBuffersHook.Disable();
    Sleep(5000);
    wglSwapBuffersHook.Enable();
    Sleep(10000);
    wglSwapBuffersHook.Disable();

    //Ejecting the DLL
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

