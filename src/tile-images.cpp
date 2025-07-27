// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// tile-images.cpp
//
#include "tile-images.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "sfml-util.hpp"

namespace castlecrawl
{

    TileImages::TileImages()
        : m_texture()
    {}

    void TileImages::setup(const GameConfig & t_config)
    {
        M_CHECK(
            m_texture.loadFromFile((t_config.media_path / "image" / "tile.png").string()),
            "Failed to load tile.png");

        // Improves image quality BUT also causes mass tile edge artifacts.
        // Texture smoothing really only works when the images have transparent edges.
        // m_texture.setSmooth(true);
    }

    const sf::Sprite TileImages::sprite(
        const Context & t_context, const TileImage t_tileImage, const sf::Vector2f & t_pos) const
    {
        sf::Sprite sprite(m_texture, tileImageToRect(t_tileImage));
        util::fit(sprite, t_context.layout.cellSize());
        sprite.setPosition(t_pos);
        return sprite;
    }

} // namespace castlecrawl
