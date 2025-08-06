// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// npc-manager.cpp
//
#include "npc-manager.hpp"

#include "context.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "random.hpp"

#include <algorithm>

namespace castlecrawl
{

    NpcManager::NpcManager()
        : m_npcs{}
    {}

    void NpcManager::add(const Context &, const MapPos_t & t_mapPos, const char t_mapChar)
    {
        m_npcs.emplace_back(t_mapPos, charToTileImage(t_mapChar));
    }

    bool NpcManager::takeTurns(const Context & t_context)
    {
        bool didAnyNpcsMove = false;
        for (Npc & npc : m_npcs)
        {
            if (npc.takeTurn(t_context))
            {
                didAnyNpcsMove = true;
            }
        }

        return didAnyNpcsMove;
    }

    std::vector<Npc>::iterator NpcManager::findFromMapPos(const MapPos_t & t_mapPos)
    {
        for (auto iter{ std::begin(m_npcs) }; iter != std::end(m_npcs); ++iter)
        {
            if (iter->mapPosition() == t_mapPos)
            {
                return iter;
            }
        }

        return std::end(m_npcs);
    }

} // namespace castlecrawl