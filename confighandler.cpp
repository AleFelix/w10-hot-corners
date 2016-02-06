#include "confighandler.h"

const char* ConfigHandler::filePath = "config.xml";

int ConfigHandler::checkIfConfigExists() {
    DWORD dwAttrib = GetFileAttributes(filePath);
    if (!(dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))) {
        const char* buffer = getDefaultConfig();
        DWORD dwWritten;
        HANDLE hFile;
        hFile=CreateFile(filePath,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
        if(hFile==INVALID_HANDLE_VALUE) {
            MessageBox(0,"Could not create/open a file","Error",16);
            return 1;
        }
        WriteFile(hFile,buffer,(strlen(buffer)*sizeof(char)),&dwWritten,0);
        CloseHandle(hFile);
    }
    return 0;
}

CONFIG_HOLDER ConfigHandler::retrieveConfig() {
    int i, id, keys[6];
    CONFIG_HOLDER configHolder;
    tinyxml2::XMLDocument xmlDoc;
    xmlDoc.LoadFile(filePath);
    xmlDocElement = xmlDoc.FirstChildElement()->FirstChildElement("corner");
    xmlDocElement->QueryIntAttribute("id", &id);
    id = id - 1;
    getValuesFromCorner();
    for (i = 0; i < 4; i++) {
        configHolder.enabled[id] = getBooleanValue(enabledElement->GetText()[0]);
        configHolder.custom[id] = getBooleanValue(customElement->GetText()[0]);
        configHolder.option[id] = strToInt(optionElement->GetText());
        parseStoredKeyValues(keys,customShElement->GetText());
        copyIntArray(keys, configHolder.customShortcut[id], 6);
        if (i < 3) {
            xmlDocElement = xmlDocElement->NextSiblingElement();
            xmlDocElement->QueryIntAttribute("id", &id);
            id = id - 1;
            getValuesFromCorner();
        }
    }
    return configHolder;
}

void ConfigHandler::saveConfig(CONFIG_HOLDER configHolder) {
    int i, id;
    tinyxml2::XMLDocument xmlDoc;
    xmlDoc.LoadFile(filePath);
    xmlDocElement = xmlDoc.FirstChildElement()->FirstChildElement("corner");
    xmlDocElement->QueryIntAttribute("id", &id);
    id = id - 1;
    for (i = 0; i < 4; i++) {
        xmlDocElement->FirstChildElement("enabled")->SetText(getCharValue(configHolder.enabled[id]).c_str());
        xmlDocElement->FirstChildElement("custom")->SetText(getCharValue(configHolder.custom[id]).c_str());
        xmlDocElement->FirstChildElement("option")->SetText(intToStr(configHolder.option[id]).c_str());
        xmlDocElement->FirstChildElement("custom_s")->SetText(keyValuesToString(configHolder.customShortcut[id]).c_str());
        if (i < 3) {
            xmlDocElement = xmlDocElement->NextSiblingElement();
            xmlDocElement->QueryIntAttribute("id", &id);
            id = id - 1;
        }
    }
    xmlDoc.SaveFile(filePath);
}

std::string ConfigHandler::keyValuesToString(int keyValues[6]) {
    int i, j, freeKeys = 6;
    bool repeatedKeys[6];
    memset(&repeatedKeys, false, sizeof(bool) * 6);
    std::string keysString = "";
    for (i = 0; i < 6; i++) {
        for (j = i + 1; j < 6; j++) {
            if (keyValues[i] == keyValues[j] && keyValues[i] != 0 && !repeatedKeys[i]) {
                repeatedKeys[j] = true;
            }
        }
        if (!repeatedKeys[i] && keyValues[i] != 0) {
            if (keysString == "") {
                keysString = keysString + intToStr(keyValues[i]);
            } else {
                keysString = keysString + "-" + intToStr(keyValues[i]);
            }
            freeKeys--;
        }
    }
    for (i = 0; i < freeKeys; i++) {
        if (keysString == "") {
            keysString = keysString + "0";
        } else {
            keysString = keysString + "-" + "0";
        }
    }
    return keysString;
}

void ConfigHandler::copyIntArray(int source[], int destination[], int length) {
    int i;
    for (i = 0; i < length; i++) {
        destination[i] = source[i];
    }
}

std::string ConfigHandler::intToStr(int i) {
    std::stringstream ss;
    ss << i;
    std::string str = ss.str();
    return str;
}

int ConfigHandler::strToInt(const std::string& s) {
    std::istringstream str(s);
    int i;
    str >> i;
    return i;
}

void ConfigHandler::getValuesFromCorner() {
    enabledElement = xmlDocElement->FirstChildElement("enabled");
    customElement = xmlDocElement->FirstChildElement("custom");
    optionElement = xmlDocElement->FirstChildElement("option");
    customShElement = xmlDocElement->FirstChildElement("custom_s");
}

void ConfigHandler::parseStoredKeyValues(int keys[6], std::string keysText) {
    int index = 0;
    std::stringstream ss(keysText);
    std::string token;
    while (getline(ss, token, '-') && index < 6) {
        keys[index] = strToInt(token);
        index++;
    }
}

std::string ConfigHandler::getCharValue(bool booleanValue) {
    if (booleanValue) {
        return "1";
    } else {
        return "0";
    }
}

bool ConfigHandler::getBooleanValue(char charValue) {
    if (charValue == '0') {
        return false;
    } else {
        return true;
    }
}

const char* ConfigHandler::getDefaultConfig() {
    return "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
            "<corners>\n"
                "\t<corner id=\"1\">\n"
                    "\t\t<enabled>1</enabled>\n"
                    "\t\t<custom>0</custom>\n"
                    "\t\t<option>0</option>\n"
                    "\t\t<custom_s>0-0-0-0-0-0</custom_s>\n"
                "\t</corner>\n"
                "\t<corner id=\"2\">\n"
                    "\t\t<enabled>0</enabled>\n"
                    "\t\t<custom>0</custom>\n"
                    "\t\t<option>0</option>\n"
                    "\t\t<custom_s>0-0-0-0-0-0</custom_s>\n"
                "\t</corner>\n"
                "\t<corner id=\"3\">\n"
                    "\t\t<enabled>0</enabled>\n"
                    "\t\t<custom>0</custom>\n"
                    "\t\t<option>0</option>\n"
                    "\t\t<custom_s>0-0-0-0-0-0</custom_s>\n"
                "\t</corner>\n"
                "\t<corner id=\"4\">\n"
                    "\t\t<enabled>0</enabled>\n"
                    "\t\t<custom>0</custom>\n"
                    "\t\t<option>0</option>\n"
                    "\t\t<custom_s>0-0-0-0-0-0</custom_s>\n"
                "\t</corner>\n"
            "</corners>";
}
