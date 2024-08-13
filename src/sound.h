#include <SFML/Audio.hpp>

using namespace sf;

class setSound
{
public:
    SoundBuffer s1, s2,s3, s4;
    Sound flap, bonus, fail, swoosh;

    setSound() {
        s1.loadFromFile("Audio/point-101soundboards.mp3");
        s2.loadFromFile("Audio/flap-101soundboards.mp3");
        s3.loadFromFile("Audio/swoosh-101soundboards.mp3");

        bonus.setBuffer(s1);
        flap.setBuffer(s2);
        swoosh.setBuffer(s3);
    }
};
