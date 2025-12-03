// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// tile-select-button.cpp
//
#include "tile-select-button.hpp"

#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"
#include "monster-stats-database.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "tile-images.hpp"

#include <sstream>

namespace castlecrawl
{

    DropDownTile::DropDownTile(
        const Context & t_context, const TileImage t_tileImage, const sf::Vector2f & t_screenPos)
        : tile_image{ t_tileImage }
        , desc_text{ util::SfmlDefaults::instance().font() }
        , tile_sprite{ t_context.tile_images.sprite(t_context, t_tileImage) }
        , background_sprite{ t_context.tile_images.sprite(t_context, TileImage::DarkBackground) }
        , outline_rectangle{}
    {
        tile_sprite.setPosition(t_screenPos);
        background_sprite.setPosition(t_screenPos);

        outline_rectangle.setFillColor(sf::Color::Transparent);
        outline_rectangle.setOutlineColor(sf::Color(0, 255, 255, 127));
        outline_rectangle.setOutlineThickness(1.0f);
        outline_rectangle.setPosition(tile_sprite.getPosition());
        outline_rectangle.setSize(tile_sprite.getGlobalBounds().size);

        desc_text = t_context.fonts.makeText(
            FontSize::Small, makeDescription(t_context, t_tileImage), sf::Color::Transparent);

        desc_text.setPosition(
            { (util::right(tile_sprite) + 6.0f),
              (util::center(tile_sprite).y - (desc_text.getGlobalBounds().size.y * 0.5f)) });
    }

    void DropDownTile::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(background_sprite, t_states);
        t_target.draw(tile_sprite, t_states);
        t_target.draw(outline_rectangle, t_states);
        t_target.draw(desc_text, t_states);
    }

    std::string
        DropDownTile::makeDescription(const Context & t_context, const TileImage t_tileImage) const
    {
        if (!isTileImageMonster(t_tileImage))
        {
            return std::string(toString(t_tileImage));
        }

        const MonsterStats stats = t_context.monster_stats.find(t_tileImage);

        std::ostringstream ss;
        ss << toString(t_tileImage);
        ss << ":  health=" << stats.health_max;
        ss << ", armor=" << stats.armor;

        if (stats.is_undead)
        {
            ss << ", undead";
        }

        if (stats.is_immune_to_nonmagical_weapons)
        {
            ss << ", immune";
        }

        if (stats.breathe_fire_attack_ratio > 0.0f)
        {
            ss << ", fire_breath";
        }

        if (stats.poison_attack_ratio > 0.0f)
        {
            ss << ", poisonous";
        }

        if (stats.acid_attack_ratio > 0.0f)
        {
            ss << ", sprays_acid";
        }

        if (stats.break_attack_ratio > 0.0f)
        {
            ss << ", breaks_weapons";
        }

        if (stats.devour_attack_ratio > 0.0f)
        {
            ss << ", devours_armor";
        }

        if (stats.is_strong_to_ice_weak_to_fire)
        {
            ss << ", of_ice";
        }

        if (stats.is_strong_to_fire_weak_to_ice)
        {
            ss << ", of_fire";
        }

        if (stats.mana_max > 0)
        {
            ss << ", mana=" << stats.mana_max;
            ss << ", cast_ratio=" << stats.spell_attack_ratio;
            ss << ", (";
            for (const Spell spell : stats.spells)
            {
                ss << toString(spell) << '/';
            }
            ss << ")";
        }

        return ss.str();
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
        m_tiles.clear();

        sf::Vector2f screenPos = t_screenPos;
        for (const TileImage & tileImage : t_tileImages)
        {
            m_tiles.emplace_back(t_context, tileImage, screenPos);
            screenPos.y += (t_context.layout.cellSize().y + 1.0f);
        }
    }

    void TileSelectButton::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
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
            bounds = m_tiles.front().tile_sprite.getGlobalBounds();

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
                if (tile.tile_sprite.getGlobalBounds().contains(t_screenPos))
                {
                    return tile.tile_image;
                }
            }
        }
        else if (m_tiles.front().tile_sprite.getGlobalBounds().contains(t_screenPos))
        {
            return m_tiles.front().tile_image;
        }

        return TileImage::Empty;
    }

    void TileSelectButton::updateMousePos(const sf::Vector2f & t_mousePos)
    {
        for (DropDownTile & tile : m_tiles)
        {
            if (tile.tile_sprite.getGlobalBounds().contains(t_mousePos))
            {
                tile.outline_rectangle.setOutlineColor(sf::Color(0, 255, 255, 255));
                tile.desc_text.setFillColor(sf::Color::White);
            }
            else
            {
                tile.outline_rectangle.setOutlineColor(sf::Color(0, 255, 255, 127));
                tile.desc_text.setFillColor(sf::Color::Transparent);
            }
        }
    }

} // namespace castlecrawl
