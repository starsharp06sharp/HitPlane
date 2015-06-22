#ifndef MOVEABLE_H
#define MOVEABLE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "constDef.h"

class Moveable : public sf::Sprite {
public:

    Moveable() {}

    Moveable(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        float angle = 0.f
        );

    static void
    initTexture( void );


    void
    resize(
        float preSCALE
        );


    virtual void
    flash( void ) = 0;

    virtual bool
    isDisappear( void ) = 0;

protected:

private:

    static sf::Texture planes;

};


#endif // MOVEABLE_H
