#ifndef ENEMY_H
#define ENEMY_H

#include <list>
#include "Plane.h"
#include "Bullet.h"


class Enemy : public Plane {
public:

    Enemy(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        int life
    );

    void
    flash( void );

    void
    shoot( void );

    bool
    isDisappear( void );

    static void
    flashAmmo( void );

protected:

private:

    static std::list<Bullet> ammo;

    sf::Vector2f speed;

};

#endif // ENEMY_H
