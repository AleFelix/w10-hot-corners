#include "controller.h"

void Controller::startApp(char* pgrmName) {
    runMouseThread(pgrmName);
    ConfigHandler cfgHandler;
    configHandler = &cfgHandler;
    configHandler->checkIfConfigExists();
    mainWindowNS::createSettingsWindow(GetModuleHandle(0),GetModuleHandle(0),NULL,SW_SHOW,this);
}

void Controller::runMouseThread(char* pgrmName) {
    HANDLE hThread;
    DWORD dwThread;
    STR_MOUSE_THREAD parameters;
    parameters.pgrmName = pgrmName;
    parameters.controller = this;
    STR_MOUSE_THREAD* ptr_parameters = &parameters;
    hThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE) MyMouseLogger, (LPVOID) ptr_parameters, NULL, &dwThread);
}

void Controller::saveNewConfig(CONFIG_HOLDER configHolder) {
    configHandler->saveConfig(configHolder);
    mouseH->setConfig(configHolder);
}

CONFIG_HOLDER Controller::askForConfig() {
    mouseH->setConfig(configHandler->retrieveConfig());
    return configHandler->retrieveConfig();
}

void Controller::registerMouseHandler(MouseHandler* mouseHandler) {
    mouseH = mouseHandler;
}
