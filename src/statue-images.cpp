// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// statue-images.cpp
//
#include "statue-images.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

namespace castlecrawl
{

    StatueImages::StatueImages()
        : m_texture{}
    {}

    void StatueImages::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(
            m_texture, (t_config.media_path / "image" / "statue.png"), false);
    }

    const sf::Sprite StatueImages::get(const Context & t_context, const StatueImage t_image) const
    {
        sf::Sprite sprite(m_texture, statueImageToRect(t_image));
        util::fit(sprite, t_context.layout.cellSize());
        return sprite;
    }

} // namespace castlecrawl
