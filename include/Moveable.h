#ifndef MOVEABLE_H
#define MOVEABLE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

typedef sf::Texture TEXTURE;

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

    void
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

    TEXTURE planes;// TODO (zl#1#): Change it into static and solve the undefined question

};

#endif // MOVEABLE_H
