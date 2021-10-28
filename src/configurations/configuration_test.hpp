#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

// Definition of GPIO assignations
// The GPIO should be choosen between 
#define GPIO_LED 5
#define GPIO_RESET_BUTTON 0 
#define GPIO_AP_MODE_BUTTON 5

// Definition of Access Point informations
#define AP_NAME "GlowingTest"
#define AP_PASSWORD "password"

// Definition of Basic Auth information
#define BASIC_AUTH_USERNAME "smart-relay"
#define BASIC_AUTH_PASSWORD "password"

// Definition of the device descriptors
#define CIRCUIT_ID "ad4d3aa8-5b81-404d-b7e2-79ddfb23a079"
#define CLIENT_ID "RingGlowTest"
#define DEVICE_USERNAME "smart_effects_test_username"
#define DEVICE_PASSWORD "smart_effects_test_passwd"

// Effects definitions
#define HOT_GLOWING_EFFECTS_FEATURE_TOPIC "light_effect_test/effects/hot_glowing"
#define HOT_GLOWING_EFFECTS_FEATURE_ID "717c0df9-2e08-4555-ba89-65d756915ba1"
#define COLD_GLOWING_EFFECTS_FEATURE_TOPIC "light_effect_test/effects/cold_glowing"
#define COLD_GLOWING_EFFECTS_FEATURE_ID "4b2e3cff-5d79-49a7-81c1-ee6edf1aab35"
#define DAWN_EFFECTS_FEATURE_TOPIC "light_effect_test/effects/dawn"
#define DAWN_EFFECTS_FEATURE_ID "1ea290ff-c28c-4ac7-a581-d43f525a5f2c"
#define SCAN_EFFECTS_FEATURE_TOPIC "light_effect_test/effects/scan"
#define SCAN_EFFECTS_FEATURE_ID "d5373802-d06b-441a-8434-5f91bde9d56f"
#define SHUT_DOWN_EFFECTS_FEATURE_TOPIC "light_effect_test/effects/shut_down"
#define SHUT_DOWN_EFFECTS_FEATURE_ID "8d651b3a-9a16-45d6-9437-7071a5080e21"

// Device user preferences
#define PREFERENCES_TOPIC "light_effect_two/settings"

// MQTT connection
#define BROKER_IP "192.168.1.187"
#define BROKER_PORT 1883

// Led strip configuration
#define LED_COUNT 12

#endif