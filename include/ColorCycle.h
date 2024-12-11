#ifndef ColorCycle_h_
#define ColorCycle_h_

#include <Arduino.h>
#include "FastLED.h"

class ColorCycle final
{
    private:
        uint8_t hue = 0;
        uint8_t minHue = 0;
        uint8_t maxHue = 64;
        bool increase = true;
        CRGB pixel = CRGB();

        uint8_t cycleHue()
        {
            if (this->hue == this->minHue) {
                this->increase  = true;
            }

            if (this->hue == this->maxHue) {
                this->increase = false;
            }

            return this->increase ? this->hue++ : this->hue--;
        };

    public:
        ColorCycle(uint8_t minHue = 0, uint8_t maxHue = 64)
        {
            this->minHue = minHue;
            this->maxHue = maxHue;
        };

        CRGB cycle()
        {
            if (random(0, 9) == 5) {
                this->cycleHue();
            }

            return this->pixel.setHue(this->cycleHue());
        };
};

#endif // ColorCycle_h_