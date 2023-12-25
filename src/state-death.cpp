// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-death.cpp
//
#include "state-death.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "enemy.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "item-factory.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "map.hpp"
#include "music-player.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

#include <string>

namespace castlecrawl
{
    StateDeath::StateDeath()
        : m_fadeRedRectangle()
        , m_fadeBlackRectangle()
        , m_titleText()
    {}

    void StateDeath::onEnter(const Context & context)
    {
        context.music.stopAll();
        context.sfx.play("game-over.ogg");

        const sf::FloatRect screenRect = context.layout.screenRect();

        m_fadeRedRectangle.setFillColor(sf::Color(255, 0, 0, 0));
        m_fadeRedRectangle.setSize(util::size(screenRect));

        m_fadeBlackRectangle.setFillColor(sf::Color(0, 0, 0, 0));
        m_fadeBlackRectangle.setSize(util::size(screenRect));

        m_titleText = context.fonts.makeText(FontSize::Huge, "You Died!", sf::Color::Red);
        util::centerInside(m_titleText, screenRect);
    }

    void StateDeath::update(const Context & context, const float)
    {
        if (m_fadeRedRectangle.getFillColor().a < 255)
        {
            sf::Color color = m_fadeRedRectangle.getFillColor();
            ++color.a;
            m_fadeRedRectangle.setFillColor(color);
        }
        else if (m_fadeBlackRectangle.getFillColor().a < 255)
        {
            sf::Color color = m_fadeBlackRectangle.getFillColor();
            ++color.a;
            m_fadeBlackRectangle.setFillColor(color);
        }
        else
        {
            context.state.change(context, State::Quit);
        }
    }

    void StateDeath::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        context.map_display.draw(context, target, states);
        context.enemies.draw(context, target, states);
        context.player_display.draw(context, target, states);
        target.draw(context.top_panel, states);
        target.draw(m_fadeRedRectangle, states);
        target.draw(m_fadeBlackRectangle, states);

        if (m_fadeRedRectangle.getFillColor().a < 255)
        {
            target.draw(m_titleText, states);
        }
    }

    void StateDeath::handleEvent(const Context & context, const sf::Event & event)
    {
        // all other handlers are key released events
        if (event.type != sf::Event::KeyPressed)
        {
            return;
        }

        if (event.key.code == sf::Keyboard::Escape)
        {
            context.state.change(context, State::Quit);
            return;
        }
    }

} // namespace castlecrawl
