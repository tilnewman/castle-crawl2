#ifndef MAPDISPLAY_HPP_INCLUDED
#define MAPDISPLAY_HPP_INCLUDED
//
// map-display.hpp
//
#include "map.hpp"
#include "tile-image-enum.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>

namespace castlecrawl
{
    struct Context;

    class MapDisplay
    {
      public:
        MapDisplay();

        void load(const Context & context);

        void
            draw(const Context & context, sf::RenderTarget & target, sf::RenderStates states) const;

      private:
        void reset(const Context & context);
        void appendVerts(const Context & context);
        void appendLiquidEdgeVerts(const Context & context);
        void resetVertexBuffers();

        void appendTileVerts(
            const Context & context,
            const TileImage image,
            const sf::Vector2f & pos,
            VertVec_t & verts) const;

        bool isFloorAdjacent(const Context & context, const MapPos_t pos) const;

      private:
        VertVec_t m_objectVerts;
        VertVec_t m_floorVerts;
        VertVec_t m_borderVerts;

        sf::VertexBuffer m_objectBuffer;
        sf::VertexBuffer m_floorBuffer;
        sf::VertexBuffer m_borderBuffer;
    };

} // namespace castlecrawl

#endif // MAPDISPLAY_HPP_INCLUDED
