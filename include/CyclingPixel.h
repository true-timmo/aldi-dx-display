#ifndef CyclingPixel_h_
#define CyclingPixel_h_

#include <Arduino.h>
#include "FastLED.h"

class CyclingPixel final
{
    private:
        uint8_t hue = 0;
        uint8_t hueMin = 0;
        uint8_t hueMax = 64;
        bool increase = true;
        CRGB pixel = CRGB();

    public:
        CyclingPixel(uint8_t hueMin = 0, uint8_t hueMax = 64)
        {
            this->hueMin = hueMin;
            this->hueMax = hueMax;
        };

        uint8_t getHue()
        {
            if (this->hue == this->hueMin) {
                this->increase  = true;
            }

            if (this->hue == this->hueMax) {
                this->increase = false;
            }

            return this->increase ? this->hue++ : this->hue--;
        };

        CRGB getPixel()
        {
            return this->pixel.setHue(this->getHue());
        };
};

#endif // CyclingPixel_h_