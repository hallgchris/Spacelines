//
// Created by christopher on 5/07/19.
//

#include "CubeServer.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include "PrivateNetworks.h"
#include "Board3x3.h"

CubeServer::CubeServer(Board *board, Cube *cube) {
    for (Network network : kNetworks)
        wiFiMulti_.addAP(network.ssid, network.passphrase);
    Serial.print("Connecting to WiFi...");
    while (wiFiMulti_.run() != WL_CONNECTED) {
        delay(250);
        Serial.print('.');
    }
    Serial.print("\n\nConnected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("cube"))
        Serial.println("mDNS responder started");
    else
        Serial.println("Error setting up mDNS responder!");

    SPIFFS.begin();

    Serial.println("SPIFFS ready");

    this->server_ = new ESP8266WebServer(80);
    this->server_->on("/move", HTTP_POST, std::bind(&CubeServer::handleMove, this));
    this->server_->on("/getsize", HTTP_GET, std::bind(&CubeServer::handleGetSize, this));
    this->server_->on("/reset", HTTP_GET, std::bind(&CubeServer::handleReset, this));
    this->server_->onNotFound(std::bind(&CubeServer::handleLoadPage, this));
    this->server_->begin();

    Serial.println("HTTP server started");

    this->board_ = board;
    this->cube_ = cube;
}

void CubeServer::updateCube() {
    MDNS.update();
    this->server_->handleClient();
    this->cube_->update();
}

void CubeServer::handleLoadPage() {
    if (!handleFileRead(this->server_->uri()))
        this->server_->send(404, "text/html", "<p>that's a 404</p>");
}

void CubeServer::handleMove() {
    if (!this->server_->hasArg("x") || this->server_->arg("x") == nullptr ||
        !this->server_->hasArg("y") || this->server_->arg("y") == nullptr ||
        !this->server_->hasArg("z") || this->server_->arg("z") == nullptr) {
        this->server_->send(400, "text/plain", "400: Invalid request");
        return;
    }
    int x = strtol(this->server_->arg("x").c_str(), nullptr, 10);
    int y = strtol(this->server_->arg("y").c_str(), nullptr, 10);
    int z = strtol(this->server_->arg("z").c_str(), nullptr, 10);
    const Vec3 &move = Vec3(x, y, z);
    Serial.println("Move from " + this->server_->client().remoteIP().toString() + ": " + move);
    this->board_->makeMove(move);
    this->board_->showCube(cube_);
    this->server_->send(204, "text/plain");
}

void CubeServer::handleGetSize() {
    String json =
            R"({"size":")" + String(this->board_->getDimensions().side_length) +
            R"(","dimensions":")" + String(this->board_->getDimensions().dimensions) + "\"}";
    this->server_->send(200, "application/json", json);
}

void CubeServer::handleReset() {
    this->board_->reset();
    this->board_->showCube(this->cube_);
    this->server_->send(204, "text/plain");
}

String CubeServer::getContentType(const String& filename) {
    if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if(filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".txt")) return "text/plain";
    return "text/plain";
}

bool CubeServer::handleFileRead(String path) {
    Serial.println("handleFileRead: " + path);

    // Accessing a folder accesses the index page
    if (path.endsWith("/"))
        path += "index.html";

    // Send the file if it exists
    if (SPIFFS.exists(path)) {
        String contentType = getContentType(path);
        File file = SPIFFS.open(path, "r");
        this->server_->streamFile(file, contentType);
        file.close();
        Serial.println("\tSent file: " + path);
        return true;
    }

    // File was not found
    Serial.println("\tFile Not found: " + path);
    return false;
}
