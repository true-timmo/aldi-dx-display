#ifndef MultiColorBlend_h_
#define MultiColorBlend_h_

#include <Arduino.h>
#include <vector>
#include "ColorBlend.h"
#include "FastLED.h"

class MultiColorBlend: ColorBlend
{
    private:
        bool invert = false;
        bool isDone = false;
        uint8_t currentElement = 0;

    public:
        MultiColorBlend(uint8_t steps = 5, unsigned int delay = 0): ColorBlend(steps, delay){};

    CRGB blend(const std::vector<CRGB>& rgbSet)
    {
        if (rgbSet.empty()) {
            return CRGB();
        }

        int nextElement = this->invert ? this->currentElement - 1 : this->currentElement + 1;

        if (nextElement < 0 || nextElement >= rgbSet.size()) {
            this->isDone = true;
            this->invert = !this->invert;

            return rgbSet[this->currentElement];
        }

        if (ColorBlend::isDone()) {
            this->currentElement = nextElement;
            ColorBlend::reset();

            return rgbSet[this->currentElement];
        }

        return ColorBlend::blend(rgbSet[this->currentElement], rgbSet[nextElement]);
    };

};

#endif // MultiColorBlend_h_