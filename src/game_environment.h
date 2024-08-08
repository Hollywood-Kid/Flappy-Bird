#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class GameEnvironment
{
private:
    const int WINDOW_WIDTH = 288;
    const int WINDOW_HEIGHT = 512;
public:
    Texture background_texture;
    Texture base1_texture;
    Texture base2_texture;

    Sprite background_sprite;
    Sprite base1_sprite;
    Sprite base2_sprite;

    Vector2f pos_base;

    GameEnvironment(const vector<string>& textureFile) {
        background_texture.loadFromFile(textureFile[0]);
        base1_texture.loadFromFile(textureFile[1]);
        base2_texture.loadFromFile(textureFile[1]);

        background_sprite.setTexture(background_texture);
        base1_sprite.setTexture(base1_texture);
        base2_sprite.setTexture(base2_texture);

        base1_sprite.setPosition(0, WINDOW_HEIGHT - 112);
        base2_sprite.setPosition(288, WINDOW_HEIGHT - 112);
    }

    void base_update(float time) {
        base1_sprite.move(-0.2f * time, 0);
        pos_base = base1_sprite.getPosition();
        if(pos_base.x < -288) base1_sprite.setPosition(0, pos_base.y);

        base2_sprite.move(-0.2f * time, 0);
        pos_base = base2_sprite.getPosition();
        if(pos_base.x < 0) base2_sprite.setPosition(288, pos_base.y);
    }
};