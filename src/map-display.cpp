// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// map-display.cpp
//
#include "map-display.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "sfml-util.hpp"
#include "tile-images.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace castlecrawl
{

    MapDisplay::MapDisplay()
        : m_objectVerts()
        , m_floorVerts()
        , m_borderVerts()
        , m_objectBuffer(sf::Quads, sf::VertexBuffer::Static)
        , m_floorBuffer(sf::Quads, sf::VertexBuffer::Static)
        , m_borderBuffer(sf::Quads, sf::VertexBuffer::Static)
    {}

    void MapDisplay::load(const Context & context)
    {
        context.layout.setupNewMap(context.maps.current().size());
        resetVertexVectors(context);
        appendVerts(context);
        appendLiquidEdgeVerts(context);
        resetVertexBuffers();
    }

    void MapDisplay::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        states.texture = &context.tile_images.texture();

        target.draw(m_floorBuffer, states);
        target.draw(m_borderBuffer); // don't use states because floor edge verts are solid black
        target.draw(m_objectBuffer, states);
    }

    void MapDisplay::resetVertexVectors(const Context & context)
    {
        m_objectVerts.clear();
        m_floorVerts.clear();
        m_borderVerts.clear();

        const std::size_t reserveCount =
            (static_cast<std::size_t>(context.layout.cellCount().x) *
             static_cast<std::size_t>(context.layout.cellCount().y) * util::verts_per_quad);

        m_objectVerts.reserve(reserveCount * 2); // there can be extra shadow and liquid edge verts
        m_floorVerts.reserve(reserveCount);
        m_borderVerts.reserve(reserveCount);
    }

    void MapDisplay::appendVerts(const Context & context)
    {
        char prevObjectChar('.'); // anything except '-' works here

        // any TileImage works here because only using the position and size
        sf::Sprite edgeSprite = context.tile_images.sprite(context, TileImage::Lava);

        // make floor border tile bigger to cover outside edges of walls with solid black
        const float growScale = 0.25f;

        const float overlapDimm{ static_cast<float>(context.layout.cellSize().x) *
                                 (growScale * 0.5f) };

        edgeSprite.scale((1.0f + growScale), (1.0f + growScale));

        // loop over map chars and for each map tile/object/shadow/etc append quad verts
        const sf::Vector2i mapSize = context.maps.current().size();
        sf::Vector2f screenPos     = util::position(context.layout.mapRect());
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const MapCell cell = context.maps.current().cell({ x, y });

                // black floor borders tiles
                if (('.' == cell.object_char) && isFloorAdjacent(context, cell.position))
                {
                    edgeSprite.setPosition(screenPos);
                    edgeSprite.move(-overlapDimm, -overlapDimm);

                    util::appendQuadVerts(
                        edgeSprite.getGlobalBounds(),
                        m_borderVerts,
                        context.config.background_color);
                }

                // floor tiles
                if (' ' != cell.floor_char)
                {
                    appendTileVerts(
                        context, charToTileImage(cell.floor_char), screenPos, m_floorVerts);
                }

                // various object tiles
                if (const TileImage objectTileImage = charToTileImage(cell.object_char);
                    objectTileImage != TileImage::Empty)
                {
                    appendTileVerts(context, objectTileImage, screenPos, m_objectVerts);
                }

                // wall shadow object tiles to the right of various wall blocks
                // must be added after object tiles
                if (('-' == cell.object_char) && ('-' != prevObjectChar))
                {
                    appendTileVerts(context, TileImage::Wall_Shadow, screenPos, m_objectVerts);
                }

                prevObjectChar = cell.object_char;
                screenPos.x += context.layout.cellSize().x;
            }

            screenPos.x = context.layout.mapRect().left;
            screenPos.y += context.layout.cellSize().y;
        }
    }

    void MapDisplay::appendLiquidEdgeVerts(const Context & context)
    {
        auto notLiq = [](const char ch) { return ((ch != 'l') && (ch != 'w')); };

        auto validNotLiquid = [&](const char ch, const MapPos_t & pos) {
            return (notLiq(ch) && context.maps.current().isPosValid(pos));
        };

        auto getChar = [&](const int x, const int y) {
            return context.maps.current().cell({ x, y }).object_char;
        };

        const sf::Vector2i mapSize = context.maps.current().size();
        sf::Vector2f screenPos     = util::position(context.layout.mapRect());
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const char ch{ getChar(x, y) };

                if (notLiq(ch))
                {
                    screenPos.x += context.layout.cellSize().x;
                    continue;
                }

                // chars in all directions
                const char upChar{ getChar(x, y - 1) };
                const char downChar{ getChar(x, y + 1) };
                const char leftChar{ getChar(x - 1, y) };
                const char rightChar{ getChar(x + 1, y) };

                // pos in all directions
                const MapPos_t upPos{ x, y - 1 };
                const MapPos_t downPos{ x, y + 1 };
                const MapPos_t leftPos{ x - 1, y };
                const MapPos_t rightPos{ x + 1, y };

                if (validNotLiquid(upChar, upPos) && validNotLiquid(leftChar, leftPos))
                {
                    appendTileVerts(
                        context, TileImage::LiquidRim_TopLeft, screenPos, m_objectVerts);
                }

                if (validNotLiquid(upChar, upPos) && validNotLiquid(rightChar, rightPos))
                {
                    appendTileVerts(
                        context, TileImage::LiquidRim_TopRight, screenPos, m_objectVerts);
                }

                if (validNotLiquid(downChar, downPos) && validNotLiquid(leftChar, leftPos))
                {
                    appendTileVerts(
                        context, TileImage::LiquidRim_BotLeft, screenPos, m_objectVerts);
                }

                if (validNotLiquid(downChar, downPos) && validNotLiquid(rightChar, rightPos))
                {
                    appendTileVerts(
                        context, TileImage::LiquidRim_BotRight, screenPos, m_objectVerts);
                }

                if (validNotLiquid(upChar, upPos))
                {
                    appendTileVerts(context, TileImage::LiquidRim_Top, screenPos, m_objectVerts);
                }

                if (validNotLiquid(downChar, downPos))
                {
                    appendTileVerts(context, TileImage::LiquidRim_Bot, screenPos, m_objectVerts);
                }

                if (validNotLiquid(leftChar, leftPos))
                {
                    appendTileVerts(context, TileImage::LiquidRim_Left, screenPos, m_objectVerts);
                }

                if (validNotLiquid(rightChar, rightPos))
                {
                    appendTileVerts(context, TileImage::LiquidRim_Right, screenPos, m_objectVerts);
                }

                screenPos.x += context.layout.cellSize().x;
            }

            screenPos.x = context.layout.mapRect().left;
            screenPos.y += context.layout.cellSize().x;
        }
    }

    void MapDisplay::resetVertexBuffers()
    {
        m_objectBuffer.create(m_objectVerts.size());
        m_objectBuffer.update(&m_objectVerts[0]);

        m_floorBuffer.create(m_floorVerts.size());
        m_floorBuffer.update(&m_floorVerts[0]);

        m_borderBuffer.create(m_borderVerts.size());
        m_borderBuffer.update(&m_borderVerts[0]);
    }

    void MapDisplay::appendTileVerts(
        const Context & context,
        const TileImage image,
        const sf::Vector2f & pos,
        VertVec_t & verts) const
    {
        util::appendQuadVerts(context.tile_images.sprite(context, image, pos), verts);
    }

    bool MapDisplay::isFloorAdjacent(const Context & context, const MapPos_t pos) const
    {
        for (const MapCell & surrCell : context.maps.current().surroundingCellsHorizVert(pos))
        {
            if (' ' != surrCell.floor_char)
            {
                return true;
            }
        }

        return false;
    }

} // namespace castlecrawl
