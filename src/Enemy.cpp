#include "Enemy.h"

std::list<Bullet> Enemy::ammo;

Enemy::Enemy(
    sf::IntRect aeraToDisplay,
    sf::Vector2f scale,
    sf::Vector2f originPos,
    int life
    ) :
        Plane(
            aeraToDisplay,
            scale,
            originPos,
            life
            ),
        speed(
            sf::Vector2f(0, 0.3)
            ),
        dead ( false )
{
    //Do nothing
}

void
Enemy::flash( void )
{
    this-> move(speed);
}

void
Enemy::getKilled( void )
{
    dead = true;
}

bool
Enemy::isDead( void )
{
    return dead;
}
