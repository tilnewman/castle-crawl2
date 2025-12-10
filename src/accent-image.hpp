#ifndef ACCENT_IMAGE_HPP_INCLUDED
#define ACCENT_IMAGE_HPP_INCLUDED
//
// accent-image.hpp
//
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl
{

    struct Context;

    //

    class AccentImage : public sf::Drawable
    {
      public:
        AccentImage();

        void setup(const Context & t_context, const sf::FloatRect & t_rect);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

      private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
    };

} // namespace castlecrawl

#endif // ACCENT_IMAGE_HPP_INCLUDED
