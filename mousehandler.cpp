#include "mousehandler.h"
#include "keypresser.h"

MouseHandler::MouseHandler() : configuration(new CONFIG_HOLDER()) {}

void MouseHandler::setController(Controller* controller) {
    appController = controller;
    controller->registerMouseHandler(this);
}

void MouseHandler::setConfig(CONFIG_HOLDER configHolder) {
    *configuration = configHolder;
    int i;
    for (i = 0; i < 4; i++) {
        enabledCorners[i] = configuration->enabled[i];
    }
}

int MouseHandler::getCornerKeyCombination(int corner) {
    int numberOfKeys = 0;
    int key;
    if(!configuration->custom[corner]) {
        numberOfKeys = keyPresser.getKeyCombination(configuration->option[corner], keys);
    } else {
        int i;
        for (i = 0; i < 6; i++) {
            key = keyPresser.getKeySystemKeyCode(configuration->customShortcut[corner][i]);
            if (key != -1) {
                keys[i] = key;
                numberOfKeys++;
            }
        }
    }
    return numberOfKeys;
}

void MouseHandler::setPoint(POINT point, int width, int height) {
    p = point;
    if (p.x <= MIN_DISTANCE && p.y <= MIN_DISTANCE && enabledCorners[0]) {
        if (!inArea) {
            numKeys = getCornerKeyCombination(0);
            keyPresser.sendKeys(numKeys, keys);
            inArea = true;
        }
    } else if (p.x >= (width - MIN_DISTANCE) && p.y <= MIN_DISTANCE && enabledCorners[1]) {
        if (!inArea) {
            numKeys = getCornerKeyCombination(1);
            keyPresser.sendKeys(numKeys, keys);
            inArea = true;
        }
    } else if (p.x <= MIN_DISTANCE && p.y >= (height - MIN_DISTANCE) && enabledCorners[2]) {
        if (!inArea) {
            numKeys = getCornerKeyCombination(2);
            keyPresser.sendKeys(numKeys, keys);
            inArea = true;
        }
    } else if (p.x >= (width - MIN_DISTANCE) && p.y >= (height - MIN_DISTANCE) && enabledCorners[3]) {
        if (!inArea) {
            numKeys = getCornerKeyCombination(3);
            keyPresser.sendKeys(numKeys, keys);
            inArea = true;
        }
    } else {
        inArea = false;
    }
}
