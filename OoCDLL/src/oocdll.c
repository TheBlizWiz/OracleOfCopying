#include <stdio.h>
#include "oocdll.h"
#include "framework.h"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD call, LPVOID reserved) {
    switch (call) {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}