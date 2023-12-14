#ifndef CASTLECRAWL2_MAPDISPLAY_HPP_INCLUDED
#define CASTLECRAWL2_MAPDISPLAY_HPP_INCLUDED
//
// map-display.hpp
//
#include "map.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl2
{
    struct Context;

    class MapDisplay
    {
      public:
        MapDisplay();

        void load(const Context & context);
        void dumpToConsole() const;

        void
            draw(const Context & context, sf::RenderTarget & target, sf::RenderStates states) const;

      private:
        void reset();
        void appendVerts(const Context & context);
        void appendLiquidEdgeVerts(const Context & context);

      private:
        VertVec_t m_objectVerts;
        VertVec_t m_floorVerts;
        VertVec_t m_borderVerts;
    };

} // namespace castlecrawl2

#endif // CASTLECRAWL2_MAPDISPLAY_HPP_INCLUDED
