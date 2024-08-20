#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class GameOver
{
public:
    Texture game_over_title_texrure;
    Texture ok_texture;

    Sprite game_over_title;
    Sprite ok;

    GameOver() {
        game_over_title_texrure.loadFromFile("Textures/Mobile - Flappy Bird - Version 12 Sprites.png");

        ok_texture.loadFromFile("Textures/Mobile - Flappy Bird - Version 12 Sprites.png");

        game_over_title.setTexture(game_over_title_texrure);
        game_over_title.setTextureRect(IntRect(390, 58, 103, 25));
        game_over_title.setScale(2.0f, 2.0f);
        game_over_title.setPosition(288 / 2 - 103, 20);

        ok.setTexture(ok_texture);
        ok.setTextureRect(IntRect(460, 42, 45, 13));
        ok.setScale(3.0f, 3.0f);
        ok.setPosition(288 / 2 - 67, 330);
    }
};