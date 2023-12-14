#ifndef CASTLECRAWL2_TILEIMAGES_HPP_INCLUDED
#define CASTLECRAWL2_TILEIMAGES_HPP_INCLUDED
//
// tile-images.hpp
//
#include "context.hpp"
#include "enemy.hpp"
#include "tile-image-enum.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl2
{
    struct Context;
    struct GameConfig;

    class TileImages
    {
      public:
        TileImages();

        void setup(const GameConfig & config);
        const sf::Sprite sprite(const Context & context, const TileImage tileImage) const;
        const sf::Texture & texture() const { return m_texture; }

      private:
        sf::Texture m_texture;
    };

} // namespace castlecrawl2

#endif // CASTLECRAWL2_TILEIMAGES_HPP_INCLUDED
