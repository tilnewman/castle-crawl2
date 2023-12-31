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

        void setup(const Context & context);
        void change(const Context & context, const MapName mapName, const MapPos_t & pos);
        void forceMapForEditting(const Map map);
        Map & current() { return *m_currentIter; }

      private:
        void load(const Context & context);
        void verify() const;

        void loadEnemies(const Context & context, Map & map) const;
        void unloadEnemies(const Context & context) const;

      private:
        std::vector<Map> m_maps;
        std::vector<Map>::iterator m_currentIter;
    };

} // namespace castlecrawl

#endif // MAPS_HPP_INCLUDED
