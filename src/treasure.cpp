// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// treasure.cpp
//
#include "treasure.hpp"

#include "context.hpp"
#include "item-factory.hpp"
#include "random.hpp"

#include <iostream>

namespace castlecrawl::item
{

    TreasureValues::TreasureValues(const TileImage t_source)
        : value_per_level{ 0 }
        , gold_value_divisor{ 1 } // don't divide by zero!
    {
        if (t_source == TileImage::Bag)
        {
            value_per_level    = 35;
            gold_value_divisor = 2;
        }
        else if (t_source == TileImage::Barrel)
        {
            value_per_level    = 50;
            gold_value_divisor = 10;
        }
        else if (t_source == TileImage::Coffin)
        {
            value_per_level    = 75;
            gold_value_divisor = 5;
        }
        else if (t_source == TileImage::Chest)
        {
            value_per_level    = 125;
            gold_value_divisor = 3;
        }
        else if (t_source == TileImage::Coins)
        {
            value_per_level    = 100;
            gold_value_divisor = 1;
        }
        else
        {
            std::cerr << "Error:  TreasureValues::TreasureValues() was given an unhandled "
                         "TileImage source=\""
                      << toString(t_source) << "\"! Using default values to keep game running.\n";

            value_per_level    = 50;
            gold_value_divisor = 5;
        }
    }

    //

    const std::string Treasure::description() const
    {
        std::string str;
        str.reserve(200);

        str += "You find";

        if ((0 == gold) && items.empty())
        {
            str += " nothing.";
            return str;
        }

        if (gold > 0)
        {
            str += ' ';
            str += std::to_string(gold);
            str += " gold";
        }

        if (items.empty())
        {
            str += '.';
        }
        else
        {
            if (gold > 0)
            {
                str += " and";
            }

            str += ":\n";

            for (const item::Item & item : items)
            {
                str += "    ";
                str += item.name();
                str += '\n';
            }
        }

        return str;
    }

    void Treasure::populateFromLoot(const Context & t_context, const Loot & t_loot)
    {
        if (t_loot.will_randomize_gold)
        {
            gold = t_context.random.fromTo(1, t_loot.gold);
        }
        else
        {
            gold = t_loot.gold;
        }

        if (t_loot.will_randomize_items)
        {
            const item::ItemOpt_t itemOpt =
                t_context.items.find(t_context.random.from(t_loot.item_names));

            if (itemOpt.has_value())
            {
                items.push_back(itemOpt.value());
            }
        }
        else
        {
            for (const std::string & itemName : t_loot.item_names)
            {
                const item::ItemOpt_t itemOpt = t_context.items.find(itemName);
                if (itemOpt.has_value())
                {
                    items.push_back(itemOpt.value());
                }
            }
        }
    }

} // namespace castlecrawl::item
