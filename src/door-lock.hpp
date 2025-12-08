#ifndef DOOR_LOCK_HPP_INCLUDED
#define DOOR_LOCK_HPP_INCLUDED
//
// door-lock.hpp
//
#include "map-types.hpp"

#include <optional>
#include <string>
#include <vector>

namespace castlecrawl
{

    struct DoorLock
    {
        MapPos_t map_pos{ -1, -1 }; // both must be negative to be invalid default
        std::string unlocking_item_name{};
    };

    using DoorLockOpt_t = std::optional<DoorLock>;
    using DoorLocks_t   = std::vector<DoorLock>;

} // namespace castlecrawl

#endif // DOOR_LOCK_HPP_INCLUDED
