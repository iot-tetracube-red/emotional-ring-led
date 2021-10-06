#include "IoTClient.hpp"

IoTClient::IoTClient(int *nextSwitchValue)
{
    this->nextSwitchValue = nextSwitchValue;
    this->client = new WiFiClient();
    this->mqtt = new Adafruit_MQTT_Client(this->client, BROKER_IP, BROKER_PORT, "", "");
    this->switchSubscription = new Adafruit_MQTT_Subscribe(this->mqtt, SWITCH_ACTION_TOPIC, MQTT_QOS_1);

    this->mqtt->subscribe(this->switchSubscription);
}

void IoTClient::keepConnection()
{
    int8_t ret;
    if (this->mqtt->connected())
    {
        Adafruit_MQTT_Subscribe *subscription;
        while ((subscription = this->mqtt->readSubscription(100)))
        {
            if (subscription == this->switchSubscription)
            {
                if (strcmp((char *)this->switchSubscription->lastread, "TURN_OFF") == 0)
                {
                    *this->nextSwitchValue = 0;
                }
                if (strcmp((char *)this->switchSubscription->lastread, "TURN_ON") == 0)
                {
                    *this->nextSwitchValue = 1;
                }
            }
        }

        if (!this->mqtt->ping((uint8_t)1000))
        {
            Serial.printf("Disconnected\n");
            this->mqtt->disconnect();
        }
        return;
    }

    Serial.print("Connecting to MQTT... ");
    uint8_t retries = 3;
    while ((ret = this->mqtt->connect()) != 0)
    {
        Serial.println(this->mqtt->connectErrorString(ret));
        Serial.println("Retrying MQTT connection in 5 seconds...");
        this->mqtt->disconnect();
        delay(5000);
        retries--;
        if (retries == 0)
        {
            while (1)
            {
            }
        }
    }
    Serial.println("MQTT Connected!");
}

void IoTClient::publishTelemetry(const char *featureId, int *valueToPublish)
{
    const char *topic = (char *)"device/telemetry";

    char valueString[32];
    itoa(*valueToPublish, valueString, 10);

    char serializedTelemetryPayload[2048];
    DynamicJsonDocument telemetryPayload(2048);
    telemetryPayload["circuit_id"] = (char *)CIRCUIT_ID;
    telemetryPayload["feature_id"] = featureId;
    telemetryPayload["value"] = valueString;
    size_t writtenBytes = serializeJson(telemetryPayload, serializedTelemetryPayload);

    this->mqtt->publish(topic, (uint8_t *)serializedTelemetryPayload, writtenBytes, 1);
}