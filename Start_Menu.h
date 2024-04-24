#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.h"
#include "Bird.h"

class Game;

class Start_Menu
{
public:
    Start_Menu(sf::Font& font, Game& game);

    void update(sf::RenderWindow* target, sf::Event event);
    void draw(sf::RenderWindow* target);

private:
    bool draw_line;
    sf::RectangleShape line, box;
    sf::Sprite select_bird[4];

    sf::Text title;
    Button b;
    Game& game;
};