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
#define CLIENT_ID "LightsEffectOne"
#define DEVICE_USERNAME "smart_effects_one_username"
#define DEVICE_PASSWORD "smart_effects_one_passwd"

// Effects definitions
#define HOT_GLOWING_EFFECTS_FEATURE_TOPIC "light_effect_one/effects/hot_glowing"
#define HOT_GLOWING_EFFECTS_FEATURE_ID "13969b56-8468-4fcb-99e1-9ae0ab42dec3"
#define COLD_GLOWING_EFFECTS_FEATURE_TOPIC "light_effect_one/effects/cold_glowing"
#define COLD_GLOWING_EFFECTS_FEATURE_ID "f3521127-9c6b-45cd-a7d3-44121a4a69d0"
#define DAWN_EFFECTS_FEATURE_TOPIC "light_effect_one/effects/dawn"
#define DAWN_EFFECTS_FEATURE_ID "f3fc9092-70a8-476d-b141-95018cea71f5"
#define SCAN_EFFECTS_FEATURE_TOPIC "light_effect_one/effects/scan"
#define SCAN_EFFECTS_FEATURE_ID "108aedda-78e9-4d83-b470-bd6826a71343"
#define SHUT_DOWN_EFFECTS_FEATURE_TOPIC "light_effect_one/effects/shut_down"
#define SHUT_DOWN_EFFECTS_FEATURE_ID "76070a3b-f0cf-452c-a0e5-cc94d34c4826"

// MQTT connection
#define BROKER_IP "cosy-hub-srv"
#define BROKER_PORT 1883

// Led strip configuration
#define LED_COUNT 12

#endif