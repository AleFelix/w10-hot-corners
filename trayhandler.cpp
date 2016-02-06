#include "trayhandler.h"

namespace {
    UINT WM_TASKBAR = 0;
    HWND Hwnd;
    HMENU Hmenu;
    NOTIFYICONDATA notifyIconData;
    TCHAR szTIP[64] = TEXT("W10 Hot Corners");
    char szClassName[ ] = "W10 Hot Corners Settings";
    HWND check1, check2, check3, check4, rdbt1_1, rdbt1_2, rdbt2_1, rdbt2_2, rdbt3_1, rdbt3_2, rdbt4_1, rdbt4_2;
    HWND cbox1, cbox2, cbox3, cbox4, tbox1, tbox2, tbox3, tbox4, bttCancel, bttSave, containerImg;
    HBITMAP img;
    HFONT customFont;
    HWND* windowChilds[NUM_CHILDS];
    int windowChildsIndex = 0;
    const char *ComboBoxItems[] = { "Task View", "Search", "Action Center", "New V. Desktop", "Close V. Desktop", "Right V. Desktop", "Left V. Desktop", "Start Menu", "Switch Task", "Settings" };
    HWND* comboBoxes[NUM_CORNERS];
    Controller* appController;
    CONFIG_HOLDER configHolder;
    HWND popupHWND, popupCbox1, popupCbox2, popupCbox3, popupCbox4, popupCbox5, popupCbox6, popupBttCancel, popupBttSave, popupLabel;
    HWND* popupComboBoxes[NUM_KEYS_SHORTCUT];
    const char *popupComboBoxItems[] = { "---", "Ctrl", "Alt", "Shift", "Tab", "Win", "Enter", "Del", "Space",
                                        "Esc", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                                        "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "0",
                                        "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    std::string customkeys[NUM_KEYS_SHORTCUT];
    int currentCorner;
}

int mainWindowNS::createSettingsWindow(HINSTANCE hThisInstance,
                         HINSTANCE hPrevInstance,
                         LPSTR lpszArgument,
                         int nCmdShow,
                         Controller* controller) {
    appController = controller;
    MSG messages;
    WNDCLASSEX wincl;
    WM_TASKBAR = RegisterWindowMessageA("TaskbarCreated");
    wincl.hInstance = GetModuleHandle(0);
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
    wincl.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 255, 255)));

    if (!RegisterClassEx (&wincl))
        return 0;

    Hwnd = CreateWindowEx (
               0,
               szClassName,
               szClassName,
               WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
               CW_USEDEFAULT,
               CW_USEDEFAULT,
               710,
               378,
               HWND_DESKTOP,
               NULL,
               GetModuleHandle(0),
               NULL
           );
    InitNotifyIconData();
    SetActiveWindow(Hwnd);

    while (GetMessage (&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}

LRESULT CALLBACK mainWindowNS::WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_TASKBAR && !IsWindowVisible(Hwnd)) {
        hideWindow();
        return 0;
    }

    switch (message) {
    case WM_ACTIVATE:
        Shell_NotifyIcon(NIM_ADD, &notifyIconData);
        break;

    case WM_CREATE:
        SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND,(LONG)CreateSolidBrush(BGRND_COLOR));
        InvalidateRect(hwnd, NULL, TRUE);
        customFont = CreateFont (17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
                                 OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                 DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma"));
        Hmenu = CreatePopupMenu();
        AppendMenu(Hmenu, MF_GRAYED, ID_TRAY_TITLE, TEXT("W10 Hot Corners"));
        AppendMenu(Hmenu, MF_SEPARATOR, NULL, NULL);
        AppendMenu(Hmenu, MF_STRING, ID_TRAY_SETTINGS, TEXT("Settings"));
        AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT, TEXT("Exit"));
        check1 = CreateWindow("BUTTON", "Enabled",
                              WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                              20, 12, 69, 18,
                              hwnd, (HMENU)ID_CHECK_1, NULL, NULL);
        check2 = CreateWindow("BUTTON", "Enabled",
                              WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                              512, 12, 69, 18,
                              hwnd, (HMENU)ID_CHECK_2, NULL, NULL);
        check3 = CreateWindow("BUTTON", "Enabled",
                              WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                              20, 154, 69, 18,
                              hwnd, (HMENU)ID_CHECK_3, NULL, NULL);
        check4 = CreateWindow("BUTTON", "Enabled",
                              WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
                              512, 154, 69, 18,
                              hwnd, (HMENU)ID_CHECK_4, NULL, NULL);
        rdbt1_1 = CreateWindow("BUTTON", "Action",
                               WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
                               20, 38, 56, 18,
                               hwnd, (HMENU)ID_RDBT_1_1, NULL, NULL);
        rdbt1_2 = CreateWindow("BUTTON", "Custom",
                               WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                               20, 97, 65, 18,
                               hwnd, (HMENU)ID_RDBT_1_2, NULL, NULL);
        rdbt2_1 = CreateWindow("BUTTON", "Action",
                               WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
                               512, 38, 56, 18,
                               hwnd, (HMENU)ID_RDBT_2_1, NULL, NULL);
        rdbt2_2 = CreateWindow("BUTTON", "Custom",
                               WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                               512, 97, 65, 18,
                               hwnd, (HMENU)ID_RDBT_2_2, NULL, NULL);
        rdbt3_1 = CreateWindow("BUTTON", "Action",
                               WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
                               20, 180, 56, 18,
                               hwnd, (HMENU)ID_RDBT_3_1, NULL, NULL);
        rdbt3_2 = CreateWindow("BUTTON", "Custom",
                               WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                               20, 239, 65, 18,
                               hwnd, (HMENU)ID_RDBT_3_2, NULL, NULL);
        rdbt4_1 = CreateWindow("BUTTON", "Action",
                               WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
                               512, 180, 56, 18,
                               hwnd, (HMENU)ID_RDBT_4_1, NULL, NULL);
        rdbt4_2 = CreateWindow("BUTTON", "Custom",
                               WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                               512, 239, 65, 18,
                               hwnd, (HMENU)ID_RDBT_4_2, NULL, NULL);
        tbox1 = CreateWindow("EDIT","",
                             WS_BORDER | WS_CHILD | WS_VISIBLE,
                             20, 122, 173, 23,
                             hwnd, (HMENU)ID_TBOX_1, NULL, NULL);
        tbox2 = CreateWindow("EDIT","",
                             WS_BORDER | WS_CHILD | WS_VISIBLE,
                             512, 122, 173, 23,
                             hwnd, (HMENU)ID_TBOX_2, NULL, NULL);
        tbox3 = CreateWindow("EDIT","",
                             WS_BORDER | WS_CHILD | WS_VISIBLE,
                             20, 264, 173, 23,
                             hwnd, (HMENU)ID_TBOX_3, NULL, NULL);
        tbox4 = CreateWindow("EDIT","",
                             WS_BORDER | WS_CHILD | WS_VISIBLE,
                             512, 264, 173, 23,
                             hwnd, (HMENU)ID_TBOX_4, NULL, NULL);
        cbox1 = CreateWindow("ComboBox", "",
                             CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                             20, 64, 173, 23,
                             hwnd, (HMENU)ID_CBOX_1, NULL, NULL);
        cbox2 = CreateWindow("ComboBox", "",
                             CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                             512, 64, 173, 23,
                             hwnd, (HMENU)ID_CBOX_2, NULL, NULL);
        cbox3 = CreateWindow("ComboBox", "",
                             CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                             20, 206, 173, 23,
                             hwnd, (HMENU)ID_CBOX_3, NULL, NULL);
        cbox4 = CreateWindow("ComboBox", "",
                             CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
                             512, 206, 173, 23,
                             hwnd, (HMENU)ID_CBOX_4, NULL, NULL);
        bttSave = CreateWindow("BUTTON", "Save",
                               WS_VISIBLE | WS_CHILD,
                               625, 315, 70, 25,
                               hwnd, (HMENU)ID_BTTSAVE, NULL, NULL);
        bttCancel = CreateWindow("BUTTON", "Cancel",
                                 WS_VISIBLE | WS_CHILD,
                                 546, 315, 70, 25,
                                 hwnd, (HMENU)ID_BTTCANCEL, NULL, NULL);
        containerImg = CreateWindow("STATIC", "",
                                    WS_CHILD | SS_BITMAP | WS_VISIBLE,
                                    202, 51, 300, 225,
                                    hwnd, (HMENU)ID_CONTAINER_IMG, NULL, NULL);
        img = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IMG1));
        SendMessage(containerImg, STM_SETIMAGE, (WPARAM) IMAGE_BITMAP, (LPARAM) img);
        addWindowChild(&check1);
        addWindowChild(&check2);
        addWindowChild(&check3);
        addWindowChild(&check4);
        addWindowChild(&rdbt1_1);
        addWindowChild(&rdbt1_2);
        addWindowChild(&rdbt2_1);
        addWindowChild(&rdbt2_2);
        addWindowChild(&rdbt3_1);
        addWindowChild(&rdbt3_2);
        addWindowChild(&rdbt4_1);
        addWindowChild(&rdbt4_2);
        addWindowChild(&tbox1);
        addWindowChild(&tbox2);
        addWindowChild(&tbox3);
        addWindowChild(&tbox4);
        addWindowChild(&cbox1);
        addWindowChild(&cbox2);
        addWindowChild(&cbox3);
        addWindowChild(&cbox4);
        addWindowChild(&bttSave);
        addWindowChild(&bttCancel);
        comboBoxes[0] = &cbox1;
        comboBoxes[1] = &cbox2;
        comboBoxes[2] = &cbox3;
        comboBoxes[3] = &cbox4;
        int i;
        for (i = 0; i < windowChildsIndex; i++) {
            SendMessage(*windowChilds[i], WM_SETFONT,(WPARAM) customFont, TRUE);
        }
        int j;
        for (i = 0; i < NUM_CORNERS; i++) {
            for (j = 0; j< NUM_ITEMS; j++) {
                SendMessage(*comboBoxes[i], CB_ADDSTRING, 0, (LPARAM) TEXT(ComboBoxItems[j]));
            }
        }
        configHolder = appController->askForConfig();
        setConfig(&hwnd);
        setVisualStrings();
        popupWindowNS::createPopupWindow();
        break;

    case WM_SYSCOMMAND:
        switch(LOWORD(wParam)) {
        case SC_MINIMIZE:
            minimizeWindow();
            return 0;
            break;
        case SC_CLOSE:
            hideWindow() ;
            return 0;
            break;
        }
        break;

    case WM_SYSICON: {
        switch(wParam) {
        case ID_TRAY_APP_ICON:
            SetForegroundWindow(Hwnd);
            break;
        }
        if (lParam == WM_LBUTTONUP && !IsWindowVisible(Hwnd)) {
            restoreWindow();
        } else if (lParam == WM_RBUTTONDOWN) {
            POINT curPoint ;
            GetCursorPos( &curPoint ) ;
            SetForegroundWindow(Hwnd);

            UINT clicked = TrackPopupMenu(Hmenu,TPM_RETURNCMD | TPM_NONOTIFY,curPoint.x,curPoint.y,0,hwnd,NULL);
            SendMessage(hwnd, WM_NULL, 0, 0);
            if (clicked == ID_TRAY_EXIT) {
                Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
                PostQuitMessage( 0 ) ;
            } else if (clicked == ID_TRAY_SETTINGS && !IsWindowVisible(Hwnd)) {
                restoreWindow();
            }
        }
    }
    break;

    case WM_NCHITTEST: {
        UINT uHitTest = DefWindowProc(hwnd, WM_NCHITTEST, wParam, lParam);
        if(uHitTest == HTCLIENT) {
            return HTCAPTION;
        } else {
            return uHitTest;
        }
    }

    case WM_CLOSE:
        hideWindow();
        return 0;
        break;

    case WM_DESTROY:
        PostQuitMessage (0);
        break;

    case WM_CTLCOLORSTATIC:
        static HBRUSH hBrushColor;
        if (!hBrushColor) {
            hBrushColor = CreateSolidBrush(BGRND_COLOR);
            SetBkColor((HDC)wParam, BGRND_COLOR);
        }
        return (LRESULT)hBrushColor;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_CHECK_1:
            CheckDlgButton(hwnd, ID_CHECK_1, changeCheck(hwnd, ID_CHECK_1));
            changeStateOfElement(hwnd,ID_CHECK_1,&cbox1);
            changeStateOfElement(hwnd,ID_CHECK_1,&tbox1);
            changeStateOfElement(hwnd,ID_CHECK_1,&rdbt1_1);
            changeStateOfElement(hwnd,ID_CHECK_1,&rdbt1_2);
            break;
        case ID_CHECK_2:
            CheckDlgButton(hwnd, ID_CHECK_2, changeCheck(hwnd, ID_CHECK_2));
            changeStateOfElement(hwnd,ID_CHECK_2,&cbox2);
            changeStateOfElement(hwnd,ID_CHECK_2,&tbox2);
            changeStateOfElement(hwnd,ID_CHECK_2,&rdbt2_1);
            changeStateOfElement(hwnd,ID_CHECK_2,&rdbt2_2);
            break;
        case ID_CHECK_3:
            CheckDlgButton(hwnd, ID_CHECK_3, changeCheck(hwnd, ID_CHECK_3));
            changeStateOfElement(hwnd,ID_CHECK_3,&cbox3);
            changeStateOfElement(hwnd,ID_CHECK_3,&tbox3);
            changeStateOfElement(hwnd,ID_CHECK_3,&rdbt3_1);
            changeStateOfElement(hwnd,ID_CHECK_3,&rdbt3_2);
            break;
        case ID_CHECK_4:
            CheckDlgButton(hwnd, ID_CHECK_4, changeCheck(hwnd, ID_CHECK_4));
            changeStateOfElement(hwnd,ID_CHECK_4,&cbox4);
            changeStateOfElement(hwnd,ID_CHECK_4,&tbox4);
            changeStateOfElement(hwnd,ID_CHECK_4,&rdbt4_1);
            changeStateOfElement(hwnd,ID_CHECK_4,&rdbt4_2);
            break;
        case ID_TBOX_1:
            if (HIWORD(wParam) == EN_SETFOCUS) {
                popupWindowNS::setPosition();
                ShowWindow(popupHWND, SW_SHOW);
                popupWindowNS::setKeysValues(0);
                EnableWindow(Hwnd, false);
            }
            break;
        case ID_TBOX_2:
            if (HIWORD(wParam) == EN_SETFOCUS) {
                popupWindowNS::setPosition();
                ShowWindow(popupHWND, SW_SHOW);
                popupWindowNS::setKeysValues(1);
                EnableWindow(Hwnd, false);
            }
            break;
        case ID_TBOX_3:
            if (HIWORD(wParam) == EN_SETFOCUS) {
                popupWindowNS::setPosition();
                ShowWindow(popupHWND, SW_SHOW);
                popupWindowNS::setKeysValues(2);
                EnableWindow(Hwnd, false);
            }
            break;
        case ID_TBOX_4:
            if (HIWORD(wParam) == EN_SETFOCUS) {
                popupWindowNS::setPosition();
                ShowWindow(popupHWND, SW_SHOW);
                popupWindowNS::setKeysValues(3);
                EnableWindow(Hwnd, false);
            }
            break;
        case ID_BTTSAVE:
            saveConfig(&hwnd);
        case ID_BTTCANCEL:
            ShowWindow(Hwnd, SW_HIDE);
            break;
        }
        break;
    }
    return DefWindowProc( hwnd, message, wParam, lParam ) ;
}

void mainWindowNS::saveConfig(HWND* hwnd) {
    configHolder.enabled[0] = getBooleanFromChecked(Button_GetCheck(check1));
    configHolder.enabled[1] = getBooleanFromChecked(Button_GetCheck(check2));
    configHolder.enabled[2] = getBooleanFromChecked(Button_GetCheck(check3));
    configHolder.enabled[3] = getBooleanFromChecked(Button_GetCheck(check4));
    configHolder.custom[0] = getBooleanFromChecked(Button_GetCheck(rdbt1_2));
    configHolder.custom[1] = getBooleanFromChecked(Button_GetCheck(rdbt2_2));
    configHolder.custom[2] = getBooleanFromChecked(Button_GetCheck(rdbt3_2));
    configHolder.custom[3] = getBooleanFromChecked(Button_GetCheck(rdbt4_2));
    configHolder.option[0] = ComboBox_GetCurSel(cbox1);
    configHolder.option[1] = ComboBox_GetCurSel(cbox2);
    configHolder.option[2] = ComboBox_GetCurSel(cbox3);
    configHolder.option[3] = ComboBox_GetCurSel(cbox4);
    appController->saveNewConfig(configHolder);
}

bool mainWindowNS::getBooleanFromChecked(UINT checkValue) {
    if (checkValue == BST_CHECKED) {
        return true;
    } else {
        return false;
    }
}

void mainWindowNS::setVisualStrings() {
    HWND* textBoxes[4] = {&tbox1, &tbox2, &tbox3, &tbox4};
    std::string keyValuesString;
    int i;
    for (i = 0; i < 4; i++) {
        keyValuesString = getVisualStringFromKeyValues(i);
        SendMessage(*textBoxes[i], WM_SETTEXT, NULL, (LPARAM)keyValuesString.c_str());
    }
}

std::string mainWindowNS::getVisualStringFromKeyValues(int cornerNum) {
    std::string keyValuesString = "";
    int i, item;
    for (i = 0; i < NUM_KEYS_SHORTCUT; i++) {
        item = configHolder.customShortcut[cornerNum][i];
        if (item != 0) {
            if (keyValuesString != "") {
                keyValuesString = keyValuesString + "+" + popupComboBoxItems[item];
            } else {
                keyValuesString = keyValuesString + popupComboBoxItems[item];
            }
        }
    }
    return keyValuesString;
}

void mainWindowNS::hideWindow() {
    ShowWindow(Hwnd, SW_HIDE);
}


void mainWindowNS::restoreWindow() {
    configHolder = appController->askForConfig();
    setConfig(&Hwnd);
    ShowWindow(Hwnd, SW_SHOW);
    setVisualStrings();
}

void mainWindowNS::minimizeWindow() {
    ShowWindow(Hwnd, SW_MINIMIZE);
}

void mainWindowNS::InitNotifyIconData() {
    memset(&notifyIconData, 0, sizeof(NOTIFYICONDATA));
    notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
    notifyIconData.hWnd = Hwnd;
    notifyIconData.uID = ID_TRAY_APP_ICON;
    notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    notifyIconData.uCallbackMessage = WM_SYSICON; //Set up our invented Windows Message
    notifyIconData.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
    strncpy(notifyIconData.szTip, szTIP, sizeof(szTIP));
}

void mainWindowNS::addWindowChild(HWND* child) {
    windowChilds[windowChildsIndex] = child;
    windowChildsIndex++;
}

void mainWindowNS::changeStateOfElement(HWND hwnd, int idCheckBox, HWND* windowElement) {
    if (IsDlgButtonChecked(hwnd, idCheckBox)) {
        EnableWindow(*windowElement, true);
    } else {
        EnableWindow(*windowElement, false);
    }
}

int mainWindowNS::changeCheck(HWND hwnd, int idCheckBox) {
    if (IsDlgButtonChecked(hwnd, idCheckBox)) {
        return BST_UNCHECKED;
    } else {
        return BST_CHECKED;
    }
}

UINT mainWindowNS::getCheckedFromBoolean(bool checkValue) {
    if (checkValue) {
        return BST_CHECKED;
    } else {
        return BST_UNCHECKED;
    }
}

void mainWindowNS::setConfig(HWND* hwnd) {
    CheckDlgButton(*hwnd, ID_CHECK_1, getCheckedFromBoolean(configHolder.enabled[0]));
    CheckDlgButton(*hwnd, ID_CHECK_2, getCheckedFromBoolean(configHolder.enabled[1]));
    CheckDlgButton(*hwnd, ID_CHECK_3, getCheckedFromBoolean(configHolder.enabled[2]));
    CheckDlgButton(*hwnd, ID_CHECK_4, getCheckedFromBoolean(configHolder.enabled[3]));
    CheckDlgButton(*hwnd, ID_RDBT_1_1, getCheckedFromBoolean(!configHolder.custom[0]));
    CheckDlgButton(*hwnd, ID_RDBT_2_1, getCheckedFromBoolean(!configHolder.custom[1]));
    CheckDlgButton(*hwnd, ID_RDBT_3_1, getCheckedFromBoolean(!configHolder.custom[2]));
    CheckDlgButton(*hwnd, ID_RDBT_4_1, getCheckedFromBoolean(!configHolder.custom[3]));
    CheckDlgButton(*hwnd, ID_RDBT_1_2, getCheckedFromBoolean(configHolder.custom[0]));
    CheckDlgButton(*hwnd, ID_RDBT_2_2, getCheckedFromBoolean(configHolder.custom[1]));
    CheckDlgButton(*hwnd, ID_RDBT_3_2, getCheckedFromBoolean(configHolder.custom[2]));
    CheckDlgButton(*hwnd, ID_RDBT_4_2, getCheckedFromBoolean(configHolder.custom[3]));
    ComboBox_SetCurSel(cbox1,configHolder.option[0]);
    ComboBox_SetCurSel(cbox2,configHolder.option[1]);
    ComboBox_SetCurSel(cbox3,configHolder.option[2]);
    ComboBox_SetCurSel(cbox4,configHolder.option[3]);
    changeStateOfElement(*hwnd,ID_CHECK_1,&cbox1);
    changeStateOfElement(*hwnd,ID_CHECK_1,&tbox1);
    changeStateOfElement(*hwnd,ID_CHECK_1,&rdbt1_1);
    changeStateOfElement(*hwnd,ID_CHECK_1,&rdbt1_2);
    changeStateOfElement(*hwnd,ID_CHECK_2,&cbox2);
    changeStateOfElement(*hwnd,ID_CHECK_2,&tbox2);
    changeStateOfElement(*hwnd,ID_CHECK_2,&rdbt2_1);
    changeStateOfElement(*hwnd,ID_CHECK_2,&rdbt2_2);
    changeStateOfElement(*hwnd,ID_CHECK_3,&cbox3);
    changeStateOfElement(*hwnd,ID_CHECK_3,&tbox3);
    changeStateOfElement(*hwnd,ID_CHECK_3,&rdbt3_1);
    changeStateOfElement(*hwnd,ID_CHECK_3,&rdbt3_2);
    changeStateOfElement(*hwnd,ID_CHECK_4,&cbox4);
    changeStateOfElement(*hwnd,ID_CHECK_4,&tbox4);
    changeStateOfElement(*hwnd,ID_CHECK_4,&rdbt4_1);
    changeStateOfElement(*hwnd,ID_CHECK_4,&rdbt4_2);
}

std::string mainWindowNS::getStringFromKeyNum(int keyNum) {
    return popupComboBoxItems[keyNum];
}

void popupWindowNS::setPosition() {
    RECT posMain, sizeMain, sizePopup;
    GetWindowRect(Hwnd,(LPRECT)&posMain);
    GetClientRect(Hwnd,(LPRECT)&sizeMain);
    GetClientRect(popupHWND,(LPRECT)&sizePopup);
    int xOffset = (sizeMain.right - sizePopup.right) / 2;
    int yOffset = (sizeMain.bottom - sizePopup.bottom) / 2;
    if (xOffset >= 0 && yOffset >= 0) {
        SetWindowPos(popupHWND, NULL, posMain.left + xOffset, posMain.top + yOffset, NULL, NULL, SWP_NOSIZE);
    }
}

void popupWindowNS::setKeysValues(int clickedCorner) {
    currentCorner = clickedCorner;
    int i;
    for (i = 0; i < NUM_KEYS_SHORTCUT; i++) {
        ComboBox_SetCurSel(*popupComboBoxes[i],configHolder.customShortcut[clickedCorner][i]);
    }
}

void popupWindowNS::setCustomShortcut() {
    int i, j, k, selection;
    bool repeatedKeys[NUM_KEYS_SHORTCUT];
    memset(&repeatedKeys, false, sizeof(bool) * NUM_KEYS_SHORTCUT);
    std::string keyValuesString;
    HWND* textBoxes[4] = {&tbox1, &tbox2, &tbox3, &tbox4};
    for (i = 0; i < NUM_KEYS_SHORTCUT; i++) {
        selection = ComboBox_GetCurSel(*popupComboBoxes[i]);
        for (j = i + 1; j < NUM_KEYS_SHORTCUT; j++) {
            if (selection != 0 && !repeatedKeys[i] && selection == ComboBox_GetCurSel(*popupComboBoxes[j])) {
                repeatedKeys[j] = true;
            }
        }
        if (selection != 0 && !repeatedKeys[i]) {
            configHolder.customShortcut[currentCorner][k] = selection;
            k++;
        }
    }
    for (i = k; i < NUM_KEYS_SHORTCUT; i++) {
        configHolder.customShortcut[currentCorner][i] = 0;
    }
    keyValuesString = mainWindowNS::getVisualStringFromKeyValues(currentCorner);
    SendMessage(*textBoxes[currentCorner], WM_SETTEXT, NULL, (LPARAM)keyValuesString.c_str());
}

int popupWindowNS::createPopupWindow() {
    WNDCLASSEX wincl;

    wincl.hInstance = GetModuleHandle(0);
    wincl.lpszClassName = "Shortcut Keys";
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
    wincl.hIconSm = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(ICO1));
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 255, 255)));

    if (!RegisterClassEx (&wincl))
        return 0;

    popupHWND = CreateWindow(
               "Shortcut Keys",
               "Shortcut Keys",
               WS_POPUPWINDOW | WS_CAPTION,
               0,
               0,
               504,
               150,
               Hwnd,
               NULL,
               GetModuleHandle(0),
               NULL
           );
}

LRESULT CALLBACK popupWindowNS::WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {

    case WM_CREATE:
    {
        SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND,(LONG)CreateSolidBrush(BGRND_COLOR));
        InvalidateRect(hwnd, NULL, TRUE);
        customFont = CreateFont (17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
                                 OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                 DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma"));
        popupLabel = CreateWindow("STATIC", "Shortcut Configuration",
                              WS_VISIBLE | WS_CHILD,
                              12, 12, 142, 18,
                              hwnd, (HMENU)ID_POPUP_LABEL_1, NULL, NULL);
        popupCbox1 = CreateWindow("ComboBox", "",
                             CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
                             12, 45, 70, 23,
                             hwnd, (HMENU)ID_POPUP_CBOX_1, NULL, NULL);
        popupCbox2 = CreateWindow("ComboBox", "",
                             CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
                             94, 45, 70, 23,
                             hwnd, (HMENU)ID_POPUP_CBOX_2, NULL, NULL);
        popupCbox3 = CreateWindow("ComboBox", "",
                             CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
                             176, 45, 70, 23,
                             hwnd, (HMENU)ID_POPUP_CBOX_3, NULL, NULL);
        popupCbox4 = CreateWindow("ComboBox", "",
                             CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
                             258, 45, 70, 23,
                             hwnd, (HMENU)ID_POPUP_CBOX_4, NULL, NULL);
        popupCbox5 = CreateWindow("ComboBox", "",
                             CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
                             340, 45, 70, 23,
                             hwnd, (HMENU)ID_POPUP_CBOX_5, NULL, NULL);
        popupCbox6 = CreateWindow("ComboBox", "",
                             CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
                             422, 45, 70, 23,
                             hwnd, (HMENU)ID_POPUP_CBOX_6, NULL, NULL);
        popupBttSave = CreateWindow("BUTTON", "Save",
                               WS_VISIBLE | WS_CHILD,
                               422, 88, 70, 25,
                               hwnd, (HMENU)ID_POPUP_BTTSAVE, NULL, NULL);
        popupBttCancel = CreateWindow("BUTTON", "Cancel",
                                 WS_VISIBLE | WS_CHILD,
                                 340, 88, 70, 25,
                                 hwnd, (HMENU)ID_POPUP_BTTCANCEL, NULL, NULL);
        HWND* windowChilds[9] = {&popupCbox1, &popupCbox2, &popupCbox3, &popupCbox4, &popupCbox5,
                                &popupCbox6, &popupBttCancel, &popupBttSave, &popupLabel};
        popupComboBoxes[0] = &popupCbox1;
        popupComboBoxes[1] = &popupCbox2;
        popupComboBoxes[2] = &popupCbox3;
        popupComboBoxes[3] = &popupCbox4;
        popupComboBoxes[4] = &popupCbox5;
        popupComboBoxes[5] = &popupCbox6;
        int i, j;
        for (i = 0; i < 9; i++) {
            SendMessage(*windowChilds[i], WM_SETFONT,(WPARAM) customFont, TRUE);
        }
        for (i = 0; i < NUM_KEYS_SHORTCUT; i++) {
            SendMessage(*popupComboBoxes[i], CB_SETMINVISIBLE, (WPARAM)7, 0);
            for (j = 0; j < NUM_SHORTCUT_ITEMS; j++) {
                SendMessage(*popupComboBoxes[i], CB_ADDSTRING, 0, (LPARAM) TEXT(popupComboBoxItems[j]));
            }
        }
    }
    break;

     case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_POPUP_BTTSAVE:
            setCustomShortcut();
        case ID_POPUP_BTTCANCEL:
            EnableWindow(Hwnd, true);
            ShowWindow(popupHWND, SW_HIDE);
            break;
        }

    case WM_SYSCOMMAND:
        switch(LOWORD(wParam)) {
        case SC_CLOSE:
            EnableWindow(Hwnd, true);
            ShowWindow(popupHWND, SW_HIDE);
            return 0;
            break;
        }
        break;

    case WM_CTLCOLORSTATIC:
        static HBRUSH hBrushColor;
        if (!hBrushColor) {
            hBrushColor = CreateSolidBrush(BGRND_COLOR);
            SetBkColor((HDC)wParam, BGRND_COLOR);
        }
        return (LRESULT)hBrushColor;
    }
    return DefWindowProc( hwnd, message, wParam, lParam ) ;
}
