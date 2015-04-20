#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

#include <Thor/Animations.hpp>

#include <vector>

class Button: public Entity, public Animation
{
public:
    Button();

    void texture(const sf::Texture& texture);
    bool contains(sf::Vector2f point);

    void update(sf::Time dt) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

    void on_press();
    void on_release();

private:
    sf::Sprite m_sprite;
};