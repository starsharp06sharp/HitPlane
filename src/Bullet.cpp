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
    int ans=0;
    float top,bottom;
    float left,right;

    sf::FloatRect bound = this-> getGlobalBounds();

    top = bound.top;
    bottom = top + bound.height;
    left = bound.left;
    right = left + bound.width;

    if ( left <0.f || 240.f < right ) return true;

    if ( top < 0.f || 400.f < bottom ) return true;

    return false;
 }
