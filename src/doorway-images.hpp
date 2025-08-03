#ifndef DOORWAY_IMAGES_HPP_INCLUDE
#define DOORWAY_IMAGES_HPP_INCLUDE
//
// doorway-images.hpp
//
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl
{

    struct Context;
    struct GameConfig;

    //

    enum class DoorwayImage
    {
        Wood,
        WoodRune,
        SatanicGray,
        SatanicRed,
        RuneOpen,
        RuneGray,
        RuneBlue,
        RuneSkull,
        MirrorLit,
        Mirror,
        SantaicLava,
        Candle,
        Ghost,
        Snake,
        Oriental,
        OrientalRed
    };

    inline const sf::IntRect doorwayImageToRect(const DoorwayImage t_image) noexcept
    {
        // clang-format off
        switch (t_image)
        {
            case DoorwayImage::Wood:        { return { { 0,  0}, {32, 32} }; }
            case DoorwayImage::WoodRune:    { return { {32,  0}, {32, 32} }; }
            case DoorwayImage::SatanicGray: { return { {64,  0}, {32, 32} }; }
            case DoorwayImage::SatanicRed:  { return { {96,  0}, {32, 32} }; }
            case DoorwayImage::RuneOpen:    { return { { 0, 32}, {32, 32} }; }
            case DoorwayImage::RuneGray:    { return { {32, 32}, {32, 32} }; }
            case DoorwayImage::RuneBlue:    { return { {64, 32}, {32, 32} }; }
            case DoorwayImage::RuneSkull:   { return { {96, 32}, {32, 32} }; }
            case DoorwayImage::MirrorLit:   { return { { 0, 64}, {32, 32} }; }
            case DoorwayImage::Mirror:      { return { {32, 64}, {32, 32} }; }
            case DoorwayImage::SantaicLava: { return { {64, 64}, {32, 32} }; }
            case DoorwayImage::Candle:      { return { {96, 64}, {32, 32} }; }
            case DoorwayImage::Ghost:       { return { {0,  96}, {32, 32} }; }
            case DoorwayImage::Snake:       { return { {32, 96}, {32, 32} }; }
            case DoorwayImage::Oriental:    { return { {64, 96}, {32, 32} }; }
            case DoorwayImage::OrientalRed:
            default:                        { return { {96, 96}, {32, 32} }; }
        }
        // clang-format on
    }

    //

    class DoorwayImages
    {
      public:
        DoorwayImages();

        void setup(const GameConfig & t_config);

        [[nodiscard]] const sf::Sprite
            get(const Context & t_context, const DoorwayImage t_image) const;

      private:
        sf::Texture m_texture;
    };

} // namespace castlecrawl

#endif // DOORWAY_IMAGES_HPP_INCLUDE
