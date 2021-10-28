#ifndef WIFIMANAGER_HPP
#define WIFIMANAGER_HPP

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>
#include <WiFiClientSecure.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "../configuration.hpp"

class NetworkManager
{

public:
    NetworkManager();
    void handleLoop(void);
    void setupWebServer();

private:
//    bool startWPS();
    void configOTA();

    char *hostname;
};

#endif //WIFIMANAGER_HPP
