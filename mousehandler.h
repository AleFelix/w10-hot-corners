#ifndef MOUSEHANDLER_H_INCLUDED
#define MOUSEHANDLER_H_INCLUDED

#define WINVER 0x0600
#include <windows.h>
#include <stdio.h>
#include <memory>
#include "keypresser.h"
#include "controller.h"

#define MIN_DISTANCE 2

class Controller;
class CONFIG_HOLDER;

class MouseHandler {
private:
    POINT p;
    bool inArea = false;
    KeyPresser keyPresser;
    int keys[MAX_KEYS];
    int numKeys;
    int selectedKeyCombination;
    Controller* appController;
    //CONFIG_HOLDER* configuration;
    std::unique_ptr<CONFIG_HOLDER> configuration;
    bool enabledCorners[4];
    int getCornerKeyCombination(int corner);
public:
    void setController(Controller* controller);
    void setPoint(POINT point, int width, int height);
    void setConfig(CONFIG_HOLDER configHolder);
    MouseHandler();
};

#endif // MOUSEHANDLER_H_INCLUDED
