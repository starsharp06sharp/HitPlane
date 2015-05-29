#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <ctime>

#include "Moveable.h"
#include "Plane.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"


int main( void ) {
    //Create the main window
    sf::RenderWindow windowMain(sf::VideoMode(240, 400), "HitPlane By L.Zheng");
    windowMain.setFramerateLimit(60);

    //Load background from file
    sf::Texture textureBackground;
    if (!textureBackground.loadFromFile("Background.png")) {
        //Exit when plane's texture is broken
        //system("pause");
        exit(-1);
    }

    //Sprite background
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setScale(sf::Vector2f(0.5f, 0.5f));


    //Create and Play BGM
    sf::Music musicBGM;
    if (!musicBGM.openFromFile("TURKY.WAV")) {
        //Exit when music file is broken
        //system("pause");
        exit (-1);
    }
    musicBGM.setVolume(100);
    musicBGM.setLoop(true);

    //Init sound effect of ecah object
    Bullet::initSound();
    Enemy::initSound();
    Player::initSound();

    //Load font from file
    sf::Font promptFont;
    if ( !promptFont.loadFromFile("courbd.ttf") ) {
        system( "pause" );
        exit( -1 );
    }
    sf::Font scoreFont;
    if ( !scoreFont.loadFromFile("LHANDW.TTF") ){
        system( "pause" );
        exit( -1 );
    }

    //Init score&life text
    sf::Text scoreText;
    scoreText.setFont( scoreFont );
    scoreText.setCharacterSize( 18 );
    scoreText.setColor( sf::Color::Blue );
    //Init life text
    sf::Text lifeText;
    lifeText.setFont( promptFont );
    lifeText.setCharacterSize( 30 );
    lifeText.setColor( sf::Color::Red );

    //Inital moveable object's texture
    Moveable::initTexture();
    //Init player
    Player player;

    unsigned long long score;
    unsigned enemy1Counter;
    unsigned enemy2Counter;
    unsigned shootCounter;
    std::list<Enemy> enemies;

    bool start = true;

    while ( start ) {
        player = Player(
            sf::IntRect(0, 99, 102, 126),
            sf::Vector2f(0.5f, 0.5f),
            sf::Vector2f(96.f, 336.f),
            3
            );
        score = 0;
        enemy1Counter = 0;
        enemy2Counter = 0;
        shootCounter = 0;
        srand( (unsigned)time(NULL) );
        enemies.clear();
        Enemy::clearBullet();
        musicBGM.play();

        //Main loop
        while (windowMain.isOpen()) {

            sf::Event event;
            while (windowMain.pollEvent(event)) {
                //Close window when exit
                if (event.type == sf::Event::Closed) {
                    windowMain.close();
                    start = false;
                }
                /*Cheat code (can use only if life<3)
                if ( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Comma ) {
                    player.addLife();
                }
                */
            }

            windowMain.clear();

            //drawBackground
            windowMain.draw(spriteBackground);

            //Create enemy1
            if( enemy1Counter == 120 ) {
                enemies.push_back(
                    Enemy(
                        enemy1,
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f( rand()% (int)(240 - 57*0.5), 0)
                        )
                    );
                enemy1Counter = 0;
            }

            //Create enemy2
            if ( enemy2Counter == 600 ) {
                enemies.push_back(
                    Enemy(
                        enemy2,
                        sf::Vector2f(0.5f, 0.5f),
                        sf::Vector2f( rand()% (int)(240 - 57*0.5), 0)
                        )
                    );
                enemy2Counter = 0;
            }

            //Flash enemy
            std::for_each(
                enemies.begin(),
                enemies.end(),
                std::mem_fun_ref(&Enemy::flash)
                //[](Enemy& enemy) {enemy.flash();}
                );

            //Enemy shoot and flash enemy'sAmmo
            std::for_each(
                enemies.begin(),
                enemies.end(),
                [&player](Enemy& enemy){
                    enemy.shoot(player.getCenter());
                }
                );
            Enemy::flashAmmo();


            //Move player
            sf::Vector2i mousePosition = sf::Mouse::getPosition(windowMain);
            player.setPosition(sf::Vector2f(mousePosition.x - 24, mousePosition.y - 32));

            //Player shoot
            if ( shootCounter >= 30 && sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
                player.shoot();
                shootCounter = 0;
            }

            //Flash all player bullet and player itself
            player.flash();

            //Mark all hited planes
            std::for_each(
                enemies.begin(),
                enemies.end(),
                [&](Enemy& enemy)
                {
                    if ( player.hitEnemy( enemy ) ) {
                        enemy.getHit();
                        if ( enemy.isDead() ) {
                            score+=deadScore [ enemy.getEnemyNo() ];
                        }
                    }
                }
                );

            //Destory all marked planes
            enemies.remove_if(
                [](Enemy& enemy) {return enemy.isDisappear();}
                );

            //TEMPLY:Weather player get hit
            if( Enemy::hitPlayer( player ) ) {
                player.getHit();
                if( player.isDead() ) {
                //
                }
            }

            //Draw all enemy
            std::for_each(
                enemies.begin(),
                enemies.end(),
                [&](Enemy& enemy) {
                    windowMain.draw(enemy);
                }
                );

            //Draw all enemy bullet
            Enemy::drawAllBullet( windowMain );

            //Draw all player bullet and player itself
            player.draw(windowMain);

            //Draw score
            char scoreStr[40];
            sprintf( scoreStr, "Score : %I64u", score );
            scoreText.setString( scoreStr );
            windowMain.draw( scoreText );
            //Draw life
            wchar_t lifeStr[10];
            int i;
            for (i = 0; i < player.getLife(); i++) lifeStr[i] = L'♥';
            lifeStr[i] = '\0';
            lifeText.setString( lifeStr );
            lifeText.setPosition(
                sf::Vector2f(
                    240 - lifeText.getGlobalBounds().width - 5,//校正
                    0 - 10//校正
                    )
                );
            windowMain.draw( lifeText );

            windowMain.display();

            if( player.isDisappear() ) break;

            enemy1Counter++;
            enemy2Counter++;
            shootCounter++;
        }

        //Dead:
        musicBGM.stop();

        sf::Text loseMessage;
        loseMessage.setFont( promptFont );
        loseMessage.setCharacterSize( 42 );
        loseMessage.setColor( sf::Color::Red );
        loseMessage.setString("GAME OVER");
        loseMessage.setPosition(
            sf::Vector2f(
                120 - loseMessage.getGlobalBounds().width / 2,
                200 - loseMessage.getGlobalBounds().height / 2
                )
            );

        sf::Text pressToReplayMessage;
        pressToReplayMessage.setFont( promptFont );
        pressToReplayMessage.setCharacterSize( 16 );
        pressToReplayMessage.setColor( sf::Color::Red );
        pressToReplayMessage.setString( "Press anykey to replay" );
        pressToReplayMessage.setPosition(
            loseMessage.getGlobalBounds().left + loseMessage.getGlobalBounds().width / 2 - pressToReplayMessage.getGlobalBounds().width / 2,
            loseMessage.getGlobalBounds().top + loseMessage.getGlobalBounds().height
            );

         //Show lose message
        windowMain.draw(loseMessage);
        windowMain.draw(pressToReplayMessage);
        windowMain.display();

        bool shouldGoOut = false;
        while ( windowMain.isOpen() && !shouldGoOut ) {

            sf::Event event;
            while (windowMain.pollEvent(event)) {
                //Close window when exit
                if (event.type == sf::Event::Closed) {
                    windowMain.close();
                    start = false;
                }

                if ( event.type == sf::Event::KeyPressed/* && event.key.code == sf::Keyboard::Comma */) {
                    start = true;
                    shouldGoOut = true;
                }
            }
        }
    }

    return 0;
}
