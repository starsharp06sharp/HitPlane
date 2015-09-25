#ifndef PLANE_H
#define PLANE_H

#include "constDef.h"
#include "Moveable.h"

class Plane : public Moveable {
public:

    Plane() = default;

    Plane(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        int life
        );

    int
    judgeOutOfBorder( void );
    /*
    *This function returns a two-bit ternary numbers
    *that each bit repestent the x-pos or y-pos
    *is corss the border or not.(left/top border:1, right/bottom border:2)
    */

    sf::Vector2f
    getCenter( void );

    int
    getLife( void );

    virtual void
    move( void ) {};

    virtual void
    setPosition(
        sf::Vector2f position
        ) {};

    virtual void
    getHit( void ) = 0;

    bool
    isDead( void );

    bool
    isDisappear( void );

    virtual void
    shoot( void ) {};

    virtual void
    shoot(
        sf::Vector2f targetPosition
        ) {};

protected:

    int life;

    bool disappear;


private:

};

#endif // PLANE_H
