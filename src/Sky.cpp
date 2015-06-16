#include "Sky.h"

Sky::Sky() :
    sf::RenderWindow(
        sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y),
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

    //Init Lvlup sound
    if( !bufferLvlup.loadFromFile( "achievement.ogg" ) ){
        //Exit when sound file is broken
        exit(-1);
    }
    soundLvlup.setBuffer( bufferLvlup );
    soundLvlup.setVolume( 100 );

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

bool
Sky::mainLoop( void )
{

    //Init player
    Player player = Player(
            sf::IntRect(0, 99, 102, 126),
            sf::Vector2f(SCALE, SCALE),
            sf::Vector2f(0, 0),
            3
            );

    score = 0;
    level = 1;
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

            //Auto resize
            if ( event.type == sf::Event::Resized ) {
                this->resize( event.size.width, event.size.height );
            }

            if ( event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Comma ) {
                player.addLife();
            }

            if( event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::P ) {
                    this->pause( enemies, player );
                }
        }

       //Add enemy if it is the right time
        enemies.addEnemy( level );

        //flash all enemies and theirs bullets
        enemies.flashAll( player );

        //Move player
        sf::Vector2i mousePosition = sf::Mouse::getPosition(*this);
        player.setPosition( sf::Vector2f( mousePosition.x / nowSCALE - 48, mousePosition.y / nowSCALE - 64) * SCALE );

        //Player shoot
        if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) ) {
            player.shoot();
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

        this->drawGameInterface( enemies, player );


        this->display();

        if( player.isDisappear() ) break;

        shootCounter++;
    }
    //Dead:
    musicBGM.stop();
    this->setMouseCursorVisible( true );
    return this->showGameOverInterface( enemies, player );
}

bool
Sky::showStartInterface( void )
{
    Message title(
        L"打 灰 机",
        yaheiFont,
        84 * SCALE,
        sf::Color::Red,
        Pos::Hmiddle + Pos::Vmiddle
        );

    Message clickStartMessage(
        L"Click to start",
        promptFont,
        32 * SCALE,
        sf::Color::Red,
        Driect::Down,
        title);

    while( this->isOpen() ) {

        sf::Event event;
        while( this->pollEvent(event) ) {
            //Close window when exit
            if( event.type == sf::Event::Closed ) {
                this->close();
                return false;
            }
            //Auto resize
            if ( event.type == sf::Event::Resized ) {
                this->resize( event.size.width, event.size.height );
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
Sky::showGameOverInterface(
    Enemies& enemies,
    Player& player
    )
{
    Message loseMessage(
        L"GAME OVER",
        promptFont,
        84 * SCALE,
        sf::Color::Red,
        Pos::Hmiddle + Pos::Vmiddle
        );

    Message clickToRestartMessage(
        L"Click to restart",
        promptFont,
        32 * SCALE,
        sf::Color::Red,
        Driect::Down,
        loseMessage
        );

    while ( this->isOpen() ) {

        sf::Event event;
        while (this->pollEvent(event)) {
            //Close window when exit
            if (event.type == sf::Event::Closed) {
                this->close();
                return false;
            }
            //Auto resize
            if ( event.type == sf::Event::Resized ) {
                this->resize( event.size.width, event.size.height );
            }
            if ( event.type == sf::Event::KeyPressed ||
                 event.type == sf::Event::MouseButtonPressed ) {
                return true;
            }
        }
        this->clear();
        this->drawGameInterface( enemies,player );
        this->draw(loseMessage);
        this->draw(clickToRestartMessage);
        this->display();
    }
    return false;
}

void
Sky::pause(
    Enemies& enemies,
    Player& player
)
{
    musicBGM.pause();
    this->setMouseCursorVisible( true );

    Message pausedMessage(
        L"Press 'P' to resume",
        promptFont,
        40 * SCALE,
        sf::Color::Red,
        Pos::Vmiddle + Pos::Hmiddle
        );

    while( this->isOpen() ) {
        sf::Event event;
        while( this->pollEvent( event ) ){
            //Close window when exit
            if (event.type == sf::Event::Closed) {
                this->close();
                return;
            }
            //Auto resize
            if ( event.type == sf::Event::Resized ) {
                this->resize( event.size.width, event.size.height );
            }
            //Return when pause are pressed
            if( event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::P ) {
                    //Recover before return
                    this->setMouseCursorVisible( false );
                    musicBGM.play();
                    return;
            }
            this->clear();
            this->drawGameInterface( enemies, player );
            this->draw( pausedMessage );
            this->display();
        }
        //Draw nothing
    }
}

Message
Sky::getScore( void )
{
    wchar_t scoreStr[40];
    swprintf( scoreStr, L"Score : %I64u", score );
    Message scoreMessage(
        scoreStr,
        this->scoreFont,
        36 * SCALE,
        sf::Color::Blue,
        Pos::Top + Pos::Left
        );
    return scoreMessage;
}

Message
Sky::getLife(
    int life
    )
{
    wchar_t lifeStr[20];
    int i;
    for (i = 0; i < life; i++) lifeStr[i] = L'♥';
    lifeStr[i] = '\0';
    Message lifeMessage(
        lifeStr,
        this->promptFont,
        60 *SCALE,
        sf::Color::Red,
        Pos::Top + Pos::Right
        );
    lifeMessage.setPosition(
        lifeMessage.getPosition() - sf::Vector2f( 10, 20 ) * SCALE
        );
    return lifeMessage;
}

Message
Sky::getLevel( void )
{
    int nowLevel = 1 + score / 25;
    if ( nowLevel > level ) {
        //Level up
        soundLvlup.play();
        level = nowLevel;
    }
    wchar_t levelStr[40];
    swprintf( levelStr, L"Level:%u", level );

    Message levelMessage(
        levelStr,
        this->scoreFont,
        36 * SCALE,
        sf::Color::Blue,
        Pos::Bottom + Pos::Left
        );

    levelMessage.setPosition(
        levelMessage.getPosition() + sf::Vector2f( 0, -15 ) * SCALE
        );

    return levelMessage;
}

void
Sky::resize(
    int newX,
    int newY
    )
{
    nowSCALE = newY / 800.0;
    this->setSize(
        sf::Vector2u(
            480 * nowSCALE,
            800 * nowSCALE
            )
        );
}

void
Sky::drawGameInterface(
    Enemies& enemies,
    Player& player
    )
{
    //drawBackground
    this->draw( this->spriteBackground );

    //Draw all enemy
    enemies.draw( *this );

    //Draw all enemy bullet
    Enemy::drawAllBullet( *this );

    //Draw all player bullet and player itself
    player.draw( *this );

    //Draw score
    this->draw( this->getScore() );

    //Draw life
    this->draw( this->getLife( player.getLife() ) );

    //Draw level
    this->draw( this->getLevel() );
}
