#ifndef TREASURE_HPP_INCLUDED
#define TREASURE_HPP_INCLUDED
//
// treasure.hpp
//
#include "item.hpp"
#include "loot.hpp"

#include <string>

namespace castlecrawl
{
    struct Context;
}

namespace castlecrawl::item
{
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
}

#endif // TREASURE_HPP_INCLUDED
