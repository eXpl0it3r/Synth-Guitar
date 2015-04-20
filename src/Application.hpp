#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Application
{
public:
    Application();

    void run();

private:
    sf::RenderWindow m_window;

    sf::Music m_music;
};
