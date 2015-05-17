#ifndef MOVEABLE_H
#define MOVEABLE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include <iostream>

class Moveable : sf::Sprite {
public:

    Moveable(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos
    );

    void
    move(
        sf::Vector2f step
    );

    static void
    initTexturePlanes( void )
    {
        if ( !planes.loadFromFile( "Planes.png" ) ) {
            //Exit when plane's texture is broken
            system( "pause" );
            exit( -1 );
        }
    }

protected:

private:

    static sf::Texture planes;

};


#endif // MOVEABLE_H
