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
#include "texture-loader.hpp"

#include <set>

namespace castlecrawl
{

    TileImages::TileImages()
        : m_texture()
    {}

    void TileImages::setup(const GameConfig & t_config)
    {
        // Note that texture smoothing is turned OFF.
        // It improves image quality BUT also causes mass tile edge artifacts.
        // Texture smoothing really only works when the images have transparent edges.
        util::TextureLoader::load(m_texture, (t_config.media_path / "image" / "tile.png"), false);

        validate();
    }

    void TileImages::validate() const
    {
        std::set<char> usedChars;

        for (std::size_t index{ static_cast<std::size_t>(TileImage::Empty) };
             index <= static_cast<std::size_t>(TileImage::BookSpeaker);
             ++index)
        {
            const TileImage tileImage = static_cast<TileImage>(index);
            const char ch             = tileImageToChar(tileImage);

            M_CHECK(
                (usedChars.find(ch) == std::end(usedChars)),
                "Error: TileImages::verify() tile_image=\"" << toString(tileImage)
                                                            << "\" has duplicate used char!");

            usedChars.insert(ch);

            M_CHECK(
                (charToTileImage(ch) == tileImage),
                "Error: TileImages::verify() tile_image=\"" << toString(tileImage)
                                                            << "\" reverse lookup failed!");
        }
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
