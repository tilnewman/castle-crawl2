#ifndef TREASURE_HPP_INCLUDED
#define TREASURE_HPP_INCLUDED
//
// treasure.hpp
//
#include "item.hpp"
#include "loot.hpp"
#include "tile-image-enum.hpp"

#include <string>

namespace castlecrawl
{
    struct Context;
}

namespace castlecrawl::item
{

    struct TreasureValues
    {
        explicit TreasureValues(const TileImage t_source);

        int value_per_level;
        float gold_amount_ratio;
    };

    //

    struct Treasure
    {
        int gold{ 0 };
        item::ItemVec_t items{};

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return ((0 == gold) && items.empty());
        }

        [[nodiscard]] const std::string description() const;

        void populateFromLoot(const Context & t_context, const Loot & t_loot);
    };
} // namespace castlecrawl::item

#endif // TREASURE_HPP_INCLUDED
