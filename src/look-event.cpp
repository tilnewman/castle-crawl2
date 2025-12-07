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
#include "player.hpp"

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

        return true;
    }

    void LookEventHandler::takePassActions(const Context & t_context, const LookEvent & t_lookEvent)
    {
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
    }

    void LookEventHandler::takeFailActions(const Context & t_context, const LookEvent & t_lookEvent)
    {
        t_context.player.healthAdj(t_lookEvent.health_adj_fail);
    }

} // namespace castlecrawl
