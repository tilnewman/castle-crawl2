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
        void forceMapForEditting(const Map t_map);
        [[nodiscard]] inline Map & current() { return *m_currentIter; }

      private:
        void load(const Context & t_context);
        void verify() const;
        void loadMonsters(const Context & t_context);
        void unloadMonsters(const Context & t_context);

      private:
        std::vector<Map> m_maps;
        std::vector<Map>::iterator m_currentIter;
    };

} // namespace castlecrawl

#endif // MAPS_HPP_INCLUDED
