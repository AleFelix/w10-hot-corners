#ifndef TRAYHANDLER_H_INCLUDED
#define TRAYHANDLER_H_INCLUDED

#define WINVER 0x0600
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "resource.h"
#include "controller.h"

#define ID_TRAY_APP_ICON    1001
#define ID_TRAY_EXIT        1002
#define ID_TRAY_SETTINGS    1003
#define ID_TRAY_TITLE       1004
#define WM_SYSICON          (WM_USER + 1)

#define BGRND_COLOR RGB(250, 250, 250)
#define NUM_CHILDS 22
#define ID_CHECK_1 101
#define ID_CHECK_2 102
#define ID_CHECK_3 103
#define ID_CHECK_4 104
#define ID_RDBT_1_1 201
#define ID_RDBT_2_1 202
#define ID_RDBT_3_1 203
#define ID_RDBT_4_1 204
#define ID_RDBT_1_2 211
#define ID_RDBT_2_2 212
#define ID_RDBT_3_2 213
#define ID_RDBT_4_2 214
#define ID_TBOX_1 301
#define ID_TBOX_2 302
#define ID_TBOX_3 303
#define ID_TBOX_4 304
#define ID_CBOX_1 401
#define ID_CBOX_2 402
#define ID_CBOX_3 403
#define ID_CBOX_4 404
#define ID_BTTSAVE 501
#define ID_BTTCANCEL 502
#define ID_CONTAINER_IMG 601
#define NUM_ITEMS 10
#define NUM_CORNERS 4
#define NUM_KEYS_SHORTCUT 6
#define NUM_SHORTCUT_ITEMS 46
#define ID_POPUP_CBOX_1 701
#define ID_POPUP_CBOX_2 702
#define ID_POPUP_CBOX_3 703
#define ID_POPUP_CBOX_4 704
#define ID_POPUP_CBOX_5 705
#define ID_POPUP_CBOX_6 706
#define ID_POPUP_BTTSAVE 801
#define ID_POPUP_BTTCANCEL 802
#define ID_POPUP_LABEL_1 901

class Controller;

namespace mainWindowNS {
    int createSettingsWindow(HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow, Controller* appController);
    LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
    void hideWindow();
    void restoreWindow();
    void minimizeWindow();
    void InitNotifyIconData();
    void addWindowChild(HWND* child);
    int changeCheck(HWND hwnd, int idCheckBox);
    void changeStateOfElement(HWND hwnd, int idCheckBox, HWND* windowElement);
    void setConfig(HWND* hwnd);
    UINT getCheckedFromBoolean(bool checkValue);
    bool getBooleanFromChecked(UINT checkValue);
    std::string getStringFromKeyNum(int keyNum);
    std::string getVisualStringFromKeyValues(int cornerNum);
    void setVisualStrings();
    void saveConfig(HWND* hwnd);
}

namespace popupWindowNS {
    int createPopupWindow();
    LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
    void setKeysValues(int clickedCorner);
    void setCustomShortcut();
    void setPosition();
}

#endif // TRAYHANDLER_H_INCLUDED
