#ifndef DOOR_LOCK_HPP_INCLUDED
#define DOOR_LOCK_HPP_INCLUDED
//
// door-lock.hpp
//
#include "json-wrapper.hpp"
#include "map-types.hpp"

#include <optional>
#include <string>
#include <vector>

namespace castlecrawl
{

    struct DoorLock
    {
        MapPos_t map_pos{ invalidMapPos };
        std::string unlocking_item_name{};
    };

    inline void to_json(nlohmann::json & j, const DoorLock & dl)
    {
        j = nlohmann::json{ { "map_pos_x", dl.map_pos.x },
                            { "map_pos_y", dl.map_pos.y },
                            { "unlocking_item_name", dl.unlocking_item_name } };
    }

    inline void from_json(const nlohmann::json & j, DoorLock & dl)
    {
        j.at("map_pos_x").get_to(dl.map_pos.x);
        j.at("map_pos_y").get_to(dl.map_pos.y);
        j.at("unlocking_item_name").get_to(dl.unlocking_item_name);
    }

    using DoorLockOpt_t = std::optional<DoorLock>;
    using DoorLocks_t   = std::vector<DoorLock>;

} // namespace castlecrawl

#endif // DOOR_LOCK_HPP_INCLUDED
