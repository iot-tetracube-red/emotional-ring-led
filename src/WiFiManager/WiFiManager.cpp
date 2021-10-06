#include "WiFiManager.hpp"

WiFiManager::WiFiManager()
{
}

bool WiFiManager::startWPS()
{
    Serial.printf("WPS configuration started");
    bool wpsSuccess = WiFi.beginWPSConfig();
    if (wpsSuccess)
    {
        String newSSID = WiFi.SSID();
        if (newSSID.length() > 0)
        {
            Serial.printf("WPS terminated. Login SSID '%s' \n ", newSSID.c_str());
        }
        else
        {
            wpsSuccess = false;
        }
    }
    return wpsSuccess;
}

void WiFiManager::configure()
{
    WiFi.mode(WIFI_STA);
    WiFi.hostname(AP_NAME);
    WiFi.begin(WiFi.SSID().c_str(), WiFi.psk().c_str());
    int cnt = 0;
    while ((WiFi.status() == WL_DISCONNECTED) && (cnt < 10))
    {
        delay(500);
        Serial.print(".");
        cnt++;
    }
    wl_status_t status = WiFi.status();
    if (status == WL_CONNECTED)
    {
        Serial.printf("\nLogin success to SSID '%s' \n", WiFi.SSID().c_str());
    }
    else
    {
        Serial.printf("\nCannot connect to WiFi. Status = '%d'\n ", status);
        if (!this->startWPS())
        {
            Serial.printf("WPS connection unsuccess, restart device and retry to connect");
        }
    }
}

void WiFiManager::resetConfiguration()
{
    station_config cfg;
    memcpy(cfg.ssid, "", 0);
    memcpy(cfg.password, "", 0);
    wifi_station_set_config(&cfg);

    bool disconnected = WiFi.disconnect(true);
    if (disconnected)
    {
        Serial.printf("Disconnected successfully\n");
    }
    delay(2000);
    ESP.reset();
}

void WiFiManager::runAPMode()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_NAME, AP_PASSWORD);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
}