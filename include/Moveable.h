#ifndef MOVEABLE_H
#define MOVEABLE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include <iostream>

class Moveable : public sf::Sprite {
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
    initTexturePlanes( void );

protected:

private:

    static sf::Texture planes;

};


#endif // MOVEABLE_H
