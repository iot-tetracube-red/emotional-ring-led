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

int nextEffect = 0;
int currentEffect = 0;
int previousSwitchStatus = 0;
bool actionIsRunning = false;
char *effects[] = {
    SHUT_DOWN_EFFECTS_FEATURE_ID,
    HOT_GLOWING_EFFECTS_FEATURE_ID,
    COLD_GLOWING_EFFECTS_FEATURE_ID,
    DAWN_EFFECTS_FEATURE_ID,
    SCAN_EFFECTS_FEATURE_ID};

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

  iotClient = new IoTClient(&nextEffect);
}

void loop()
{
  //applicationServer->handleClient();
  iotClient->keepConnection();

  if (nextEffect != currentEffect)
  {
    Serial.printf("Current value %d and next value %d\n", currentEffect, nextEffect);

    for (int effectIdx = 0; effectIdx < 5; effectIdx++)
    {
      int value = effectIdx == nextEffect ? 1 : 0;
      iotClient->publishTelemetry(effects[effectIdx], &value);
    }
  }

  if (nextEffect == 1)
  {
    actionIsRunning = true;
    deviceActions->doHotEmotional(&currentEffect, 60);
  }
  else if (nextEffect == 2)
  {
    actionIsRunning = true;
    deviceActions->doColdEmotional(&currentEffect, 60);
  }
  else if (nextEffect == 3)
  {
    actionIsRunning = true;
    deviceActions->doDawn(&currentEffect);
  }
  else if (nextEffect == 4)
  {
    actionIsRunning = true;
    deviceActions->doScanEffect(&currentEffect);
  }
  else if (nextEffect == 0)
  {
    actionIsRunning = false;
    deviceActions->doShutDown(&currentEffect);
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