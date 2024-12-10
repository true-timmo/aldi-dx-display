#include <Arduino.h>
#include "FastLED.h"

#define CLK_PIN     GPIO_NUM_16
#define SI_PIN      GPIO_NUM_17
#define LED_TYPE    WS2801
#define COLOR_ORDER RBG
#define NUM_LEDS    4
#define BRIGHTNESS  255

CRGB leds[NUM_LEDS];
uint8_t currentHue[NUM_LEDS];
bool increaseHue[NUM_LEDS];

void setup()
{
    delay(1000);
    Serial.begin(9600);
    while(!Serial);

    FastLED.addLeds<LED_TYPE, SI_PIN, CLK_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip)
        .setDither(BRIGHTNESS < 255);

    FastLED.setBrightness(BRIGHTNESS);

    leds[0] = CRGB(255,0,0);
    leds[1] = CRGB(255,0,0);
    leds[2] = CRGB(255,0,0);
    leds[3] = CRGB(255,0,0);

    currentHue[0] = 6;
    currentHue[1] = 12;
    currentHue[2] = 24;
    currentHue[3] = 48;

    increaseHue[0] = true;
    increaseHue[1] = false;
    increaseHue[2] = true;
    increaseHue[3] = false;
}

uint8_t cycleHue(uint8_t index)
{
    if (currentHue[index] == 0 || currentHue[index] == 64) {
        increaseHue[index] = !increaseHue[index];
    }

    return increaseHue[index] ? currentHue[index]++ : currentHue[index]--;
}

void loop()
{
    leds[0].setHue(cycleHue(0));
    leds[1].setHue(cycleHue(1));
    leds[2].setHue(cycleHue(2));
    leds[3].setHue(cycleHue(3));

    delay(200);

    FastLED.show();
}