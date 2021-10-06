#include "DeviceActions.hpp"

DeviceActions::DeviceActions()
{
    this->strip = new Adafruit_NeoPixel(LED_COUNT, GPIO_LED, NEO_GRB + NEO_KHZ800);
    this->ledCount = LED_COUNT;
}

void DeviceActions::doHotEmotional(int *currentEffect, int wait)
{
    *currentEffect = 1;
    if (pixelHueHot >= maxHueHot)
    {
        signHot = -1;
    }
    if (pixelHueHot <= startHueHot)
    {
        signHot = 1;
    }
    colorWipe(strip->gamma32(strip->ColorHSV(pixelHueHot)), wait);
    pixelHueHot = pixelHueHot + signHot * (maxHueHot - startHueHot) / 32;
}

void DeviceActions::doColdEmotional(int *currentEffect, int wait)
{
    *currentEffect = 2;
    if (pixelHueCold >= maxHueCold)
    {
        signCold = -1;
    }
    if (pixelHueCold <= startHueCold)
    {
        signCold = 1;
    }
    colorWipe(strip->gamma32(strip->ColorHSV(pixelHueCold)), wait);
    pixelHueCold = pixelHueCold + signCold * (maxHueCold - startHueCold) / 32;
}

void DeviceActions::doDawn(int *currentEffect)
{
    *currentEffect = 3;
    if (!isDelaySpent(delayTimeDawn) || stopDawn)
    {
        return;
    }
    currentRampStep = floor(map(iDawn, 0, durationDawn, 0, 24));
    if (iDawn == 0 || currentRampStep != lastRampStep)
    {
        colorWipe(strip->Color(redRamp[currentRampStep] / 4, greenRamp[currentRampStep] / 4, blueRamp[currentRampStep] / 4), delayTimeDawn);
        lastRampStep = currentRampStep;
    }
    iDawn = iDawn + delayTimeDawn;
    if (iDawn >= durationDawn)
    {
        iDawn = 0;
        stopDawn = true;
    }
}

void DeviceActions::doScanEffect(int *currentEffect)
{
    *currentEffect = 4;
    this->totalSteps = (this->ledCount - 1) * 2;

    if (!isDelaySpent(delayTimeScanner))
    {
        return;
    }
    scanner(strip->Color(scannerRed, scannerGreen, scannerBlue));
}

void DeviceActions::scanner(uint32_t color)
{
    for (int i = 0; i < this->ledCount; i++)
    {
        if (i == index) // first half of the scan
        {
            Serial.print(i);
            strip->setPixelColor(i, color);
        }
        else if (i == this->totalSteps - index) // The return trip.
        {
            Serial.print(i);
            strip->setPixelColor(i, color);
        }
        else // fade to black
        {
            strip->setPixelColor(i, dimColor(strip->getPixelColor(i)));
        }
    }
    strip->show();
    index++;
    if (index >= this->ledCount)
    {
        index = 0;
    }
}

void DeviceActions::doShutDown(int *currentEffect)
{
    *currentEffect = 0;
    colorWipe(this->strip->Color(0, 0, 0), 50);
}

void DeviceActions::colorWipe(uint32_t color, int wait)
{
    for (int i = 0; i < this->strip->numPixels(); i++)
    {                                         // For each pixel in strip...
        this->strip->setPixelColor(i, color); //  Set pixel's color (in RAM)
        this->strip->show();                  //  Update strip to match
        delay(wait);                          //  Pause for a moment
    }
}

bool DeviceActions::isDelaySpent(int interval)
{
    currentMillis = millis();
    if ((currentMillis - previousMillis) < interval)
    {
        return false;
    }
    previousMillis = currentMillis;
    return true;
}

uint32_t DeviceActions::dimColor(uint32_t color)
{
    uint32_t dimColor = strip->Color(red(color) >> 1, green(color) >> 1, blue(color) >> 1);
    return dimColor;
}

uint8_t DeviceActions::red(uint32_t color)
{
    return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t DeviceActions::green(uint32_t color)
{
    return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t DeviceActions::blue(uint32_t color)
{
    return color & 0xFF;
}