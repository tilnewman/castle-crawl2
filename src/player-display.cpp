// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// player-display.cpp
//
#include "player-display.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "layout.hpp"
#include "map.hpp"
#include "tile-images.hpp"

namespace castlecrawl
{

    PlayerDisplay::PlayerDisplay()
        : m_position(0, 0)
        , m_sprite()
    {}

    void PlayerDisplay::setup(const Context & context)
    {
        m_sprite = context.tile_images.sprite(context, TileImage::Avatar);
    }

    void PlayerDisplay::position(const Context & context, const MapPos_t & newPosition)
    {
        // assert player in a valid position? -no, because map transitions are invalid positions

        m_position = newPosition;
        m_sprite.setPosition(context.map.mapPosToScreenPos(context, m_position));
    }

    void PlayerDisplay::draw(
        const Context &, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }

} // namespace castlecrawl
