#include "Sky.h"

#include "gameFunc.h"

Sky::Sky() :
    sf::RenderWindow(
        sf::VideoMode(240, 400),
        "HitPlane By L.Zheng"
        )
{
    this->setFramerateLimit( 60 );
    this->initBackground();
    this->initMusic();
    this->initFont();
    Moveable::initTexture();
}

void
Sky::initBackground( void )
{
    if (!this->textureBackground.loadFromFile("Background.png")) {
        //Exit when plane's texture is broken
        //system("pause");
        exit(-1);
    }

    this->spriteBackground.setTexture(textureBackground);
    this->spriteBackground.setScale(sf::Vector2f(0.5f, 0.5f));
}

void
Sky::initMusic( void )
{
    //Create BGM
    if (!this->musicBGM.openFromFile(/*"WJJ.WAV"*/"TURKY.WAV")) {
        //Exit when music file is broken
        //system("pause");
        exit (-1);
    }
    this->musicBGM.setVolume(100);
    this->musicBGM.setLoop(true);

    //Init sound effect of ecah object
    Bullet::initSound();
    Enemy::initSound();
    Player::initSound();
}

void
Sky::initFont( void )
{
    //Load font from file
    if ( !this->promptFont.loadFromFile("courbd.ttf") ) {
        //system( "pause" );
        exit( -1 );
    }

    if ( !this->scoreFont.loadFromFile("LHANDW.TTF") ){
        //system( "pause" );
        exit( -1 );
    }

    if( !this->yaheiFont.loadFromFile("msyh.ttf") ){
        //system( "pause" );
        exit( -1 );
    }
}

void
Sky::mainLoop( void )
{

    //Init player
    Player player = Player(
            sf::IntRect(0, 99, 102, 126),
            sf::Vector2f(0.5f, 0.5f),
            sf::Vector2f(96.f, 336.f),
            3
            );

    unsigned long long score = 0;
    unsigned enemy1Counter = 0;
    unsigned enemy2Counter = 0;
    unsigned shootCounter = 0;
    std::list<Enemy> enemies;


    srand( (unsigned)time(NULL) );
    Enemy::clearBullet();
    this->setMouseCursorVisible( false );
    musicBGM.play();

    //Main loop
    while (this->isOpen()) {

        sf::Event event;
        while (this->pollEvent(event)) {
            //Close window when exit
            if (event.type == sf::Event::Closed) {
                this->close();
            }
            /*Cheat code (can use only if life<3)
            if ( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Comma ) {
                player.addLife();
            }
            */
        }

        this->clear();

        //drawBackground
        this->draw(spriteBackground);

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
        for( auto &enemy : enemies ){
            enemy.flash();
        }

        //Enemy shoot
        for( auto &enemy : enemies ){
            enemy.shoot(player.getCenter());
        }
        //Flash enemy'sAmmo
        Enemy::flashAmmo();


        //Move player
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*this);
        player.setPosition(sf::Vector2f(mousePosition.x - 24, mousePosition.y - 32));

        //Player shoot
        if ( shootCounter >= 30 && sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
            player.shoot();
            shootCounter = 0;
        }

        //Flash all player bullet and player itself
        player.flash();

        //Mark all hited planes
            for( auto &enemy : enemies ){
                if ( player.hitEnemy( enemy ) ) {
                    enemy.getHit();
                    if ( enemy.isDead() ) {
                        score+=deadScore [ enemy.getEnemyNo() ];
                    }
                }
            }

        //Destory all marked planes
        enemies.remove_if(
            std::mem_fun_ref(&Enemy::isDisappear)
            );

        //TEMPLY:Weather player get hit
        if( Enemy::hitPlayer( player ) ) {
            player.getHit();
        }

        //Draw all enemy
        for( auto &enemy : enemies ){
            this->draw( enemy );
        }

        //Draw all enemy bullet
        Enemy::drawAllBullet( *this );

        //Draw all player bullet and player itself
        player.draw(*this);

        //Draw score
        this->draw( getScore( scoreFont, score ) );

        //Draw life
        this->draw( getLife( promptFont, player.getLife() ) );

        this->display();

        if( player.isDisappear() ) break;

        enemy1Counter++;
        enemy2Counter++;
        shootCounter++;
    }

    //Dead:
    musicBGM.stop();
    this->setMouseCursorVisible( true );
}

bool
Sky::showStartInterface( void )
{
    sf::Text title;
    title.setFont( yaheiFont );
    title.setCharacterSize( 42 );
    title.setColor( sf::Color::Red );
    title.setString(L"打 灰 机");
    title.setPosition(
            sf::Vector2f(
                120 - title.getGlobalBounds().width / 2,
                200 - title.getGlobalBounds().height / 2
                )
            );

    sf::Text clickStartMessage;
    clickStartMessage.setFont( promptFont );
    clickStartMessage.setCharacterSize( 16 );
    clickStartMessage.setColor( sf::Color::Red );
    clickStartMessage.setString( "Click to start" );
    clickStartMessage.setPosition(
        title.getGlobalBounds().left + title.getGlobalBounds().width / 2 - clickStartMessage.getGlobalBounds().width / 2,
        title.getGlobalBounds().top + title.getGlobalBounds().height
        );

    while( this->isOpen() ) {

        sf::Event event;
        while( this->pollEvent(event) ) {
            //Close window when exit
            if( event.type == sf::Event::Closed ) {
                this->close();
                return false;
            }

            if( event.type == sf::Event::KeyPressed ||
                event.type == sf::Event::MouseButtonPressed ) {
                return true;
            }
        }
        this->clear();
        this->draw( spriteBackground );
        this->draw( title );
        this->draw( clickStartMessage );
        this->display();
    }
    return false;
}

bool
Sky::showGameOverInterface( void )
{
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

    sf::Text clickToRestartMessage;
    clickToRestartMessage.setFont( promptFont );
    clickToRestartMessage.setCharacterSize( 16 );
    clickToRestartMessage.setColor( sf::Color::Red );
    clickToRestartMessage.setString( "Click to restart" );
    clickToRestartMessage.setPosition(
        loseMessage.getGlobalBounds().left + loseMessage.getGlobalBounds().width / 2 - clickToRestartMessage.getGlobalBounds().width / 2,
        loseMessage.getGlobalBounds().top + loseMessage.getGlobalBounds().height
        );

     //Show lose message
    this->draw(loseMessage);
    this->draw(clickToRestartMessage);
    this->display();

    while ( this->isOpen() ) {

        sf::Event event;
        while (this->pollEvent(event)) {
            //Close window when exit
            if (event.type == sf::Event::Closed) {
                this->close();
                return false;
            }

            if ( event.type == sf::Event::KeyPressed ||
                 event.type == sf::Event::MouseButtonPressed ) {
                return true;
            }
        }
    }
    return false;
}
