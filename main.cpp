#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
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
        system("pause");
        exit(-1);
    }

    //Create and Play BGM
    sf::Music musicBGM;
    if (!musicBGM.openFromFile("TURKY.WAV")) {
        //Exit when music file is broken
        system("pause");
        exit (-1);
    }
    musicBGM.setVolume(100);
    musicBGM.setLoop(true);
    musicBGM.play();

    //Create sound buffer
    sf::SoundBuffer bufferShoot, bufferExplode;
    if(!bufferShoot.loadFromFile("bullet.ogg")) {
        //Exit when sound file is broken
        system("pause");
        exit(-1);
    }
    if(!bufferExplode.loadFromFile("enemy1_down.ogg")) {
        //Exit when sound file is broken
        system("pause");
        exit(-1);
    }
    sf::Sound soundShoot, soundExplode;
    soundShoot.setBuffer(bufferShoot);
    soundShoot.setVolume(125);
    soundExplode.setBuffer(bufferExplode);
    soundShoot.setVolume(5);



    //Sprite background
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setScale(sf::Vector2f(0.5f, 0.5f));

    //Inital moveable object's texture
    Moveable::initTexturePlanes();
    //TEMP player
    Player player(
        sf::IntRect(0, 99, 102, 126),
        sf::Vector2f(0.5f, 0.5f),
        sf::Vector2f(96.f, 336.f),
        3
        );

    unsigned NUM=0;
    unsigned shootCounter = 0;
    srand( (unsigned)time(NULL) );
    std::list<Enemy> enemies;

    //Main loop
    while (windowMain.isOpen()) {

        sf::Vector2i mousePosition = sf::Mouse::getPosition(windowMain);
        player.setPosition(sf::Vector2f(mousePosition.x - 24, mousePosition.y - 32));

        sf::Event event;
        while (windowMain.pollEvent(event)) {
            //Close window when exit
            if (event.type == sf::Event::Closed) {
                windowMain.close();
            }
        }

        if ( shootCounter >= 20 && sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
            //TEMP playerBullet
            soundShoot.setVolume(75);
            player.shoot();
            shootCounter = 0;
            soundShoot.play();
        }

        windowMain.clear();

        //drawBackground
        windowMain.draw(spriteBackground);

        //Create , move and draw enemy
        if( NUM%60 == 0 ) {
            enemies.push_back(
                Enemy(
                    sf::IntRect(534, 612, 57, 43),
                    sf::Vector2f(0.5f, 0.5f),
                    sf::Vector2f( rand()% (int)(240 - 57*0.5), 0),
                    1
                    )
                );
        }
        std::for_each(
            enemies.begin(),
            enemies.end(),
            std::mem_fun_ref(&Enemy::flash)
            //[](Enemy& enemy) {enemy.flash();}
            );

        //Flash all player bullet and player itself
        player.flash();

        //TEMPLY:Mark all hited planes
        std::for_each(
            enemies.begin(),
            enemies.end(),
            [&](Enemy& enemy)
            {
                if ( player.hitEnemy( enemy ) ) {
                    enemy.getKilled();
                    soundExplode.play();
                }
            }
            );

        //TEMPLY:Destory all marked planes
        enemies.remove_if(
            std::mem_fun_ref(&Enemy::isDead)
            );

        //Draw all player bullet and player itself
        player.draw(windowMain);
        //Draw all enemy
        std::for_each(
            enemies.begin(),
            enemies.end(),
            [&](Enemy& enemy) {windowMain.draw(enemy);}
            );



        windowMain.display();
        NUM++;
        shootCounter++;
    }

    return 0;
}
