// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster-manager.cpp
//
#include "monster-manager.hpp"

#include "context.hpp"
#include "fight-util.hpp"
#include "font.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "random.hpp"

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
        for (const Monster & monster : m_monsters)
        {
            if (monster.healthRatio() < 1.0f)
            {
                t_target.draw(
                    makeCreatureHealthBar(t_context, monster.healthRatio(), monster.mapPosition()),
                    t_states);
            }

            if (!monster.m_actionString.empty())
            {
                sf::Text text = t_context.fonts.makeText(FontSize::Small, monster.m_actionString);

                text.setPosition(
                    t_context.maps.current().mapPosToScreenPos(t_context, monster.mapPosition()));

                text.move({ 0.0f, -text.getGlobalBounds().size.y });

                t_target.draw(text, t_states);
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