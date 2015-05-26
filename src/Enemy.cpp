#include <cmath>
#include "Enemy.h"

#define PI 3.1415926

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
            sf::Vector2f(0, 0.3)
            ),
        deadCounter( 0 ),
        shootCounter( 0 ),
        disappear( false )
{
    //Do nothing
}

void
Enemy::flash( void )
{
    if ( deadCounter <= 0 ) {
        this-> move(speed);
        if ( this-> judgeOutOfBorder() >= 6 ) this-> disappear = true;
    } else {
        if (deadDelayConuter == deadDelaySpeed[enemyNo]) {
            this-> setTextureRect(
                deadPlaneToDisplay [enemyNo] [deadCounter]
                );
            if( deadCounter++ > 4 ) this-> disappear = true;
        deadDelayConuter=0;
        } else deadDelayConuter++;
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
Enemy::shoot( Player& player )
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
        deltaX = myPosition.x - player.getCenter().x;
        deltaY = myPosition.y - player.getCenter().y;
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
