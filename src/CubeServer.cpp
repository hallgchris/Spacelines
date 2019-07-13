//
// Created by christopher on 5/07/19.
//

#include "CubeServer.h"
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "PrivateNetworks.h"

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

    this->server_ = new ESP8266WebServer(80);
    this->server_->on("/", HTTP_GET, std::bind(&CubeServer::handleRoot, this));
    this->server_->on("/move", HTTP_POST, std::bind(&CubeServer::handleMove, this));
    this->server_->onNotFound(std::bind(&CubeServer::handleNotFound, this));
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

void CubeServer::handleRoot() {
    this->server_->send(200, "text/html", "<form action=\"/move\" method=\"POST\">\n"
                                          "    <input type=\"text\" name=\"x\"></br>\n"
                                          "    <input type=\"text\" name=\"y\"></br>\n"
                                          "    <input type=\"submit\" value=\"Move\">\n"
                                          "</form>");
}

void CubeServer::handleNotFound() {
    this->server_->send(200, "text/html", "<p>that's a 404</p>");
}

void CubeServer::handleMove() {
    if (!this->server_->hasArg("x") || !this->server_->hasArg("y")
            || this->server_->arg("x") == nullptr || this->server_->arg("y") == nullptr) {
        this->server_->send(400, "text/plain", "400: Invalid request");
        return;
    }
    int x = strtol(this->server_->arg("x").c_str(), nullptr, 10);
    int y = strtol(this->server_->arg("y").c_str(), nullptr, 10);
    this->board_->makeMove(x, y);
    this->board_->showCube(cube_);
    this->server_->send(204, "text/plain");
}
