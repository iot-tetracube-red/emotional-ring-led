#include <Arduino.h>

#include "configuration.hpp"
#include "WiFiManager/WiFiManager.hpp"
#include "DeviceActions.hpp"
#include "IoTClient/IoTClient.hpp"

void resetSettings();
void setApMode();

WiFiManager *wifiManager;
//ApplicationServer *applicationServer;
DeviceActions *deviceActions;
IoTClient *iotClient;

int nextSwitchValue = 0;
int currentValueSwitch = 0;
int previousSwitchStatus = 0;
bool actionIsRunning = false;

void setup()
{
  Serial.begin(115200);

  Serial.printf("Setup reset button\n");
  //pinMode(GPIO_RESET_BUTTON, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(GPIO_RESET_BUTTON), resetSettings, CHANGE);

  Serial.printf("Setup AP mode button\n");
  //pinMode(GPIO_AP_MODE_BUTTON, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(GPIO_AP_MODE_BUTTON), setApMode, CHANGE);

  Serial.printf("Initialize WiFi Manager\n");
  wifiManager = new WiFiManager();
  wifiManager->configure();

  Serial.printf("Creating device actions\n");
  deviceActions = new DeviceActions();

  //Serial.printf("Initialize Application server\n");
  //applicationServer = new ApplicationServer(deviceActions);

  iotClient = new IoTClient(&nextSwitchValue);
}

void loop()
{
  //applicationServer->handleClient();
  iotClient->keepConnection();

  if (nextSwitchValue != currentValueSwitch && !actionIsRunning)
  {
    Serial.printf("Current value %d and next value %d\n", currentValueSwitch, nextSwitchValue);
    if (nextSwitchValue == 0)
    {
      //deviceActions->turnOffRelay(&actionIsRunning, &currentValueSwitch, iotClient);
    }
    else if (nextSwitchValue == 1)
    {
      //deviceActions->turnOnRelay(&actionIsRunning, &currentValueSwitch, iotClient);
    }

    Serial.println("Finished to run");
    actionIsRunning = false;
  }
}

/*
void ICACHE_RAM_ATTR resetSettings()
{
  Serial.printf("Resetting device settings\n");
  wifiManager->resetConfiguration();
}

void ICACHE_RAM_ATTR setApMode()
{
  Serial.printf("Setting WiFi in AP mode\n");
  wifiManager->runAPMode();
}
*/