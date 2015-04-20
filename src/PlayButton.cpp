#include "PlayButton.hpp"

PlayButton::PlayButton()
: Animation{"res/play.json"}
{
    m_animator.playAnimation("steady", true);
}

void PlayButton::texture(const sf::Texture& texture)
{
    m_sprite.setTexture(texture, true);
}

void PlayButton::update(sf::Time dt)
{
    m_animator.update(dt);
    m_animator.animate(m_sprite);
}

void PlayButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

bool PlayButton::contains(sf::Vector2f point)
{
    return getTransform().transformRect(m_sprite.getLocalBounds()).contains(point);
}


void PlayButton::on_enter()
{
    m_animator.playAnimation("hover");
}

void PlayButton::on_leave()
{
    m_animator.playAnimation("steady");
}
