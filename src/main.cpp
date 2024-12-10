#include <Arduino.h>
#include "FastLED.h"
#include "CyclingPixel.h"

#define CLK_PIN     GPIO_NUM_16
#define SI_PIN      GPIO_NUM_17
#define LED_TYPE    WS2801
#define COLOR_ORDER RBG
#define NUM_LEDS    4
#define BRIGHTNESS  255

CRGB leds[NUM_LEDS];
CyclingPixel cyclingPixels[NUM_LEDS];

void setup()
{
    delay(1000);
    Serial.begin(9600);
    while(!Serial);

    FastLED.addLeds<LED_TYPE, SI_PIN, CLK_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip)
        .setDither(BRIGHTNESS < 255);

    FastLED.setBrightness(BRIGHTNESS);

    cyclingPixels[0] = CyclingPixel(0, 30);
    cyclingPixels[1] = CyclingPixel(160,175);
    cyclingPixels[2] = CyclingPixel(30, 55);
    cyclingPixels[3] = CyclingPixel(31, 60);
}

void loop()
{
    leds[0] = cyclingPixels[0].getPixel();
    leds[1] = cyclingPixels[1].getPixel();
    leds[2] = cyclingPixels[2].getPixel();
    leds[3] = cyclingPixels[3].getPixel();

    delay(100);

    FastLED.show();
}