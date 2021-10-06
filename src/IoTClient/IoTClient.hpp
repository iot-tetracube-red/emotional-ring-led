#ifndef IOTCLIENT_HPP
#define IOTCLIENT_HPP

#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <ArduinoJson.h>

#include "configuration.hpp"

class IoTClient
{

public:
    IoTClient(int *nextEffect);
    void keepConnection();
    void publishTelemetry(const char *featureId, int *valueToPublish);

private:
    int *nextEffect;
    WiFiClient *client;
    Adafruit_MQTT_Client *mqtt;
    Adafruit_MQTT_Subscribe *switchSubscription;
};

#endif