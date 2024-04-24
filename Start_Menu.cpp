#include "Start_Menu.h"
#include "Game.h"

Start_Menu::Start_Menu(sf::Font& font, Game& game) : game(game){
    this->title.setFont(font);
    this->title.setFillColor(sf::Color::White);
    this->title.setString("Flappy Bird");
    this->title.setPosition((300 - this->title.getGlobalBounds().width)/2.f, 150);
    this->title.setCharacterSize(65);

    this->b = Button("Play", sf::Color::White, font, 45, 270.f, 300.f, sf::Color::Transparent);

    this->select_bird[0].setTexture(this->game.player.textures[1]); // default
    this->select_bird[1].setTexture(this->game.player.textures_purple[1]);
    this->select_bird[2].setTexture(this->game.player.textures_blue[1]);
    this->select_bird[3].setTexture(this->game.player.textures_green[1]);

    this->select_bird[0].setScale(7, 7);
    this->select_bird[1].setScale(7, 7);
    this->select_bird[2].setScale(7, 7);
    this->select_bird[3].setScale(7, 7);

    this->select_bird[0].setPosition(65.f, 750.f);
    this->select_bird[1].setPosition(this->select_bird[0].getPosition().x + this->select_bird[0].getGlobalBounds().width + 30.f, 750.f);
    this->select_bird[2].setPosition(this->select_bird[1].getPosition().x + this->select_bird[1].getGlobalBounds().width + 30.f, 750.f);
    this->select_bird[3].setPosition(this->select_bird[2].getPosition().x + this->select_bird[2].getGlobalBounds().width + 30.f, 750.f);

    this->line.setFillColor(sf::Color::White);
    this->line.setSize(sf::Vector2f(this->select_bird[0].getGlobalBounds().width, 5.f));
    this->box.setFillColor(sf::Color::White);
    this->box.setSize(sf::Vector2f(this->select_bird[0].getGlobalBounds().width, this->select_bird[0].getGlobalBounds().height));
}

void Start_Menu::update(sf::RenderWindow* target, sf::Event event){
    if(this->b.click_mouse(target, event)){
        this->game.currentState = GameState::PLAYING;
    }
    if(this->b.contains_mouse(target)){
        this->b.hover_func();
    }else{
        this->b.reset();
    }

    sf::Vector2i pos = sf::Mouse::getPosition(*target);
    this->draw_line = true;

    if(this->select_bird[0].getGlobalBounds().contains(pos.x, pos.y)){
        this->line.setPosition(this->select_bird[0].getPosition().x, 750 + this->select_bird[0].getGlobalBounds().height + 5);
    }else if(this->select_bird[1].getGlobalBounds().contains(pos.x, pos.y)){
        this->line.setPosition(this->select_bird[1].getPosition().x, 750 + this->select_bird[1].getGlobalBounds().height + 5);
    }else if(this->select_bird[2].getGlobalBounds().contains(pos.x, pos.y)){
        this->line.setPosition(this->select_bird[2].getPosition().x, 750 + this->select_bird[2].getGlobalBounds().height + 5);
    }else if(this->select_bird[3].getGlobalBounds().contains(pos.x, pos.y)){
        this->line.setPosition(this->select_bird[3].getPosition().x, 750 + this->select_bird[3].getGlobalBounds().height + 5);
    }else{
        this->draw_line = false;
    }

    if(event.mouseButton.button == sf::Mouse::Left){
        if(this->select_bird[0].getGlobalBounds().contains(pos.x, pos.y)){
            this->game.player.bird_color = COLOR::DEFAULT;
            this->box.setPosition(this->select_bird[0].getPosition().x,this->select_bird[0].getPosition().y);
        }else if(this->select_bird[1].getGlobalBounds().contains(pos.x, pos.y)){
            this->game.player.bird_color = COLOR::PURPLE;
            this->box.setPosition(this->select_bird[1].getPosition().x,this->select_bird[1].getPosition().y);
        }else if(this->select_bird[2].getGlobalBounds().contains(pos.x, pos.y)){
            this->game.player.bird_color = COLOR::BLUE;
            this->box.setPosition(this->select_bird[2].getPosition().x,this->select_bird[2].getPosition().y);
        }else if(this->select_bird[3].getGlobalBounds().contains(pos.x, pos.y)){
            this->game.player.bird_color = COLOR::GREEN;
            this->box.setPosition(this->select_bird[3].getPosition().x,this->select_bird[3].getPosition().y);
        }
    }
}

void Start_Menu::draw(sf::RenderWindow* target){
    target->draw(this->title);
    this->b.draw(target);
    if(this->draw_line){
        target->draw(this->line);
    }
    if(!this->box.getPosition().x == 0){
        target->draw(this->box);
    }

    target->draw(this->select_bird[0]);
    target->draw(this->select_bird[1]);
    target->draw(this->select_bird[2]);
    target->draw(this->select_bird[3]);
}