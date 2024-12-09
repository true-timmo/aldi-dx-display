#include <Arduino.h>
#include "FastLED.h"

#define CLK_PIN     GPIO_NUM_16
#define SI_PIN      GPIO_NUM_17
#define LED_TYPE    WS2801
#define COLOR_ORDER RBG
#define NUM_LEDS    4
#define BRIGHTNESS  255

CRGB red = CRGB(240, 42, 0);
CRGB clinic = CRGB(212, 81, 4);
CRGB orange = CRGB(240, 212, 0);
CRGB yellow = CRGB(255, 255, 0);
CRGB blue = CRGB(80, 0 ,250);

CRGB leds[NUM_LEDS];

void setup()
{
    delay(1000);
    Serial.begin(9600);
    while(!Serial);

    FastLED.addLeds<LED_TYPE, SI_PIN, CLK_PIN, COLOR_ORDER>(leds, NUM_LEDS)
        .setCorrection(TypicalLEDStrip)
        .setDither(BRIGHTNESS < 255);

    FastLED.setBrightness(BRIGHTNESS);

    leds[0] = red;
    leds[1] = blue;
    leds[2] = clinic;
    leds[3] = yellow;
}

void loop()
{
    FastLED.show();
}