#include "Player.hpp"

Player::Player(std::size_t tile_size)
: Animation{"res/player.json"}
, m_tile_size{tile_size}
{
    m_animator.playAnimation("standby", true);
}

void Player::texture(const sf::Texture& texture)
{
    m_sprite.setTexture(texture, true);
}

void Player::update(sf::Time dt)
{
    if(m_duration > sf::Time::Zero)
    {
        m_elapsed += dt;

        if(m_elapsed > m_duration)
        {
            m_elapsed = sf::Time::Zero;
            m_duration = sf::Time::Zero;
            m_animator.playAnimation("standby", true);
        }
    }

    m_animator.update(dt);
    m_animator.animate(m_sprite);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

void Player::on_play_sine(sf::Time duration)
{
    m_animator.playAnimation("sine", true);
    m_duration = duration;
    m_elapsed = sf::Time::Zero;
}

void Player::on_play_saw(sf::Time duration)
{
    m_animator.playAnimation("saw", true);
    m_duration = duration;
    m_elapsed = sf::Time::Zero;
}

void Player::on_play_triangle(sf::Time duration)
{
    m_animator.playAnimation("triangle", true);
    m_duration = duration;
    m_elapsed = sf::Time::Zero;
}

void Player::on_play_square(sf::Time duration)
{
    m_animator.playAnimation("square", true);
    m_duration = duration;
    m_elapsed = sf::Time::Zero;
}
