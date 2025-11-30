// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-levelup.cpp
//
#include "state-levelup.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "monster-manager.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    StateLevelUp::StateLevelUp()
        : m_bgFadeRectangle{}
        , m_titleText{ util::SfmlDefaults::instance().font() }
        , m_subTitleText{ util::SfmlDefaults::instance().font() }
        , m_instructionText{ util::SfmlDefaults::instance().font() }
        , m_errorText{ util::SfmlDefaults::instance().font() }
        , m_errorTimerSec{ 0.0f }
        , haveAllStatPointsBeenAwarded{ false }
    {}

    void StateLevelUp::onEnter(const Context & t_context)
    {
        // background fade
        const sf::FloatRect screenRect{ t_context.layout.screenRegion() };
        m_bgFadeRectangle.setPosition(screenRect.position);
        m_bgFadeRectangle.setSize(screenRect.size);
        m_bgFadeRectangle.setFillColor(t_context.config.stage_background_color);

        const sf::FloatRect botRect{ t_context.layout.botRegion() };

        // title
        m_titleText = t_context.fonts.makeText(FontSize::Huge, "Level Up");

        const float pad{ botRect.size.y * 0.05f };

        m_titleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_titleText.getGlobalBounds().size.x * 0.5f)),
              (botRect.position.y + pad) });

        // sub tittle text
        std::string subTitleStr =
            "Congradulations, you have earned enough experience to advance to level ";

        subTitleStr += std::to_string(t_context.player.level());
        subTitleStr += '!';

        m_subTitleText = t_context.fonts.makeText(
            FontSize::Small, subTitleStr, t_context.config.state_color_subtitle);

        m_subTitleText.setStyle(sf::Text::Italic);

        m_subTitleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_subTitleText.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_titleText) + (pad * 0.25f)) });

        // stat point award instruction text
        m_instructionText = t_context.fonts.makeText(
            FontSize::Small,
            "Use the arrow keys to award your ten stat points below.",
            t_context.config.state_color_subtitle);

        m_instructionText.setStyle(sf::Text::Italic);

        m_instructionText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_instructionText.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_instructionText) + (pad * 0.75f)) });

        // error text
        m_errorText =
            t_context.fonts.makeText(FontSize::Large, "", t_context.config.error_message_color);
    }

    void StateLevelUp::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
    }

    void StateLevelUp::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(t_context.top_panel, t_states);
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.monsters.drawHealthLines(t_context, t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.anim.draw(t_target, t_states);
        t_context.framerate.draw(t_target, t_states);

        t_target.draw(m_bgFadeRectangle, t_states);
        t_target.draw(m_titleText, t_states);
        t_target.draw(m_subTitleText, t_states);
        t_target.draw(m_instructionText, t_states);
        t_target.draw(m_errorText, t_states);
    }

    void StateLevelUp::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>();
        if (!keyPtr)
        {
            return;
        }

        if ((keyPtr->scancode == sf::Keyboard::Scancode::Escape) && haveAllStatPointsBeenAwarded)
        {
            t_context.state.setChangePending(State::Play);
            return;
        }
    }

    void StateLevelUp::showErrorMessage(const Context & t_context, const std::string & t_message)
    {
        m_errorText.setString(t_message);
        util::setOriginToPosition(m_errorText);

        m_errorText.setPosition({ ((t_context.layout.botRegion().size.x * 0.5f) -
                                   (m_errorText.getGlobalBounds().size.x * 0.5f)),
                                  (t_context.layout.botRegion().size.y * 0.925f) });

        m_errorTimerSec = 0.0f;
    }

} // namespace castlecrawl