#include "Bird.h"

Bird::Bird(){
    this->gravity = 30;
    this->jump_speed = 450;
    this->anim_counter = 0;
    this->fall_start = false;
    this->bird_color = COLOR::DEFAULT;

    this->init();

    //Default
    if(!this->textures[0].loadFromFile("Content/Content/images/bird/gul_down1.png")){
        std::cerr << "Could not load downflap" << std::endl;
    }
    if(!this->textures[1].loadFromFile("Content/Content/images/bird/gul_mid.png")){
        std::cerr << "Could not load midflap" << std::endl;
    }
    if(!this->textures[2].loadFromFile("Content/Content/images/bird/gul_up.png")){
        std::cerr << "Could not load upflap" << std::endl;
    }

    //Purple
    if(!this->textures_purple[0].loadFromFile("Content/Content/images/purple_bird/lilla_down1.png")){
        std::cerr << "Could not load purple downflap" << std::endl;
    }
    if(!this->textures_purple[1].loadFromFile("Content/Content/images/purple_bird/lilla_mid.png")){
        std::cerr << "Could not load purple midflap" << std::endl;
    }
    if(!this->textures_purple[2].loadFromFile("Content/Content/images/purple_bird/lilla_up1.png")){
        std::cerr << "Could not load purple upflap" << std::endl;
    }

    //Blue
    if(!this->textures_blue[0].loadFromFile("Content/Content/images/blue_bird/blue_down1.png")){
        std::cerr << "Could not load blue downflap" << std::endl;
    }
    if(!this->textures_blue[1].loadFromFile("Content/Content/images/blue_bird/blu_mid.png")){
        std::cerr << "Could not load blue midflap" << std::endl;
    }
    if(!this->textures_blue[2].loadFromFile("Content/Content/images/blue_bird/blue_up.png")){
        std::cerr << "Could not load blue upflap" << std::endl;
    }

    //Green
    if(!this->textures_green[0].loadFromFile("Content/Content/images/green_bird/green_down1.png")){
        std::cerr << "Could not load green downflap" << std::endl;
    }
    if(!this->textures_green[1].loadFromFile("Content/Content/images/green_bird/green_mid.png")){
        std::cerr << "Could not load green midflap" << std::endl;
    }
    if(!this->textures_green[2].loadFromFile("Content/Content/images/green_bird/green_up.png")){
        std::cerr << "Could not load green upflap" << std::endl;
    }
}

void Bird::init(){
    this->bird.setScale(6.5f, 6.5f);
    this->reset_bird_position();
}

void Bird::set_fly(bool fly){
    this->fly = fly;
}

void Bird::reset_bird_position(){
    this->bird.setPosition((320 - this->bird.getGlobalBounds().width) / 2.f, 300);
    this->y_velocity = 0;
}

void Bird::jump(sf::Time& dt){
    this->y_velocity = -this->jump_speed * dt.asSeconds();
}

float Bird::getRightBound(){
    return this->bird.getGlobalBounds().left + this->bird.getGlobalBounds().width;
}

void Bird::update(sf::Time& dt){
    this->anim_counter++;

    if(this->anim_counter == 5){
        this->texture_switch = (this->texture_switch + 1) % 3; //cycles through bird sprites
        switch(this->bird_color){
            case COLOR::DEFAULT: 
                this->bird.setTexture(this->textures[this->texture_switch]);
                break;
            case COLOR::BLUE:
                this->bird.setTexture(this->textures_blue[this->texture_switch]);
                break;
            case COLOR::PURPLE: 
                this->bird.setTexture(this->textures_purple[this->texture_switch]);
                break;
            case COLOR::GREEN: 
                this->bird.setTexture(this->textures_green[this->texture_switch]);
                break;
        }
        
        this->anim_counter = 0;
    }

    if(this->fall_start){
        this->y_velocity += this->gravity * dt.asSeconds();
        this->bird.move(0, this->y_velocity);
    }
}

void Bird::draw(sf::RenderTarget* target){
    target->draw(this->bird);
}