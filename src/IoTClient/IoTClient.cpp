#include "IoTClient.hpp"

IoTClient::IoTClient(int *nextEffect)
{
    this->nextEffect = nextEffect;
    this->client = new WiFiClient();
    this->mqtt = new Adafruit_MQTT_Client(this->client, BROKER_IP, BROKER_PORT, "", "");
    this->hotGlowEffectSubscription = new Adafruit_MQTT_Subscribe(this->mqtt, HOT_GLOWING_EFFECTS_FEATURE_TOPIC, MQTT_QOS_1);
    this->coldGlowEffectSubscription = new Adafruit_MQTT_Subscribe(this->mqtt, COLD_GLOWING_EFFECTS_FEATURE_TOPIC, MQTT_QOS_1);
    this->dawnEffectSubscription = new Adafruit_MQTT_Subscribe(this->mqtt, DAWN_EFFECTS_FEATURE_TOPIC, MQTT_QOS_1);
    this->scanEffectSubscription = new Adafruit_MQTT_Subscribe(this->mqtt, SCAN_EFFECTS_FEATURE_TOPIC, MQTT_QOS_1);
    this->shutDownSubscription = new Adafruit_MQTT_Subscribe(this->mqtt, SHUT_DOWN_EFFECTS_FEATURE_TOPIC, MQTT_QOS_1);

    this->mqtt->subscribe(this->hotGlowEffectSubscription);
    this->mqtt->subscribe(this->coldGlowEffectSubscription);
    this->mqtt->subscribe(this->dawnEffectSubscription);
    this->mqtt->subscribe(this->scanEffectSubscription);
    this->mqtt->subscribe(this->shutDownSubscription);
}

void IoTClient::keepConnection()
{
    int8_t ret;
    if (this->mqtt->connected())
    {
        Adafruit_MQTT_Subscribe *subscription;
        while ((subscription = this->mqtt->readSubscription(100)))
        {
            if (subscription == this->hotGlowEffectSubscription && strcmp((char *)this->hotGlowEffectSubscription->lastread, "1") == 0)
            {
                *this->nextEffect = 1;
            }
            if (subscription == this->coldGlowEffectSubscription && strcmp((char *)this->coldGlowEffectSubscription->lastread, "1") == 0)
            {
                *this->nextEffect = 2;
            }
            if (subscription == this->dawnEffectSubscription && strcmp((char *)this->dawnEffectSubscription->lastread, "1") == 0)
            {
                *this->nextEffect = 3;
            }
            if (subscription == this->scanEffectSubscription && strcmp((char *)this->scanEffectSubscription->lastread, "1") == 0)
            {
                *this->nextEffect = 4;
            }
            if (subscription == this->shutDownSubscription && strcmp((char *)this->shutDownSubscription->lastread, "1") == 0)
            {
                *this->nextEffect = 0;
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