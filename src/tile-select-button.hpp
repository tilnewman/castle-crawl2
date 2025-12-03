#ifndef TILE_SELECT_BUTTON_HPP_INCLUDED
#define TILE_SELECT_BUTTON_HPP_INCLUDED
//
// tile-select-button.hpp
//
#include "tile-image-enum.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>
#include <vector>

namespace castlecrawl
{

    struct Context;

    //

    struct DropDownTile
    {
        DropDownTile(
            const Context & t_context,
            const TileImage t_tileImage,
            const sf::Vector2f & t_screenPos);

        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

        std::string makeDescription(const Context & t_context, const TileImage t_tileImage) const;

        TileImage tile_image;
        sf::Text desc_text;
        sf::Sprite tile_sprite;
        sf::Sprite background_sprite;
        sf::RectangleShape outline_rectangle;
    };

    //

    class TileSelectButton
    {
      public:
        TileSelectButton();

        void setup(
            const Context & t_context,
            const sf::Vector2f & t_screenPos,
            const std::vector<TileImage> & t_tileImages);

        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

        inline void setIsDroppedDown(const bool t_isDroppedDown)
        {
            m_isDroppedDown = t_isDroppedDown;
        }

        [[nodiscard]] const sf::FloatRect globalBounds() const;

        [[nodiscard]] TileImage screenPosToTileImage(const sf::Vector2f &) const;

        void updateMousePos(const sf::Vector2f & t_mousePos);

      private:
        bool m_isDroppedDown;
        std::vector<DropDownTile> m_tiles;
    };

} // namespace castlecrawl

#endif // TILE_SELECT_BUTTON_HPP_INCLUDED
