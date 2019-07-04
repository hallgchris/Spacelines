//
// Created by christopher on 3/07/19.
//

#include <Arduino.h>
#include <FastLED.h>

const uint8_t kCubeSize = 5;

#define NUM_LEDS kCubeSize * kCubeSize * kCubeSize
#define DATA_PIN 2
#define DELAY_INTERVAL 40

#define POT_PIN A0

CRGBArray<NUM_LEDS> leds;

void setup() {
    FastLED.addLeds<PL9823, DATA_PIN>(leds, NUM_LEDS);
    FastLED.show();
}

void setBrightness()
{
    FastLED.setBrightness(static_cast<uint8_t>(map(analogRead(POT_PIN), 0, 1023, 0, 255)));
}

int xyz(uint8_t x, uint8_t y, uint8_t z)
{
    int i;

    // Check for odd numbered vertical rows to take care of cube's zig-zag wiring
    if (z & 1u) i = kCubeSize * ((y * kCubeSize) + z) + (kCubeSize - 1) - x;
    else i = kCubeSize * ((y * kCubeSize) + z) + x;

    if ((i >= 0) && (i <= NUM_LEDS)) return i;
    return 0;
}

void loop() {
    static uint8_t hue;
    for (uint8_t z = 0; z < kCubeSize; z++)
        for (uint8_t x = 0; x < kCubeSize; x++)
            for (uint8_t y = 0; y < kCubeSize; y++)
            {
                leds.fadeToBlackBy(20);
                leds[xyz(x, y, z)] = CHSV(hue++,255,255);
                setBrightness();
                FastLED.show();
                delay(DELAY_INTERVAL);
            }

}


