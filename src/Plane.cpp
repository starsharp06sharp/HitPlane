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
        life ( life )
{
    //Do nothing
}

int
 Plane::judgeOutOfBorder( void )
/*
*This function returns a two-bit ternary numbers
*that each bit repestent the x-pos or y-pos
*is corss the border or not.(left border:1, right border:2)
*/
 {
    int ans=0;
    float top,bottom;
    float left,right;

    sf::FloatRect bound = this-> getGlobalBounds();

    top = bound.top;
    bottom = top + bound.height;
    left = bound.left;
    right = left + bound.width;

    if ( left <-1.f ) ans++;
    else if ( 242.f < right ) ans+=2;

    if ( top < -1.f ) ans+=3;
    else if ( 406.f < bottom ) ans+=6;

    return ans;
 }
