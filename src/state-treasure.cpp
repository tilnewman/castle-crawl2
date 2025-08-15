// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-treasure.cpp
//
#include "state-treasure.hpp"

#include "animation-manager.hpp"
#include "check-macros.hpp"
#include "context.hpp"
#include "framerate-text.hpp"
#include "item-factory.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "map.hpp"
#include "monster-manager.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "sfml-defaults.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

#include <string>

namespace castlecrawl
{
    item::Treasure StateTreasure::m_treasure;

    StateTreasure::StateTreasure()
        : m_fadeRectangle()
        , m_itemListboxUPtr()
        , m_titleText(util::SfmlDefaults::instance().font())
        , m_descText(util::SfmlDefaults::instance().font())
        , m_itemDescText(util::SfmlDefaults::instance().font())
        , m_helpText(util::SfmlDefaults::instance().font())
    {}

    void StateTreasure::onEnter(const Context & t_context)
    {
        m_itemListboxUPtr = std::make_unique<Listbox>(m_treasure.items);

        m_itemListboxUPtr->setup(
            t_context, FontSize::Medium, t_context.items.textExtents().longest_name, 8);

        //

        const sf::FloatRect boardRect{ t_context.layout.botRect() };
        const float pad{ boardRect.size.y * 0.015f };

        m_fadeRectangle.setFillColor(t_context.config.stage_background_color);
        m_fadeRectangle.setPosition(boardRect.position);
        m_fadeRectangle.setSize(boardRect.size);

        //

        m_titleText = t_context.fonts.makeText(
            FontSize::Huge, "Treasure!", t_context.config.message_color_coins);

        m_titleText.setPosition(
            { ((boardRect.size.x * 0.5f) - (m_titleText.getGlobalBounds().size.x * 0.5f)),
              (boardRect.position.y + (pad * 10.0f)) });

        //

        std::string descStr{ "You find " };

        if (m_treasure.gold > 0)
        {
            descStr += std::to_string(m_treasure.gold);
            descStr += " gold";
        }

        if (m_treasure.gold > 0 && !m_treasure.items.empty())
        {
            descStr += " and ";
        }

        if (m_treasure.items.empty())
        {
            descStr += ".";
        }
        else
        {
            descStr += std::to_string(m_treasure.items.size());
            descStr += " items:";
        }

        m_descText = t_context.fonts.makeText(FontSize::Large, descStr);

        m_descText.setPosition(
            { ((boardRect.size.x * 0.5f) - (m_descText.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_titleText) + (pad * 4.0f)) });

        //

        std::string helpStr{ "(Press Enter to take items then Escape when finished)" };
        if (m_treasure.items.empty())
        {
            helpStr = "(Press Enter or Escape to return to the game)";
        }

        m_helpText = t_context.fonts.makeText(FontSize::Small, helpStr, sf::Color(200, 200, 200));

        m_helpText.setStyle(sf::Text::Italic);

        m_helpText.setPosition(
            { ((boardRect.size.x * 0.5f) - (m_helpText.getGlobalBounds().size.x * 0.5f)),
              util::bottom(m_descText) });

        //

        m_itemListboxUPtr->setPosition(
            { ((boardRect.size.x * 0.5f) - (m_itemListboxUPtr->getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_helpText) + (pad * 2.0f)) });

        m_itemListboxUPtr->setFocus(true);

        //

        m_itemDescText = t_context.fonts.makeText(FontSize::Small, "");
        updateItemDescText(t_context);
    }

    void StateTreasure::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
    }

    void StateTreasure::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.monsters.drawHealthLines(t_context, t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.anim.draw(t_target, t_states);

        t_target.draw(t_context.top_panel, t_states);
        t_target.draw(m_fadeRectangle, t_states);
        t_target.draw(m_titleText, t_states);
        t_target.draw(m_descText, t_states);
        t_target.draw(m_helpText, t_states);

        if (!m_itemListboxUPtr->empty())
        {
            t_target.draw(*m_itemListboxUPtr, t_states);
            t_target.draw(m_itemDescText, t_states);
        }
    }

    void StateTreasure::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>();
        if (!keyPtr)
        {
            return;
        }

        if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
        {
            t_context.state.setChangePending(State::Play);
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Up)
        {
            if (m_itemListboxUPtr->selectPrev())
            {
                updateItemDescText(t_context);
                t_context.sfx.play("tick-on");
            }
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Down)
        {
            if (m_itemListboxUPtr->selectNext())
            {
                updateItemDescText(t_context);
                t_context.sfx.play("tick-on");
            }
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Enter)
        {
            if (m_itemListboxUPtr->empty())
            {
                t_context.state.setChangePending(State::Play);
                return;
            }

            const std::size_t index{ m_itemListboxUPtr->selectedIndex() };
            if (index < m_treasure.items.size())
            {
                t_context.player.inventory().add(m_treasure.items.at(index));

                m_treasure.items.erase(
                    std::begin(m_treasure.items) + static_cast<std::ptrdiff_t>(index));

                m_itemListboxUPtr->redraw();
                updateItemDescText(t_context);
                t_context.sfx.play("equip-armor");

                if (m_treasure.items.empty())
                {
                    t_context.state.setChangePending(State::Play);
                }
            }
        }
    }

    void StateTreasure::updateItemDescText(const Context & t_context)
    {
        m_itemDescText.setString("");

        if (!m_itemListboxUPtr->empty())
        {
            const std::size_t index = m_itemListboxUPtr->selectedIndex();
            if (index < m_treasure.items.size())
            {
                m_itemDescText.setString(m_treasure.items.at(index).description());
            }
        }

        m_itemDescText.setPosition({ ((t_context.layout.screenRect().size.x * 0.5f) -
                                      (m_itemDescText.getGlobalBounds().size.x * 0.5f)),
                                     util::bottom(*m_itemListboxUPtr) });
    }

} // namespace castlecrawl
