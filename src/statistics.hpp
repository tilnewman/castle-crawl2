#ifndef STATISTICS_HPP_INCLUDED
#define STATISTICS_HPP_INCLUDED
//
// statistics.hpp
//
#include "json-wrapper.hpp"

#include <cstddef>

namespace castlecrawl
{

    struct Statistics
    {
        void reset() { *this = Statistics(); }

        std::size_t walk_count          = 0;
        std::size_t barrels_opened      = 0;
        std::size_t coffins_opened      = 0;
        std::size_t rooms_discovered    = 0;
        std::size_t spells_cast         = 0;
        std::size_t monsters_killed     = 0;
        std::size_t items_collected     = 0;
        std::size_t items_dropped       = 0;
        std::size_t obstacles_destroyed = 0;
        std::size_t most_coins_held     = 0;
        std::size_t level_reached       = 0;
        std::size_t chests_opened       = 0;
    };

    inline void to_json(nlohmann::json & j, const Statistics & s)
    {
        j = nlohmann::json{
            { "walk_count", s.walk_count },
            { "barrels_opened", s.barrels_opened },
            { "coffins_opened", s.coffins_opened },
            { "rooms_discovered", s.rooms_discovered },
            { "spells_cast", s.spells_cast },
            { "monsters_killed", s.monsters_killed },
            { "items_collected", s.items_collected },
            { "items_dropped", s.items_dropped },
            { "obstacles_destroyed", s.obstacles_destroyed },
            { "most_coins_held", s.most_coins_held },
            { "level_reached", s.level_reached },
            { "chests_opened", s.chests_opened },
        };
    }

    inline void from_json(const nlohmann::json & j, Statistics & s)
    {
        j.at("walk_count").get_to(s.walk_count);
        j.at("barrels_opened").get_to(s.barrels_opened);
        j.at("coffins_opened").get_to(s.coffins_opened);
        j.at("rooms_discovered").get_to(s.rooms_discovered);
        j.at("spells_cast").get_to(s.spells_cast);
        j.at("monsters_killed").get_to(s.monsters_killed);
        j.at("items_collected").get_to(s.items_collected);
        j.at("items_dropped").get_to(s.items_dropped);
        j.at("obstacles_destroyed").get_to(s.obstacles_destroyed);
        j.at("most_coins_held").get_to(s.most_coins_held);
        j.at("level_reached").get_to(s.level_reached);
        j.at("chests_opened").get_to(s.chests_opened);
    }

} // namespace castlecrawl

#endif // STATISTICS_HPP_INCLUDED
