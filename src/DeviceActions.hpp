#ifndef DEVICEACTIONS_HPP
#define DEVICEACTIONS_HPP

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "configuration.hpp"
#include "IoTClient/IoTClient.hpp"

class DeviceActions
{
public:
    DeviceActions();
    void doHotEmotional(int *currentEffect, int wait);
    void doColdEmotional(int *currentEffect, int wait);
    void doDawn(int *currentEffect);
    void doScanEffect(int *currentEffect);
    void doShutDown(int *currentEffect);
    void setBrightness(int value);

private:
    int brightness = 100;
    /*** HOT EFFECT ***/
    long startHueHot = -8000;
    long pixelHueHot = startHueHot;
    long maxHueHot = 15000;
    int signHot = 1;

    /*** COLD EFFECT ***/
    long startHueCold = 15000;
    long pixelHueCold = startHueCold;
    long maxHueCold = 57536;
    int signCold = 1;

    /*** DAWN EFFECT ***/
    int durationDawn = 900000; //15 min
    const int delayTimeDawn = 20;
    // non serve modificare altro da qui in poi
    int lastRampStep = 0;
    const int redRamp[25] = {44, 54, 68, 85, 106, 133, 166, 207, 259, 324, 405, 456, 513, 577, 649, 730, 822, 924, 1023, 1023, 1023, 1023, 1023, 1023, 1023};
    const int greenRamp[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 51, 120, 214, 340, 506, 570, 641, 721, 811, 913, 1023, 1023, 1023, 1023};
    const int blueRamp[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 155, 367, 671, 755, 850, 956, 1023, 1023, 1023};
    int iDawn = 0;
    int currentRampStep = 0;
    bool stopDawn = false;

    /*** SCANNER EFFECT ***/
    int totalSteps = 0;
    int index = 0;
    int delayTimeScanner = 100;
    int scannerRed = 0;
    int scannerGreen = 0;
    int scannerBlue = 0;

    Adafruit_NeoPixel *strip;
    int ledCount;
    unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

    void colorWipe(uint32_t color, int wait);
    void scanner(uint32_t color);
    bool isDelaySpent(int interval);
    uint32_t dimColor(uint32_t color);
    uint8_t red(uint32_t color);
    uint8_t green(uint32_t color);
    uint8_t blue(uint32_t color);
};

#endif //DEVICEACTIONS_HPP