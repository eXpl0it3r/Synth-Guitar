#pragma once

#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "Button.hpp"
#include "Synth.hpp"

#include <Thor/Resources.hpp>

#include <string>

class PlayState : public State
{
public:
    PlayState(sf::RenderWindow& window);

private:
    void process_events() final;
    void update(const sf::Time dt) final;
    void render() final;

    void load_resources();

private:
    thor::ResourceHolder<sf::Texture, std::string> m_textures;
    thor::ResourceHolder<sf::Font, std::string> m_fonts;

    Synth m_synth;

    World m_world;
    Player m_player;
    Button m_sine;
    Button m_saw;
    Button m_triangle;
    Button m_square;

    sf::Time m_count;
    sf::Text m_score;
    int m_points;

    sf::Vector2i m_direction;
    sf::Time m_pressed;
    sf::Keyboard::Key m_button;
    std::string m_level;
};