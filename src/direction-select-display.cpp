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
        : m_topRectangle()
        , m_botRectangle()
        , m_leftRectangle()
        , m_rightRectangle()
    {}

    void DirectionSelectDisplay::setup(const Context & context)
    {
        const MapPos_t mapPos = context.player_display.position();

        const MapPos_t topPos{ mapPos.x, (mapPos.y - 1) };
        const MapPos_t botPos{ mapPos.x, (mapPos.y + 1) };
        const MapPos_t leftPos{ (mapPos.x - 1), mapPos.y };
        const MapPos_t rightPos{ (mapPos.x + 1), mapPos.y };

        const sf::Color fillColor{ 0, 255, 255, 64 };
        const sf::Color outlineColor{ 0, 255, 255 };

        if (context.maps.current().isPosValid(topPos))
        {
            m_topRectangle.setFillColor(fillColor);
            m_topRectangle.setOutlineColor(outlineColor);
            m_topRectangle.setOutlineThickness(2.0f);
            m_topRectangle.setPosition(context.maps.current().mapPosToScreenPos(context, topPos));
            m_topRectangle.setSize(context.layout.cellSize());
        }

        if (context.maps.current().isPosValid(botPos))
        {
            m_botRectangle.setFillColor(fillColor);
            m_botRectangle.setOutlineColor(outlineColor);
            m_botRectangle.setOutlineThickness(2.0f);
            m_botRectangle.setPosition(context.maps.current().mapPosToScreenPos(context, botPos));
            m_botRectangle.setSize(context.layout.cellSize());
        }

        if (context.maps.current().isPosValid(leftPos))
        {
            m_leftRectangle.setFillColor(fillColor);
            m_leftRectangle.setOutlineColor(outlineColor);
            m_leftRectangle.setOutlineThickness(2.0f);
            m_leftRectangle.setPosition(context.maps.current().mapPosToScreenPos(context, leftPos));
            m_leftRectangle.setSize(context.layout.cellSize());
        }

        if (context.maps.current().isPosValid(rightPos))
        {
            m_rightRectangle.setFillColor(fillColor);
            m_rightRectangle.setOutlineColor(outlineColor);
            m_rightRectangle.setOutlineThickness(2.0f);
            m_rightRectangle.setPosition(
                context.maps.current().mapPosToScreenPos(context, rightPos));
            m_rightRectangle.setSize(context.layout.cellSize());
        }
    }

    void DirectionSelectDisplay::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_topRectangle, states);
        target.draw(m_botRectangle, states);
        target.draw(m_leftRectangle, states);
        target.draw(m_rightRectangle, states);
    }

} // namespace castlecrawl
