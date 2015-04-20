#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

class Player : public Entity, public Animation
{
public:
    Player(std::size_t tile_size);

    void texture(const sf::Texture& texture);

    void update(sf::Time dt) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

    void on_play_sine(sf::Time duration);
    void on_play_saw(sf::Time duration);
    void on_play_triangle(sf::Time duration);
    void on_play_square(sf::Time duration);

private:
    std::size_t m_tile_size;
    sf::Sprite m_sprite;

    sf::Time m_elapsed;
    sf::Time m_duration;
};