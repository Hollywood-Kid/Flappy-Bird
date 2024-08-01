#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Menu {
private:
    const int WINDOW_WIDTH = 288;
    const int WINDOW_HEIGHT = 512;

public:
    Texture game_title_texture;
    Texture button_play_texture;

    Sprite game_title_sprite;
    Sprite button_play_sprite;

    Menu(const vector<string>& textureFile) {
        game_title_texture.loadFromFile(textureFile[0]);
        button_play_texture.loadFromFile(textureFile[1]);

        game_title_sprite.setTexture(game_title_texture);
        game_title_sprite.setTextureRect(IntRect(0, 0, 184, 50));
        game_title_sprite.setPosition(WINDOW_WIDTH / 2 - 184 / 2, 20);

        button_play_sprite.setTexture(button_play_texture);
        button_play_sprite.setTextureRect(IntRect(352, 116, 56, 34));
        button_play_sprite.setPosition(WINDOW_WIDTH / 2 - 56, 270);
        button_play_sprite.setScale(2.0f, 2.0f);
    }
};