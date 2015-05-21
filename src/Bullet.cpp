#include "Bullet.h"

Bullet::Bullet(
    sf::IntRect aeraToDisplay,
    sf::Vector2f scale,
    sf::Vector2f originPos,
    sf::Vector2f speed
    ) :
        Moveable(
            aeraToDisplay,
            scale,
            originPos
            ),
        speed(speed)
{
    //Do nothing
}

void
Bullet::flash( void )
{
    this-> move(speed);
}

bool
Bullet::isDisappear( void )
{
    return ! this-> getGlobalBounds().intersects( sf::FloatRect(0.f, 0.f, 240.f, 400.f) );
}