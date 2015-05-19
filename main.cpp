#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <list>

#include "Moveable.h"
#include "Plane.h"
#include "Bullet.h"

//sf::Vector2f
//getStepFromKeyboardEvent(
//    sf::Event keyEvent
//    );
template < typename T>
void flashIt (T& it) {
    it.flash();
}

int main() {
    //Create the main window
    sf::RenderWindow windowMain(sf::VideoMode(240, 400), "HitPlane By L.Zheng");

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
    musicBGM.setVolume(25);
    musicBGM.setLoop(true);
    musicBGM.play();

    //Sprite background
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setScale(sf::Vector2f(0.5f, 0.5f));

    //Inital moveable object's texture
    Moveable::initTexturePlanes();
    //TEMP player
    Plane player(
        sf::IntRect(0, 99, 102, 126),
        sf::Vector2f(0.5f, 0.5f),
        sf::Vector2f(96.f, 336.f),
        3
        );
    //TEMP player's bullet
    std::list<Bullet*> playerBullet;

    unsigned NUM=0;
    bool shot;
    //Main loop
    while (windowMain.isOpen()) {
        sf::Event event;
        while (windowMain.pollEvent(event)) {
            //Close window when exit
            if (event.type == sf::Event::Closed) {
                windowMain.close();
            }

            /*
            //Move player's plane when key preessed
            if (event.type == sf::Event::KeyPressed) {
                player.move(
                    getStepFromKeyboardEvent( event )
                    );
                sf::FloatRect gBound = player.getGlobalBounds();
                //std::cout<<'('<<gBound.left<<','<<gBound.top<<')'
                //<<','<<'('<<gBound.left+gBound.width<<','<<gBound.top+gBound.height<<')'<<std::endl;
            }
            */
        }
        sf::Vector2i mousePosition = sf::Mouse::getPosition(windowMain);
        player.setPosition(sf::Vector2f(mousePosition.x - 24, mousePosition.y - 32));

        if(NUM%200 == 0) {
            shot = false;
        }
        if (!shot && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            //TEMP playerBullet
            Bullet* tmp =
                new Bullet(
                    sf::IntRect(69, 78, 9, 21),
                    sf::Vector2f(0.5f, 0.5f),
                    player.getPosition() + sf::Vector2f(24.f, -10.f),
                    sf::Vector2f(0, -0.5)
                    );
            playerBullet.push_back(tmp);
            shot = true;
        }

        windowMain.clear();

        //draw
        windowMain.draw(spriteBackground);
        windowMain.draw(*(sf::Sprite*)&player);

        //Flash and draw all player's bullet
        std::list<Bullet*>::iterator it;
        for (it = playerBullet.begin(); it!=playerBullet.end();) {
            (*it)-> flash();
            if ((*it)-> isDisappear()) {
                //Delete when disappear
                delete (*it);
                playerBullet.erase( it++ );
            } else {
                windowMain.draw( *(sf::Sprite*)(*it) );
                ++it;
            }
        }


        windowMain.display();
        NUM++;
    }

    return 0;
}

//sf::Vector2f
//getStepFromKeyboardEvent(
//    sf::Event keyEvent
//    )
//{
//    sf::Vector2f step;
//
//    switch(keyEvent.key.code) {
//    case sf::Keyboard::Up :
//        step = sf::Vector2f(0, -8);
//        break;
//
//    case sf::Keyboard::Down :
//        step = sf::Vector2f(0, 8);
//        break;
//
//    case sf::Keyboard::Left :
//        step = sf::Vector2f(-8, 0);
//        break;
//
//    case sf::Keyboard::Right :
//        step = sf::Vector2f(8, 0);
//        break;
//    }
//
//    return step;
//}
