//
// Created by christopher on 3/07/19.
//

#include <Arduino.h>
#include <FastLED.h>
#include <Cube.h>
#include <CubeServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <Board3x3x3.h>
#include <Board5x5x5.h>
#include "Board3x3.h"

const int kUpdateInterval = 20; // ms

CubeServer *cubeServer;

void setupOTA() {
    ArduinoOTA.setHostname("cube");
    ArduinoOTA.setPassword("esp8266");

    ArduinoOTA.onStart([]() {
        Serial.println("Starting OTA update");
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd OTA update");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\n", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    ArduinoOTA.begin();
    Serial.println("OTA ready");
}

void setup() {
    Serial.begin(9600);

    // Setup and show board on cube
    auto cube = new Cube();
    auto board = new Board5x5x5();
    board->showCube(cube);
    cube->update();

    // Networking
    cubeServer = new CubeServer(board, cube);
    setupOTA();

    Serial.println();
}

void demo(Cube cube) {
    static uint8_t hue;
    for (uint8_t z = 0; z < Cube::kSize; z++)
        for (uint8_t x = 0; x < Cube::kSize; x++)
            for (uint8_t y = 0; y < Cube::kSize; y++)
            {
                cube.fade(20);
                cube.setLed(Vec3(x, y, z), CHSV(hue++, 255, 255));
                cube.update();
                delay(kUpdateInterval);
            }
}

void loop() {
//    demo(cube);
    cubeServer->updateCube();
    ArduinoOTA.handle();
    delay(kUpdateInterval);
}


