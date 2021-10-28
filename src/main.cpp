#include <Arduino.h>

#include "configuration.hpp"
#include "Networkmanager/Networkmanager.hpp"
#include "DeviceActions.hpp"
#include "IoTClient/IoTClient.hpp"

void resetSettings();
void setApMode();

NetworkManager *networkManager;
DeviceActions *deviceActions;
IoTClient *iotClient;
boolean justTurnedOn = true;

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

  Serial.printf("Initialize WiFi Manager\n");
  networkManager = new NetworkManager();

  Serial.printf("Creating device actions\n");
  deviceActions = new DeviceActions();

  iotClient = new IoTClient(&nextEffect);
}

void loop()
{
  networkManager->handleLoop();
  iotClient->keepConnection();


  if (justTurnedOn)
  {
    for (int effectIdx = 0; effectIdx < 5; effectIdx++)
    {
      int value = 0;
      iotClient->publishTelemetry(effects[effectIdx], &value);
    }
    justTurnedOn = false;
    return;
  }

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