#pragma once

#include "Tile.hpp"
#include "Synth.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <vector>

class World : public sf::Drawable
{
public:
    World(thor::ResourceHolder<sf::Texture, std::string>& textures);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
    bool check_collision(sf::Vector2i direction, sf::Vector2f position);
    bool check_walls(sf::Vector2f position, Synth::Type type, float frequency);
    bool check_win(sf::Vector2f position);
    void next_level(const std::string& level);

    std::size_t tile_size();
    sf::Vector2f player_spawn();

private:
    void load_level(const std::string& filename);
    bool check_bounds(sf::Vector2i index);
    bool check_action(size_t index, Synth::Type type, float frequency);

private:
    thor::ResourceHolder<sf::Texture, std::string>& m_textures;

    std::size_t m_tile_size;
    sf::Vector2u m_dimension;
    std::vector<Tile> m_tiles;
    std::vector<std::size_t> m_logic;
    Tile m_empty_tile;

    sf::Vector2f m_spawn;

};

