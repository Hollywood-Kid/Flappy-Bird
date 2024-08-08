#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Bird
{
private:
    const int WINDOW_WIDTH = 288;
    const int WINDOW_HEIGHT = 512;

    int x;
    int y;
public:
    Texture bird_texture[3];
    Sprite bird_sprite;

    float curFrame;

    Bird(const vector<string>& textureFile) {
        bird_texture[0].loadFromFile(textureFile[0]);
        bird_texture[1].loadFromFile(textureFile[1]);
        bird_texture[2].loadFromFile(textureFile[2]);

        bird_sprite.setTexture(bird_texture[0]);

        bird_sprite.setPosition(WINDOW_WIDTH / 2 - 34 / 2, 150);

        curFrame = 0;
    }

    void update(float time) {
        curFrame += 0.005 * time;

        if(curFrame > 3) {
            curFrame -= 3;
        }

        bird_sprite.setTexture(bird_texture[(int)curFrame]);
    }

    void setPosition(int x, int y) {
        bird_sprite.setPosition(x, y);
    }
};