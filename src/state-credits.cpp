// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-credits.cpp
//
#include "state-credits.hpp"

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
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

#include <string>

namespace castlecrawl
{
    Credit::Credit()
        : m_nameText()
        , m_descText()
    {}

    void Credit::setup(const Context & context, const std::string & name, const std::string & desc)
    {
        const sf::FloatRect screenRect = context.layout.screenRect();
        m_nameText                     = context.fonts.makeText(FontSize::Large, name);

        m_nameText.setPosition(
            ((screenRect.width * 0.5f) - (m_nameText.getGlobalBounds().width * 0.5f)),
            screenRect.height);

        m_descText = context.fonts.makeText(FontSize::Medium, desc, sf::Color(200, 200, 200));

        const float vertPad = 10.0f;

        m_descText.setPosition(
            ((screenRect.width * 0.5f) - (m_descText.getGlobalBounds().width * 0.5f)),
            util::bottom(m_nameText) + vertPad);
    }

    void Credit::update(const float frameTimeSec)
    {
        const float scrollSpeed = 30.0f;
        m_nameText.move(0.0f, -(frameTimeSec * scrollSpeed));
        m_descText.move(0.0f, -(frameTimeSec * scrollSpeed));
    }

    void Credit::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_nameText, states);
        target.draw(m_descText, states);
    }

    StateCredits::StateCredits()
        : m_castleTexture()
        , m_castleSprite()
        , m_testCredit()
    {}

    void StateCredits::onEnter(const Context & context)
    {
        const sf::FloatRect screenRect = context.layout.screenRect();

        m_castleTexture.loadFromFile((context.config.media_path / "image" / "splash.png").string());
        m_castleTexture.setSmooth(true);

        m_castleSprite.setTexture(m_castleTexture);
        m_castleSprite.setColor(sf::Color(255, 255, 255, 32));

        util::fit(m_castleSprite, { (screenRect.width * 0.2f), screenRect.width });

        m_castleSprite.setPosition(
            ((screenRect.width * 0.5f) - (m_castleSprite.getGlobalBounds().width * 0.5f)),
            ((screenRect.height * 0.5f) - (m_castleSprite.getGlobalBounds().height * 0.5f)));

        m_testCredit.setup(context, "Ziesche Til Newman", "Software");
    }

    void StateCredits::update(const Context &, const float frameTimeSec)
    {
        m_testCredit.update(frameTimeSec);
    }

    void StateCredits::draw(
        const Context &, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_castleSprite, states);
        target.draw(m_testCredit, states);
    }

    void StateCredits::handleEvent(const Context & context, const sf::Event & event)
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
