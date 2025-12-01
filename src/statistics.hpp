#ifndef STATISTICS_HPP
#define STATISTICS_HPP
//
// statistics.hpp
//
#include <cstddef>

namespace castlecrawl
{

    struct Statistics
    {
        void reset() { *this = Statistics(); }

        std::size_t walk_count          = 0;
        std::size_t barrels_opened      = 0;
        std::size_t rooms_discovered    = 0; // TODO
        std::size_t spells_cast         = 0;
        std::size_t monsters_killed     = 0;
        std::size_t items_collected     = 0;
        std::size_t items_dropped       = 0;
        std::size_t obstacles_destroyed = 0;
        std::size_t keys_found          = 0; // TODO
        std::size_t most_coins_held     = 0;
        std::size_t level_reached       = 0;
    };

} // namespace castlecrawl

#endif // STATISTICS_HPP
