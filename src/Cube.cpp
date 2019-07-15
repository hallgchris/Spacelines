//
// Created by christopher on 4/07/19.
//

#include "Cube.h"
#include "Vec3.h"

Cube::Cube() {
    CFastLED::addLeds<PL9823, Cube::kLedPin>(this->leds_, Cube::kNumLeds);
    FastLED.show();
}

void Cube::setLed(Vec3 pos, const CRGB &color) {
    this->leds_[xyz(pos)] = color;
    this->cube_updated = true;
}

void Cube::clear() {
    for (int i = 0; i < Cube::kNumLeds; ++i)
        this->leds_[i] = CRGB::Black;
    this->cube_updated = true;
}

void Cube::fade(uint8_t rate) {
    this->leds_.fadeToBlackBy(rate);
}

void Cube::update() {
    this->updateBrightness();
    if (this->cube_updated)
        FastLED.show();
    this->cube_updated = false;
}

int Cube::xyz(Vec3 pos) {
    int i;
    int x = pos.getX(); int y = pos.getY(); int z = pos.getZ();

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
    auto new_value = map(analogRead(Cube::kDimmerPotPin), 0, 1023, 0, 255);
    // Try to reduce flickering on low brightnesses due to noise on pot input
    if (abs(new_value - this->prev_brightness_) > 1) {
        FastLED.setBrightness(static_cast<uint8_t>(new_value));
        this->prev_brightness_ = new_value;
        this->cube_updated = true;
    }
}
