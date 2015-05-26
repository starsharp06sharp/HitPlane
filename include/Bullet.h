#ifndef BULLET_H
#define BULLET_H

#include <SFML/Audio.hpp>
#include "Moveable.h"

class Bullet : public Moveable {
public:

    Bullet(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        sf::Vector2f speed,
        float angle = 0.f
    );

    static void
    initSound( void );

    void
    flash( void );

    bool
    isDisappear( void );

    bool
    hit(
        sf::FloatRect target
        );

protected:

private:

    sf::Vector2f speed;

    static sf::SoundBuffer bufferShoot;

    static sf::Sound soundShoot;

};

#endif // BULLET_H
