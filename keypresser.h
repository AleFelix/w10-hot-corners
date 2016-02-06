#ifndef KEYPRESSER_H_INCLUDED
#define KEYPRESSER_H_INCLUDED

#define WINVER 0x0600
#include <windows.h>
#include <utility>

#define KEY_COMBINATION_TASK_VIEW 0
#define KEY_COMBINATION_SEARCH 1
#define KEY_COMBINATION_ACTION_CENTER 2
#define KEY_COMBINATION_NEW_VIRTUAL_DESKTOP 3
#define KEY_COMBINATION_CLOSE_VIRTUAL_DESKTOP 4
#define KEY_COMBINATION_RIGHT_VIRTUAL_DESKTOP 5
#define KEY_COMBINATION_LEFT_VIRTUAL_DESKTOP 6
#define KEY_COMBINATION_START_MENU 7
#define KEY_COMBINATION_SWITCH_TASK 8
#define KEY_COMBINATION_SETTINGS 9
#define KEY_CODE_NONE 0
#define KEY_CODE_CTRL 1
#define KEY_CODE_ALT 2
#define KEY_CODE_SHIFT 3
#define KEY_CODE_TAB 4
#define KEY_CODE_WIN 5
#define KEY_CODE_ENTER 6
#define KEY_CODE_DEL 7
#define KEY_CODE_SPACE 8
#define KEY_CODE_ESC 9
#define KEY_CODE_A 10
#define KEY_CODE_B 11
#define KEY_CODE_C 12
#define KEY_CODE_D 13
#define KEY_CODE_E 14
#define KEY_CODE_F 15
#define KEY_CODE_G 16
#define KEY_CODE_H 17
#define KEY_CODE_I 18
#define KEY_CODE_J 19
#define KEY_CODE_K 20
#define KEY_CODE_L 21
#define KEY_CODE_M 22
#define KEY_CODE_N 23
#define KEY_CODE_O 24
#define KEY_CODE_P 25
#define KEY_CODE_Q 26
#define KEY_CODE_R 27
#define KEY_CODE_S 28
#define KEY_CODE_T 29
#define KEY_CODE_U 30
#define KEY_CODE_V 31
#define KEY_CODE_W 32
#define KEY_CODE_X 33
#define KEY_CODE_Y 34
#define KEY_CODE_Z 35
#define KEY_CODE_0 36
#define KEY_CODE_1 37
#define KEY_CODE_2 38
#define KEY_CODE_3 39
#define KEY_CODE_4 40
#define KEY_CODE_5 41
#define KEY_CODE_6 42
#define KEY_CODE_7 43
#define KEY_CODE_8 44
#define KEY_CODE_9 45
#define MAX_KEYS 6

class KeyPresser {
private:
    INPUT input;
    int keyCodes[MAX_KEYS];
public:
    KeyPresser();
    void sendKeys(int numKeys, int keys[MAX_KEYS]);
    int getKeyCombination(int keyCombinationCode, int keys[MAX_KEYS]);
    int getKeySystemKeyCode(int keyCode);
};

#endif // KEYPRESSER_H_INCLUDED
