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

        void load(const Context & t_context);

        void draw(const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states)
            const;

      private:
        void resetVertexVectors(const Context & t_context);
        void appendVerts(const Context & t_context);
        void appendLiquidEdgeVerts(const Context & t_context);
        void resetVertexBuffers();

        void appendTileVerts(
            const Context & t_context,
            const TileImage t_image,
            const sf::Vector2f & t_pos,
            VertVec_t & t_verts) const;

        [[nodiscard]] bool isFloorAdjacent(const Context & t_context, const MapPos_t t_pos) const;

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
