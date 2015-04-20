#pragma once

#include "State.hpp"
#include "PlayButton.hpp"
#include "ExitButton.hpp"

#include <Thor/Resources.hpp>

#include <string>

class FinalState : public State
{
public:
    FinalState(sf::RenderWindow& window, int points);

private:
    void process_events() final;
    void update(const sf::Time dt) final;
    void render() final;

    void load_resources();

private:
    thor::ResourceHolder<sf::Texture, std::string> m_textures;
    thor::ResourceHolder<sf::Font, std::string> m_fonts;

    int m_points;
    sf::Text m_score;

    PlayButton m_play;
    ExitButton m_exit;

    sf::Vector2i m_mouse;
    int m_selected;
};