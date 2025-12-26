// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-load-game.cpp
//
#include "state-load-game.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "json-wrapper.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "player-display.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "state-save-game.hpp"
#include "top-panel.hpp"

#include <fstream>

namespace castlecrawl
{

    StateLoadGame::StateLoadGame()
        : m_bgFadeRectangle{}
        , m_titleText{ util::SfmlDefaults::instance().font() }
        , m_subTitleText{ util::SfmlDefaults::instance().font() }
        , m_errorText{ util::SfmlDefaults::instance().font() }
    {}

    void StateLoadGame::onEnter(const Context & t_context)
    {
        // background fade
        const sf::FloatRect screenRect{ t_context.layout.screenRegion() };
        m_bgFadeRectangle.setPosition(screenRect.position);
        m_bgFadeRectangle.setSize(screenRect.size);
        m_bgFadeRectangle.setFillColor(t_context.config.stage_background_color);

        const sf::FloatRect botRect{ t_context.layout.botRegion() };

        // title
        m_titleText = t_context.fonts.makeText(FontSize::Huge, "Load Game");
        m_titleText.setStyle(sf::Text::Underlined);

        const float pad{ botRect.size.y * 0.075f };

        m_titleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_titleText.getGlobalBounds().size.x * 0.5f)),
              (botRect.position.y + pad) });

        // sub tittle text
        m_subTitleText = t_context.fonts.makeText(
            FontSize::Medium,
            "To abandon this game and load a saved game press 'Y'.",
            t_context.config.state_color_subtitle);

        m_subTitleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_subTitleText.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_titleText) + (pad * 0.25f)) });

        // error text
        m_errorText = t_context.fonts.makeText(FontSize::Small, "", sf::Color::Red);
    }

    void StateLoadGame::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
    }

    void StateLoadGame::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        StateBase::draw(t_context, t_target, t_states);

        t_target.draw(m_bgFadeRectangle, t_states);
        t_target.draw(m_titleText, t_states);
        t_target.draw(m_subTitleText, t_states);
        t_target.draw(m_errorText, t_states);
    }

    void StateLoadGame::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Y)
            {
                loadGame(t_context);
            }
            else
            {
                t_context.state.setChangePending(State::Play);
            }
        }
    }

    void StateLoadGame::loadGame(const Context & t_context)
    {
        try
        {
            nlohmann::json json;

            {
                std::ifstream ifStream(t_context.config.save_game_file_name);
                ifStream >> json;
            }

            SavedGamePack pack = json.get<SavedGamePack>();
            t_context.player = pack.player;
            t_context.maps   = pack.maps;

            t_context.top_panel.update(t_context);
            t_context.maps.change(t_context, t_context.maps.current().name(), pack.player_position);

            t_context.sfx.play("magic-1");
            t_context.state.setChangePending(State::Play);
            return;
        }
        catch (const std::exception & ex)
        {
            m_errorText.setString(ex.what());
        }
        catch (...)
        {
            m_errorText.setString("Unknown (non std) exception error!");
        }

        util::setOriginToPosition(m_errorText);
        util::centerInside(m_errorText, t_context.layout.botRegion());

        t_context.sfx.play("error-1");
    }

} // namespace castlecrawl