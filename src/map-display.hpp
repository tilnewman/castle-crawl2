#ifndef MAPDISPLAY_HPP_INCLUDED
#define MAPDISPLAY_HPP_INCLUDED
//
// map-display.hpp
//
#include "map.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
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

} // namespace castlecrawl

#endif // MAPDISPLAY_HPP_INCLUDED
