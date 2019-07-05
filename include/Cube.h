//
// Created by christopher on 4/07/19.
//

#pragma once

#include <FastLED.h>

class Cube {
public:
    static const int kSize = 5;

    Cube();

    void setLed(const CRGB& color, int x, int y, int z);
    void clear();
    void fade(uint8_t rate);

    static void update();

private:
    static const int kNumLeds = kSize * kSize * kSize;

    static const int kLedPin = 2;
    static const int kDimmerPotPin = A0;

    static void updateBrightness();

    static int xyz(int x, int y, int z);

    CRGBArray<kNumLeds> leds_;
};
