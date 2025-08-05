// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// tile-select-button.cpp
//
#include "tile-select-button.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "sfml-util.hpp"
#include "tile-images.hpp"

namespace castlecrawl
{

    DropDownTile::DropDownTile(
        const Context & t_context, const TileImage t_tileImage, const sf::Vector2f & t_screenPos)
        : tile_image{ t_tileImage }
        , sprite{ t_context.tile_images.sprite(t_context, t_tileImage) }
        , outline_rectangle{}
        , background_rectangle{}
    {
        sprite.setPosition(t_screenPos);

        outline_rectangle.setFillColor(sf::Color::Transparent);
        outline_rectangle.setOutlineColor(sf::Color(0, 255, 255, 127));
        outline_rectangle.setOutlineThickness(1.0f);
        outline_rectangle.setPosition(sprite.getPosition());
        outline_rectangle.setSize(sprite.getGlobalBounds().size);

        background_rectangle.setFillColor(sf::Color::Black);
        background_rectangle.setPosition(sprite.getPosition());
        background_rectangle.setSize(sprite.getGlobalBounds().size);
    }

    void DropDownTile::draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        t_target.draw(background_rectangle, t_states);
        t_target.draw(sprite, t_states);
        t_target.draw(outline_rectangle, t_states);
    }

    //

    TileSelectButton::TileSelectButton()
        : m_isDroppedDown{ false }
        , m_tiles{}
    {}

    void TileSelectButton::setup(
        const Context & t_context,
        const sf::Vector2f & t_screenPos,
        const std::vector<TileImage> & t_tileImages)
    {
        sf::Vector2f screenPos = t_screenPos;
        for (const TileImage & tileImage : t_tileImages)
        {
            m_tiles.emplace_back(t_context, tileImage, screenPos);
            screenPos.y += t_context.layout.cellSize().y;
        }
    }

    // void TileSelectButton::update(const Context & t_context, const float t_elapsedTimeSec) {}

    void TileSelectButton::draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        if (m_isDroppedDown)
        {
            for (const DropDownTile & tile : m_tiles)
            {
                tile.draw(t_target, t_states);
            }
        }
        else if (!m_tiles.empty())
        {
            m_tiles.front().draw(t_target, t_states);
        }
    }

    const sf::FloatRect TileSelectButton::globalBounds() const
    {
        sf::FloatRect bounds{ { 0.0f, 0.0f }, { 0.0f, 0.0f } };

        if (!m_tiles.empty())
        {
            bounds = m_tiles.front().sprite.getGlobalBounds();

            if (m_isDroppedDown)
            {
                bounds.size.y = (static_cast<float>(m_tiles.size()) * bounds.size.y);
            }
        }

        return bounds;
    }

    TileImage TileSelectButton::screenPosToTileImage(const sf::Vector2f & t_screenPos) const
    {
        if (m_tiles.empty())
        {
            return TileImage::Empty;
        }

        if (m_isDroppedDown)
        {
            for (const DropDownTile & tile : m_tiles)
            {
                if (tile.sprite.getGlobalBounds().contains(t_screenPos))
                {
                    return tile.tile_image;
                }
            }
        }
        else if (m_tiles.front().sprite.getGlobalBounds().contains(t_screenPos))
        {
            return m_tiles.front().tile_image;
        }

        return TileImage::Empty;
    }

} // namespace castlecrawl
