#ifndef MOVEABLE_H
#define MOVEABLE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "constDef.h"

class Moveable : public sf::Sprite {
public:

    Moveable() {}

    void
    resize(
        float preSCALE
        );

    Moveable(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        float angle = 0.f
        );

    static void
    initTexture( void );

protected:

private:

    static sf::Texture planes;

};


#endif // MOVEABLE_H
