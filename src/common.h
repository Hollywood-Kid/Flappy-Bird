// common.h
#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>

const std::vector<std::string> textureFileBird = {
    "Textures/bluebird-downflap.png",
    "Textures/bluebird-midflap.png",
    "Textures/bluebird-upflap.png"
};

const std::vector<std::string> textureFileGameEnvironment = {
    "Textures/background-day.png",
    "Textures/base.png"
};

const std::vector<std::string> textureFileMenu = {
    "Textures/message.png",
    "Textures/Mobile - Flappy Bird - Version 12 Sprites.png"
};

const std::string textureFileTap = {
    "Textures/message.png"
};

const std::string textureFilePipe = {
    "Textures/pipe-green.png"
};

const std::vector<std::string> textureFileScore = {
    "Textures/0.png",
    "Textures/1.png",
    "Textures/2.png",
    "Textures/3.png",
    "Textures/4.png",
    "Textures/5.png",
    "Textures/6.png",
    "Textures/7.png",
    "Textures/8.png",
    "Textures/9.png"
};

bool isMenu = true;
bool isTap = false;
bool isStart = false;

const int BLACK_SCREEN_DURATION = 2000; // 2 seconds

#endif // COMMON_H
