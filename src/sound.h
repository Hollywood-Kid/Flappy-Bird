#include <SFML/Audio.hpp>

using namespace sf;

class setSound
{
public:
    SoundBuffer s1, s2,s3;
    Sound flap, bonus, fail;

    setSound() {
        s1.loadFromFile("point-101soundboards.mp3");
        s2.loadFromFile("flap-101soundboards.mp3");
        bonus.setBuffer(s1);
        flap.setBuffer(s2);
    }
};
