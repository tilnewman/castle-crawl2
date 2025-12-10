// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-text-popup.cpp
//
#include "state-text-popup.hpp"

#include "animation-manager.hpp"
#include "check-macros.hpp"
#include "context.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "monster-manager.hpp"
#include "npc-manager.hpp"
#include "player-display.hpp"
#include "sfml-util.hpp"
#include "state-manager.hpp"
#include "texture-loader.hpp"
#include "top-panel.hpp"
#include "turn-keeper.hpp"

namespace castlecrawl
{

    StateTextPopup::StateTextPopup()
        : m_paperTexture{}
        , m_paperSprite{ m_paperTexture }
        , m_accentImage{}
        , m_textLayout{}
    {}

    void StateTextPopup::onEnter(const Context & t_context)
    {
        M_CHECK(
            !m_info.message.empty(),
            "State TextPopup was switched to but there was no TextPopupInfo!");

        util::TextureLoader::load(
            m_paperTexture, (t_context.config.media_path / "image/old-paper.png"), true);

        m_paperSprite.setTexture(m_paperTexture, true);

        sf::FloatRect region = t_context.layout.screenRegion();
        util::scaleRectInPlace(region, t_context.config.popup_text_region_ratio);
        util::fitAndCenterInside(m_paperSprite, region);

        m_textLayout = TextLayout::typeset(
            t_context,
            m_info.message,
            m_paperSprite.getGlobalBounds(),
            m_info.font_size,
            t_context.config.text_inner_pad_ratio,
            m_info.will_center_justify,
            m_info.color);

        const sf::FloatRect accentRect = util::scaleRectInPlaceCopy(
            region, (1.0f - t_context.config.text_inner_pad_ratio));

        m_accentImage.setup(t_context, accentRect);
    }

    void StateTextPopup::onExit(const Context &) { m_info = TextPopupInfo(); }

    void StateTextPopup::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
    }

    void StateTextPopup::draw(
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

    void StateTextPopup::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>();
        if (keyPtr)
        {
            if (m_info.will_advance_turn)
            {
                t_context.turn.advance(t_context, t_context.config.turn_delay_after_player_misc);
            }

            t_context.state.setChangePending(State::Play);
        }
    }

} // namespace castlecrawl
