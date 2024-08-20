#ifndef GAME_STATE_H
#define GAME_STATE_H

enum class GameState
{
    Menu,
    Tap,
    Start,
    GameOver
};

class GameStateManager {
private:
    GameState currentState;

public:
    GameStateManager() : currentState(GameState::Menu) {}

    void setState(GameState state) {
        currentState = state;
    }

    GameState getState() const {
        return currentState;
    }

    bool isMenu() const { return currentState == GameState::Menu; }
    bool isTap() const { return currentState == GameState::Tap; }
    bool isStart() const { return currentState == GameState::Start; }
    bool isGameOver() const { return currentState == GameState::GameOver; }
};

#endif // GAME_STATE_H
