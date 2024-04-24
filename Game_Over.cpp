#include "Game_Over.h"
#include "Game.h"

Game_Over::Game_Over(sf::Font& font, Game& game) : game(game){
    this->gameover.setFont(font);
    this->gameover.setFillColor(sf::Color::White);
    this->gameover.setString("Game Over!");
    this->gameover.setPosition((300 - this->gameover.getGlobalBounds().width)/2.f, 150.f);
    this->gameover.setCharacterSize(65);

    this->b = Button("Play Again", sf::Color::White, font, 45, 210.f, 700.f, sf::Color::Transparent);
    this->back = Button("Main Menu", sf::Color::White, font, 45, 200.f, 800.f, sf::Color::Transparent);
}

void Game_Over::update(sf::RenderWindow* target, sf::Event event){
    if(this->b.click_mouse(target, event)){
        this->game.reset_game();
        this->game.currentState = GameState::PLAYING;
    }
    if(this->back.click_mouse(target, event)){
        this->game.reset_game();
        this->game.currentState = GameState::STARTMENU;
    }

    if(this->b.contains_mouse(target)){
        this->b.hover_func();
    }else{
        this->b.reset();
    }
    if(this->back.contains_mouse(target)){
        this->back.hover_func();
    }else{
        this->back.reset();
    }
}

void Game_Over::draw(sf::RenderWindow* target){
    target->draw(this->gameover);
    this->b.draw(target);
    this->back.draw(target);

    this->game.score_text.setPosition(320, this->gameover.getPosition().y + 150);
    target->draw(this->game.score_text);
}