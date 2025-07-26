#ifndef SPLATIMAGES_HPP_INCLUDED
#define SPLATIMAGES_HPP_INCLUDED
//
// splat-images.hpp
//
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl
{
    struct Context;
    struct GameConfig;

    class SplatImages
    {
      public:
        SplatImages();

        void setup(const GameConfig & t_config);
        const sf::Sprite & getRandom(const Context & t_context) const;

      private:
        sf::Texture m_texture;
        sf::Sprite m_sprite1;
        sf::Sprite m_sprite2;
        sf::Sprite m_sprite3;
        sf::Sprite m_sprite4;
        sf::Sprite m_sprite5;
        sf::Sprite m_sprite6;
    };

} // namespace castlecrawl

#endif // SPLATIMAGES_HPP_INCLUDED