//
// Created by christopher on 4/07/19.
//

#pragma once

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include "Vec3.h"

class Cube {
public:
    static const int kSize = 5;

    Cube();

    void setLed(Vec3 pos, const CRGB &color);
    void clear();
    void fade(uint8_t rate);

    void update();

private:
    static const int kNumLeds = kSize * kSize * kSize;

    static const int kLedPin = 2;
    static const int kDimmerPotPin = A0;

    static int xyz(Vec3 pos);

    void updateBrightness();

    CRGBArray<kNumLeds> leds_;
    int prev_brightness_ = 0;
    bool cube_updated = false;
};
