// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// doorway-images.cpp
//
#include "doorway-images.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

namespace castlecrawl
{

    DoorwayImages::DoorwayImages()
        : m_texture{}
    {}

    void DoorwayImages::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(
            m_texture, (t_config.media_path / "image" / "doorway.png"), false);
    }

    const sf::Sprite DoorwayImages::get(const Context & t_context, const DoorwayImage t_image) const
    {
        sf::Sprite sprite(m_texture, doorwayImageToRect(t_image));
        util::fit(sprite, t_context.layout.cellSize());
        return sprite;
    }

} // namespace castlecrawl
