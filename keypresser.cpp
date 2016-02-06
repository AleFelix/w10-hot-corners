#include "keypresser.h"

#define KEYPRESS 0

KeyPresser::KeyPresser() {
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
}

void KeyPresser::sendKeys(int numKeys, int keys[MAX_KEYS]) {
    int i;
    for (i=0; i<numKeys; i++) {
        input.ki.wVk = keys[i];
        input.ki.dwFlags = KEYPRESS;
        SendInput(1, &input, sizeof(INPUT));
    }
    for (i=numKeys-1; i>=0; i--) {
        input.ki.wVk = keys[i];
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }
}

int KeyPresser::getKeyCombination(int keyCombinationCode, int keys[MAX_KEYS]) {
    int nKeys = 0;
    switch (keyCombinationCode) {
        case KEY_COMBINATION_TASK_VIEW:
            nKeys = 2;
            keys[0] = VK_LWIN;
            keys[1] = VK_TAB;
            break;
        case KEY_COMBINATION_SEARCH:
            nKeys = 2;
            keys[0] = VK_LWIN;
            keys[1] = 'S';
            break;
        case KEY_COMBINATION_ACTION_CENTER:
            nKeys = 2;
            keys[0] = VK_LWIN;
            keys[1] = 'A';
            break;
        case KEY_COMBINATION_NEW_VIRTUAL_DESKTOP:
            nKeys = 3;
            keys[0] = VK_LWIN;
            keys[1] = VK_LCONTROL;
            keys[2] = 'D';
            break;
        case KEY_COMBINATION_CLOSE_VIRTUAL_DESKTOP:
            nKeys = 3;
            keys[0] = VK_LWIN;
            keys[1] = VK_LCONTROL;
            keys[2] = VK_F4;
            break;
        case KEY_COMBINATION_RIGHT_VIRTUAL_DESKTOP:
            nKeys = 3;
            keys[0] = VK_LWIN;
            keys[1] = VK_LCONTROL;
            keys[2] = VK_RIGHT;
            break;
        case KEY_COMBINATION_LEFT_VIRTUAL_DESKTOP:
            nKeys = 3;
            keys[0] = VK_LWIN;
            keys[1] = VK_LCONTROL;
            keys[2] = VK_LEFT;
            break;
        case KEY_COMBINATION_START_MENU:
            nKeys = 1;
            keys[0] = VK_LWIN;
            break;
        case KEY_COMBINATION_SWITCH_TASK:
            nKeys = 2;
            keys[0] = VK_MENU;
            keys[1] = VK_TAB;
            break;
        case KEY_COMBINATION_SETTINGS:
            nKeys = 2;
            keys[0] = VK_LWIN;
            keys[1] = 'I';
            break;
    }
    return nKeys;
}

int KeyPresser::getKeySystemKeyCode(int keyCode) {
    switch (keyCode) {
        case KEY_CODE_NONE:
            return -1;
        case KEY_CODE_CTRL:
            return VK_LCONTROL;
        case KEY_CODE_ALT:
            return VK_MENU;
        case KEY_CODE_SHIFT:
            return VK_LSHIFT;
        case KEY_CODE_TAB:
            return VK_TAB;
        case KEY_CODE_WIN:
            return VK_LWIN;
        case KEY_CODE_ENTER:
            return VK_RETURN;
        case KEY_CODE_DEL:
            return VK_DELETE;
        case KEY_CODE_SPACE:
            return VK_SPACE;
        case KEY_CODE_A:
            return 'A';
        case KEY_CODE_B:
            return 'B';
        case KEY_CODE_C:
            return 'C';
        case KEY_CODE_D:
            return 'D';
        case KEY_CODE_E:
            return 'E';
        case KEY_CODE_F:
            return 'F';
        case KEY_CODE_G:
            return 'G';
        case KEY_CODE_H:
            return 'H';
        case KEY_CODE_I:
            return 'I';
        case KEY_CODE_J:
            return 'J';
        case KEY_CODE_K:
            return 'K';
        case KEY_CODE_L:
            return 'L';
        case KEY_CODE_M:
            return 'M';
        case KEY_CODE_N:
            return 'N';
        case KEY_CODE_O:
            return 'O';
        case KEY_CODE_P:
            return 'P';
        case KEY_CODE_Q:
            return 'Q';
        case KEY_CODE_R:
            return 'R';
        case KEY_CODE_S:
            return 'S';
        case KEY_CODE_T:
            return 'T';
        case KEY_CODE_U:
            return 'U';
        case KEY_CODE_V:
            return 'V';
        case KEY_CODE_W:
            return 'W';
        case KEY_CODE_X:
            return 'X';
        case KEY_CODE_Y:
            return 'Y';
        case KEY_CODE_Z:
            return 'Z';
        case KEY_CODE_0:
            return '0';
        case KEY_CODE_1:
            return '1';
        case KEY_CODE_2:
            return '2';
        case KEY_CODE_3:
            return '3';
        case KEY_CODE_4:
            return '4';
        case KEY_CODE_5:
            return '5';
        case KEY_CODE_6:
            return '6';
        case KEY_CODE_7:
            return '7';
        case KEY_CODE_8:
            return '8';
        case KEY_CODE_9:
            return '9';
    }
    return -1;
}
