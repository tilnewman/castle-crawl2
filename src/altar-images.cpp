// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// altar-images.cpp
//
#include "altar-images.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

namespace castlecrawl
{

    AltarImages::AltarImages()
        : m_texture{}
    {}

    void AltarImages::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(m_texture, (t_config.media_path / "image" / "altar.png"), false);
    }

    const sf::Sprite AltarImages::get(const Context & t_context, const AltarImage t_image) const
    {
        sf::Sprite sprite(m_texture, altarImageToRect(t_image));
        util::fit(sprite, t_context.layout.cellSize());
        return sprite;
    }

} // namespace castlecrawl
