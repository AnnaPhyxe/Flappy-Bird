#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"

class Game;

class Game_Over
{
public:
    Game_Over(sf::Font& font, Game& game);

    void update(sf::RenderWindow* target, sf::Event event);
    void draw(sf::RenderWindow* target);
private:
    sf::Text gameover;
    Button b;
    Button back;
    Game& game;
};