#include "NetworkManager.hpp"

NetworkManager::NetworkManager()
{
    this->hostname = AP_NAME;
    Serial.begin(115200);
    WiFiManager wifiManager;
    wifiManager.resetSettings();

    wifiManager.autoConnect(this->hostname);

    if (!MDNS.begin(this->hostname))
    {
        while (1)
        {
            delay(1000);
        }
    }
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(5000);
        ESP.restart();
    }
    configOTA();
}

void NetworkManager::handleLoop() {
    ArduinoOTA.handle();
    MDNS.update();
}

void NetworkManager::configOTA() {
    ArduinoOTA.setHostname(this->hostname);
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
        } else { // U_FS
            type = "filesystem";
        }

        // NOTE: if updating FS this would be the place to unmount FS using FS.end()
        Serial.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) {
            Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
            Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
            Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
            Serial.println("End Failed");
        }
    });
    ArduinoOTA.begin();
    Serial.println("OTA Ready");
}
