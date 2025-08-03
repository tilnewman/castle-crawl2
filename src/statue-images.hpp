#ifndef STATUE_IMAGES_HPP_INCLUDE
#define STATUE_IMAGES_HPP_INCLUDE
//
// statue-images.hpp
//
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl
{

    struct Context;
    struct GameConfig;

    //

    enum class StatueImage
    {
        Twins,
        Mermaid,
        Demonic,
        Wraith,
        Sword,
        Thresher,
        Orb,
        Naga,
        Imp,
        Hydra,
        Elephant,
        Dwarf,
        Dragon,
        Flamberg,
        Centaur,
        Cat,
        Angel,
        Monster,
        Princess,
        Tengu
    };

    inline const sf::IntRect statueImageToRect(const StatueImage t_image) noexcept
    {
        // clang-format off
        switch (t_image)
        {
            case StatueImage:: Twins:       { return { {  0,  0}, {32, 32} }; }
            case StatueImage:: Mermaid:     { return { { 32,  0}, {32, 32} }; }
            case StatueImage:: Demonic:     { return { { 64,  0}, {32, 32} }; }
            case StatueImage:: Wraith:      { return { { 96,  0}, {32, 32} }; }
            case StatueImage:: Sword:       { return { {128,  0}, {32, 32} }; }
            case StatueImage:: Thresher:    { return { {  0, 32}, {32, 32} }; }
            case StatueImage:: Orb:         { return { { 32, 32}, {32, 32} }; }
            case StatueImage:: Naga:        { return { { 64, 32}, {32, 32} }; }
            case StatueImage:: Imp:         { return { { 96, 32}, {32, 32} }; }
            case StatueImage:: Hydra:       { return { {128, 32}, {32, 32} }; }
            case StatueImage:: Elephant:    { return { {  0, 64}, {32, 32} }; }
            case StatueImage:: Dwarf:       { return { { 32, 64}, {32, 32} }; }
            case StatueImage:: Dragon:      { return { { 64, 64}, {32, 32} }; }
            case StatueImage:: Flamberg:    { return { { 96, 64}, {32, 32} }; }
            case StatueImage:: Centaur:     { return { {128, 64}, {32, 32} }; }
            case StatueImage:: Cat:         { return { {  0, 96}, {32, 32} }; }
            case StatueImage:: Angel:       { return { { 32, 96}, {32, 32} }; }
            case StatueImage:: Monster:     { return { { 64, 96}, {32, 32} }; }
            case StatueImage:: Princess:    { return { { 96, 96}, {32, 32} }; }
            case StatueImage:: Tengu:
            default:                        { return { {128, 96}, {32, 32} }; }
        }
        // clang-format on
    }

    //

    class StatueImages
    {
      public:
        StatueImages();

        void setup(const GameConfig & t_config);

        [[nodiscard]] const sf::Sprite
            get(const Context & t_context, const StatueImage t_image) const;

      private:
        sf::Texture m_texture;
    };

} // namespace castlecrawl

#endif // STATUE_IMAGES_HPP_INCLUDE
