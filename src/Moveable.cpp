#include "Moveable.h"

sf::Texture Moveable::planes;

Moveable::Moveable(
    sf::IntRect aeraToDisplay,
    sf::Vector2f scale,
    sf::Vector2f originPos,
    float angle
    )
{
    this-> setTexture( planes );
    this-> setTextureRect( aeraToDisplay );
    this-> setScale( scale );
    this-> setPosition( originPos );
    this-> setRotation( angle );
}

void
Moveable::initTexture( void )
{
    if ( !planes.loadFromFile( "Planes.png" ) ) {
        //Exit when plane's texture is broken
        system( "pause" );
        exit( -1 );
    }
}
