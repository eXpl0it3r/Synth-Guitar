#pragma once

#include "State.hpp"
#include "PlayButton.hpp"
#include "ExitButton.hpp"

#include <Thor/Resources.hpp>

#include <string>

class MenuState : public State
{
public:
    MenuState(sf::RenderWindow& window);

private:
    void process_events() final;
    void update(const sf::Time dt) final;
    void render() final;

    void load_resources();

private:
    thor::ResourceHolder<sf::Texture, std::string> m_textures;

    PlayButton m_play;
    ExitButton m_exit;

    sf::Vector2i m_mouse;
    int m_selected;
};