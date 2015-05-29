#include <cmath>
#include "Enemy.h"

#define PI 3.1415926


const int maxLife[] ={ 1, 2, 4 };

const sf::Vector2f initSpeed[] =
{
    sf::Vector2f( 0, 0.3 ),
    sf::Vector2f( 0.4 , 0.4 )
};

const int shootInterval[] = {100, 80, 50};

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

const int deadDelaySpeed[] = { 6, 10 };


sf::SoundBuffer Enemy::bufferExplode[3];
sf::Sound Enemy::soundExplode[3];

std::list<Bullet> Enemy::ammo;

Enemy::Enemy(
    enemyStyle enemyNo,
    sf::Vector2f scale,
    sf::Vector2f originPos
    ) :
        Plane(
            livePlaneToDisplay [ enemyNo ] [ maxLife [ enemyNo ] ],//aeraToDisplay
            scale,
            originPos,
            maxLife [ enemyNo ]//life
            ),
        enemyNo( enemyNo ),
        speed(
            initSpeed[ enemyNo ]
            ),
        deadCounter( 0 ),
        shootCounter( 0 )
{
    //Do nothing
}

void
Enemy::flash( void )
{
    if ( deadCounter <= 0 ) {

        this-> move();

    } else {

        if (deadDelayConuter == deadDelaySpeed[enemyNo]) {

            if( deadCounter++ > 4 ) this-> disappear = true;
            this-> setTextureRect(
                deadPlaneToDisplay [enemyNo] [deadCounter]
                );
            deadDelayConuter=0;

        } else
            deadDelayConuter++;
    }
}

void
Enemy::getHit( void )
{
    life--;
    if ( life > 0 ) {
        this-> setTextureRect(
            livePlaneToDisplay [enemyNo] [life]
            );
    } else if ( life == 0 ) {
        deadCounter = 1;
        soundExplode[enemyNo].play();
        deadDelayConuter = 0;
    }
}

bool
Enemy::isDisappear( void )
{
    return disappear;
}

void
Enemy::initSound( void )
{
    char soundFileName[] = "enemy1_down.ogg";
    for (int i = enemy1;
           i <= enemy2;
           i++
          )
    {
        soundFileName[5] = '1' + i;
        if( !bufferExplode[i].loadFromFile(soundFileName) ) {
            //Exit when sound file is broken
            system("pause");
            exit(-1);
        }
        soundExplode[i].setBuffer(bufferExplode[i]);
        soundExplode[i].setVolume(100);
    }
}

enemyStyle
Enemy::getEnemyNo( void )
{
    return enemyNo;
}

bool
Enemy::isDead( void )
{
    return ( life <= 0 );
}

void
Enemy::shoot( sf::Vector2f targetPosition )
{
    shootCounter++;
    if ( shootCounter < shootInterval[enemyNo] ) return;
    if ( this->isDead() ) return;

    shootCounter = 0;

    sf::FloatRect myBound = this-> getGlobalBounds();
    sf::Vector2f myPosition;
    myPosition = sf::Vector2f(
        myBound.left + myBound.width / 2,
        myBound.top +myBound.height
        );

    sf::Vector2f bulletSpeed;
    double theta = 0;
    if ( enemyNo == enemy1 ) {
        bulletSpeed = sf::Vector2f(0, 2);
    } else if ( enemyNo == enemy2 ) {
        float deltaX, deltaY;
        deltaX = myPosition.x -targetPosition.x;
        deltaY = myPosition.y - targetPosition.y;
        theta = atan( deltaX / deltaY );
        if ( deltaY>0 ) theta += PI;
        bulletSpeed = sf::Vector2f( 2*sin(theta), 2*cos(theta) );
        theta = -theta * 360 /(2*PI);
    }

    ammo.push_back(
        Bullet(
            sf::IntRect(1004, 987, 9, 21),
            sf::Vector2f(0.5f, 0.5f),
            myPosition,
            bulletSpeed,
            theta
            )
        );
}

void
Enemy::drawAllBullet( sf::RenderWindow& window )
{
    std::for_each(
        ammo.begin(),
        ammo.end(),
        [&window](Bullet& bullet) {
                  window.draw( bullet );
            }
        );
}

void
Enemy::flashAmmo( void )
{
    std::for_each(
        ammo.begin(),
        ammo.end(),
        [](Bullet& bullet) {bullet.flash();}
        );
    ammo.remove_if(
        []( Bullet& bullet ) {return bullet.isDisappear();}
        );
}

void
Enemy::move( void )
{
    sf::Sprite::move( speed );

    int status = this->judgeOutOfBorder();

    if( status % 3 > 0 )//Out left or right border
    {
        this->speed =
        sf::Vector2f(
            -speed.x,
            speed.y
            );
    }

    if( status / 3 > 0 )//Out top or bottom border
        this-> disappear = true;
}

bool
Enemy::hitPlayer(Player& player)
{
    sf::FloatRect playerRect = player.getGlobalBounds();
    std::list<Bullet>::iterator it = ammo.begin();

    for ( ;it != ammo.end(); ++it ) {
        if( it-> hit( playerRect ) ){
            ammo.erase( it );
            return true;
        }
    }

    return false;
}
