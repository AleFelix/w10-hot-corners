#ifndef CONFIGHANDLER_H_INCLUDED
#define CONFIGHANDLER_H_INCLUDED

#define WINVER 0x0600
#include <windows.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "lib/tinyxml2.h"
#include "controller.h"

class CONFIG_HOLDER;

class ConfigHandler {
private:
    tinyxml2::XMLElement *xmlDocElement, *enabledElement, *customElement, *optionElement, *customShElement;
    const char* getDefaultConfig();
    static const char* filePath;
    bool getBooleanValue(char charValue);
    std::string getCharValue(bool booleanValue);
    int strToInt(const std::string& s);
    std::string intToStr(int i);
    void getValuesFromCorner();
    void parseStoredKeyValues(int keys[6], std::string keysText);
    void copyIntArray(int source[], int destination[], int length);
    std::string keyValuesToString(int keyValues[6]);
public:
    int checkIfConfigExists();
    CONFIG_HOLDER retrieveConfig();
    void saveConfig(CONFIG_HOLDER configHolder);
};

#endif // CONFIGHANDLER_H_INCLUDED
