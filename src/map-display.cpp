// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// map-display.cpp
//
#include "map-display.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "sfml-util.hpp"
#include "tile-images.hpp"

#include <SFML/Graphics/Sprite.hpp>

namespace castlecrawl
{

    MapDisplay::MapDisplay()
        : vertReserveCount{ 0 }
        , m_objectVerts{}
        , m_floorVerts{}
        , m_borderVerts{}
        , m_objectBuffer{ sf::PrimitiveType::Triangles, sf::VertexBuffer::Usage::Static }
        , m_floorBuffer{ sf::PrimitiveType::Triangles, sf::VertexBuffer::Usage::Static }
        , m_borderBuffer{ sf::PrimitiveType::Triangles, sf::VertexBuffer::Usage::Static }
    {}

    void MapDisplay::load(const Context & t_context)
    {
        const sf::Vector2i mapSize = t_context.maps.current().size();
        vertReserveCount = (static_cast<std::size_t>(mapSize.x * mapSize.y) * util::verts_per_quad);

        t_context.layout.setupNewMap(mapSize);
        resetVertexVectors();
        appendVerts(t_context);
        appendLiquidEdgeVerts(t_context);
        resetVertexBuffers();
    }

    void MapDisplay::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_states.texture = &t_context.tile_images.texture();

        t_target.draw(m_floorBuffer, t_states);
        t_target.draw(m_borderBuffer); // no states here because edge verts are solid black
        t_target.draw(m_objectBuffer, t_states);
    }

    void MapDisplay::resetVertexVectors()
    {
        m_objectVerts.clear();
        m_floorVerts.clear();
        m_borderVerts.clear();

        m_objectVerts.reserve(vertReserveCount * 2); // there can be extra object verts
        m_floorVerts.reserve(vertReserveCount);
        m_borderVerts.reserve(vertReserveCount);
    }

    void MapDisplay::appendVerts(const Context & t_context)
    {
        char prevObjectChar('.'); // anything except '-' works here

        // any TileImage works here because only using the position and size
        sf::Sprite edgeSprite = t_context.tile_images.sprite(t_context, TileImage::Lava);

        // make floor border tile bigger to cover outside edges of walls with solid black
        const float growScale = 0.25f;

        const float overlapDimm{ static_cast<float>(t_context.layout.cellSize().x) *
                                 (growScale * 0.5f) };

        edgeSprite.scale({ (1.0f + growScale), (1.0f + growScale) });

        // loop over map chars and for each map tile/object/shadow/etc append quad verts
        const sf::Vector2i mapSize = t_context.maps.current().size();
        sf::Vector2f screenPos     = t_context.layout.mapRect().position;
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const MapCell cell = t_context.maps.current().cell({ x, y });

                // black floor borders tiles
                if (('.' == cell.object_char) && isFloorAdjacent(t_context, cell.position))
                {
                    edgeSprite.setPosition(screenPos);
                    edgeSprite.move({ -overlapDimm, -overlapDimm });

                    util::appendTriangleVerts(
                        edgeSprite.getGlobalBounds(),
                        m_borderVerts,
                        t_context.config.background_color);
                }

                // floor tiles
                if (' ' != cell.floor_char)
                {
                    appendTileVerts(
                        t_context, charToTileImage(cell.floor_char), screenPos, m_floorVerts);
                }

                // various object tiles
                if (const TileImage objectTileImage = charToTileImage(cell.object_char);
                    objectTileImage != TileImage::Empty)
                {
                    appendTileVerts(t_context, objectTileImage, screenPos, m_objectVerts);
                }

                // wall shadow object tiles to the right of various wall blocks
                // must be added after object tiles
                if (('-' == cell.object_char) && ('-' != prevObjectChar))
                {
                    appendTileVerts(t_context, TileImage::Wall_Shadow, screenPos, m_objectVerts);
                }

                prevObjectChar = cell.object_char;
                screenPos.x += t_context.layout.cellSize().x;
            }

            screenPos.x = t_context.layout.mapRect().position.x;
            screenPos.y += t_context.layout.cellSize().y;
        }
    }

    void MapDisplay::appendLiquidEdgeVerts(const Context & t_context)
    {
        auto isLiquid = [](const char ch) { return ((ch == 'l') || (ch == 'w') || (ch == 'g')); };

        auto validNotLiquid = [&](const char ch, const MapPos_t & pos) {
            return (!isLiquid(ch) && t_context.maps.current().isPosValid(pos));
        };

        auto getChar = [&](const int x, const int y) {
            return t_context.maps.current().cell({ x, y }).object_char;
        };

        const sf::Vector2i mapSize = t_context.maps.current().size();
        sf::Vector2f screenPos     = t_context.layout.mapRect().position;
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                // chars in all directions
                const char ch{ getChar(x, y) };
                const char upChar{ getChar(x, y - 1) };
                const char downChar{ getChar(x, y + 1) };
                const char leftChar{ getChar(x - 1, y) };
                const char rightChar{ getChar(x + 1, y) };

                // pos in all directions
                const MapPos_t upPos{ x, y - 1 };
                const MapPos_t downPos{ x, y + 1 };
                const MapPos_t leftPos{ x - 1, y };
                const MapPos_t rightPos{ x + 1, y };

                if (isLiquid(ch))
                {
                    // liquid rim corners
                    if (validNotLiquid(upChar, upPos) && validNotLiquid(leftChar, leftPos))
                    {
                        appendTileVerts(
                            t_context, TileImage::LiquidRim_TopLeft, screenPos, m_objectVerts);
                    }

                    if (validNotLiquid(upChar, upPos) && validNotLiquid(rightChar, rightPos))
                    {
                        appendTileVerts(
                            t_context, TileImage::LiquidRim_TopRight, screenPos, m_objectVerts);
                    }

                    if (validNotLiquid(downChar, downPos) && validNotLiquid(leftChar, leftPos))
                    {
                        appendTileVerts(
                            t_context, TileImage::LiquidRim_BotLeft, screenPos, m_objectVerts);
                    }

                    if (validNotLiquid(downChar, downPos) && validNotLiquid(rightChar, rightPos))
                    {
                        appendTileVerts(
                            t_context, TileImage::LiquidRim_BotRight, screenPos, m_objectVerts);
                    }

                    // liquid rim sides
                    if (validNotLiquid(upChar, upPos))
                    {
                        appendTileVerts(
                            t_context, TileImage::LiquidRim_Top, screenPos, m_objectVerts);
                    }

                    if (validNotLiquid(downChar, downPos))
                    {
                        appendTileVerts(
                            t_context, TileImage::LiquidRim_Bot, screenPos, m_objectVerts);
                    }

                    if (validNotLiquid(leftChar, leftPos))
                    {
                        appendTileVerts(
                            t_context, TileImage::LiquidRim_Left, screenPos, m_objectVerts);
                    }

                    if (validNotLiquid(rightChar, rightPos))
                    {
                        appendTileVerts(
                            t_context, TileImage::LiquidRim_Right, screenPos, m_objectVerts);
                    }
                }
                else
                {
                    const sf::Vector2f cellSize = t_context.layout.cellSize();

                    // liquid rim corners
                    if (isLiquid(getChar(x - 1, y - 1)) && isLiquid(upChar) && isLiquid(leftChar))
                    {
                        appendTileVerts(
                            t_context,
                            TileImage::LiquidCor_TopLeft,
                            (screenPos - cellSize),
                            m_objectVerts);
                    }

                    if (isLiquid(getChar(x + 1, y - 1)) && isLiquid(upChar) && isLiquid(rightChar))
                    {
                        appendTileVerts(
                            t_context,
                            TileImage::LiquidCor_TopRight,
                            { (screenPos.x + cellSize.x), (screenPos.y - cellSize.y) },
                            m_objectVerts);
                    }

                    if (isLiquid(getChar(x - 1, y + 1)) && isLiquid(downChar) && isLiquid(leftChar))
                    {
                        appendTileVerts(
                            t_context,
                            TileImage::LiquidCor_BotLeft,
                            { (screenPos.x - cellSize.x), (screenPos.y + cellSize.y) },
                            m_objectVerts);
                    }

                    if (isLiquid(getChar(x + 1, y + 1)) && isLiquid(downChar) &&
                        isLiquid(rightChar))
                    {
                        appendTileVerts(
                            t_context,
                            TileImage::LiquidCor_BotRight,
                            { (screenPos.x + cellSize.x), (screenPos.y + cellSize.y) },
                            m_objectVerts);
                    }
                }

                screenPos.x += t_context.layout.cellSize().x;
            }

            screenPos.x = t_context.layout.mapRect().position.x;
            screenPos.y += t_context.layout.cellSize().x;
        }
    }

    void MapDisplay::resetVertexBuffers()
    {
        M_CHECK(m_objectBuffer.create(m_objectVerts.size()), "m_objectBuffer.create() failed");
        if (!m_objectVerts.empty())
        {
            M_CHECK(m_objectBuffer.update(&m_objectVerts[0]), "m_objectBuffer.update() failed");
        }

        M_CHECK(m_floorBuffer.create(m_floorVerts.size()), "m_floorBuffer.create() failed");
        if (!m_floorVerts.empty())
        {
            M_CHECK(m_floorBuffer.update(&m_floorVerts[0]), "m_floorBuffer.update() failed");
        }

        M_CHECK(m_borderBuffer.create(m_borderVerts.size()), "m_borderBuffer.create() failed");
        if (!m_borderVerts.empty())
        {
            M_CHECK(m_borderBuffer.update(&m_borderVerts[0]), "m_borderBuffer.update() failed");
        }
    }

    void MapDisplay::appendTileVerts(
        const Context & t_context,
        const TileImage t_image,
        const sf::Vector2f & t_pos,
        VertVec_t & t_verts) const
    {
        util::appendTriangleVerts(t_context.tile_images.sprite(t_context, t_image, t_pos), t_verts);
    }

    bool MapDisplay::isFloorAdjacent(const Context & t_context, const MapPos_t t_pos) const
    {
        for (const MapCell & surrCell : t_context.maps.current().surroundingCellsHorizVert(t_pos))
        {
            if (' ' != surrCell.floor_char)
            {
                return true;
            }
        }

        return false;
    }

} // namespace castlecrawl
