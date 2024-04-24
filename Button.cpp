#include "Button.h"

Button::Button(){

}

Button::Button(std::string text, sf::Color color_text, sf::Font& font, int size, float pos_x, float pos_y,
            sf::Color color_shape){
                this->button_text.setString(text);
                this->button_text.setFillColor(color_text);
                this->button_text.setFont(font);
                this->button_text.setCharacterSize(size);
                this->button_text.setPosition(pos_x, pos_y);

                this->shape.setFillColor(color_shape);
                this->shape.setSize(sf::Vector2f(text.length() * 22, size * 1.6));
                this->shape.setPosition(this->button_text.getPosition().x, this->button_text.getPosition().y);
}

bool Button::contains_mouse(sf::RenderWindow* target){
    sf::Vector2i pos = sf::Mouse::getPosition(*target);
    return this->shape.getGlobalBounds().contains(pos.x, pos.y);
}

bool Button::click_mouse(sf::RenderWindow* target, sf::Event event){
    return this->contains_mouse(target) && event.type == sf::Event::MouseButtonPressed;
}

void Button::hover_func(){
    this->button_text.setFillColor(sf::Color(255, 128, 13, 255));
}

void Button::reset(){
    this->button_text.setFillColor(sf::Color::White);
}

void Button::draw(sf::RenderWindow* target){
    target->draw(this->shape);
    target->draw(this->button_text);
}