// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// player-display.cpp
//
#include "player-display.hpp"

#include "context.hpp"
#include "fight-util.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "player.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "splat-images.hpp"
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
        , m_splatTimeSec{ 0.0f }
        , m_splatSprite{ util::SfmlDefaults::instance().texture() }
    {}

    void PlayerDisplay::setup(const Context & t_context)
    {
        m_sprite = t_context.tile_images.sprite(t_context, TileImage::Avatar);
        m_shaker.setup((t_context.layout.cellSize().x * 0.1f), 75.0f);
    }

    void PlayerDisplay::position(const Context & t_context, const MapPos_t & t_newPosition)
    {
        // Assert player in a valid position?
        // No, because map transitions are intentionally invalid positions.

        m_isShaking = false;
        m_mapPos    = t_newPosition;
        m_screenPos = t_context.maps.current().mapPosToScreenPos(t_context, m_mapPos);
        m_sprite.setPosition(m_screenPos);
    }

    void PlayerDisplay::update(const Context & t_context, const float t_elapsedSec)
    {
        if (m_isShaking)
        {
            m_shaker.update(t_elapsedSec);
            m_shakeTimeSec += t_elapsedSec;

            const float shakeDurationSec{ 0.5f };
            if (m_shakeTimeSec > shakeDurationSec)
            {
                m_isShaking    = false;
                m_shakeTimeSec = 0.0f;
            }
        }

        m_sprite.setPosition({ (m_screenPos.x + m_shaker.adjustment()), m_screenPos.y });

        m_splatTimeSec -= t_elapsedSec;
        if (m_splatTimeSec < 0.0f)
        {
            m_splatTimeSec = 0.0f;
        }

        util::fitAndCenterInside(m_splatSprite, { m_screenPos, t_context.layout.cellSize() });
    }

    void PlayerDisplay::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_sprite, t_states);

        if (m_splatTimeSec > 0.0f)
        {
            t_target.draw(m_splatSprite, t_states);
        }

        const float healthRatio =
            (static_cast<float>(t_context.player.health()) /
             static_cast<float>(t_context.player.health()));

        if (healthRatio < 1.0f)
        {
            const auto rectangles{ fight::makeCreatureHealthBars(
                t_context, healthRatio, m_mapPos) };

            t_target.draw(rectangles.background, t_states);
            t_target.draw(rectangles.foreground, t_states);
        }
    }

    void PlayerDisplay::bloodSplatStart(const Context & t_context)
    {
        m_splatTimeSec = 0.75f;
        m_splatSprite  = t_context.splat_images.getRandom(t_context);
    }

} // namespace castlecrawl
