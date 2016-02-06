#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "mouselistener.h"
#include "trayhandler.h"
#include "confighandler.h"
#include "mousehandler.h"

class ConfigHandler;
class MouseHandler;

struct CONFIG_HOLDER {
    bool enabled[4];
    bool custom[4];
    int option[4];
    int customShortcut[4][6];
};

class Controller {
private:
    ConfigHandler* configHandler;
    void runMouseThread(char* pgrmName);
    MouseHandler* mouseH;
public:
    void startApp(char* pgrmName);
    void saveNewConfig(CONFIG_HOLDER configHolder);
    CONFIG_HOLDER askForConfig();
    void registerMouseHandler(MouseHandler* mouseHandler);
};

#endif // CONTROLLER_H_INCLUDED
