#ifndef FONT_HPP_INCLUDED
#define FONT_HPP_INCLUDED
//
// font.hpp
//
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>

namespace castlecrawl
{
    struct GameConfig;

    //

    enum class FontSize
    {
        Huge,
        Large,
        Medium,
        Small
    };

    //

    struct FontExtent
    {
        unsigned int char_size = 0;
        sf::Vector2f letter_size{};
    };

    //

    class FontManager
    {
      public:
        FontManager();

        void setup(const GameConfig & t_config);
        [[nodiscard]] const sf::Font & font() const { return m_font; }

        [[nodiscard]] inline const FontExtent extent(const FontSize t_size) const noexcept
        {
            // clang-format off
            switch (t_size)
            {
                case FontSize::Huge:    { return m_fontExtentHuge;   }
                case FontSize::Large:   { return m_fontExtentLarge;  }
                case FontSize::Medium:  { return m_fontExtentMedium; }
                case FontSize::Small:  
                default:                { return m_fontExtentSmall;  }
            }
            // clang-format on
        }

        sf::Text makeText(
            const FontSize t_size,
            const std::string & t_str,
            const sf::Color & t_color = sf::Color::White) const;

      private:
        void setupFontExtents(const GameConfig & t_config);

      private:
        sf::Font m_font;

        FontExtent m_fontExtentHuge;
        FontExtent m_fontExtentLarge;
        FontExtent m_fontExtentMedium;
        FontExtent m_fontExtentSmall;
    };

} // namespace castlecrawl

#endif // FONT_HPP_INCLUDED
