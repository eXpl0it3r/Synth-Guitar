#include "Button.hpp"

Button::Button()
: Animation{"res/button.json"}
{
    m_animator.playAnimation("normal", true);
}

void Button::texture(const sf::Texture& texture)
{
    m_sprite.setTexture(texture, true);
}

void Button::update(sf::Time dt)
{
    m_animator.update(dt);
    m_animator.animate(m_sprite);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

bool Button::contains(sf::Vector2f point)
{
    return getTransform().transformRect(m_sprite.getLocalBounds()).contains(point);
}

void Button::on_press()
{
    m_animator.playAnimation("pressed");
}

void Button::on_release()
{
    m_animator.playAnimation("normal");
}