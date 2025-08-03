#ifndef ALTAR_IMAGES_HPP_INCLUDE
#define ALTAR_IMAGES_HPP_INCLUDE
//
// altar-images.hpp
//
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl
{

    struct Context;
    struct GameConfig;

    //

    enum class AltarImage
    {
        Statue,
        Challace,
        Skull,
        Throne,
        Blood,
        Body,
        Demonic,
        Hand,
        King
    };

    inline const sf::IntRect altarImageToRect(const AltarImage t_image) noexcept
    {
        // clang-format off
        switch (t_image)
        {
            case AltarImage::Statue:    { return { { 0,  0}, {32, 32} }; }
            case AltarImage::Challace:  { return { {32,  0}, {32, 32} }; }
            case AltarImage::Skull:     { return { {64,  0}, {32, 32} }; }
            case AltarImage::Throne:    { return { { 0, 32}, {32, 32} }; }
            case AltarImage::Blood:     { return { {32, 32}, {32, 32} }; }
            case AltarImage::Body:      { return { {64, 32}, {32, 32} }; }
            case AltarImage::Demonic:   { return { { 0, 64}, {32, 32} }; }
            case AltarImage::Hand:      { return { {32, 64}, {32, 32} }; }
            case AltarImage::King:      
            default:                    { return { {64, 64}, {32, 32} }; }
        }
        // clang-format on
    }

    //

    class AltarImages
    {
      public:
        AltarImages();

        void setup(const GameConfig & t_config);

        [[nodiscard]] const sf::Sprite
            get(const Context & t_context, const AltarImage t_image) const;

      private:
        sf::Texture m_texture;
    };

} // namespace castlecrawl

#endif // ALTAR_IMAGES_HPP_INCLUDE
