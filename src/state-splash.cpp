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
        : m_castleTexture{}
        , m_castleSprite{ m_castleTexture }
        , m_lightningTexture{}
        , m_lightningSprite{ m_lightningTexture }
        , m_willShowLightning{ false }
        , m_timerSec{ 0.0f }
        , m_isFadingOut{ false }
    {}

    void StateSplash::onEnter(const Context & t_context)
    {
        const sf::FloatRect screenRect = t_context.layout.screenRect();

        util::TextureLoader::load(
            m_castleTexture, (t_context.config.media_path / "image/splash.png"), true);

        m_castleSprite.setTexture(m_castleTexture, true);

        util::fit(m_castleSprite, { (screenRect.size.x * 0.2f), screenRect.size.x });

        m_castleSprite.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_castleSprite.getGlobalBounds().size.x * 0.5f)),
              ((screenRect.size.y * 0.5f) - (m_castleSprite.getGlobalBounds().size.y * 0.5f)) });

        //

        util::TextureLoader::load(
            m_lightningTexture, (t_context.config.media_path / "image/lightning.png"), true);

        m_lightningSprite.setTexture(m_lightningTexture, true);

        util::fit(m_lightningSprite, { (screenRect.size.x * 0.1f), screenRect.size.x });

        m_lightningSprite.setPosition({ (m_castleSprite.getGlobalBounds().position.x -
                                         (m_lightningSprite.getGlobalBounds().size.x * 0.45f)),
                                        (m_castleSprite.getGlobalBounds().position.y -
                                         (m_lightningSprite.getGlobalBounds().size.y * 0.15f)) });

        //

        m_fader.setup(true, sf::Color::Black, 1.5f, screenRect);
    }

    void StateSplash::update(const Context & t_context, const float t_frameTimeSec)
    {
        m_fader.update(t_frameTimeSec);

        m_timerSec += t_frameTimeSec;

        if (m_isFadingOut)
        {
            const float fadeOutDuration = 1.0f;
            if (m_timerSec > fadeOutDuration)
            {
                t_context.state.setChangePending(State::Play);
            }
            else
            {
                sf::Color color = m_castleSprite.getColor();

                color.a = static_cast<uint8_t>(
                    255 - util::map(m_timerSec, 0.0f, fadeOutDuration, 0, 255));

                m_castleSprite.setColor(color);
            }
        }
        else
        {
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
    }

    void StateSplash::draw(
        const Context &, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_castleSprite, t_states);

        if (m_willShowLightning)
        {
            t_target.draw(m_lightningSprite, t_states);
        }

        m_fader.draw(t_target, t_states);
    }

    void StateSplash::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (m_fader.isFading() || m_isFadingOut)
        {
            return;
        }

        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::E)
            {
                t_context.state.setChangePending(State::Editor);
            }
            else
            {
                m_isFadingOut       = true;
                m_willShowLightning = false;
                m_timerSec          = 0.0f;
            }
        }
    }

} // namespace castlecrawl
