#include "Game.h"
#include <iostream>

Game::Game()
{
    window = nullptr;
    this->currentState = GameState::STARTMENU;
    this->startMenu = new Start_Menu(this->font, *this);
    this->gameOver = new Game_Over(this->font, *this);

    this->pipe_counter = 71;
    this->pipe_spawn_time = 70;
    this->gameover = false;
    this->monitoring = false;
    this->score = 0;
    this->start = false;

    this->load_assets();
    this->init();
}

Game::~Game()
{
    if (window != nullptr)
    {
        delete window;
    }
}

void Game::run()
{
    sf::Clock clock;
    while (window->isOpen())
    {
        sf::Time dt = clock.restart(); // get the time since last update

        switch (this->currentState)
        {
        case GameState::STARTMENU:
            this->startMenu->update(this->window, this->event);
            break;
        case GameState::PLAYING:
            this->update_game_logic(dt);
            break;
        case GameState::GAMEOVER:
            this->gameOver->update(this->window, this->event);
            break;
        default:
            break;
        }
        update(dt);
        draw(this->window);
    }
}

void Game::load_assets()
{
    // Texture
    if (!this->bg_text.loadFromFile("Content/Content/images/background-sprite.png"))
    {
        std::cerr << "Could not load background" << std::endl;
    }
    if (!this->grass_text.loadFromFile("Content/Content/images/ground-sp.png"))
    {
        std::cerr << "Could not load background" << std::endl;
    }
    if (!this->bg_night_text.loadFromFile("Content/Content/images/background-night.png"))
    {
        std::cerr << "Could not load background" << std::endl;
    }

    // Font
    if (!this->font.loadFromFile("Content/Content/fonts/flappy-font.ttf"))
    {
        std::cerr << "Could not load font" << std::endl;
    }

    // Sound
    if (!this->point_sound_buffer.loadFromFile("Content/Content/audio/point.wav"))
    {
        std::cerr << "Could not load point sound" << std::endl;
    }
    if (!this->dead_sound_buffer.loadFromFile("Content/Content/audio/hit.wav"))
    {
        std::cerr << "Could not load dead sound" << std::endl;
    }
    if (!this->jump_sound_buffer.loadFromFile("Content/Content/audio/jump.wav"))
    {
        std::cerr << "Could not load jump sound" << std::endl;
    }
}

void Game::init()
{
    gameName = "Flappy Bird";

    videoMode.height = 960;
    videoMode.width = 640;
    window = new sf::RenderWindow(videoMode, gameName);
    this->window->setFramerateLimit(60);

    // GUI
    this->bg.setTexture(this->bg_text);
    this->bg.setPosition(sf::Vector2f(0.f, -180.f));
    this->bg.setScale(1.6f, 1.6f);

    this->bg_night.setTexture(this->bg_night_text);
    this->bg_night.setPosition(sf::Vector2f(0.f, -180.f));
    this->bg_night.setScale(1.6f, 1.6f);

    this->grass1.setTexture(this->grass_text);
    this->grass2.setTexture(this->grass_text);
    this->grass1.setScale(1.6f, 1.6f);
    this->grass2.setScale(1.6f, 1.6f);
    this->grass1.setPosition(0.f, 750.f);
    this->grass2.setPosition(this->grass1.getPosition().x + this->grass1.getGlobalBounds().width, 750.f);

    this->score_text.setFont(this->font);
    this->score_text.setFillColor(sf::Color::White);
    this->score_text.setCharacterSize(60);
    this->score_text.setPosition((640 + (this->score_text.getGlobalBounds().width) / 2.f) / 2.f, 150);
    this->score_text.setString("0");

    // Sound
    this->jump_sound.setBuffer(this->jump_sound_buffer);
    this->dead_sound.setBuffer(this->dead_sound_buffer);
    this->point_sound.setBuffer(this->point_sound_buffer);
    this->point_sound.setVolume(30);
}

void Game::move_grass(sf::Time &dt)
{
    this->grass1.move(-this->move_speed * dt.asSeconds(), 0.f);
    this->grass2.move(-this->move_speed * dt.asSeconds(), 0.f);

    if (this->grass1.getGlobalBounds().left + this->grass1.getGlobalBounds().width < 0)
    {
        this->grass1.setPosition(this->grass2.getGlobalBounds().left + this->grass2.getGlobalBounds().width, 750);
    }
    if (this->grass2.getGlobalBounds().left + this->grass2.getGlobalBounds().width < 0)
    {
        this->grass2.setPosition(this->grass1.getGlobalBounds().left + this->grass1.getGlobalBounds().width, 750);
    }
}

void Game::check_collisions()
{
    if (this->pipes.size() > 0)
    {
        if (this->pipes[0].sp_down.getGlobalBounds().intersects(this->player.bird.getGlobalBounds()) ||
            this->pipes[0].sp_up.getGlobalBounds().intersects(this->player.bird.getGlobalBounds()) ||
            this->player.bird.getGlobalBounds().top >= 960)
        {
            this->gameover = true;
            this->dead_sound.play();
            this->currentState = GameState::GAMEOVER;
        }
    }
}

void Game::check_point()
{
    if (this->pipes.size() > 0)
    {
        if (!this->monitoring)
        {
            if (this->player.bird.getGlobalBounds().left > this->pipes[0].sp_down.getGlobalBounds().left &&
                this->player.getRightBound() < this->pipes[0].getBounds())
            {
                this->monitoring = true;
            }
        }
        else
        {
            if (this->player.bird.getGlobalBounds().left > (this->pipes[0].getBounds() / 2.f))
            {
                this->score++;
                this->score_text.setString(std::to_string(this->score));
                this->point_sound.play();
                this->monitoring = false;
            }
        }
    }
}

void Game::reset_game()
{
    this->player.reset_bird_position();
    this->gameover = false;
    this->score = 0;
    this->score_text.setPosition((640 + (this->score_text.getGlobalBounds().width) / 2.f) / 2.f, 150);
    this->start = false;
    this->pipes.clear();
    this->player.fall_start = false;
}

void Game::update_game_logic(sf::Time &dt)
{
    this->move_grass(dt);

    // Make pipes
    if (this->pipe_counter > this->pipe_spawn_time && this->start)
    {
        this->pipes.push_back(Pibe(dist(rd)));
        this->pipe_counter = 0;
    }
    this->pipe_counter++;

    // Move and delete pipes
    for (int i = 0; i < this->pipes.size(); i++)
    {
        this->pipes[i].update(dt);
        if (pipes[i].getBounds() < 0)
        {
            this->pipes.erase(this->pipes.begin() + i);
        }
    }

    this->player.update(dt);
    this->check_collisions();
    this->check_point();
}

void Game::update(sf::Time &dt)
{
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        if (event.key.code == sf::Keyboard::Escape)
        {
            window->close();
        }
        if (this->event.key.code == sf::Keyboard::Space && this->currentState == GameState::PLAYING)
        {
            this->player.jump(dt);
            this->jump_sound.play();
            if (!this->start)
            {
                this->start = true;
            }
            if (!this->player.fall_start)
            {
                this->player.fall_start = true;
            }
        }
    }
}

void Game::draw(sf::RenderWindow *target)
{
    window->clear();

    if (!this->gameover)
    {
        window->draw(this->bg);
    }
    else
    {
        window->draw(this->bg_night);
    }

    switch (this->currentState)
    {
    case GameState::STARTMENU:
        this->startMenu->draw(target);
        break;
    case GameState::PLAYING:
        for (Pibe &pipe : this->pipes)
        {
            window->draw(pipe.sp_down);
            window->draw(pipe.sp_up);
        }

        window->draw(this->grass1);
        window->draw(this->grass2);
        this->player.draw(this->window);
        window->draw(this->score_text);
        break;
    case GameState::GAMEOVER:
        this->gameOver->draw(target);
        break;
    default:
        break;
    }
    window->display();
}