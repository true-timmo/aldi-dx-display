#ifndef ColorBlend_h_
#define ColorBlend_h_

#include <Arduino.h>
#include "FastLED.h"

class ColorBlend
{
    private:
        unsigned int delay = 0;

        uint8_t steps = 5;
        uint8_t currentStep = 0;
        uint8_t colors[3];

        bool invert = false;
        unsigned long finishedBlendAt = 0;

        uint8_t blendColor(uint8_t fromColor, uint8_t toColor)
        {
            if (this->currentStep == 0) {
                return fromColor;
            }

            if (fromColor == toColor || this->isDone()) {
                return toColor;
            }

            return map(this->currentStep, 0, this->steps, fromColor, toColor);
        };

    public:
        ColorBlend(uint8_t steps = 5, unsigned int delay = 0)
        {
            this->steps = steps;
            this->delay = delay;
        };

        bool isDone()
        {
            return (this->finishedBlendAt != 0 && (this->finishedBlendAt + this->delay) < millis());
        };

        void reset()
        {
            this->finishedBlendAt = 0;
            this->currentStep = 0;
        };

        void reverse()
        {
            this->invert = !this->invert;
            this->reset();
        };

        CRGB blend(CRGB fromRGB, CRGB toRGB)
        {
            if (this->invert == true) {
                std::swap(fromRGB, toRGB);
            }

            if (this->currentStep == this->steps) {
                if (this->finishedBlendAt == 0) {
                    this->finishedBlendAt = millis();
                }

                return toRGB;
            }

            this->colors[0] = this->blendColor(fromRGB.red, toRGB.red);
            this->colors[1] = this->blendColor(fromRGB.green, toRGB.green);
            this->colors[2] = this->blendColor(fromRGB.blue, toRGB.blue);
            this->currentStep++;

            return CRGB(this->colors[0], this->colors[1], this->colors[2]);
        };
};

#endif // ColorBlend_h_