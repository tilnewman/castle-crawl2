// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster-manager.cpp
//
#include "monster-manager.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "random.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include <algorithm>

namespace castlecrawl
{

    MonsterManager::MonsterManager()
        : m_monsters{}
    {}

    void MonsterManager::add(
        const Context & t_context, const MapPos_t & t_mapPos, const char t_mapChar)
    {
        m_monsters.emplace_back(t_context, t_mapPos, charToTileImage(t_mapChar));
    }

    bool MonsterManager::takeTurns(const Context & t_context)
    {
        bool didAnyMonstersMove = false;
        for (Monster & monster : m_monsters)
        {
            if (monster.takeTurn(t_context))
            {
                didAnyMonstersMove = true;
            }
        }

        return didAnyMonstersMove;
    }

    void MonsterManager::drawHealthLines(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        const sf::Vector2f cellSize = t_context.layout.cellSize();
        const float height          = (cellSize.y * 0.075f);

        for (const Monster & monster : m_monsters)
        {
            const float healthRatio = monster.healthRatio();

            if (healthRatio < 1.0f)
            {
                sf::RectangleShape rectangle;

                auto findColor = [&]() {
                    sf::Color color = sf::Color::Green;
                    if (healthRatio < 0.333f)
                    {
                        color = sf::Color::Red;
                    }
                    else if (healthRatio < 0.666f)
                    {
                        color = sf::Color::Yellow;
                    }

                    return color;
                };

                rectangle.setFillColor(findColor());
                rectangle.setOutlineThickness(0.0f);
                rectangle.setSize({ cellSize.x, height });

                const sf::Vector2f cellScreenPos =
                    t_context.maps.current().mapPosToScreenPos(t_context, monster.mapPosition());

                sf::Vector2f screenPos = cellScreenPos;
                screenPos.y            = ((screenPos.y + cellSize.y) - height);
                rectangle.setPosition(screenPos);

                t_target.draw(rectangle, t_states);
            }
        }
    }

    std::vector<Monster>::iterator MonsterManager::findFromMapPos(const MapPos_t & t_mapPos)
    {
        for (auto iter{ std::begin(m_monsters) }; iter != std::end(m_monsters); ++iter)
        {
            if (iter->mapPosition() == t_mapPos)
            {
                return iter;
            }
        }

        return std::end(m_monsters);
    }

} // namespace castlecrawl