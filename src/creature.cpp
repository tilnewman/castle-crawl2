// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// creature.cpp
//
#include "creature.hpp"

#include "context.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "random.hpp"
#include "tile-images.hpp"

#include <SFML/Graphics/RenderStates.hpp>

#include <algorithm>

namespace castlecrawl
{

    Creature::Creature(
        const Context & t_context, const MapPos_t & t_mapPos, const TileImage t_tileImage)
        : m_mapPos{ t_mapPos }
        , m_tileImage{ t_tileImage }
        , m_sprite{ t_context.tile_images.sprite(
              t_context,
              t_tileImage,
              t_context.maps.current().mapPosToScreenPos(t_context, t_mapPos)) }
        , m_isFacingLeft{ true } // all creature/npc images from stone soup face left
    {}

    void Creature::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_sprite, t_states);
    }

    bool Creature::isPlayerAdjacent(const Context & t_context) const
    {
        const std::vector<MapCell> surroundingCells =
            t_context.maps.current().surroundingCellsHorizVert(m_mapPos);

        const auto foundIter = std::find_if(
            std::begin(surroundingCells), std::end(surroundingCells), [&](const MapCell & cell) {
                return (t_context.player_display.position() == cell.position);
            });

        return (foundIter != std::end(surroundingCells));
    }

    bool Creature::moveToward(const Context & t_context, const MapPos_t & t_targetMapPos)
    {
        // construct a vector of all possible places we could move to
        const std::vector<MapCell> adjacentCells =
            t_context.maps.current().surroundingCellsHorizVert(m_mapPos);

        std::vector<PositionDistance> positions;
        positions.reserve(adjacentCells.size());

        for (const MapCell & cell : adjacentCells)
        {
            if (cell.object_char == ' ')
            {
                positions.emplace_back(cell.position, distance(t_targetMapPos, cell.position));
            }
        }

        // sort it by distance to the t_targetMapPos
        std::sort(
            std::begin(positions),
            std::end(positions),
            [](const PositionDistance & a, const PositionDistance & b) {
                return (a.distance < b.distance);
            });

        if (positions.empty())
        {
            // there are no adjacent valid and empty positions, so do nothing
            return false;
        }

        // allow moving away from the target half of the time
        // this makes no sense but looks like more natural eager monster movement
        // this also allows monsters to sometimes move around obstacles more naturally
        if (t_context.random.boolean())
        {
            const int currentDistance = distance(t_targetMapPos, m_mapPos);

            std::erase_if(positions, [&](const PositionDistance & mpd) {
                return (mpd.distance > currentDistance);
            });

            if (positions.empty())
            {
                return false;
            }
        }

        moveTo(t_context, t_context.random.from(positions).position);
        return true;
    }

    void Creature::moveTo(const Context & t_context, const MapPos_t & t_newMapPos)
    {
        const char myChar = t_context.maps.current().cell(m_mapPos).object_char;
        t_context.maps.current().setObjectChar(m_mapPos, ' ');
        m_mapPos = t_newMapPos;
        t_context.maps.current().setObjectChar(m_mapPos, myChar);

        m_sprite.setPosition(t_context.maps.current().mapPosToScreenPos(t_context, m_mapPos));

        if (!m_isFacingLeft)
        {
            m_sprite.move({ m_sprite.getGlobalBounds().size.x, 0.0f });
        }
    }

    void Creature::turn()
    {
        m_isFacingLeft = !m_isFacingLeft;
        m_sprite.scale({ -1.0f, 1.0f });

        if (m_isFacingLeft)
        {
            m_sprite.move({ -m_sprite.getGlobalBounds().size.x, 0.0f });
        }
        else
        {
            m_sprite.move({ m_sprite.getGlobalBounds().size.x, 0.0f });
        }
    }

} // namespace castlecrawl