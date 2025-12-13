// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-look-event.cpp
//
#include "state-look-event.hpp"

#include "animation-manager.hpp"
#include "check-macros.hpp"
#include "context.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "look-event.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "npc-manager.hpp"
#include "player-display.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "texture-loader.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    StateLookEvent::StateLookEvent()
        : m_paperTexture{}
        , m_paperSprite{ m_paperTexture }
        , m_accentImage{}
        , m_textLayout{}
    {}

    void StateLookEvent::onEnter(const Context & t_context)
    {
        M_CHECK(
            !m_lookEvent.empty(), "State LookEvent was switched to but there was no LookEvent!");

        util::TextureLoader::load(
            m_paperTexture, (t_context.config.media_path / "image/old-paper.png"), true);

        m_paperSprite.setTexture(m_paperTexture, true);

        sf::FloatRect region = t_context.layout.screenRegion();
        util::scaleRectInPlace(region, t_context.config.look_text_region_ratio);
        util::fitAndCenterInside(m_paperSprite, region);

        std::string message = m_lookEvent.message;
        if (m_lookEvent.hasRequirements())
        {
            message += ' ';

            if (LookEventHandler::areAllRequirementsMet(t_context, m_lookEvent))
            {
                message += m_lookEvent.message_pass;
                message += LookEventHandler::takePassActions(t_context, m_lookEvent);
                t_context.sfx.play("magic-1");

                if (!m_lookEvent.will_always_happen)
                {
                    t_context.maps.current().setLookEventAsHappened(m_lookEvent.map_pos);
                }
            }
            else
            {
                message += m_lookEvent.message_fail;
                message += LookEventHandler::takeFailActions(t_context, m_lookEvent);
            }
        }

        m_textLayout = TextLayout::typeset(
            t_context,
            message,
            region,
            FontSize::Medium,
            t_context.config.text_inner_pad_ratio,
            true,
            sf::Color::Black);

        const sf::FloatRect accentRect =
            util::scaleRectInPlaceCopy(region, (1.0f - t_context.config.text_inner_pad_ratio));

        m_accentImage.setup(t_context, accentRect);
    }

    void StateLookEvent::onExit(const Context &) { m_lookEvent = LookEvent(); }

    void StateLookEvent::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
    }

    void StateLookEvent::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.monsters.draw(t_context, t_target, t_states);
        t_context.npcs.draw(t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.anim.draw(t_target, t_states);
        t_context.framerate.draw(t_target, t_states);

        t_target.draw(t_context.top_panel, t_states);
        t_target.draw(m_paperSprite, t_states);
        t_target.draw(m_accentImage, t_states);

        for (const sf::Text & text : m_textLayout.texts)
        {
            t_target.draw(text, t_states);
        }
    }

    void StateLookEvent::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if ((keyPtr->scancode == sf::Keyboard::Scancode::Escape) ||
                (keyPtr->scancode == sf::Keyboard::Scancode::Enter))
            {
                t_context.state.setChangePending(State::Play);
            }
        }
    }

} // namespace castlecrawl
