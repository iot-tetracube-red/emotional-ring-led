#ifndef WIFIMANAGER_HPP
#define WIFIMANAGER_HPP

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "../configuration.hpp"

class WiFiManager
{

public:
    WiFiManager();
    void configure();
    void resetConfiguration();
    void runAPMode();

private:
    bool startWPS();
};

#endif //WIFIMANAGER_HPP
