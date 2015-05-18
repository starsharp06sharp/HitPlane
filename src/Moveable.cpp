#include "Moveable.h"

sf::Texture Moveable::planes;

Moveable::Moveable(
    sf::IntRect aeraToDisplay,
    sf::Vector2f scale,
    sf::Vector2f originPos
    )
{
    this-> setTexture( planes );
    this-> setTextureRect( aeraToDisplay );
    this-> setScale( scale );
    this-> setOrigin( originPos );
}

void
Moveable::move(
    sf::Vector2f step
    )
{
    float top,bottom;
    float left,right;

     sf::FloatRect bound = this-> getGlobalBounds();

     top = bound.top;
     bottom = top + bound.height;
     left = bound.left;
     right = left + bound.width;

     if (-1.f > top + step.y || bottom + step.y > 406.f)
        step.y = 0.f;
     if (-1.f > left + step.x || right +step.x > 242.f)
        step.x = 0.f;

    this-> sf::Sprite::move(step);
}

void
Moveable::initTexturePlanes( void )
{
    if ( !planes.loadFromFile( "Planes.png" ) ) {
        //Exit when plane's texture is broken
        system( "pause" );
        exit( -1 );
    }
}
