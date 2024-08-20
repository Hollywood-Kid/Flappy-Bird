#pragma once

#include <SFML/Graphics.hpp>
#include "GameStateManager.h"

using namespace std;
using namespace sf;

class Bird
{
private:
    Texture bird_texture[3];

    float curFrame;
    float velocity;
    const float gravity = 0.25f;
    const float jumpStrength = -5.0f;

public:
    Sprite bird_sprite;

    Bird(const vector<string>& textureFile) {
        bird_texture[0].loadFromFile(textureFile[0]);
        bird_texture[1].loadFromFile(textureFile[1]);
        bird_texture[2].loadFromFile(textureFile[2]);

        bird_sprite.setTexture(bird_texture[0]);

        bird_sprite.setPosition(288 / 2 - 34 / 2, 150);

        curFrame = 0;
        velocity = 0;
    }

    void update(float time, GameStateManager &stateManager) {
        curFrame += 0.005 * time;

        if(curFrame > 3) {
            curFrame -= 3;
        }

        bird_sprite.setTexture(bird_texture[(int)curFrame]);

        
        if(stateManager.isStart()) {
            velocity += gravity;  // Применение гравитации
            bird_sprite.move(0, velocity);  // Перемещение птички по оси Y
        }
    }

    void jump() {
        velocity = jumpStrength;  // Применение прыжка
    }

    void setPosition(int x, int y) {
        bird_sprite.setPosition(x, y);
        velocity = 0;  // Сброс скорости при изменении позиции
    }

    void draw(RenderWindow &window) {
        window.draw(bird_sprite);
    }
};
