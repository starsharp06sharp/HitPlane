#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <functional>
#include <SFML/Graphics.hpp>
#include "constDef.h"
#include "Plane.h"
#include "Bullet.h"
#include "Enemy.h"

class Enemy;

class Player : public Plane {
public:

    Player() = default;

    Player(
        sf::IntRect aeraToDisplay,
        sf::Vector2f scale,
        sf::Vector2f originPos,
        int life
        );

    static void
    initSound( void );

    void
    setPosition(
        sf::Vector2f position
        );

    void
    getHit( void );

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

    void
    addLife( void );

    void
    drawAllBullet( sf::RenderWindow& window );

protected:

private:

    std::list<Bullet> ammo;

    bool whichFrameToDisplay = 0;

    int changeFrameCounter = 0;

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

    unsigned shootCounter;
    /*
    *This counter control the shoot frequency of the enemy.
    *The frequency depends on the array shootInterval[]
    */

    static sf::SoundBuffer bufferExplode;

    static sf::Sound soundExplode;

    static sf::SoundBuffer bufferGetHit;

    static sf::Sound soundGetHit;

};

#endif // PLAYER_H
