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

    void StateTreasure::onEnter(const Context & context)
    {
        m_itemListboxUPtr = std::make_unique<Listbox>(m_treasure.items);

        m_itemListboxUPtr->setup(
            context, FontSize::Medium, context.items.textExtents().longest_name, 8);

        //

        const sf::FloatRect boardRect = context.layout.botRect();
        const float pad               = (boardRect.size.y * 0.015f);

        m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, 190));
        m_fadeRectangle.setPosition(boardRect.position);
        m_fadeRectangle.setSize(boardRect.size);

        //

        m_titleText = context.fonts.makeText(FontSize::Huge, "Treasure!", sf::Color(255, 200, 100));

        m_titleText.setPosition(
            { ((boardRect.size.x * 0.5f) - (m_titleText.getGlobalBounds().size.x * 0.5f)),
              (boardRect.position.y + (pad * 10.0f)) });

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
            { ((boardRect.size.x * 0.5f) - (m_descText.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_titleText) + pad) });

        //

        m_helpText = context.fonts.makeText(
            FontSize::Small,
            "(Press 'T' to take items then 'Enter' when finished)",
            sf::Color(200, 200, 200));

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
        if (const auto * keyPtr = event.getIf<sf::Event::KeyPressed>())
        {
            if ((keyPtr->scancode == sf::Keyboard::Scancode::Enter) ||
                (keyPtr->scancode == sf::Keyboard::Scancode::Escape))
            {
                context.state.change(context, State::Play);
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::Up)
            {
                if (m_itemListboxUPtr->selectPrev())
                {
                    context.sfx.play("tick-on");
                }

                updateItemDescText(context);
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::Down)
            {
                if (m_itemListboxUPtr->selectNext())
                {
                    context.sfx.play("tick-on");
                }

                updateItemDescText(context);
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::T)
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
            }
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

        m_itemDescText.setPosition({ ((context.layout.screenRect().size.x * 0.5f) -
                                      (m_itemDescText.getGlobalBounds().size.x * 0.5f)),
                                     util::bottom(*m_itemListboxUPtr) });
    }

} // namespace castlecrawl
