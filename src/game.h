// game.h
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "bird.h"
#include "menu.h"
#include "game_environment.h"
#include "common.h"

using namespace sf;

class Game
{
private:
    const int WINDOW_WIDTH = 288;
    const int WINDOW_HEIGHT = 512;

    Bird bird;
    GameEnvironment environment;
    Menu menu;

public:
    Game() : bird(textureFileBird), environment(textureFileGameEnvironment), menu(textureFileMenu) {}

    void drawMenu(RenderWindow &window) {
        window.draw(environment.background_sprite);
        window.draw(menu.game_title_sprite);
        window.draw(menu.button_play_sprite);
        window.draw(environment.base1_sprite);
        window.draw(environment.base2_sprite);
        window.draw(bird.bird_sprite);
    }

    void run() {
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

            if (isMenu) {
                drawMenu(window);
            }
            
            else {
                window.draw(environment.background_sprite);
                window.draw(environment.base1_sprite);
                window.draw(environment.base2_sprite);
                window.draw(bird.bird_sprite);
            }

            window.display();
        }
    }
};

#endif // GAME_H
