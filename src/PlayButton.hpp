#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

#include <Thor/Animations.hpp>

#include <vector>

class PlayButton : public Entity, public Animation
{
public:
    PlayButton();

    void update(sf::Time dt) final;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

    void texture(const sf::Texture& texture);
    bool contains(sf::Vector2f point);

    void on_enter();
    void on_leave();

private:
    sf::Sprite m_sprite;
};