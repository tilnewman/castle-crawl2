// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// look-event.cpp
//
#include "look-event.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "inventory.hpp"
#include "item-factory.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "monster-spawn.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "random.hpp"
#include "sfml-util.hpp"

#include <iostream>

namespace castlecrawl
{

    LookEventHandler::LookEventHandler() {}

    bool LookEventHandler::areAllRequirementsMet(
        const Context & t_context, const LookEvent & t_lookEvent)
    {
        Player & player     = t_context.player;
        const Stats & stats = t_lookEvent.stats_required;

        if ((player.accuracy().current() < stats.acc) || (player.arcane().current() < stats.arc) ||
            (player.dexterity().current() < stats.dex) || (player.luck().current() < stats.lck) ||
            (player.strength().current() < stats.str))
        {
            return false;
        }

        if (!t_lookEvent.item_required.empty())
        {
            if (!t_context.player.inventory().contains(t_lookEvent.item_required))
            {
                return false;
            }
        }

        if (!t_lookEvent.item_keyword_required.empty())
        {
            if (!t_context.player.inventory().containsKeyword(t_lookEvent.item_keyword_required))
            {
                return false;
            }
        }

        if (t_lookEvent.gold_required > 0)
        {
            if (t_context.player.gold() < t_lookEvent.gold_required)
            {
                return false;
            }
        }

        return true;
    }

    const std::string
        LookEventHandler::takePassActions(const Context & t_context, const LookEvent & t_lookEvent)
    {
        std::string message;

        const std::string & itemName = t_lookEvent.item_given_pass;
        if (!itemName.empty())
        {
            const auto itemOpt = t_context.items.find(itemName);

            M_CHECK(
                itemOpt.has_value(),
                "LookEventHandler::takePassActions() cannot give item_given_pass=\""
                    << itemName << "\" because that item does not exist!");

            t_context.player.inventory().add(itemOpt.value());
        }

        t_context.player.healthAdj(t_lookEvent.health_adj_pass);
        t_context.player.goldAdj(t_lookEvent.gold_adj_pass);

        t_context.player.accuracy().adjCurrentNormalClamped(t_lookEvent.stats_adj_pass.acc);
        t_context.player.arcane().adjCurrentNormalClamped(t_lookEvent.stats_adj_pass.arc);
        t_context.player.dexterity().adjCurrentNormalClamped(t_lookEvent.stats_adj_pass.dex);
        t_context.player.luck().adjCurrentNormalClamped(t_lookEvent.stats_adj_pass.lck);
        t_context.player.strength().adjCurrentNormalClamped(t_lookEvent.stats_adj_pass.str);

        if (t_lookEvent.will_spawn_monster)
        {
            // construct a vector of all possible places we could move to
            const std::vector<MapCell> adjacentCells =
                t_context.maps.current().surroundingCellsHorizVert(t_lookEvent.map_pos);

            std::vector<MapPos_t> positions;
            positions.reserve(adjacentCells.size());

            for (const MapCell & cell : adjacentCells)
            {
                if ((cell.object_char == tileImageToChar(TileImage::Empty)) &&
                    (cell.position != t_context.player_display.position()))
                {
                    positions.emplace_back(cell.position);
                }
            }

            // if there are no adjacent valid and empty positions then we can't spawn the montser
            if (positions.empty())
            {
                message += "a monster eats it!";
            }
            else
            {
                const MapPos_t spawnPos        = t_context.random.from(positions);
                const TileImage spawnTileImage = MonsterSpawn::randomMonster(t_context);
                t_context.maps.current().setObjectChar(spawnPos, tileImageToChar(spawnTileImage));
                t_context.map_display.load(t_context);
                t_context.monsters.add(t_context, spawnPos, tileImageToChar(spawnTileImage));

                message += "a terrifying ";
                message += toString(spawnTileImage);
                message += " climbs out!";
            }
        }

        return message;
    }

    const std::string
        LookEventHandler::takeFailActions(const Context & t_context, const LookEvent & t_lookEvent)
    {
        t_context.player.healthAdj(t_lookEvent.health_adj_fail);
        return "";
    }

} // namespace castlecrawl
