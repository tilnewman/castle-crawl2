#ifndef LOOT_HPP_INCLUDED
#define LOOT_HPP_INCLUDED
//
// loot.hpp
//
#include "json-wrapper.hpp"
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

    inline void to_json(nlohmann::json & j, const Loot & l)
    {
        j = nlohmann::json{ { "has_been_collected", l.has_been_collected },
                            { "map_pos_x", l.map_pos.x },
                            { "map_pos_y", l.map_pos.y },
                            { "item_names", l.item_names },
                            { "will_randomize_items", l.will_randomize_items },
                            { "gold", l.gold },
                            { "will_randomize_gold", l.will_randomize_gold } };
    }

    inline void from_json(const nlohmann::json & j, Loot & l)
    {
        j.at("has_been_collected").get_to(l.has_been_collected);
        j.at("map_pos_x").get_to(l.map_pos.x);
        j.at("map_pos_y").get_to(l.map_pos.y);
        j.at("item_names").get_to(l.item_names);
        j.at("will_randomize_items").get_to(l.will_randomize_items);
        j.at("gold").get_to(l.gold);
        j.at("will_randomize_gold").get_to(l.will_randomize_gold);
    }

} // namespace castlecrawl

#endif // LOOT_HPP_INCLUDED
