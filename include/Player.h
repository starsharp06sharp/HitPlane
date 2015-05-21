#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Plane.h"
#include "Bullet.h"

class Player : public Plane {
public:

    Player(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        int life
        );

    void
    shoot( void );

    void
    flash( void );

    bool
    hitEnemy( void );

    void
    draw(
        sf::RenderWindow& window
        );

protected:

private:

    std::list<Bullet> ammo;

};

#endif // PLAYER_H
