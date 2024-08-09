#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Tap
{
public:
    Texture tap_texture;
    Texture get_ready_texture;

    Sprite tap_sprite;
    Sprite get_ready_sprite;

    Clock blinkClock;          // Timer for blinking
    float blinkInterval = 0.5f; // Time interval for blinking (in seconds)
    bool isVisible = true;     // Visibility state of the tap sprite

    Tap(const string& textureFile) {
        tap_texture.loadFromFile(textureFile);
        tap_sprite.setTexture(tap_texture);
        tap_sprite.setTextureRect(IntRect(0, 160, 184, 107));
        tap_sprite.setPosition(288 / 2 - 184 / 2, 250);

        get_ready_texture.loadFromFile(textureFile);
        get_ready_sprite.setTexture(get_ready_texture);
        get_ready_sprite.setTextureRect(IntRect(0, 100, 184, 55));
        get_ready_sprite.setPosition(288 / 2 - 184 / 2 + 30, 140);
    }

    void tap_update() {
        // Check if it's time to toggle visibility
        if (blinkClock.getElapsedTime().asSeconds() >= blinkInterval) {
            isVisible = !isVisible;  // Toggle visibility
            blinkClock.restart();    // Restart the clock
        }

        // Update sprite visibility
        tap_sprite.setColor(Color(255, 255, 255, isVisible ? 255 : 0)); // Fully opaque or fully transparent
    }
};
