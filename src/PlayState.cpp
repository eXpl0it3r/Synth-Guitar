#include "PlayState.hpp"

#include "FinalState.hpp"

PlayState::PlayState(sf::RenderWindow& window)
: State{window}
, m_world{m_textures}
, m_player{m_world.tile_size()}
, m_points{1000}
, m_button{sf::Keyboard::Unknown}
, m_level{"res/level01.json"}
{
    load_resources();

    m_player.texture(m_textures["player"]);
    m_player.setPosition(m_world.player_spawn());

    m_sine.texture(m_textures["sine"]);
    m_sine.setPosition({0.f, 640.f});
    m_saw.texture(m_textures["saw"]);
    m_saw.setPosition({128.f, 640.f});
    m_triangle.texture(m_textures["triangle"]);
    m_triangle.setPosition({256.f, 640.f});
    m_square.texture(m_textures["square"]);
    m_square.setPosition({384.f, 640.f});

    m_score.setFont(m_fonts["font"]);
    m_score.setCharacterSize(50);
    m_score.setPosition({750, 670});
    m_score.setString("0");
    m_score.setColor(sf::Color(130, 130, 130));
}

void PlayState::process_events()
{
    sf::Event event;

    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                m_button = event.key.code;

                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    m_direction = {0, -1};
                    break;
                case sf::Keyboard::Down:
                    m_direction = {0, 1};
                    break;
                case sf::Keyboard::Right:
                    m_direction = {1, 0};
                    break;
                case sf::Keyboard::Left:
                    m_direction = {-1, 0};
                    break;
                }
                break;
        }
    }
}

void PlayState::update(const sf::Time dt)
{
    process_events();

    if(!m_world.check_win(m_player.getPosition()))
    {
        m_count += dt;

        if(m_count > sf::seconds(1.f))
        {
            m_points -= 73;
            m_count = sf::Time::Zero;
        }

        if(m_pressed <= sf::seconds(1.f))
        {
            m_pressed += dt;
            m_button = sf::Keyboard::Unknown;
        }
        else if(m_button == sf::Keyboard::A || m_button == sf::Keyboard::Q) // Support French keyboard layouts
        {
            m_player.on_play_sine(sf::seconds(1.f));
            m_synth.play(Synth::SINE, 440.f, sf::seconds(1.f));

            if(m_world.check_walls(m_player.getPosition(), Synth::SINE, 440.f))
                m_points += 70;
            else
                m_points -= 100;

            m_pressed = sf::Time::Zero;
            m_button = sf::Keyboard::Unknown;
            m_sine.on_press();
        }
        else if(m_button == sf::Keyboard::D)
        {
            m_player.on_play_triangle(sf::seconds(1.f));
            m_synth.play(Synth::TRIANGLE, 440.f, sf::seconds(1.f));

            if(m_world.check_walls(m_player.getPosition(), Synth::TRIANGLE, 440.f))
                m_points += 80;
            else
                m_points -= 100;

            m_pressed = sf::Time::Zero;
            m_button = sf::Keyboard::Unknown;
            m_triangle.on_press();
        }
        else if(m_button == sf::Keyboard::S)
        {
            m_player.on_play_saw(sf::seconds(1.f));
            m_synth.play(Synth::SAW, 440.f, sf::seconds(1.f));

            if(m_world.check_walls(m_player.getPosition(), Synth::SAW, 440.f))
                m_points += 90;
            else
                m_points -= 100;

            m_pressed = sf::Time::Zero;
            m_button = sf::Keyboard::Unknown;
            m_saw.on_press();
        }
        else if(m_button == sf::Keyboard::F)
        {
            m_player.on_play_square(sf::seconds(1.f));
            m_synth.play(Synth::SQUARE, 440.f, sf::seconds(1.f));

            if(m_world.check_walls(m_player.getPosition(), Synth::SQUARE, 440.f))
                m_points += 100;
            else
                m_points -= 100;

            m_pressed = sf::Time::Zero;
            m_button = sf::Keyboard::Unknown;
            m_square.on_press();
        }
        else
        {
            m_sine.on_release();
            m_saw.on_release();
            m_triangle.on_release();
            m_square.on_release();
        }

        m_player.update(dt);
        m_sine.update(dt);
        m_saw.update(dt);
        m_triangle.update(dt);
        m_square.update(dt);

        if(!m_world.check_collision(m_direction, m_player.getPosition()))
        {
            if(m_direction != sf::Vector2i(0, 0))
                m_points -= 10;

            m_player.move(sf::Vector2f(m_direction * static_cast<int>(m_world.tile_size())));
            m_direction = {0, 0}; // Move once
        }

        // Don't be evil
        if(m_points < 0)
            m_points = 0;

        m_score.setString(std::to_string(m_points));
    }
    else
    {
        if(m_level == "res/level01.json")
            m_level = "res/level02.json";
        else if(m_level == "res/level02.json")
            m_level = "res/level03.json";
        else if(m_level == "res/level03.json")
            m_level = "res/level04.json";
        else if(m_level == "res/level04.json")
            m_level = "res/level05.json";
        else
            m_next = std::unique_ptr<FinalState>(new FinalState(m_window, m_points));

        m_world.next_level(m_level);
        m_player.setPosition(m_world.player_spawn());
        m_points += 1000;
        m_count = sf::Time::Zero;
    }
}

void PlayState::render()
{
    m_window.clear(sf::Color(0, 48, 65));
    m_window.draw(m_world);
    m_window.draw(m_player);
    m_window.draw(m_sine);
    m_window.draw(m_saw);
    m_window.draw(m_triangle);
    m_window.draw(m_square);
    m_window.draw(m_score);
    m_window.display();
}

void PlayState::load_resources()
{
    m_textures.acquire("player", thor::Resources::fromFile<sf::Texture>("res/player.png"));
    m_textures.acquire("sine", thor::Resources::fromFile<sf::Texture>("res/button-sine.png"));
    m_textures.acquire("saw", thor::Resources::fromFile<sf::Texture>("res/button-saw.png"));
    m_textures.acquire("triangle", thor::Resources::fromFile<sf::Texture>("res/button-triangle.png"));
    m_textures.acquire("square", thor::Resources::fromFile<sf::Texture>("res/button-square.png"));
    m_fonts.acquire("font", thor::Resources::fromFile<sf::Font>("res/DejaVuSansMono-Bold.ttf"));
}