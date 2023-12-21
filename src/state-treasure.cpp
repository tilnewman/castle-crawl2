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

namespace castlecrawl
{
    item::Treasure StateTreasure::m_treasure;

    StateTreasure::StateTreasure()
        : m_fadeRectangle()
        , m_itemListboxUPtr()
    {}

    void StateTreasure::onEnter(const Context & context)
    {
        m_itemListboxUPtr = std::make_unique<Listbox>(m_treasure.items);

        m_itemListboxUPtr->setup(
            context, FontSize::Medium, context.items.textExtents().longest_name, 8);

        const sf::FloatRect boardRect = context.layout.botRect();

        m_itemListboxUPtr->setPosition(
            { ((boardRect.width * 0.5f) - (m_itemListboxUPtr->getGlobalBounds().width * 0.5f)),
              (boardRect.top + (boardRect.height * 0.15f)) });

        m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, 127));
        m_fadeRectangle.setPosition(util::position(boardRect));
        m_fadeRectangle.setSize(util::size(boardRect));
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
        target.draw(*m_itemListboxUPtr, states);
    }

    void StateTreasure::handleEvent(const Context & context, const sf::Event & event)
    {
        // all other handlers are key released events
        if (event.type != sf::Event::KeyReleased)
        {
            return;
        }

        if (event.key.code == sf::Keyboard::Escape)
        {
            context.state.change(context, State::Play);
            return;
        }
    }

} // namespace castlecrawl
