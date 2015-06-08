#include "gameFunc.h"

sf::Text&
getScore(sf::Font& font, unsigned long long score)
{
    static sf::Text scoreText;
    scoreText.setFont( font );
    scoreText.setCharacterSize( 36 * SCALE );
    scoreText.setColor( sf::Color::Blue );

    char scoreStr[40];
    sprintf( scoreStr, "Score : %I64u", score );
    scoreText.setString( scoreStr );

    return scoreText;
}

sf::Text&
getLife(sf::Font& font, int life)
{
    static sf::Text lifeText;
    lifeText.setFont( font );
    lifeText.setCharacterSize( 60 *SCALE );
    lifeText.setColor( sf::Color::Red );

    //Draw life
    wchar_t lifeStr[20];
    int i;
    for (i = 0; i < life; i++) lifeStr[i] = L'♥';
    lifeStr[i] = '\0';
    lifeText.setString( lifeStr );
    lifeText.setPosition(
        sf::Vector2f(
            WINDOW_SIZE_X - lifeText.getGlobalBounds().width - 5,//校正
            0 - 10//校正
            )
        );

    return lifeText;
}
