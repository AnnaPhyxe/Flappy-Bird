#include "Pibe.h"
sf::Texture Pibe::pipe_up; 
sf::Texture Pibe::pipe_down;

Pibe::Pibe(int y_pos){
    if(!this->loaded){
        this->load_textures();
    }

    this->pipe_dist = 700;
    this->move_speed = 400;

    this->sp_up.setTexture(pipe_up);
    this->sp_down.setTexture(pipe_down);
    this->sp_up.setPosition(640, y_pos);
    this->sp_down.setPosition(640, y_pos - this->pipe_dist - this->sp_up.getGlobalBounds().height);
    this->sp_down.setScale(7.f, 7.f);
    this->sp_up.setScale(7.f, 7.f);
}

void Pibe::load_textures(){
    if(!pipe_down.loadFromFile("Content/Content/images/pibe/down.png")){
        std::cerr << "Could not load pipe down" << std::endl;
    }
    if(!pipe_up.loadFromFile("Content/Content/images/pibe/up.png")){
        std::cerr << "Could not load pipe up" << std::endl;
    }
    this->loaded = true;
}

float Pibe::getBounds(){
    return this->sp_down.getGlobalBounds().left + this->sp_down.getGlobalBounds().width;
}

void Pibe::update(sf::Time& dt){
    this->sp_up.move(-this->move_speed * dt.asSeconds(), 0.f);
    this->sp_down.move(-this->move_speed * dt.asSeconds(), 0.f);
}