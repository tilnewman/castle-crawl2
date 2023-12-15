// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// mouseover.cpp
//
#include "mouseover.hpp"

#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"
#include "map.hpp"
#include "player-display.hpp"

namespace castlecrawl
{

    Mouseover::Mouseover()
        : m_clock()
        , m_willDisplay(false)
        , m_mousePos(0, 0)
        , m_text()
    {}

    void Mouseover::reset()
    {
        m_clock.restart();
        m_willDisplay = false;
    }

    void Mouseover::update(const Context & context, const float)
    {
        const float elapsedTimeSec = m_clock.getElapsedTime().asSeconds();
        if (elapsedTimeSec >= 2.0f)
        {
            m_clock.restart();

            if (m_willDisplay == false)
            {
                m_willDisplay = true;
                setupDisplay(context);
            }
        }
    }

    void Mouseover::handleMouseMovedEvent(const sf::Vector2i & newPos)
    {
        reset();
        m_mousePos = newPos;
    }

    void Mouseover::draw(const Context &, sf::RenderTarget & target, sf::RenderStates states) const
    {
        if (!m_willDisplay)
        {
            return;
        }

        target.draw(m_text, states);
    }

    void Mouseover::setupDisplay(const Context & context)
    {
        const sf::Vector2f mousePos{ m_mousePos };

        const MapPos_t mapPos = context.map.screenPosToMapPos(context, mousePos);
        const MapCell mapCell = context.map.cell(mapPos);

        std::string message;

        if (context.player_display.position() == mapPos)
        {
            message = "you";
        }
        else if ((mapCell.object_char != ' ') && (mapCell.object_char != '.'))
        {
            if (mapCell.object_char == 'l')
            {
                message = "lava";
            }
            else if (mapCell.object_char == 'w')
            {
                message = "water";
            }
            else if (mapCell.object_char == 'd')
            {
                message = "unlocked door";
            }
            else if (mapCell.object_char == 'D')
            {
                message = "locked door";
            }
            else if (mapCell.object_char == 'r')
            {
                message = "solid rock";
            }
            else if (mapCell.object_char == 's')
            {
                message = "stairs leading down";
            }
            else if (mapCell.object_char == 'S')
            {
                message = "stairs leading up";
            }
            else if (mapCell.object_char == 'b')
            {
                message = "barrel";
            }
            else if (mapCell.object_char == 'c')
            {
                message = "chest";
            }
            else if (mapCell.object_char == 'k')
            {
                message = "coffin";
            }
            else if (mapCell.object_char == '1')
            {
                message = "bag of snakes";
            }
            else if (mapCell.object_char == '3')
            {
                message = "spiderweb";
            }
            else if (mapCell.object_char == '5')
            {
                message = "barrel of goblins";
            }
            else if (mapCell.object_char == '7')
            {
                message = "bats";
            }
            else if (mapCell.object_char == '9')
            {
                message = "skeleton grave";
            }
            else if (mapCell.object_char == ';')
            {
                message = "demon doorway";
            }
            else if (mapCell.object_char == ']')
            {
                message = "dragon inferno";
            }
        }

        if (message.empty())
        {
            m_willDisplay = false;
            return;
        }

        const FontSize fontSize     = FontSize::Small;
        const FontExtent fontExtent = context.fonts.extent(fontSize);

        m_text = context.fonts.makeText(fontSize, message);

        m_text.setPosition(
            (mousePos.x + fontExtent.letter_size.x), (mousePos.y - fontExtent.letter_size.y));
    }

} // namespace castlecrawl
