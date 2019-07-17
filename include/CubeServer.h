//
// Created by christopher on 5/07/19.
//

#pragma once

#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h>
#include "Board.h"

class CubeServer {
public:
    CubeServer(Board *board, Cube *cube);

    void updateCube();

private:
    void handleLoadPage();
    void handleMove();
    void handleGetSize();
    void handleReset();

    static String getContentType(const String& filename);
    bool handleFileRead(String path);

    ESP8266WiFiMulti wiFiMulti_;
    ESP8266WebServer *server_;
    Board *board_;
    Cube *cube_;
};
