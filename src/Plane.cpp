#include "Plane.h"

Plane::Plane(
    sf::IntRect aeraToDisplay,
    sf::Vector2f scale,
    sf::Vector2f originPos,
    int life
    ) :
        Moveable(
            aeraToDisplay,
            scale,
            originPos
            ),
        life ( life ),
        disappear( false )
{
    //Do nothing
}

int
 Plane::judgeOutOfBorder( void )
 {
    int ans=0;
    float top,bottom;
    float left,right;

    sf::FloatRect bound = this-> getGlobalBounds();

    top = bound.top;
    bottom = top + bound.height;
    left = bound.left;
    right = left + bound.width;

    if ( left <-2 * SCALE ) ans++;
    else if ( WINDOW_SIZE_X + 4 * SCALE < right ) ans += 2;

    if ( top < -2 * SCALE ) ans += 3;
    else if ( WINDOW_SIZE_Y + 12 * SCALE < bottom ) ans += 6;

    return ans;
 }

 int
Plane::getLife( void )
{
    return this->life;
}

sf::Vector2f
Plane::getCenter( void )
{
    sf::FloatRect myBound = this->getGlobalBounds();
    return sf::Vector2f(
        myBound.left + myBound.width / 2,
        myBound.top + myBound.height / 2
        );
}

bool
Plane::isDead( void )
{
    return ( life <= 0 );
}

bool
Plane::isDisappear( void )
{
    return this->disappear;
}
