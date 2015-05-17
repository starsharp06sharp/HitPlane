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
    // TODO (zl#1#): Add out-of-border judge and fix step driectly
    sf::Sprite::move(step);
}
