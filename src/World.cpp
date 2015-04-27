#include "World.hpp"

#include "json.hpp"

#include <fstream>

World::World(thor::ResourceHolder<sf::Texture, std::string>& textures)
: m_textures{textures}
{
    load_level("res/level01.json");

}

void World::load_level(const std::string& filename)
{
    nlohmann::json level;

    std::fstream file(filename, std::ios::in | std::ios::binary);

    if(!file.is_open())
        throw(std::runtime_error{"Failed to open animation file \"" + filename + "\"."});

    try
    {
        file >> level;
    }
    catch(std::exception& e)
    {
        throw(std::runtime_error{"The animation file \"" + filename + "\" contains invalid JSON data."});
    }

    // Load texture
    std::string texture = level["texture"];
    m_textures.acquire("level", thor::Resources::fromFile<sf::Texture>(texture));

    // Load base tiles
    m_tile_size = level["tile_size"];
    std::vector<Tile> base_tiles;

    for(auto& rect : level["tiles"])
    {
        base_tiles.emplace_back();
        base_tiles.back().texture(m_textures["level"], {rect[0], rect[1], static_cast<int>(m_tile_size), static_cast<int>(m_tile_size)});
    }

    m_empty_tile.texture(m_textures["level"], {level["empty_tile"][0], level["empty_tile"][1],static_cast<int>( m_tile_size), static_cast<int>(m_tile_size)});

    // Load board
    std::size_t x = 0;
    std::size_t y = 0;

    m_dimension = sf::Vector2u(level["board"].begin()->size(), level["board"].size());

    for(auto& line : level["board"])
    {
        for(std::size_t tile : line)
        {
            // First tile
            if(x == 0 && y == 0)
                m_tiles.resize(m_dimension.y * m_dimension.x);

            std::size_t index = y * m_dimension.x + x;

            // Copy base tile
            m_tiles[index] = base_tiles[tile];
            m_tiles[index].setPosition({static_cast<float>(x * m_tile_size), static_cast<float>(y * m_tile_size)});

            ++x;
        };
        ++y;
        x = 0;
    }

    // Load logic part
    x = 0;
    y = 0;

    for(auto& line : level["logic"])
    {
        for(std::size_t tile : line)
        {
            // First tile
            if(x == 0 && y == 0)
                m_logic.resize(m_dimension.y * m_dimension.x);

            m_logic[y * m_dimension.x + x] = tile;

            if(tile == 1)
                m_spawn = {static_cast<float>(x * m_tile_size), static_cast<float>(y * m_tile_size)};

            ++x;
        }
        ++y;
        x = 0;
    }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& tile : m_tiles)
        target.draw(tile, states);
}

std::size_t World::tile_size()
{
    return m_tile_size;
}

bool World::check_collision(sf::Vector2i direction, sf::Vector2f position)
{
    sf::Vector2i index = static_cast<sf::Vector2i>(position) / static_cast<int>(m_tile_size) + direction;

    return !check_bounds(index) || m_logic[index.y * m_dimension.x + index.x] >= 10;
}

sf::Vector2f World::player_spawn()
{
    return m_spawn;
}

bool World::check_action(std::size_t index, Synth::Type type, float frequency)
{
    switch(m_logic[index])
    {
        case 11:
            return type == Synth::SINE && frequency > 200.f && frequency <= 250.f;
        case 12:
            return type == Synth::SINE && frequency > 100.f && frequency <= 200.f;
        case 13:
            return type == Synth::SINE && frequency > 300.f && frequency <= 380.f;
        case 14:
            return type == Synth::SINE && frequency > 380.f && frequency <= 450.f;
        case 15:
            return type == Synth::SINE && frequency == 440.f;
        case 16:
            return type == Synth::SINE && frequency > 450.f && frequency <= 550.f;
        case 17:
            return type == Synth::SINE && frequency > 550.f && frequency <= 700.f;
        case 18:
            return type == Synth::SINE && frequency > 700.f && frequency <= 850.f;
        case 19:
            return type == Synth::SINE && frequency > 850.f && frequency <= 1000.f;

        case 21:
            return type == Synth::SAW && frequency > 200.f && frequency <= 250.f;
        case 22:
            return type == Synth::SAW && frequency > 100.f && frequency <= 200.f;
        case 23:
            return type == Synth::SAW && frequency > 300.f && frequency <= 380.f;
        case 24:
            return type == Synth::SAW && frequency > 380.f && frequency <= 450.f;
        case 25:
            return type == Synth::SAW && frequency == 440.f;
        case 26:
            return type == Synth::SAW && frequency > 450.f && frequency <= 550.f;
        case 27:
            return type == Synth::SAW && frequency > 550.f && frequency <= 700.f;
        case 28:
            return type == Synth::SAW && frequency > 700.f && frequency <= 850.f;
        case 29:
            return type == Synth::SAW && frequency > 850.f && frequency <= 1000.f;


        case 31:
            return type == Synth::TRIANGLE && frequency > 200.f && frequency <= 250.f;
        case 32:
            return type == Synth::TRIANGLE && frequency > 100.f && frequency <= 200.f;
        case 33:
            return type == Synth::TRIANGLE && frequency > 300.f && frequency <= 380.f;
        case 34:
            return type == Synth::TRIANGLE && frequency > 380.f && frequency <= 450.f;
        case 35:
            return type == Synth::TRIANGLE && frequency == 440.f;
        case 36:
            return type == Synth::TRIANGLE && frequency > 450.f && frequency <= 550.f;
        case 37:
            return type == Synth::TRIANGLE && frequency > 550.f && frequency <= 700.f;
        case 38:
            return type == Synth::TRIANGLE && frequency > 700.f && frequency <= 850.f;
        case 39:
            return type == Synth::TRIANGLE && frequency > 850.f && frequency <= 1000.f;


        case 41:
            return type == Synth::SQUARE && frequency > 200.f && frequency <= 250.f;
        case 42:
            return type == Synth::SQUARE && frequency > 100.f && frequency <= 200.f;
        case 43:
            return type == Synth::SQUARE && frequency > 300.f && frequency <= 380.f;
        case 44:
            return type == Synth::SQUARE && frequency > 380.f && frequency <= 450.f;
        case 45:
            return type == Synth::SQUARE && frequency == 440.f;
        case 46:
            return type == Synth::SQUARE && frequency > 450.f && frequency <= 550.f;
        case 47:
            return type == Synth::SQUARE && frequency > 550.f && frequency <= 700.f;
        case 48:
            return type == Synth::SQUARE && frequency > 700.f && frequency <= 850.f;
        case 49:
            return type == Synth::SQUARE && frequency > 850.f && frequency <= 1000.f;
    }

    return false;
}

bool World::check_walls(sf::Vector2f position, Synth::Type type, float frequency)
{
    sf::Vector2i index = static_cast<sf::Vector2i>(position) / static_cast<int>(m_tile_size);
    bool ret = false;

    if(check_bounds(index + sf::Vector2i(1, 0)) && check_action(index.y * m_dimension.x + index.x + 1, type, frequency))
    {
        m_empty_tile.setPosition((index.x + 1) * m_tile_size, index.y * m_tile_size);
        m_tiles[index.y * m_dimension.x + index.x + 1] = m_empty_tile;
        m_logic[index.y * m_dimension.x + index.x + 1] = 0;
        ret = true;
    }
    if(check_bounds(index + sf::Vector2i(-1, 0)) && check_action(index.y * m_dimension.x + index.x - 1, type, frequency))
    {
        m_empty_tile.setPosition((index.x - 1) * m_tile_size, index.y * m_tile_size);
        m_tiles[index.y * m_dimension.x + index.x - 1] = m_empty_tile;
        m_logic[index.y * m_dimension.x + index.x - 1] = 0;
        ret = true;
    }
    if(check_bounds(index + sf::Vector2i(0, 1)) && check_action((index.y + 1) * m_dimension.x + index.x, type, frequency))
    {
        m_empty_tile.setPosition(index.x * m_tile_size, (index.y + 1) * m_tile_size);
        m_tiles[(index.y + 1) * m_dimension.x + index.x] = m_empty_tile;
        m_logic[(index.y + 1) * m_dimension.x + index.x] = 0;
        ret = true;
    }
    if(check_bounds(index + sf::Vector2i(0, -1)) && check_action((index.y - 1) * m_dimension.x + index.x, type, frequency))
    {
        m_empty_tile.setPosition(index.x * m_tile_size, (index.y - 1) * m_tile_size);
        m_tiles[(index.y - 1) * m_dimension.x + index.x] = m_empty_tile;
        m_logic[(index.y - 1) * m_dimension.x + index.x] = 0;
        ret = true;
    }

    return ret;
}

bool World::check_bounds(sf::Vector2i index)
{
    return !(index.x < 0 || index.x > m_dimension.x - 1 || index.y < 0 || index.y > m_dimension.y - 1);
}

bool World::check_win(sf::Vector2f position)
{
    sf::Vector2i index = static_cast<sf::Vector2i>(position) / static_cast<int>(m_tile_size);
    return m_logic[index.y * m_dimension.x + index.x] == 2;
}

void World::next_level(const std::string& level)
{
    m_textures.release("level");
    load_level(level);
}
