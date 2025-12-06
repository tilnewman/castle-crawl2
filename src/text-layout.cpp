// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// text-layout.cpp
//
#include "text-layout.hpp"

#include "context.hpp"
#include "sfml-util.hpp"

#include <algorithm>
#include <sstream>

namespace castlecrawl
{

    const TextLayoutPack TextLayout::typeset(
        const Context & t_context,
        const std::string & t_text,
        const sf::FloatRect & t_rect,
        const FontSize & t_fontSize,
        const bool t_willCenterJustify,
        const sf::Color & t_color)
    {
        const FontExtent fontExtent{ t_context.fonts.extent(t_fontSize) };

        // split message into words
        const std::vector<std::string> words{ splitIntoWords(t_text) };

        // transform words into one sf::Text per line of text that fits into t_rect
        TextLayoutPack layout;
        layout.rect = t_rect;

        if (words.empty())
        {
            return layout;
        }

        layout.texts.reserve(words.size());

        sf::Vector2f pos{ t_rect.position };
        std::string lineStr;
        sf::Text lineText = t_context.fonts.makeText(t_fontSize, "", t_color);
        lineText.setPosition(pos);

        for (auto wordIter = std::begin(words); wordIter != std::end(words); ++wordIter)
        {
            if ("<paragraph>" == *wordIter)
            {
                layout.texts.push_back(lineText);
                pos.y += fontExtent.letter_size.y;
                pos.y += fontExtent.letter_size.y;
                lineStr.clear();
                lineText.setString(lineStr);
                util::setOriginToPosition(lineText);
                lineText.setPosition(pos);
                continue;
            }

            const std::string tempStr{ lineStr + " " + *wordIter };

            sf::Text tempText{ lineText };
            tempText.setString(tempStr);
            util::setOriginToPosition(tempText);
            tempText.setPosition(pos);

            if (util::right(tempText) < util::right(t_rect))
            {
                lineText = tempText;
                lineStr  = tempStr;
            }
            else
            {
                layout.texts.push_back(lineText);

                pos.y += fontExtent.letter_size.y;
                lineStr = *wordIter;
                lineText.setString(lineStr);
                util::setOriginToPosition(lineText);
                lineText.setPosition(pos);
            }
        }

        layout.texts.push_back(lineText);

        if (t_willCenterJustify)
        {
            centerTextLines(layout);
        }
        else
        {
            centerTextBlock(layout);
        }

        return layout;
    }

    const std::vector<std::string> TextLayout::splitIntoWords(const std::string & t_text)
    {
        std::vector<std::string> words;
        words.reserve(t_text.size() / 4); // found by experiment to be a good upper bound

        std::istringstream iss{ t_text };

        std::copy(
            std::istream_iterator<std::string>(iss),
            std::istream_iterator<std::string>(),
            std::back_inserter(words));

        return words;
    }

    void TextLayout::centerTextBlock(TextLayoutPack & layout)
    {
        if (layout.texts.empty())
        {
            return;
        }

        // find the widest line of text
        float width = 0.0f;
        for (const sf::Text & text : layout.texts)
        {
            if (text.getGlobalBounds().size.x > width)
            {
                width = text.getGlobalBounds().size.x;
            }
        }

        // center all the text as a block into t_rect
        const float height{ util::bottom(layout.texts.back()) -
                            layout.texts.front().getGlobalBounds().position.y };

        const sf::Vector2f offset{ (layout.rect.size.x - width) * 0.5f,
                                   (layout.rect.size.y - height) * 0.5f };

        for (sf::Text & text : layout.texts)
        {
            text.move(offset);
        }
    }

    void TextLayout::centerTextLines(TextLayoutPack & layout)
    {
        centerTextBlock(layout);

        if (layout.texts.size() == 1)
        {
            util::centerInside(layout.texts.front(), layout.rect);
        }
        else
        {
            for (sf::Text & text : layout.texts)
            {
                const sf::Vector2f offset{
                    (layout.rect.size.x - text.getGlobalBounds().size.x) * 0.5f, 0.0f
                };

                text.move(offset);
            }
        }
    }

} // namespace castlecrawl