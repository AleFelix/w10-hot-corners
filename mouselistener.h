#ifndef MOUSELISTENER_H_INCLUDED
#define MOUSELISTENER_H_INCLUDED

#define WINVER 0x0600
#include <windows.h>
#include <stdio.h>

#include "controller.h"

class Controller;

struct STR_MOUSE_THREAD {
    char* pgrmName;
    Controller* controller;
};

__declspec(dllexport) LRESULT CALLBACK KeyboardEvent (int nCode, WPARAM wParam, LPARAM lParam);

DWORD WINAPI MyMouseLogger(LPVOID lpParm);

void MessageLoop();

#endif // MOUSELISTENER_H_INCLUDED
