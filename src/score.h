#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Score
{
public:
    Texture texture_digits[10];
    vector<Sprite> digits;

    int score;

    Score(const vector<string>& textureFile) {
        for(int i = 0; i < 10; i++) {
            texture_digits[i].loadFromFile(textureFile[i]);
        }

        digits.clear();

        setScore(0);
    }

    void setScore(int newScore) {
        score = newScore;
        updateDigits();
    }

    void addScore(int points) {
        score += points;
        updateDigits();
    }

    void updateDigits() {
        digits.clear();

        string scoreStr = to_string(score);

        float currentX = 0;

        for (size_t i = 0; i < scoreStr.size(); ++i) {
            int digit = scoreStr[i] - '0';

            Sprite digitSprite(texture_digits[digit]);

            // Устанавливаем позицию цифры на экране
            digitSprite.setPosition(currentX, 0);

            // Обновляем текущую позицию X с учётом ширины текущей цифры и небольшого зазора
            currentX += digitSprite.getGlobalBounds().width;

            digits.push_back(digitSprite);
        }
    }

    void draw(RenderWindow &window) const{
        for (auto& digit : digits) {
            window.draw(digit);
        }
    }
};
