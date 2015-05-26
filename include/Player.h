#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Plane.h"
#include "Bullet.h"
#include "Enemy.h"

class Enemy;

class Player : public Plane {
public:

    Player(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        int life
        );

    sf::Vector2f
    getCenter( void );

    void
    setPosition(
        sf::Vector2f position
        );

    void
    shoot( void );

    void
    flash( void );

    bool
    hitEnemy(
        Enemy& enemy
        );

    void
    draw(
        sf::RenderWindow& window
        );

protected:

private:

    std::list<Bullet> ammo;

};

#endif // PLAYER_H
