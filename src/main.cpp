#include <Arduino.h>
#include "FastLED.h"
#include "ColorCycle.h"
#include "ColorBlend.h"
#include "MultiColorBlend.h"

#define CLK_PIN     GPIO_NUM_16
#define SI_PIN      GPIO_NUM_17
#define LED_TYPE    WS2801
#define COLOR_ORDER RBG
#define NUM_LEDS    4
#define BRIGHTNESS  255

CRGB leds[NUM_LEDS];
MultiColorBlend multiPixel[NUM_LEDS];

bool isBlue = false;
unsigned long turnedBlue = 0;

std::vector<CRGB> availableColors = {
    CRGB(250,205,73),
    CRGB(213,41,15),
    CRGB(55,25,80),
    CRGB(242,130,11),
    CRGB(138,39,58),
    CRGB(255,255,255),
};

void setup()
{
    delay(1000);
    Serial.begin(9600);
    while(!Serial);

    FastLED.addLeds<LED_TYPE, SI_PIN, CLK_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(UncorrectedColor)
        .setDither(BRIGHTNESS < 255);

    FastLED.setBrightness(BRIGHTNESS);

    multiPixel[0] = MultiColorBlend(60, 1000);
    multiPixel[1] = MultiColorBlend(60, 500);
    multiPixel[2] = MultiColorBlend(60, 800);
    multiPixel[3] = MultiColorBlend(60, 1200);
}

void loop()
{
    leds[0] = multiPixel[0].blend(availableColors);
    leds[1] = multiPixel[1].blend(availableColors);
    leds[2] = multiPixel[2].blend(availableColors);
    leds[3] = multiPixel[3].blend(availableColors);

    delay(50);

    FastLED.show();
}