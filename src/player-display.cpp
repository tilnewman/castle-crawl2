// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// player-display.cpp
//
#include "player-display.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "sfml-defaults.hpp"
#include "tile-images.hpp"

namespace castlecrawl
{

    PlayerDisplay::PlayerDisplay()
        : m_mapPos{ 0, 0 }
        , m_screenPos{ 0.0f, 0.0f }
        , m_sprite{ util::SfmlDefaults::instance().texture() }
        , m_isShaking{ false }
        , m_shakeTimeSec{ 0.0f }
        , m_shaker{}
    {}

    void PlayerDisplay::setup(const Context & t_context)
    {
        m_sprite = t_context.tile_images.sprite(t_context, TileImage::Avatar);
        m_shaker.setup((t_context.layout.cellSize().x * 0.1f), 75.0f);
    }

    void PlayerDisplay::position(const Context & t_context, const MapPos_t & t_newPosition)
    {
        // assert player in a valid position? -no, because map transitions are invalid positions

        m_isShaking = false;
        m_mapPos    = t_newPosition;
        m_screenPos = t_context.maps.current().mapPosToScreenPos(t_context, m_mapPos);
        m_sprite.setPosition(m_screenPos);
    }

    void PlayerDisplay::update(const Context &, const float t_frameTimeSec)
    {
        if (m_isShaking)
        {
            m_shaker.update(t_frameTimeSec);
            m_shakeTimeSec += t_frameTimeSec;

            const float shakeDurationSec{ 0.5f };
            if (m_shakeTimeSec > shakeDurationSec)
            {
                m_isShaking    = false;
                m_shakeTimeSec = 0.0f;
            }
        }

        m_sprite.setPosition({ (m_screenPos.x + m_shaker.adjustment()), m_screenPos.y });
    }

    void PlayerDisplay::draw(
        const Context &, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_sprite, t_states);
    }

} // namespace castlecrawl
