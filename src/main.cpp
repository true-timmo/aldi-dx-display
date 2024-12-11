#include <Arduino.h>
#include "FastLED.h"
#include "ColorCycle.h"
#include "ColorBlend.h"

#define CLK_PIN     GPIO_NUM_16
#define SI_PIN      GPIO_NUM_17
#define LED_TYPE    WS2801
#define COLOR_ORDER RBG
#define NUM_LEDS    4
#define BRIGHTNESS  255

CRGB leds[NUM_LEDS];
ColorCycle cyclingPixels[NUM_LEDS];
ColorBlend blendingPixel = ColorBlend(60, 5000);

bool isBlue = false;
unsigned long turnedBlue = 0;

void setup()
{
    delay(1000);
    Serial.begin(9600);
    while(!Serial);

    FastLED.addLeds<LED_TYPE, SI_PIN, CLK_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip)
        .setDither(BRIGHTNESS < 255);

    FastLED.setBrightness(BRIGHTNESS);

    cyclingPixels[0] = ColorCycle(0, 40);
    cyclingPixels[1] = ColorCycle(0, 40);
    leds[3] = CRGB(CRGB::WhiteSmoke);
    leds[3].maximizeBrightness();

}

void loop()
{
    leds[0] = cyclingPixels[0].cycle();
    leds[1] = cyclingPixels[1].cycle();
    leds[2] = blendingPixel.blend(CRGB(16,18,158), CRGB(255, 255, 255));

    if (blendingPixel.isDone()) {
        blendingPixel.reverse();
    }

    delay(50);

    FastLED.show();
}