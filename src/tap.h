#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Tap
{
private:
    Texture tap_texture;
    Texture get_ready_texture;

    Sprite tap_sprite;
    Sprite get_ready_sprite;
    
public:
    Tap(const string textureFile) {
        tap_texture.loadFromFile(textureFile);
        tap_sprite.setTexture(tap_texture);
        tap_sprite.setTextureRect(IntRect(0, 160, 184, 107));
        tap_sprite.setPosition(288 / 2 - 184 / 2, 250);

        get_ready_texture.loadFromFile(textureFile);
        get_ready_sprite.setTexture(get_ready_texture);
        get_ready_sprite.setTextureRect(IntRect(0, 100, 184, 55));
        get_ready_sprite.setPosition(288 / 2 - 184 / 2 + 30, 140);
    }

    void tap_update() {

    }
};