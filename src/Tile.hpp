#pragma once

#include "Entity.hpp"

#include <vector>

class Tile : public Entity
{
public:
    Tile();

    void texture(const sf::Texture& texture, const sf::IntRect& rect);

    void update(sf::Time dt) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

private:
    sf::Sprite m_sprite;
};