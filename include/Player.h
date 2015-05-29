#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Plane.h"
#include "Bullet.h"
#include "Enemy.h"

class Enemy;

class Player : public Plane {
public:

    Player() {}

    Player(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        int life
        );

    sf::Vector2f
    getCenter( void );

    static void
    initSound( void );

    void
    setPosition(
        sf::Vector2f position
        );

    void
    getHit( void );

    bool
    isDead( void );

    bool
    isDisappear( void );

    void
    shoot( void );

    void
    flash( void );

    bool
    hitEnemy(
        Enemy& enemy
        );

    void
    draw(
        sf::RenderWindow& window
        );

    int
    getLife( void );

    void
    addLife( void );

protected:

private:

    std::list<Bullet> ammo;

    int deadCounter;
    /*
    *This counter repesents the different stage of dead plane:
    *When it is 0, the plane is alive
    *When it is a num>0 ,it means the picture NO that is putting on the screen now.
    */

    int deadDelayConuter;
    /*
    *This counter can control the speed of explode action.
    *Every to number play one frame.
    */

    static sf::SoundBuffer bufferExplode;

    static sf::Sound soundExplode;

    static sf::SoundBuffer bufferGetHit;

    static sf::Sound soundGetHit;

};

#endif // PLAYER_H
