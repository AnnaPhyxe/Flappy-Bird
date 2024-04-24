#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Button
{
public:
    Button();
    Button(std::string text, sf::Color color_text, sf::Font& font, int size, float pos_x, float pos_y,
            sf::Color color_shape);

    sf::RectangleShape shape;
    sf::Text button_text;

    bool contains_mouse(sf::RenderWindow* target);
    bool click_mouse(sf::RenderWindow* target, sf::Event event);
    void hover_func();
    void reset();
    void draw(sf::RenderWindow* target);
};