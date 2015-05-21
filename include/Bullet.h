#ifndef BULLET_H
#define BULLET_H

#include "Moveable.h"

class Bullet : public Moveable {
public:

    Bullet(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        sf::Vector2f speed
    );

    void
    flash( void );

    bool
    isDisappear( void );

protected:

private:

    sf::Vector2f speed;

};

#endif // BULLET_H
