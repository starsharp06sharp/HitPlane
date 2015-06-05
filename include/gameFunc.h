#ifndef GAMEFUNC_H_INCLUDED
#define GAMEFUNC_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <ctime>

#include "Moveable.h"
#include "Plane.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

sf::Text&
getScore(sf::Font& font, unsigned long long score);

sf::Text&
getLife(sf::Font& font, int life);

#endif // GAMEFUNC_H_INCLUDED
