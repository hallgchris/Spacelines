//
// Created by christopher on 4/07/19.
//

#pragma once

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

class Cube {
public:
    static const int kSize = 5;

    Cube();

    void setLed(const CRGB& color, int x, int y, int z);
    void clear();
    void fade(uint8_t rate);

    void update();

private:
    static const int kNumLeds = kSize * kSize * kSize;

    static const int kLedPin = 2;
    static const int kDimmerPotPin = A0;

    static int xyz(int x, int y, int z);

    void updateBrightness();

    CRGBArray<kNumLeds> leds_;
    int prev_brightness_ = 0;
    bool cube_updated = false;
};
