#include "MenuState.hpp"
#include "PlayState.hpp"

#include <cmath>

MenuState::MenuState(sf::RenderWindow& window)
: State{window}
, m_selected{0}
{
    load_resources();

    m_play.texture(m_textures["play"]);
    m_play.setPosition({112.f, 122.f});
    m_exit.texture(m_textures["exit"]);
    m_exit.setPosition({112.f, 446.f});

    m_play.on_enter();
    m_mouse = sf::Mouse::getPosition(m_window);
}

void MenuState::process_events()
{
    sf::Event event;

    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseMoved:
                if(std::abs(m_mouse.x - event.mouseMove.x) > 5.f || std::abs(m_mouse.y - event.mouseMove.y) > 5.f)
                {
                    if(m_play.contains(m_window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y})))
                    {
                        m_play.on_enter();
                        m_selected = 0;
                    }
                    else
                        m_play.on_leave();
                    if(m_exit.contains(m_window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y})))
                    {
                        m_exit.on_enter();
                        m_selected = 1;
                    }
                    else
                        m_exit.on_leave();
                }
                m_mouse = {event.mouseMove.x, event.mouseMove.y};
                break;
            case sf::Event::MouseButtonReleased:
                if(m_play.contains(m_window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})))
                {
                    m_next = std::unique_ptr<PlayState>(new PlayState{m_window});
                }
                else if(m_exit.contains(m_window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y})))
                    m_window.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Up)
                {
                    m_play.on_enter();
                    m_exit.on_leave();
                    m_selected = 0;
                }
                else if(event.key.code == sf::Keyboard::Down)
                {
                    m_exit.on_enter();
                    m_play.on_leave();
                    m_selected = 1;
                }
                else if(event.key.code == sf::Keyboard::Return)
                {
                    if(m_selected == 0)
                        m_next = std::unique_ptr<PlayState>(new PlayState{m_window});
                    else
                        m_window.close();
                }
                break;
        }
    }
}

void MenuState::update(const sf::Time dt)
{
    process_events();

    m_play.update(dt);
    m_exit.update(dt);
}

void MenuState::render()
{
    m_window.clear(sf::Color(0, 48, 65));
    m_window.draw(m_play);
    m_window.draw(m_exit);
    m_window.display();
}

void MenuState::load_resources()
{
    m_textures.acquire("play", thor::Resources::fromFile<sf::Texture>("res/play.png"));
    m_textures.acquire("exit", thor::Resources::fromFile<sf::Texture>("res/exit.png"));
}