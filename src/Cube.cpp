//
// Created by christopher on 4/07/19.
//

#include "Cube.h"

Cube::Cube() {
    CFastLED::addLeds<PL9823, Cube::kLedPin>(this->leds_, Cube::kNumLeds);
    FastLED.show();
}

void Cube::setLed(const CRGB& color, int x, int y, int z) {
    this->leds_[xyz(x, y, z)] = color;
}

void Cube::clear() {
    for (int i = 0; i < Cube::kNumLeds; ++i)
        this->leds_[i] = CRGB::Black;
}

void Cube::fade(uint8_t rate) {
    this->leds_.fadeToBlackBy(rate);
}

void Cube::update() {
    Cube::updateBrightness();
    FastLED.show();
}

int Cube::xyz(int x, int y, int z) {
    int i;

    // Check for odd numbered vertical rows to take care of cube's zig-zag wiring
    if (z % 2 == 1)
        i = Cube::kSize * ((y * Cube::kSize) + z) + (Cube::kSize - 1) - x;
    else
        i = Cube::kSize * ((y * Cube::kSize) + z) + x;

    if ((i >= 0) && (i <= Cube::kNumLeds))
        return i;
    return 0;
}

void Cube::updateBrightness() {
    FastLED.setBrightness(static_cast<uint8_t>(map(analogRead(Cube::kDimmerPotPin), 0, 1023, 0, 255)));
}
