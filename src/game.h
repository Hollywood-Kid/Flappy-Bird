#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "bird.h"
#include "menu.h"
#include "game_over.h"
#include "game_environment.h"
#include "tap.h"
#include "pipe.h"
#include "score.h"
#include "common.h"
#include "sound.h"
#include "GameStateManager.h"
#include "InputHandler.h"

using namespace sf;

class Game
{
private:
    const int WINDOW_WIDTH = 288;
    const int WINDOW_HEIGHT = 512;

    Bird bird;
    GameEnvironment environment;
    Menu menu;
    Pipe pipe;
    Tap tap;
    Score score;
    setSound sound;
    GameOver game_over;

    FloatRect birdBounds;
    FloatRect topPipeBounds;
    FloatRect bottomPipeBounds;

    GameStateManager stateManager;  // Менеджер состояний игры

    bool pointAwarded;
public:

    // Конструктор класса Game
    Game() : bird(textureFileBird), 
             environment(textureFileGameEnvironment), 
             menu(textureFileMenu), 
             tap(textureFileTap), 
             pipe(textureFilePipe), 
             score(textureFileScore)
    {
        pointAwarded = false;
    }

    // Метод для отрисовки меню
    void drawMenu(RenderWindow &window) {
        window.draw(environment.background_sprite);
        window.draw(menu.game_title_sprite);
        window.draw(menu.button_play_sprite);
        window.draw(environment.base1_sprite);
        window.draw(environment.base2_sprite);
        window.draw(bird.bird_sprite);
    }

    // Метод для отрисовки экрана "Tap to Start"
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

    // Метод для отрисовки основного экрана игры
    void drawStart(RenderWindow &window) {
        window.draw(environment.background_sprite); // Отрисовка фона
        window.draw(pipe.bottom_pipe);
        window.draw(pipe.top_pipe); // Отрисовка труб
        window.draw(environment.base1_sprite);
        window.draw(environment.base2_sprite);
        window.draw(bird.bird_sprite); // Отрисовка птички
        score.draw(window); // Отрисовка счета
    }

    // Главный игровой цикл
    void run() {
        RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird", Style::Close);
        window.setFramerateLimit(60);

        Clock clock;
        bool gameOver = false;

        while (window.isOpen()) {
            Event event;

            while (window.pollEvent(event)) {
                InputHandler::handleInput(event, window, stateManager, bird, menu, game_over, pipe, score, sound);
            }

            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();

            time = time / 800;

            if (!stateManager.isGameOver()) {
                environment.base_update(time);
                bird.update(time, stateManager);
                tap.tap_update();
                pipe.update(time, stateManager);

                if (pipe.bottom_pipe.getPosition().x < bird.bird_sprite.getPosition().x - 52 && !pointAwarded) {
                    score.addScore(1);
                    sound.bonus.play();
                    pointAwarded = true;
                }

                if(pipe.bottom_pipe.getPosition().x == WINDOW_WIDTH) {
                    pointAwarded = false;
                }

                birdBounds = bird.bird_sprite.getGlobalBounds();
                topPipeBounds = pipe.top_pipe.getGlobalBounds();
                bottomPipeBounds = pipe.bottom_pipe.getGlobalBounds();

                if (birdBounds.intersects(topPipeBounds) || birdBounds.intersects(bottomPipeBounds) || bird.bird_sprite.getPosition().y + birdBounds.height >= environment.base1_sprite.getPosition().y) {
                    gameOver = true;
                    sound.hit.play();
                    stateManager.setState(GameState::GameOver);
                }
            }

            window.clear();

            if (stateManager.isMenu()) {
                drawMenu(window);
            }

            if (stateManager.isTap()) {
                drawTap(window);
            }

            if (stateManager.isStart()) {
                drawStart(window);
            }

            if (stateManager.isGameOver()) {
                window.draw(environment.background_sprite); // Отрисовка фона
                window.draw(pipe.bottom_pipe);
                window.draw(pipe.top_pipe); // Отрисовка труб
                window.draw(environment.base1_sprite);
                window.draw(environment.base2_sprite);
                window.draw(bird.bird_sprite); // Отрисовка птички
                score.draw(window); // Отрисовка счета
                window.draw(game_over.game_over_title);
                window.draw(game_over.ok);
            }

            window.display();
        }
    }
};

#endif // GAME_H
