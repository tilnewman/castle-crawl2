#ifndef FONT_HPP_INCLUDED
#define FONT_HPP_INCLUDED
//
// font.hpp
//
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

namespace castlecrawl2
{
    struct GameConfig;

    enum class FontSize
    {
        Huge,
        Large,
        Medium,
        Small
    };

    struct FontExtent
    {
        unsigned int char_size = 0;
        sf::Vector2f letter_size;
    };

    class FontManager
    {
      public:
        FontManager();

        void setup(const GameConfig & config);
        const sf::Font & font() const { return m_font; }

        inline const FontExtent extent(const FontSize size) const noexcept
        {
            // clang-format off
            switch (size)
            {
                case FontSize::Huge:    { return m_fontExtentHuge; }
                case FontSize::Large:   { return m_fontExtentLarge; }
                case FontSize::Medium:  { return m_fontExtentMedium; }
                case FontSize::Small:  
                default:                { return m_fontExtentSmall; }
            }
            // clang-format on
        }

        const sf::Text makeText(
            const FontSize size,
            const std::string & str,
            const sf::Color & color = sf::Color::White) const;

      private:
        void setupFontExtents(const GameConfig & config);

      private:
        sf::Font m_font;

        FontExtent m_fontExtentHuge;
        FontExtent m_fontExtentLarge;
        FontExtent m_fontExtentMedium;
        FontExtent m_fontExtentSmall;
    };

} // namespace castlecrawl2

#endif // FONT_HPP_INCLUDED
