// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// direction-select-display.cpp
//
#include "direction-select-display.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "sfml-util.hpp"

namespace castlecrawl
{

    DirectionSelectDisplay::DirectionSelectDisplay()
        : m_topRectangle{}
        , m_botRectangle{}
        , m_leftRectangle{}
        , m_rightRectangle{}
    {}

    void DirectionSelectDisplay::setup(const Context & t_context)
    {
        const MapPos_t mapPos = t_context.player_display.position();

        const MapPos_t topPos{ mapPos.x, (mapPos.y - 1) };
        const MapPos_t botPos{ mapPos.x, (mapPos.y + 1) };
        const MapPos_t leftPos{ (mapPos.x - 1), mapPos.y };
        const MapPos_t rightPos{ (mapPos.x + 1), mapPos.y };

        const sf::Color fillColor{ 0, 255, 255, 64 };
        const sf::Color outlineColor{ 0, 255, 255 };

        if (t_context.maps.current().isPosValid(topPos))
        {
            m_topRectangle.setFillColor(fillColor);
            m_topRectangle.setOutlineColor(outlineColor);
            m_topRectangle.setOutlineThickness(2.0f);

            m_topRectangle.setPosition(
                t_context.maps.current().mapPosToScreenPos(t_context, topPos));
            
            m_topRectangle.setSize(t_context.layout.cellSize());
        }

        if (t_context.maps.current().isPosValid(botPos))
        {
            m_botRectangle.setFillColor(fillColor);
            m_botRectangle.setOutlineColor(outlineColor);
            m_botRectangle.setOutlineThickness(2.0f);

            m_botRectangle.setPosition(
                t_context.maps.current().mapPosToScreenPos(t_context, botPos));
            
            m_botRectangle.setSize(t_context.layout.cellSize());
        }

        if (t_context.maps.current().isPosValid(leftPos))
        {
            m_leftRectangle.setFillColor(fillColor);
            m_leftRectangle.setOutlineColor(outlineColor);
            m_leftRectangle.setOutlineThickness(2.0f);

            m_leftRectangle.setPosition(
                t_context.maps.current().mapPosToScreenPos(t_context, leftPos));

            m_leftRectangle.setSize(t_context.layout.cellSize());
        }

        if (t_context.maps.current().isPosValid(rightPos))
        {
            m_rightRectangle.setFillColor(fillColor);
            m_rightRectangle.setOutlineColor(outlineColor);
            m_rightRectangle.setOutlineThickness(2.0f);

            m_rightRectangle.setPosition(
                t_context.maps.current().mapPosToScreenPos(t_context, rightPos));

            m_rightRectangle.setSize(t_context.layout.cellSize());
        }
    }

    void DirectionSelectDisplay::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_topRectangle, t_states);
        t_target.draw(m_botRectangle, t_states);
        t_target.draw(m_leftRectangle, t_states);
        t_target.draw(m_rightRectangle, t_states);
    }

} // namespace castlecrawl
