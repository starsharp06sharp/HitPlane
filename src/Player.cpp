#include "Player.h"

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
            )
{
    //Do nothing
}

void
Player::shoot( void )
{
    ammo.push_back(
        Bullet(
            sf::IntRect(69, 78, 9, 21),
            sf::Vector2f(0.5f, 0.5f),
            this-> getPosition() + sf::Vector2f(24.f, -10.f),
            sf::Vector2f(0, -5)
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
}

void
Player::draw(
    sf::RenderWindow& window
    )
{
    window.draw(*this);
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
    sf::Sprite::setPosition(position);
    int status = judgeOutOfBorder();

    if ( status%3 == 1) position.x = -1.f;
    else if( status%3 ==2) position.x = 242.f - this-> getGlobalBounds().width;

    status/=3;

    if ( status%3 == 1) position.y = -1.f;
    else if( status%3 ==2) position.y = 406.f - this-> getGlobalBounds().height;

    sf::Sprite::setPosition(position);
}
