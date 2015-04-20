#pragma once

#include <SFML/Audio.hpp>

#include <deque>
#include <map>

const float PI = 3.14159265359;
const float TAU = 2*PI;

class Synth
{
public:
    enum Type
    {
        SINE,
        SAW,
        TRIANGLE,
        SQUARE
    };

public:
    Synth();

    void play(Type type, float frequency, sf::Time duration);

private:
    sf::SoundBuffer generate(Type type, float frequency, sf::Time duration);
    void clear_sounds();

private:
    unsigned int m_rate;
    sf::Int16 m_amplitude;

    sf::Clock m_clock;

    std::deque<std::pair<sf::Time, sf::SoundBuffer>> m_buffers;
    std::deque<sf::Sound> m_sounds;
};