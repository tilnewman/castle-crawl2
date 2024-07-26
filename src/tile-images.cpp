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

    void TileImages::setup(const GameConfig & config)
    {
        M_CHECK(
            m_texture.loadFromFile((config.media_path / "image" / "tile.png").string()),
            "Failed to load tile.png");

        // improves image quality BUT also causes mass tile edge artifacts
        // texture smoothing really only works when the images have transparent edges
        // m_texture.setSmooth(true);
    }

    const sf::Sprite TileImages::sprite(const Context & context, const TileImage tileImage) const
    {
        sf::Sprite sprite(m_texture, tileImageToRect(tileImage));
        util::fit(sprite, context.layout.cellSize());
        return sprite;
    }

} // namespace castlecrawl
