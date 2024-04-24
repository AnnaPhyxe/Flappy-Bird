#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

enum class COLOR{
    DEFAULT, PURPLE, BLUE, GREEN
};

class Bird
{
public:
    Bird();

    sf::Sprite bird;
    COLOR bird_color;
    bool fall_start;
    void update(sf::Time& dt);
    void draw(sf::RenderTarget* target);
    void jump(sf::Time& dt);
    float getRightBound();
    void reset_bird_position();

    sf::Texture textures[3]; //default
    sf::Texture textures_purple[3];
    sf::Texture textures_green[3];
    sf::Texture textures_blue[3];

private:
    int gravity;
    int jump_speed;
    int anim_counter;
    int texture_switch;
    float y_velocity;
    bool fly;

    void init();
    void set_fly(bool fly);
};