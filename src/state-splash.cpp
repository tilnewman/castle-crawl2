// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-splash.cpp
//
#include "state-splash.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "state-manager.hpp"
#include "sfml-util.hpp"

namespace castlecrawl
{

    StateSplash::StateSplash()
        : m_castleTexture()
        , m_castleSprite()
        , m_lightningTexture()
        , m_lightningSprite()
        , m_willShowLightning(false)
        , m_timerSec(0.0f)
    {}

    void StateSplash::onEnter(const Context & context)
    {
        const sf::FloatRect screenRect = context.layout.screenRect();

        m_castleTexture.loadFromFile((context.config.media_path / "image" / "splash.png").string());
        m_castleTexture.setSmooth(true);

        m_castleSprite.setTexture(m_castleTexture);

        util::fit(m_castleSprite, { (screenRect.width * 0.2f), screenRect.width });

        m_castleSprite.setPosition(
            ((screenRect.width * 0.5f) - (m_castleSprite.getGlobalBounds().width * 0.5f)),
            ((screenRect.height * 0.5f) - (m_castleSprite.getGlobalBounds().height * 0.5f)));

        //

        m_lightningTexture.loadFromFile(
            (context.config.media_path / "image" / "lightning.png").string());

        m_lightningTexture.setSmooth(true);

        m_lightningSprite.setTexture(m_lightningTexture);

        util::fit(m_lightningSprite, { (screenRect.width * 0.1f), screenRect.width });

        m_lightningSprite.setPosition(
            (m_castleSprite.getGlobalBounds().left -
             (m_lightningSprite.getGlobalBounds().width * 0.45f)),
            (m_castleSprite.getGlobalBounds().top -
             (m_lightningSprite.getGlobalBounds().height * 0.15f)));

        //

        m_fader.setup(true, sf::Color::Black, 1.5f, screenRect);
    }

    void StateSplash::update(const Context &, const float frameTimeSec)
    {
        m_fader.update(frameTimeSec);

        //

        m_timerSec += frameTimeSec;
        if ((m_timerSec >= 3.5f) && (m_timerSec < 3.75f))
        {
            m_willShowLightning = true;
            return;
        }
        else if ((m_timerSec >= 6.0f) && (m_timerSec < 6.25f))
        {
            m_willShowLightning = true;
            return;
        }
        else if ((m_timerSec >= 7.0f) && (m_timerSec < 7.25f))
        {
            m_willShowLightning = true;
            return;
        }
        else if (m_timerSec >= 9.0f)
        {
            m_timerSec = 0.0f;
        }

        m_willShowLightning = false;
    }

    void
        StateSplash::draw(const Context &, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_castleSprite, states);

        if (m_willShowLightning)
        {
            target.draw(m_lightningSprite, states);
        }

        m_fader.draw(target, states);
    }

    void StateSplash::handleEvent(const Context & context, const sf::Event & event)
    {
        if (m_fader.isFading())
        {
            return;
        }

        if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::E))
        {
            context.state.change(context, State::Editor);
        }
        else if (
            (event.type == sf::Event::KeyReleased) || (event.type == sf::Event::MouseButtonPressed))
        {
            context.state.change(context, State::Play);
        }
    }

} // namespace castlecrawl
