//
// Created by christopher on 3/07/19.
//

#include <Arduino.h>
#include <FastLED.h>
#include <Cube.h>
#include <Board.h>

const int kUpdateInterval = 40; // ms
Cube *cube;
Board board(3);

void setup() {
    cube = new Cube();
    cube->clear();

    Serial.begin(9600);

    board.makeMove(0, 0);
    board.makeMove(2, 2);
    board.makeMove(0, 1);
    board.makeMove(0, 2);
    board.makeMove(1, 2);
    board.makeMove(2, 0);
    board.makeMove(1, 1);
    board.makeMove(2, 1);

    board.showCube(cube);
    Cube::update();
}

void demo(Cube cube) {
    static uint8_t hue;
    for (uint8_t z = 0; z < Cube::kSize; z++)
        for (uint8_t x = 0; x < Cube::kSize; x++)
            for (uint8_t y = 0; y < Cube::kSize; y++)
            {
                cube.fade(20);
                cube.setLed(CHSV(hue++, 255, 255), x, y, z);
                Cube::update();
                delay(kUpdateInterval);
            }
}

void loop() {
//    demo(cube);
    delay(kUpdateInterval);
    Cube::update();
}


