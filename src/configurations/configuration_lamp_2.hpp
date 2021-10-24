#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

// Definition of GPIO assignations
// The GPIO should be choosen between 
#define GPIO_LED 5
#define GPIO_RESET_BUTTON 0 
#define GPIO_AP_MODE_BUTTON 5

// Definition of Access Point informations
#define AP_NAME "EffectTwo"
#define AP_PASSWORD "password"

// Definition of Basic Auth information
#define BASIC_AUTH_USERNAME "smart-relay"
#define BASIC_AUTH_PASSWORD "password"

// Definition of the device descriptors
#define CIRCUIT_ID "1492b28c-e33b-4749-9644-8867a8993041"
#define CLIENT_ID "LightsEffectTwo"
#define DEVICE_USERNAME "smart_effects_two_username"
#define DEVICE_PASSWORD "smart_effects_two_passwd"

// Effects definitions
#define HOT_GLOWING_EFFECTS_FEATURE_TOPIC "light_effect_two/effects/hot_glowing"
#define HOT_GLOWING_EFFECTS_FEATURE_ID "0dd36f46-a358-44cd-9b97-5e98db8ff797"
#define COLD_GLOWING_EFFECTS_FEATURE_TOPIC "light_effect_two/effects/cold_glowing"
#define COLD_GLOWING_EFFECTS_FEATURE_ID "4b521bcb-f834-4d61-84cf-42cddbf92f21"
#define DAWN_EFFECTS_FEATURE_TOPIC "light_effect_two/effects/dawn"
#define DAWN_EFFECTS_FEATURE_ID "1ea290ff-c28c-4ac7-a581-d43f525a5f2c"
#define SCAN_EFFECTS_FEATURE_TOPIC "light_effect_two/effects/scan"
#define SCAN_EFFECTS_FEATURE_ID "8c37d5ce-ffa7-4303-9142-750a0691bd1d"
#define SHUT_DOWN_EFFECTS_FEATURE_TOPIC "light_effect_two/effects/shut_down"
#define SHUT_DOWN_EFFECTS_FEATURE_ID "7bbf0be2-82dc-49ba-af5e-29723ac51b2d"

// MQTT connection
#define BROKER_IP "cosy-hub-srv"
#define BROKER_PORT 1883

// Led strip configuration
#define LED_COUNT 12

#endif