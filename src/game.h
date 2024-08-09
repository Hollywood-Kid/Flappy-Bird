// game.h
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "bird.h"
#include "menu.h"
#include "game_environment.h"
#include "tap.h"
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
    Tap tap;

public:
    Game() : bird(textureFileBird), environment(textureFileGameEnvironment), menu(textureFileMenu), tap(textureFileTap) {}

    void drawMenu(RenderWindow &window) {
        window.draw(environment.background_sprite);
        window.draw(menu.game_title_sprite);
        window.draw(menu.button_play_sprite);
        window.draw(environment.base1_sprite);
        window.draw(environment.base2_sprite);
        window.draw(bird.bird_sprite);
    }

    void drawTap(RenderWindow &window) {
        window.draw(environment.background_sprite);
        window.draw(environment.base1_sprite);
        window.draw(environment.base2_sprite);
        window.draw(bird.bird_sprite);
        if(tap.isVisible) {
            window.draw(tap.tap_sprite);
        }
        window.draw(tap.get_ready_sprite);
    }

    void run() {
        RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird", Style::Close);
        window.setFramerateLimit(60);

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
                        if (isTap) {
                            bird.jump();  // Прыжок птички
                            isTap = false;
                            isStart = true;
                        } 
                        
                        else if (isMenu) {
                            if(menu.button_play_sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                isMenu = false;
                                isTap = true;

                                bird.setPosition(30, 150);
                            }
                        }

                        else if (isStart){
                            bird.jump();
                        }
                    }
                }
            }

            environment.base_update(time);
            bird.update(time);
            tap.tap_update();

            window.clear();

            if (isMenu) {
                drawMenu(window);
            }

            if (isTap) {
                drawTap(window);
            }

            if (isStart) {
                // Отрисовка игры в процессе
                window.draw(environment.background_sprite);
                window.draw(environment.base1_sprite);
                window.draw(environment.base2_sprite);
                window.draw(bird.bird_sprite);
                // Здесь можно добавить отрисовку труб и других объектов
            }

            window.display();
        }
    }
};

#endif // GAME_H
