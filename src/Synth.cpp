#include "Synth.hpp"

#include <cmath>
#include <limits>
#include <iostream>

Synth::Synth()
: m_rate{44100}
, m_amplitude{std::numeric_limits<sf::Int16>::max() / 2}
{
    m_clock.restart();
}

void Synth::play(Type type, float frequency, sf::Time duration)
{
    sf::Time expiration = m_clock.getElapsedTime() + duration + sf::seconds(5);
    sf::SoundBuffer buffer = generate(type, frequency, duration);

    m_buffers.push_back(std::make_pair(expiration, buffer));
    m_sounds.emplace_back();
    m_sounds.back().setBuffer(m_buffers.back().second);
    m_sounds.back().play();

    clear_sounds();
}

void Synth::clear_sounds()
{
    // Remove sounds that have stopped playing
    while(m_sounds.front().getStatus() == sf::Sound::Stopped)
        m_sounds.pop_front();

    // Remove expired buffers
    for(auto it = m_buffers.begin(); it != m_buffers.end(); )
    {
        if(it->first < m_clock.getElapsedTime())
            it = m_buffers.erase(it);
        else
            ++it;
    }
}

sf::SoundBuffer Synth::generate(Type type, float frequency, sf::Time duration)
{
    std::size_t count = static_cast<std::size_t>(m_rate * duration.asSeconds()) + 1;
    float sample_duration = duration.asSeconds() / count;

    std::vector<sf::Int16> samples(count*2, 0);

    switch(type)
    {
        case SINE:
            for(std::size_t i = 0, c = 0; i < samples.size(); i += 2, ++c)
            {
                float t = c * sample_duration * frequency;
                samples[i] = static_cast<sf::Int16>(std::sin(TAU * t) * m_amplitude);
                samples[i + 1] = samples[i];
            }
            break;
        case SAW:
            for(std::size_t i = 0, c = 0; i < samples.size(); i += 2, ++c)
            {
                float t = c * sample_duration * frequency;
                samples[i] = static_cast<sf::Int16>((2.f * (t - std::floor(t)) - 1) * (m_amplitude * 2.f/3.f));
                samples[i + 1] = samples[i];
            }
            break;
        case TRIANGLE:
            for(std::size_t i = 0, c = 0; i < samples.size(); i += 2, ++c)
            {
                float t = c * sample_duration * frequency;
                samples[i] = static_cast<sf::Int16>((2.f * std::abs(2.f * (t - std::floor(t)) - 1) - 1) * m_amplitude);
                samples[i + 1] = samples[i];
            }
            break;
        case SQUARE:
            for(std::size_t i = 0, c = 0; i < samples.size(); i += 2, ++c)
            {
                float sine = std::sin(TAU * frequency * c * sample_duration);
                samples[i] = static_cast<sf::Int16>(((0 < sine) - (sine < 0)) * (m_amplitude * 2.f/3.f));
                samples[i + 1] = samples[i];
            }
            break;
    }

    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples.data(), samples.size(), 2, m_rate);
    //buffer.saveToFile("buffer.wav");
    return std::move(buffer);
}
