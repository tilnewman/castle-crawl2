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
        : m_mapPos(0, 0)
        , m_screenPos(0.0f, 0.0f)
        , m_sprite()
        , m_isShaking(false)
        , m_shakeTimeSec(0.0f)
        , m_shaker()
    {}

    void PlayerDisplay::setup(const Context & context)
    {
        m_sprite = context.tile_images.sprite(context, TileImage::Avatar);
        m_shaker.setup((context.layout.cellSize().x * 0.1f), 75.0f);
    }

    void PlayerDisplay::position(const Context & context, const MapPos_t & newPosition)
    {
        // assert player in a valid position? -no, because map transitions are invalid

        m_isShaking = false;
        m_mapPos    = newPosition;
        m_screenPos = context.map.mapPosToScreenPos(context, m_mapPos);
        m_sprite.setPosition(m_screenPos);
    }

    void PlayerDisplay::update(const Context &, const float frameTimeSec)
    {
        if (m_isShaking)
        {
            m_shaker.update(frameTimeSec);
            m_shakeTimeSec += frameTimeSec;

            const float shakeDurationSec{ 0.5f };
            if (m_shakeTimeSec > shakeDurationSec)
            {
                m_isShaking    = false;
                m_shakeTimeSec = 0.0f;
            }
        }

        m_sprite.setPosition((m_screenPos.x + m_shaker.adjustment()), m_screenPos.y);
    }

    void PlayerDisplay::draw(
        const Context &, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }

} // namespace castlecrawl
