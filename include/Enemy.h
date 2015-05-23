#ifndef ENEMY_H
#define ENEMY_H

#include <list>
#include "Plane.h"
#include "Bullet.h"

enum enemyStyle {
    enemy1,
    enemy2
    //,enemy3
};

const int maxLife[] ={ 1, 2, 4 };

const sf::IntRect livePlaneToDisplay[][7] =
/*
*This array storge the position rectangle in texture
* of each plane in different life.
*E.g. livePlaneToDisplay [enemyNo] [lifeRemain]
*/
{
    {//enemy1
        sf::IntRect(),
        sf::IntRect( 534, 612, 57, 43 )//life = 1
    },

    {//enemy2
        sf::IntRect(),
        sf::IntRect( 432, 525, 69, 99 ),//life = 1
        sf::IntRect( 0, 0, 69, 99 )//life = 2
    }
};

const sf::IntRect deadPlaneToDisplay[][7] =
/*
*This array storge the position rectangle in texture
* of each dead plane at different time.
*E.g. deadPlaneToDisplay [enemyNo] [deadCounter]
*/
{
    {//enemy1
        sf::IntRect(),
        sf::IntRect( 267, 347, 57, 51 ),//deadCounter = 1
        sf::IntRect( 873, 697, 57, 51 ),//deadCounter = 2
        sf::IntRect( 267, 296, 57, 51 ),//deadCounter = 3
        sf::IntRect( 930, 697, 57, 51)//deadCounter = 4
    },

    {//enemy2
        sf::IntRect(),
        sf::IntRect( 534, 655, 69, 95 ),//deadCounter = 1
        sf::IntRect( 603, 655, 69, 95 ),//deadCounter = 2
        sf::IntRect( 672, 653, 69, 95 ),//deadCounter = 3
        sf::IntRect( 741, 653, 69, 95)//deadCounter = 4
    }
};

const int deadDelaySpeed[] = { 3, 6 };

class Enemy : public Plane {
public:

    Enemy(
        enemyStyle enemyNo,
        sf::Vector2f scale,
        sf::Vector2f originPos
    );

    static void
    initSound( void );

    void
    flash( void );

    void
    getHit( void );

    bool
    isDisappear( void );

    void
    shoot( void );

    static void
    flashAmmo( void );

protected:

private:

    enemyStyle enemyNo;

    bool disappear;

    static std::list<Bullet> ammo;

    sf::Vector2f speed;

    int deadCounter;
    /*
    *This counter repesents the different stage of dead plane:
    *When it is 0, the plane is alive
    *When it is a num>0 ,it means the picture NO that is putting on the screen now.
    */

    int deadDelayConuter;
    /*
    *This counter can control the speed of explode action.
    Every to number play one frame.
    */

    static sf::SoundBuffer bufferExplode[3];

    static sf::Sound soundExplode[3];

};

#endif // ENEMY_H
