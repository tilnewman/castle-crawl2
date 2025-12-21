#ifndef LOOT_HPP_INCLUDED
#define LOOT_HPP_INCLUDED
//
// loot.hpp
//
#include "map-types.hpp"

#include <optional>
#include <string>
#include <vector>

namespace castlecrawl
{

    struct Loot
    {
        bool has_been_collected{ false };

        MapPos_t map_pos{ invalidMapPos };

        std::vector<std::string> item_names{};
        bool will_randomize_items{ false };

        int gold{ 0 };
        bool will_randomize_gold{ false };
    };

    using LootOpt_t = std::optional<Loot>;
    using Loots_t   = std::vector<Loot>;

} // namespace castlecrawl

#endif // LOOT_HPP_INCLUDED
