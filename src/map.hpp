#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
//
// map.hpp
//
#include "door-lock.hpp"
#include "json-wrapper.hpp"
#include "look-event.hpp"
#include "loot.hpp"
#include "map-types.hpp"

namespace castlecrawl
{
    struct Context;

    class Map
    {
      public:
        Map(); // this default contstructor creates an invalid map and is used by json

        Map(const MapName t_name,
            const Context & t_context,
            const Floor t_floor,
            const MapChars_t & t_mapChars,
            const MapTransitions_t & t_transVec,
            const LookEvents_t & t_lookEvents = {},
            const DoorLocks_t & t_doorLocks   = {},
            const Loots_t & t_loots           = {});

        [[nodiscard]] constexpr MapName name() const noexcept { return m_name; }
        [[nodiscard]] const Map_t mapCellsVec() const noexcept { return m_map; }
        [[nodiscard]] constexpr Floor floor() const noexcept { return m_floor; }

        [[nodiscard]] inline const MapTransitions_t transitions() const noexcept
        {
            return m_transitions;
        }

        [[nodiscard]] constexpr bool isEmpty() const noexcept { return m_map.empty(); }
        [[nodiscard]] constexpr bool isDiscovered() const noexcept { return m_isDiscovered; }

        [[nodiscard]] const LookEvents_t lookEvents() const noexcept { return m_lookEvents; }
        [[nodiscard]] const LookEventOpt_t lookEvent(const MapPos_t & t_pos) const;
        void setLookEventAsHappened(const MapPos_t & t_pos);

        [[nodiscard]] const DoorLocks_t doorLocks() const noexcept { return m_doorLocks; }
        [[nodiscard]] const DoorLockOpt_t doorLock(const MapPos_t & t_pos) const;

        [[nodiscard]] const Loots_t loots() const noexcept { return m_loots; }
        [[nodiscard]] const LootOpt_t loot(const MapPos_t & t_pos) const;
        void setLootAsCollected(const MapPos_t & t_pos);

        [[nodiscard]] const sf::Vector2i size() const;
        [[nodiscard]] bool isPosValid(const MapPos_t & t_pos) const;
        [[nodiscard]] MapCell cell(const MapPos_t & t_pos) const;
        void setObjectChar(const MapPos_t & t_pos, const char t_newChar);

        constexpr void setDiscovered() noexcept { m_isDiscovered = true; }

        [[nodiscard]] MapPos_t
            screenPosToMapPos(const Context & t_context, const sf::Vector2f & t_screenPos) const;

        [[nodiscard]] sf::Vector2f
            mapPosToScreenPos(const Context & t_context, const MapPos_t & t_mapPos) const;

        [[nodiscard]] const std::vector<MapCell>
            surroundingCellsHorizVert(const MapPos_t & t_pos) const;

        [[nodiscard]] const std::vector<MapCell> surroundingCellsAll(const MapPos_t & t_pos) const;

        void dumpToConsole() const;

        friend void to_json(nlohmann::json & j, const Map & m);
        friend void from_json(const nlohmann::json & j, Map & m);

      private:
        MapName m_name;
        Map_t m_map;
        Floor m_floor;
        MapTransitions_t m_transitions;
        bool m_isDiscovered;
        LookEvents_t m_lookEvents;
        DoorLocks_t m_doorLocks;
        Loots_t m_loots;
    };

    inline void to_json(nlohmann::json & j, const Map & m)
    {
        j = nlohmann::json{ { "name", m.m_name },
                            { "map", m.m_map },
                            { "floor", m.m_floor },
                            { "transitions", m.m_transitions },
                            { "isDiscovered", m.m_isDiscovered },
                            { "lookEvents", m.m_lookEvents },
                            { "doorLocks", m.m_doorLocks },
                            { "loots", m.m_loots } };
    }

    inline void from_json(const nlohmann::json & j, Map & m)
    {
        j.at("name").get_to(m.m_name);
        j.at("map").get_to(m.m_map);
        j.at("floor").get_to(m.m_floor);
        j.at("transitions").get_to(m.m_transitions);
        j.at("isDiscovered").get_to(m.m_isDiscovered);
        j.at("lookEvents").get_to(m.m_lookEvents);
        j.at("doorLocks").get_to(m.m_doorLocks);
        j.at("loots").get_to(m.m_loots);
    }

} // namespace castlecrawl

#endif // MAP_HPP_INCLUDED
