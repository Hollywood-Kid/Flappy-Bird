#include "SFML/Graphics.hpp"
#include <random>
#include <iostream>
#include "common.h"

using namespace sf;
using namespace std;

class Pipe
{
private:
    Texture texture_pipe;
    Vector2f pos;
    int gap = 100;  // Промежуток между верхним и нижним столбом

public:
    Sprite bottom_pipe;
    Sprite top_pipe;

    Pipe(const string textureFile) {
        if (!texture_pipe.loadFromFile(textureFile)) {
            cerr << "Failed to load texture: " << textureFile << endl;
            throw runtime_error("Unable to load texture");
        }

        bottom_pipe.setTexture(texture_pipe);
        top_pipe.setTexture(texture_pipe);

        // Отразить верхний столб по вертикали
        top_pipe.setScale(1, -1);

        rand_pos();
    }

    void rand_pos() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(130, 360);

        int y = dist(gen);

        // Установка позиции нижнего столба
        bottom_pipe.setPosition(288, y);

        // Установка позиции верхнего столба
        top_pipe.setPosition(288, y - gap);
    }

    void update(float time) {
        if (isStart) {
            bottom_pipe.move(-0.15f * time, 0);
            top_pipe.move(-0.15f * time, 0);

            pos = bottom_pipe.getPosition();

            if (pos.x < -52) {
                rand_pos();
            }
        }
    }

    Vector2f get_poa_pip() {
        return pos;
    }
};
