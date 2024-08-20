#pragma once

#include <SFML/Graphics.hpp>
#include "GameStateManager.h"
#include "bird.h"
#include "pipe.h"
#include "score.h"
#include "menu.h"
#include "game_over.h"
#include "sound.h"

class InputHandler {
public:
    static void handleInput(sf::Event &event, sf::RenderWindow &window, GameStateManager &stateManager, 
    Bird &bird, Menu &menu, GameOver &game_over, Pipe &pipe, Score &score, setSound &sound)
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            switch (stateManager.getState()) {
                case GameState::Tap:
                    bird.jump();
                    sound.flap.play();
                    stateManager.setState(GameState::Start);
                    break;

                case GameState::Menu:
                    if (menu.button_play_sprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        stateManager.setState(GameState::Tap);
                        bird.setPosition(30, 150);
                        sound.swoosh.play();
                    }
                    break;

                case GameState::Start:
                    bird.jump();
                    sound.flap.play();
                    break;

                case GameState::GameOver:
                    if(game_over.ok.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        stateManager.setState(GameState::Tap);
                        bird.setPosition(30, 150);
                        pipe.rand_pos();
                        score.setScore(0);
                    }

                default:
                    break;
            }
        }
    }
};