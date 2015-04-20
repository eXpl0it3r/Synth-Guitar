#include "ExitButton.hpp"

ExitButton::ExitButton()
: Animation{"res/exit.json"}
{
    m_animator.playAnimation("steady", true);
}

void ExitButton::texture(const sf::Texture& texture)
{
    m_sprite.setTexture(texture, true);
}

void ExitButton::update(sf::Time dt)
{
    m_animator.update(dt);
    m_animator.animate(m_sprite);
}

void ExitButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

bool ExitButton::contains(sf::Vector2f point)
{
    return getTransform().transformRect(m_sprite.getLocalBounds()).contains(point);
}

void ExitButton::on_enter()
{
    m_animator.playAnimation("hover");
}

void ExitButton::on_leave()
{
    m_animator.playAnimation("steady");
}
