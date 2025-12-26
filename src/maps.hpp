#ifndef MAPS_HPP_INCLUDED
#define MAPS_HPP_INCLUDED
//
// maps.hpp
//
#include "json-wrapper.hpp"
#include "map-types.hpp"
#include "map.hpp"

#include <vector>

namespace castlecrawl
{
    struct Context;

    class Maps
    {
      public:
        Maps();

        void setup(const Context & t_context);
        void change(const Context & t_context, const MapName t_mapName, const MapPos_t & t_pos);
        void forceMapForEditting(const Context & t_context, const Map t_map);
        [[nodiscard]] Map & current();
        std::size_t discoveredCount() const;

        friend void to_json(nlohmann::json & j, const Maps & m);
        friend void from_json(const nlohmann::json & j, Maps & m);

      private:
        void load(const Context & t_context);
        void verify(const Context & t_context) const;
        void verifyTransitions(const Context & t_context, const Map & t_map) const;
        void verifyLookEvents(const Context & t_context, const Map & t_map) const;
        void verifyDoorLocks(const Context & t_context, const Map & t_map) const;
        void verifyLoots(const Context & t_context, const Map & t_map) const;
        void loadCreatures(const Context & t_context);
        void unloadCreatures(const Context & t_context);
        void loadAnimations(const Context & t_context);
        void unloadAnimations(const Context & t_context);

      private:
        std::vector<Map> m_maps;
        std::size_t m_currentIndex;
    };

    inline void to_json(nlohmann::json & j, const Maps & m)
    {
        j = nlohmann::json{ { "maps", m.m_maps } };
        j = nlohmann::json{ { "currentIndex", m.m_currentIndex } };
    }

    inline void from_json(const nlohmann::json & j, Maps & m)
    {
        j.at("maps").get_to(m.m_maps);
        j.at("currentIndex").get_to(m.m_currentIndex);
    }

} // namespace castlecrawl

#endif // MAPS_HPP_INCLUDED
