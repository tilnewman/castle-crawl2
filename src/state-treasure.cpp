// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-treasure.cpp
//
#include "state-treasure.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "enemy.hpp"
#include "framerate-text.hpp"
#include "item-factory.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "map.hpp"
#include "player-display.hpp"
#include "player.hpp"
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
        , m_titleText()
        , m_descText()
        , m_itemDescText()
        , m_helpText()
    {}

    void StateTreasure::onEnter(const Context & context)
    {
        m_itemListboxUPtr = std::make_unique<Listbox>(m_treasure.items);

        m_itemListboxUPtr->setup(
            context, FontSize::Medium, context.items.textExtents().longest_name, 8);

        //

        const sf::FloatRect boardRect = context.layout.botRect();
        const float pad               = (boardRect.height * 0.015f);

        m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, 190));
        m_fadeRectangle.setPosition(util::position(boardRect));
        m_fadeRectangle.setSize(util::size(boardRect));

        //

        m_titleText = context.fonts.makeText(FontSize::Huge, "Treasure!", sf::Color(255, 200, 100));

        m_titleText.setPosition(
            ((boardRect.width * 0.5f) - (m_titleText.getGlobalBounds().width * 0.5f)),
            (boardRect.top + (pad * 10.0f)));

        //

        std::string descStr{ "You find " };

        if (m_treasure.gold > 0)
        {
            descStr += std::to_string(m_treasure.gold);
            descStr += " gold and ";
        }

        descStr += std::to_string(m_treasure.items.size());
        descStr += " items";

        if (m_treasure.items.empty())
        {
            descStr += ".";
        }
        else
        {
            descStr += ":";
        }

        m_descText = context.fonts.makeText(FontSize::Large, descStr);

        m_descText.setPosition(
            ((boardRect.width * 0.5f) - (m_descText.getGlobalBounds().width * 0.5f)),
            (util::bottom(m_titleText) + pad));

        //

        m_helpText = context.fonts.makeText(
            FontSize::Small,
            "(Press 'T' to take items then 'Enter' when finished)",
            sf::Color(200, 200, 200));

        m_helpText.setStyle(sf::Text::Italic);

        m_helpText.setPosition(
            ((boardRect.width * 0.5f) - (m_helpText.getGlobalBounds().width * 0.5f)),
            util::bottom(m_descText));

        //

        m_itemListboxUPtr->setPosition(
            { ((boardRect.width * 0.5f) - (m_itemListboxUPtr->getGlobalBounds().width * 0.5f)),
              (util::bottom(m_helpText) + (pad * 2.0f)) });

        m_itemListboxUPtr->setFocus(true);

        //

        m_itemDescText = context.fonts.makeText(FontSize::Small, "");
        updateItemDescText(context);
    }

    void StateTreasure::update(const Context & context, const float) { context.framerate.update(); }

    void StateTreasure::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        context.map_display.draw(context, target, states);
        context.enemies.draw(context, target, states);
        context.player_display.draw(context, target, states);
        context.framerate.draw(target, states);
        target.draw(context.top_panel, states);
        target.draw(m_fadeRectangle, states);
        target.draw(m_titleText, states);
        target.draw(m_descText, states);

        if (!m_itemListboxUPtr->empty())
        {
            target.draw(*m_itemListboxUPtr, states);
        }

        target.draw(m_itemDescText, states);
        target.draw(m_helpText, states);
    }

    void StateTreasure::handleEvent(const Context & context, const sf::Event & event)
    {
        // all other handlers are key released events
        if (event.type != sf::Event::KeyPressed)
        {
            return;
        }

        if ((event.key.code == sf::Keyboard::Enter) || (event.key.code == sf::Keyboard::Escape))
        {
            context.state.change(context, State::Play);
            return;
        }
        else if (event.key.code == sf::Keyboard::Up)
        {
            if (m_itemListboxUPtr->selectPrev())
            {
                context.sfx.play("tick-on");
            }

            updateItemDescText(context);
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            if (m_itemListboxUPtr->selectNext())
            {
                context.sfx.play("tick-on");
            }

            updateItemDescText(context);
        }
        else if (event.key.code == sf::Keyboard::T)
        {
            if (m_itemListboxUPtr->empty())
            {
                context.sfx.play("error-1.ogg");
            }
            else
            {
                const std::size_t index = m_itemListboxUPtr->selectedIndex();
                if (index < m_treasure.items.size())
                {
                    context.player.inventory().add(m_treasure.items.at(index));

                    m_treasure.items.erase(
                        std::begin(m_treasure.items) + static_cast<std::ptrdiff_t>(index));

                    m_itemListboxUPtr->redraw();
                    updateItemDescText(context);
                    context.sfx.play("equip.ogg");

                    if (m_treasure.items.empty())
                    {
                        context.state.change(context, State::Play);
                    }
                }
            }

            return;
        }
    }

    void StateTreasure::updateItemDescText(const Context & context)
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

        m_itemDescText.setPosition(
            ((context.layout.screenRect().width * 0.5f) -
             (m_itemDescText.getGlobalBounds().width * 0.5f)),
            util::bottom(*m_itemListboxUPtr));
    }

} // namespace castlecrawl
