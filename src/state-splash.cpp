// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-splash.cpp
//
#include "state-splash.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "sfml-util.hpp"
#include "state-manager.hpp"
#include "texture-loader.hpp"

namespace castlecrawl
{

    StateSplash::StateSplash()
        : m_castleTexture()
        , m_castleSprite(m_castleTexture)
        , m_lightningTexture()
        , m_lightningSprite(m_lightningTexture)
        , m_willShowLightning(false)
        , m_timerSec(0.0f)
    {}

    void StateSplash::onEnter(const Context & context)
    {
        const sf::FloatRect screenRect = context.layout.screenRect();

        util::TextureLoader::load(
            m_castleTexture, (context.config.media_path / "image/splash.png"), true);

        m_castleSprite.setTexture(m_castleTexture, true);

        util::fit(m_castleSprite, { (screenRect.size.x * 0.2f), screenRect.size.x });

        m_castleSprite.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_castleSprite.getGlobalBounds().size.x * 0.5f)),
              ((screenRect.size.y * 0.5f) - (m_castleSprite.getGlobalBounds().size.y * 0.5f)) });

        //

        util::TextureLoader::load(
            m_lightningTexture, (context.config.media_path / "image/lightning.png"), true);

        m_lightningSprite.setTexture(m_lightningTexture, true);

        util::fit(m_lightningSprite, { (screenRect.size.x * 0.1f), screenRect.size.x });

        m_lightningSprite.setPosition({ (m_castleSprite.getGlobalBounds().position.x -
                                         (m_lightningSprite.getGlobalBounds().size.x * 0.45f)),
                                        (m_castleSprite.getGlobalBounds().position.y -
                                         (m_lightningSprite.getGlobalBounds().size.y * 0.15f)) });

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

    void StateSplash::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (m_fader.isFading())
        {
            return;
        }

        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::E)
            {
                t_context.state.change(t_context, State::Editor);
            }
            else
            {
                t_context.state.change(t_context, State::Play);
            }
        }
    }

} // namespace castlecrawl
