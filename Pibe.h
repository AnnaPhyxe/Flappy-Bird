#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bird.h"

class Pibe
{
public:
    Pibe(int y_pos);
    sf::Sprite sp_down;
    sf::Sprite sp_up;
    static sf::Texture pipe_up;
    static sf::Texture pipe_down;
    bool loaded = false;
    bool point_given;
    int pibe_passed(Bird &player);
    void update(sf::Time&);
    float getRightBounds();
    void load_textures();

private:
    int pipe_dist, move_speed;
};