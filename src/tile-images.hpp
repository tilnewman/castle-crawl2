#ifndef TILEIMAGES_HPP_INCLUDED
#define TILEIMAGES_HPP_INCLUDED
//
// tile-images.hpp
//
#include "context.hpp"
#include "enemy.hpp"
#include "tile-image-enum.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl
{
    struct Context;
    struct GameConfig;

    class TileImages
    {
      public:
        TileImages();

        void setup(const GameConfig & t_config);

        [[nodiscard]] const sf::Sprite sprite(
            const Context & t_context,
            const TileImage t_tileImage,
            const sf::Vector2f & t_pos = {}) const;

        [[nodiscard]] inline const sf::Texture & texture() const { return m_texture; }

      private:
        sf::Texture m_texture;
    };

} // namespace castlecrawl

#endif // TILEIMAGES_HPP_INCLUDED
