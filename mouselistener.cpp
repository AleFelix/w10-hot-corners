#include "mouselistener.h"
#include "mousehandler.h"

namespace {
    HHOOK hMouseHook;
    MouseHandler mouseHandler;
    Controller* applicationController;
    MOUSEHOOKSTRUCT* pMouseStruct;
}

__declspec(dllexport) LRESULT CALLBACK KeyboardEvent (int nCode, WPARAM wParam, LPARAM lParam) {
    pMouseStruct = (MOUSEHOOKSTRUCT *)lParam;
    if (pMouseStruct != NULL) {
        mouseHandler.setPoint(pMouseStruct->pt,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
    }
    return CallNextHookEx(hMouseHook,nCode,wParam,lParam);
}

void MessageLoop() {
    MSG message;
    while (GetMessage(&message,NULL,0,0)) {
        TranslateMessage( &message );
        DispatchMessage( &message );
    }
}

DWORD WINAPI MyMouseLogger(LPVOID lpParm) {
    STR_MOUSE_THREAD* parameters = (STR_MOUSE_THREAD*) lpParm;
    applicationController = parameters->controller;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    if (!hInstance) {
            hInstance = LoadLibrary((LPCSTR) parameters->pgrmName);
    }
    if (!hInstance) {
            return 1;
    }
    mouseHandler.setController(applicationController);
    hMouseHook = SetWindowsHookEx (WH_MOUSE_LL,(HOOKPROC) KeyboardEvent,hInstance,NULL);
    MessageLoop();
    UnhookWindowsHookEx(hMouseHook);
    return 0;
}
