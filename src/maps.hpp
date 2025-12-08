#ifndef MAPS_HPP_INCLUDED
#define MAPS_HPP_INCLUDED
//
// maps.hpp
//
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
        [[nodiscard]] inline Map & current() { return *m_currentIter; }
        std::size_t discoveredCount() const;

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
        std::vector<Map>::iterator m_currentIter;
    };

} // namespace castlecrawl

#endif // MAPS_HPP_INCLUDED
