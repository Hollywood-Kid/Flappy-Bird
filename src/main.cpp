#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 288;
const int WINDOW_HEIGHT = 512;

class Bird
{
private:
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

        curFrame = 0;
    }

    void update(float time) {
        curFrame += 0.005 * time;

        if(curFrame > 3) {
            curFrame -= 3;
        }

        bird_sprite.setTexture(bird_texture[(int)curFrame]);
    }
};

class GameEnvironment
{
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
        base2_sprite.setPosition(Vector2f(288, WINDOW_HEIGHT - 112));
    }

    void base_update(float time) {
        // Update base animation
        base1_sprite.move(-0.2f * time, 0);
        pos_base = base1_sprite.getPosition();
        if(pos_base.x < -288) base1_sprite.setPosition(0, pos_base.y);

        base2_sprite.move(-0.2f * time, 0);
        pos_base = base2_sprite.getPosition();
        if(pos_base.x < 0) base2_sprite.setPosition(288, pos_base.y);
    }
};

class Menu {
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

int main() {
    vector<string> textureFileBird = {
        "Textures/bluebird-downflap.png",
        "Textures/bluebird-midflap.png",
        "Textures/bluebird-upflap.png"
    };

    vector<string> textureFileGameEnvironment = {
        "Textures/background-day.png",
        "Textures/base.png"
    };

    vector<string> textureFileMenu = {
        "Textures/message.png",
        "Textures/Mobile - Flappy Bird - Version 12 Sprites.png"
    };

    Bird bird(textureFileBird);
    GameEnvironment environment(textureFileGameEnvironment);
    Menu menu(textureFileMenu);

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird", Style::Close);
    window.setFramerateLimit(60);

    bool isMenu = true;

    Clock clock;

    while (window.isOpen())
    {
        Vector2i mousePos = Mouse::getPosition(window);

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == Event::MouseButtonPressed) {
                if(event.mouseButton.button == Mouse::Left) {
                    if(menu.button_play_sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        isMenu = false;
                    }
                }
            }
        }

        environment.base_update(time);
        bird.update(time);

        window.clear();

        window.draw(environment.background_sprite);

        if (isMenu) {
            window.draw(menu.game_title_sprite);
            window.draw(menu.button_play_sprite);

            window.draw(environment.base1_sprite);
            window.draw(environment.base2_sprite);

            window.draw(bird.bird_sprite);
        }
        
        else {
            window.draw(environment.base1_sprite);
            window.draw(environment.base2_sprite);
            window.draw(bird.bird_sprite);
        }
        window.display();
    }

    return 0;
}