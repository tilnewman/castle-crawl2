// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-save-game.cpp
//
#include "state-save-game.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "json-wrapper.hpp"
#include "layout.hpp"
#include "player-display.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

#include <fstream>

namespace castlecrawl
{

    StateSaveGame::StateSaveGame()
        : m_bgFadeRectangle{}
        , m_titleText{ util::SfmlDefaults::instance().font() }
        , m_subTitleText{ util::SfmlDefaults::instance().font() }
    {}

    void StateSaveGame::onEnter(const Context & t_context)
    {
        // background fade
        const sf::FloatRect screenRect{ t_context.layout.screenRegion() };
        m_bgFadeRectangle.setPosition(screenRect.position);
        m_bgFadeRectangle.setSize(screenRect.size);
        m_bgFadeRectangle.setFillColor(t_context.config.stage_background_color);

        const sf::FloatRect botRect{ t_context.layout.botRegion() };

        // title
        m_titleText = t_context.fonts.makeText(FontSize::Huge, "Save Game");
        m_titleText.setStyle(sf::Text::Underlined);

        const float pad{ botRect.size.y * 0.05f };

        m_titleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_titleText.getGlobalBounds().size.x * 0.5f)),
              (botRect.position.y + pad) });

        // sub tittle text
        m_subTitleText = t_context.fonts.makeText(
            FontSize::Medium,
            "To save your game press 'Y' or press any other key to exit.",
            t_context.config.state_color_subtitle);

        m_subTitleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_subTitleText.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_titleText) + (pad * 0.25f)) });
    }

    void StateSaveGame::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
    }

    void StateSaveGame::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        StateBase::draw(t_context, t_target, t_states);

        t_target.draw(m_bgFadeRectangle, t_states);
        t_target.draw(m_titleText, t_states);
        t_target.draw(m_subTitleText, t_states);
    }

    void StateSaveGame::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Y)
            {
                saveGame(t_context);
            }
            else
            {
                t_context.state.setChangePending(State::Play);
            }
        }
    }

    void StateSaveGame::saveGame(const Context & t_context)
    {
        try
        {
            SavedGamePack pack;
            pack.player_position = t_context.player_display.position();
            pack.player          = t_context.player;
            pack.maps            = t_context.maps;

            nlohmann::json json = pack;

            {
                std::ofstream ofStream(t_context.config.save_game_file_name, std::ios::trunc);
                ofStream << json;
            }

            t_context.sfx.play("magic-1");
            t_context.state.setChangePending(State::Play);
            return;
        }
        catch (...)
        {
            t_context.sfx.play("error-1");
        }
    }

} // namespace castlecrawl