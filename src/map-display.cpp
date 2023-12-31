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
#include "tile-image-enum.hpp"
#include "tile-images.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

namespace castlecrawl
{

    MapDisplay::MapDisplay()
        : m_objectVerts()
        , m_floorVerts()
        , m_borderVerts()
    {}

    void MapDisplay::load(const Context & context)
    {
        context.layout.setupNewMap(context.maps.current().size());
        reset();
        appendVerts(context);
        appendLiquidEdgeVerts(context);
    }

    void MapDisplay::reset()
    {
        m_objectVerts.clear();
        m_floorVerts.clear();
        m_borderVerts.clear();

        // these values found by experiment to work well with even the largest of maps
        m_objectVerts.reserve(2000);
        m_floorVerts.reserve(3000);
        m_borderVerts.reserve(2000);
    }

    void MapDisplay::dumpToConsole() const
    {
        std::cout << "object_verts: " << m_objectVerts.size() << std::endl;
        std::cout << "floor_verts: " << m_floorVerts.size() << std::endl;
        std::cout << "edge_verts: " << m_borderVerts.size() << std::endl << std::endl;
    }

    void MapDisplay::appendVerts(const Context & context)
    {
        char prevObjectChar('.'); // anything except '-' works here

        // any non-empty works here because empty would be transparent and the color would not work
        sf::Sprite edgeSprite = context.tile_images.sprite(context, TileImage::Lava);
        edgeSprite.setColor(context.config.background_color);

        // make edge verts bigger to cover corner cases (it's drawn below walls anyway)
        const float growScale = 0.5f;
        edgeSprite.scale((1.0f + growScale), (1.0f + growScale));
        const float mapCellDimm{ context.layout.cellSize().x };
        const float overlapDimm{ mapCellDimm * (growScale * 0.5f) };
        const sf::Vector2f overlap{ overlapDimm, overlapDimm };

        const sf::Vector2i mapSize = context.maps.current().size();
        sf::Vector2f screenPos     = util::position(context.layout.mapRect());
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const MapCell cell = context.maps.current().cell({ x, y });

                if ('.' == cell.object_char)
                {
                    edgeSprite.setPosition(screenPos);
                    edgeSprite.move(-overlapDimm, -overlapDimm);

                    util::appendQuadVerts(
                        edgeSprite.getGlobalBounds(),
                        m_borderVerts,
                        context.config.background_color);
                }

                if (' ' != cell.floor_char)
                {
                    sf::Sprite floorSprite =
                        context.tile_images.sprite(context, charToTileImage(cell.floor_char));

                    floorSprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        floorSprite.getGlobalBounds(), floorSprite.getTextureRect(), m_floorVerts);
                }

                const TileImage tileImage = charToTileImage(cell.object_char);
                if (tileImage != TileImage::Empty)
                {
                    sf::Sprite sprite = context.tile_images.sprite(context, tileImage);
                    sprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), sprite.getTextureRect(), m_objectVerts);
                }

                if (('-' == cell.object_char) && ('-' != prevObjectChar))
                {
                    sf::Sprite sprite = context.tile_images.sprite(context, TileImage::Wall_Shadow);
                    sprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), sprite.getTextureRect(), m_objectVerts);
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
            const MapCell cell = context.maps.current().cell({ x, y });
            return cell.object_char;
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
                    sf::Sprite sprite =
                        context.tile_images.sprite(context, TileImage::LiquidRim_TopLeft);

                    sprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), sprite.getTextureRect(), m_objectVerts);
                }

                if (validNotLiquid(upChar, upPos) && validNotLiquid(rightChar, rightPos))
                {
                    sf::Sprite sprite =
                        context.tile_images.sprite(context, TileImage::LiquidRim_TopRight);

                    sprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), sprite.getTextureRect(), m_objectVerts);
                }

                if (validNotLiquid(downChar, downPos) && validNotLiquid(leftChar, leftPos))
                {
                    sf::Sprite sprite =
                        context.tile_images.sprite(context, TileImage::LiquidRim_BotLeft);

                    sprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), sprite.getTextureRect(), m_objectVerts);
                }

                if (validNotLiquid(downChar, downPos) && validNotLiquid(rightChar, rightPos))
                {
                    sf::Sprite sprite =
                        context.tile_images.sprite(context, TileImage::LiquidRim_BotRight);

                    sprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), sprite.getTextureRect(), m_objectVerts);
                }

                if (validNotLiquid(upChar, upPos))
                {
                    sf::Sprite sprite =
                        context.tile_images.sprite(context, TileImage::LiquidRim_Top);

                    sprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), sprite.getTextureRect(), m_objectVerts);
                }

                if (validNotLiquid(downChar, downPos))
                {
                    sf::Sprite sprite =
                        context.tile_images.sprite(context, TileImage::LiquidRim_Bot);

                    sprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), sprite.getTextureRect(), m_objectVerts);
                }

                if (validNotLiquid(leftChar, leftPos))
                {
                    sf::Sprite sprite =
                        context.tile_images.sprite(context, TileImage::LiquidRim_Left);

                    sprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), sprite.getTextureRect(), m_objectVerts);
                }

                if (validNotLiquid(rightChar, rightPos))
                {
                    sf::Sprite sprite =
                        context.tile_images.sprite(context, TileImage::LiquidRim_Right);

                    sprite.setPosition(screenPos);

                    util::appendQuadVerts(
                        sprite.getGlobalBounds(), sprite.getTextureRect(), m_objectVerts);
                }

                screenPos.x += context.layout.cellSize().x;
            }

            screenPos.x = context.layout.mapRect().left;
            screenPos.y += context.layout.cellSize().x;
        }
    }

    void MapDisplay::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        states.texture = &context.tile_images.texture();

        if (!m_floorVerts.empty())
        {
            target.draw(&m_floorVerts[0], m_floorVerts.size(), sf::Quads, states);
        }

        if (!m_borderVerts.empty())
        {
            // don't use states because the floor edge verts are just solid color
            target.draw(&m_borderVerts[0], m_borderVerts.size(), sf::Quads);
        }

        if (!m_objectVerts.empty())
        {
            target.draw(&m_objectVerts[0], m_objectVerts.size(), sf::Quads, states);
        }
    }

} // namespace castlecrawl
