#include "Tile.hpp"

Tile::Tile()
{
}

void Tile::texture(const sf::Texture& texture, const sf::IntRect& rect)
{
    m_sprite.setTexture(texture, true);
    m_sprite.setTextureRect(rect);
}

void Tile::update(sf::Time dt)
{
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}
