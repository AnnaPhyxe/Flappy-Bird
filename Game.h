#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include "Bird.h"
#include "Pibe.h"
#include "Start_Menu.h"
#include "Game_Over.h"

enum class GameState{
    STARTMENU, PLAYING, GAMEOVER
};

class Game{
    public:
        Game();
        ~Game();

        bool gameover;
        sf::Event event;
        sf::VideoMode videoMode;
        GameState currentState;
        sf::Text score_text;
        Bird player;

        void run();
        void reset_game();
    private:
        sf::RenderWindow *window;
        std::string gameName;

        Start_Menu* startMenu;
        Game_Over* gameOver;

        sf::Sprite bg, bg_night, grass1, grass2;
        sf::Texture bg_text, bg_night_text, grass_text;
        sf::Font font;

        sf::RectangleShape select_line;
        sf::RectangleShape selected;

        sf::Sound point_sound;
        sf::SoundBuffer point_sound_buffer;
        sf::Sound jump_sound;
        sf::SoundBuffer jump_sound_buffer;
        sf::Sound dead_sound;
        sf::SoundBuffer dead_sound_buffer;

        const int move_speed = 270;
        int pipe_counter;
        int pipe_spawn_time;
        bool monitoring;
        bool start;
        int score;
        int pipes_present;

        std::vector<Pibe> pipes;
        std::random_device rd;
        std::uniform_int_distribution<int> dist{255,550};

        void init();
        void load_assets();
        void move_grass(sf::Time& dt);
        void check_collisions();
        void check_point();
        void update_game_logic(sf::Time& dt); //handles the update of moving grass, pipes, collisions, score etc.
        void update(sf::Time& dt);
        void draw(sf::RenderWindow* target);
};