#ifndef TEXT_LAYOUT_HPP_INCLUDED
#define TEXT_LAYOUT_HPP_INCLUDED
//
// text-layout.hpp
//
#include "font.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>
#include <vector>

namespace castlecrawl
{

    struct Context;

    //

    struct TextLayoutPack
    {
        sf::FloatRect rect_outer{};
        sf::FloatRect rect_inner{};
        std::vector<sf::Text> texts{};
    };

    //

    class TextLayout
    {
      public:
        [[nodiscard]] static const TextLayoutPack typeset(
            const Context & t_context,
            const std::string & t_text,
            const sf::FloatRect & t_rect,
            const FontSize & t_fontSize,
            const float t_padRatio         = 0.0f,
            const bool t_willCenterJustify = true,
            const sf::Color & t_color      = sf::Color::White);

      private:
        [[nodiscard]] static const std::vector<std::string>
            splitIntoWords(const std::string & t_text);

        static void centerTextBlock(TextLayoutPack & layout);
        static void centerTextLines(TextLayoutPack & layout);
    };

} // namespace castlecrawl

#endif // TEXT_LAYOUT_HPP_INCLUDED
