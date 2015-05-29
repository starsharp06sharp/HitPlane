#include "Player.h"

const sf::IntRect livePlaneToDisplay[] =
/*
*This array storge the position rectangle in texture
* of player in different life.
*E.g. livePlaneToDisplay [lifeRemain]
*/
{
    sf::IntRect(),
    sf::IntRect( 165, 360, 102, 126 ),//life = 1
    sf::IntRect( 165, 360, 102, 126 ),//life = 2,the same
    sf::IntRect( 0, 99, 102, 126 )//life = 3
};

const sf::IntRect deadPlaneToDisplay[] =
/*
*This array storge the position rectangle in texture
* of dead player at different time.
*E.g. deadPlaneToDisplay [deadCounter]
*/
{
    sf::IntRect(),
    sf::IntRect( 165, 234, 102, 126 ),//deadCounter = 1
    sf::IntRect( 330, 624, 102, 126 ),//deadCounter = 2
    sf::IntRect( 330, 498, 102, 126 ),//deadCounter = 3
    sf::IntRect( 432, 624, 102, 126 )//deadCounter = 4
};

sf::SoundBuffer Player::bufferExplode;
sf::Sound Player::soundExplode;

sf::SoundBuffer Player::bufferGetHit;
sf::Sound Player::soundGetHit;

Player::Player(
    sf::IntRect aeraToDisplay,
    sf::Vector2f scale,
    sf::Vector2f originPos,
    int life
    ) :
        Plane(
            aeraToDisplay,
            scale,
            originPos,
            life
            ),
        deadCounter( 0 )
{
    //Do nothing
}

void
Player::initSound( void )
{
    if( !bufferGetHit.loadFromFile("get_hit.ogg") ) {
        //Exit when sound file is broken
        //system("pause");
        exit(-1);
    }
    soundGetHit.setBuffer(bufferGetHit);
    soundGetHit.setVolume(100);

    if( !bufferExplode.loadFromFile("game_over.ogg") ) {
        //Exit when sound file is broken
        //system("pause");
        exit(-1);
    }
    soundExplode.setBuffer(bufferExplode);
    soundExplode.setVolume(100);
}

void
Player::shoot( void )
{
    ammo.push_back(
        Bullet(
            sf::IntRect( 69, 78, 9, 21 ),
            sf::Vector2f( 0.5f, 0.5f ),
            this-> getPosition() + sf::Vector2f( 24.f, -10.f ),
            sf::Vector2f( 0, -4 )
            )
        );
}

void
Player::flash( void )
{
    std::for_each(
        ammo.begin(),
        ammo.end(),
        std::mem_fun_ref(&Bullet::flash)
        );
    ammo.remove_if(
        []( Bullet& bullet ) {return bullet.isDisappear();}
        );

    if( deadCounter > 0 ) {
        if( deadDelayConuter == 10 ) {
            if( deadCounter++ > 4 )
                this-> disappear = true;
            else {
                this-> setTextureRect(
                    deadPlaneToDisplay [deadCounter]
                    );
            }
            deadDelayConuter = 0;
        } else
            deadDelayConuter++;
    }
}

void
Player::draw(
    sf::RenderWindow& window
    )
{
    window.draw( *this );
    std::for_each(
        ammo.begin(),
        ammo.end(),
        //std::bind1st(std::mem_fun1_ref(&sf::RenderWindow::draw),window)
        [&]( Bullet& bullet ) {window.draw(bullet);}
        );
//    std::list<Bullet>::iterator it = ammo.begin();
//    for (; it != )
}

bool
Player::hitEnemy(
    Enemy& enemy
    )
{
    sf::FloatRect enemyRect = enemy.getGlobalBounds();
    std::list<Bullet>::iterator it = ammo.begin();

    for ( ;it != ammo.end(); ++it ) {
        if( it-> hit( enemyRect ) ){
            ammo.erase( it );
            return true;
        }
    }

    return false;
}

void
Player::setPosition(
    sf::Vector2f position
    )
{
    if ( life <= 0 ) return;
    sf::Sprite::setPosition( position );
    int status = judgeOutOfBorder();

    if ( status%3 == 1 ) position.x = -1.f;//Out left border
    else if( status%3 ==2 ) position.x = 242.f - this-> getGlobalBounds().width;//Out right border

    status /= 3;

    if ( status%3 == 1 ) position.y = -1.f;//Out top border
    else if( status%3 ==2 ) position.y = 406.f - this-> getGlobalBounds().height;//Out bottom border

    sf::Sprite::setPosition( position );
}

sf::Vector2f
Player::getCenter( void )
{
    sf::FloatRect myBound = this->getGlobalBounds();
    return sf::Vector2f(
        myBound.left + myBound.width / 2,
        myBound.top + myBound.height / 2
        );
}

bool
Player::isDead( void )
{
    return ( life <= 0 );
}

bool
Player::isDisappear( void )
{
    return this->disappear;
}

void
Player::getHit( void )
{
    life--;
    soundGetHit.play();
    if ( life > 0 ) {
        this-> setTextureRect(
            livePlaneToDisplay[life]
            );
    } else if ( life == 0 ) {
        deadCounter = 1;
        soundExplode.play();
        deadDelayConuter = 0;
    }
}

int
Player::getLife( void )
{
    return this->life;
}

void
Player::addLife( void )
{
    life++;
}
