#include "Sky.h"

#include "gameFunc.h"

Sky::Sky() :
    sf::RenderWindow(
        sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y),
        "HitPlane By L.Zheng",
        sf::Style::Close
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
    this->spriteBackground.setScale(sf::Vector2f(SCALE, SCALE));
}

void
Sky::initMusic( void )
{
    //Create BGM
    if (!this->musicBGM.openFromFile("TURKY.WAV")) {
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
            sf::Vector2f(SCALE, SCALE),
            sf::Vector2f(0, 0),
            3
            );

    unsigned long long score = 0;
    unsigned shootCounter = 0;
    Enemies enemies;


    srand( (unsigned)time(NULL) );
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
            //Close window when esc is pressed
            if ( event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Escape ) {
                this->close();
            }

            if ( event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Comma ) {
                player.addLife();
            }

            if( event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::P ) {
                    this->pause();
                }
        }

       //Add enemy if it is the right time
        enemies.addEnemy();

        //flash all enemies and theirs bullets
        enemies.flashAll( player );

        //Move player
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*this);
        player.setPosition(sf::Vector2f(mousePosition.x - 48 * SCALE, mousePosition.y - 64 * SCALE));

        //Player shoot
        if ( shootCounter >= 30 && sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
            player.shoot();
            shootCounter = 0;
        }

        //Flash all player bullet and player itself
        player.flash();

        //Judge if enemies hitted by player's bullet
        score += enemies.judge( player );

        //Weather player get hit
        if( enemies.hit( player ) ) {
            player.getHit();
        }

        this->clear();

        //drawBackground
        this->draw(spriteBackground);

        //Draw all enemy
        enemies.draw( *this );

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
    title.setCharacterSize( 84 *SCALE );
    title.setColor( sf::Color::Red );
    title.setString(L"打 灰 机");
    title.setPosition(
            sf::Vector2f(
                240 * SCALE - title.getGlobalBounds().width / 2,
                400 * SCALE - title.getGlobalBounds().height / 2
                )
            );

    sf::Text clickStartMessage;
    clickStartMessage.setFont( promptFont );
    clickStartMessage.setCharacterSize( 32 * SCALE );
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
    loseMessage.setCharacterSize( 84 * SCALE );
    loseMessage.setColor( sf::Color::Red );
    loseMessage.setString("GAME OVER");
    loseMessage.setPosition(
        sf::Vector2f(
            240 * SCALE - loseMessage.getGlobalBounds().width / 2,
            400 * SCALE - loseMessage.getGlobalBounds().height / 2
            )
        );

    sf::Text clickToRestartMessage;
    clickToRestartMessage.setFont( promptFont );
    clickToRestartMessage.setCharacterSize( 32 *SCALE );
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

void
Sky::pause( void )
{
    musicBGM.pause();
    this->setMouseCursorVisible( true );

    sf::Text pausedMessage;
    pausedMessage.setFont( promptFont );
    pausedMessage.setCharacterSize( 40 *SCALE );
    pausedMessage.setColor( sf::Color::Red );
    pausedMessage.setString( "Press 'P' to resume" );
    pausedMessage.setPosition(
        240 * SCALE - pausedMessage.getGlobalBounds().width / 2,
        400 * SCALE - pausedMessage.getGlobalBounds().height / 2
        );
    this->draw( pausedMessage );
    this->display();

    while( this->isOpen() ) {
        sf::Event event;
        while( this->pollEvent( event ) ){
            //Close window when exit
            if (event.type == sf::Event::Closed) {
                this->close();
                return;
            }
            //Return when pause are pressed
            if( event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::P ) {
                    //Recover before return
                    this->setMouseCursorVisible( false );
                    musicBGM.play();

                    return;
            }
        }
        //Draw nothing
    }
}
