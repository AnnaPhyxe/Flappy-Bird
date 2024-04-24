#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Pibe
{
public:
    Pibe(int y_pos);
    sf::Sprite sp_down;
    sf::Sprite sp_up;
    static sf::Texture pipe_up;
    static sf::Texture pipe_down;
    bool loaded = false;
    void update(sf::Time&);
    float getBounds();
    void load_textures();

private:
    int pipe_dist, move_speed;
};