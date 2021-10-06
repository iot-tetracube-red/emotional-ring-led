#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

// Definition of GPIO assignations
// The GPIO should be choosen between 
#define GPIO_LED 5
#define GPIO_RESET_BUTTON 0 
#define GPIO_AP_MODE_BUTTON 5

// Definition of Access Point informations
#define AP_NAME "EffectOne"
#define AP_PASSWORD "password"

// Definition of Basic Auth information
#define BASIC_AUTH_USERNAME "smart-relay"
#define BASIC_AUTH_PASSWORD "password"

// Definition of the device descriptors
#define CIRCUIT_ID "3fa85f64-5717-4562-b3fc-2c963f66afa6"
#define EFFECTS_FEATURE_ID "3845367f-2c1b-4c01-a2d7-42c708cf299c"
#define CLIENT_ID "LightEffectOne"
#define DEVICE_USERNAME "smart_relay_username"
#define DEVICE_PASSWORD "smart_relay_passwd"
#define EFFECTS_ACTION_TOPIC "light_effect_one/effects"

// MQTT connection
#define BROKER_IP "cosy-hub-srv"
#define BROKER_PORT 1883

// Led strip configuration
#define LED_COUNT 12

#endif