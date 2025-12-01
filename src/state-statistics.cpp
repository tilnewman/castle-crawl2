// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-statistics.cpp
//
#include "state-statistics.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "state-manager.hpp"
#include "statistics.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    StatBlock::StatBlock(
        const Context & t_context,
        const std::string & t_name,
        const std::size_t t_value,
        const sf::FloatRect & t_rect)
        : m_rect{ t_rect }
        , m_name{ t_name }
        , m_nameText{ util::SfmlDefaults::instance().font() }
        , m_valueText{ util::SfmlDefaults::instance().font() }
    {
        const float pad = (t_context.layout.screenRegion().size.x * 0.01f);

        m_nameText = t_context.fonts.makeText(FontSize::Medium, m_name);
        util::centerInside(m_nameText, m_rect);

        m_nameText.setPosition(
            { (m_rect.position.x + pad), m_nameText.getGlobalBounds().position.y });

        m_valueText = t_context.fonts.makeText(FontSize::Medium, std::to_string(t_value));

        util::centerInside(m_valueText, m_rect);

        m_valueText.setPosition({ util::right(m_rect), m_valueText.getGlobalBounds().position.y });
    }

    void StatBlock::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_nameText, t_states);
        t_target.draw(m_valueText, t_states);
    }

    //

    StateStatistics::StateStatistics()
        : m_bgFadeRectangle{}
        , m_titleText{ util::SfmlDefaults::instance().font() }
        , m_subTitleText{ util::SfmlDefaults::instance().font() }
        , m_statBlocks{}
    {}

    void StateStatistics::onEnter(const Context & t_context)
    {
        // background fade
        const sf::FloatRect screenRect{ t_context.layout.screenRegion() };
        m_bgFadeRectangle.setPosition(screenRect.position);
        m_bgFadeRectangle.setSize(screenRect.size);
        m_bgFadeRectangle.setFillColor(t_context.config.stage_background_color);

        const sf::FloatRect botRect{ t_context.layout.botRegion() };

        // title
        m_titleText = t_context.fonts.makeText(FontSize::Huge, "Looking Back");
        m_titleText.setStyle(sf::Text::Underlined);

        const float pad{ botRect.size.y * 0.05f };

        m_titleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_titleText.getGlobalBounds().size.x * 0.5f)),
              (botRect.position.y + pad) });

        // sub tittle text
        m_subTitleText = t_context.fonts.makeText(
            FontSize::Medium,
            "You may have died, but take a moment to look at some achievments.",
            t_context.config.state_color_subtitle);

        m_subTitleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_subTitleText.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_titleText) + (pad * 0.25f)) });

        // stat blocks
        const float blockWidth  = screenRect.size.x * 0.2f;
        const float blockHeight = screenRect.size.y * 0.03f;

        sf::FloatRect blockRect{ { ((screenRect.size.x * 0.5f) - (blockWidth * 0.5f)),
                                   (util::bottom(m_subTitleText) +
                                    m_subTitleText.getGlobalBounds().size.y) },
                                 { blockWidth, blockHeight } };

        m_statBlocks.push_back(
            StatBlock(t_context, "Walk Count", t_context.statistics.walk_count, blockRect));

        blockRect.position.y += blockHeight;

        m_statBlocks.push_back(
            StatBlock(t_context, "Barrels Opened", t_context.statistics.barrels_opened, blockRect));

        blockRect.position.y += blockHeight;

        t_context.statistics.rooms_discovered = t_context.maps.discoveredCount();

        m_statBlocks.push_back(StatBlock(
            t_context, "Rooms Discovered", t_context.statistics.rooms_discovered, blockRect));

        blockRect.position.y += blockHeight;

        m_statBlocks.push_back(
            StatBlock(t_context, "Spells Cast", t_context.statistics.spells_cast, blockRect));

        blockRect.position.y += blockHeight;

        m_statBlocks.push_back(StatBlock(
            t_context, "Monsters Killed", t_context.statistics.monsters_killed, blockRect));

        blockRect.position.y += blockHeight;

        m_statBlocks.push_back(StatBlock(
            t_context, "Items Collected", t_context.statistics.items_collected, blockRect));

        blockRect.position.y += blockHeight;

        m_statBlocks.push_back(
            StatBlock(t_context, "Items Dropped", t_context.statistics.items_dropped, blockRect));

        blockRect.position.y += blockHeight;

        m_statBlocks.push_back(StatBlock(
            t_context, "Obstacles Destroyed", t_context.statistics.obstacles_destroyed, blockRect));

        blockRect.position.y += blockHeight;
        t_context.statistics.most_coins_held =
            static_cast<std::size_t>(t_context.player.goldMaxHeld());

        m_statBlocks.push_back(StatBlock(
            t_context, "Most Coins Held", t_context.statistics.most_coins_held, blockRect));

        blockRect.position.y += blockHeight;
        t_context.statistics.level_reached = static_cast<std::size_t>(t_context.player.level());

        m_statBlocks.push_back(
            StatBlock(t_context, "Level Reached", t_context.statistics.level_reached, blockRect));

        blockRect.position.y += blockHeight;

        m_statBlocks.push_back(
            StatBlock(t_context, "Chests Opened", t_context.statistics.chests_opened, blockRect));
    }

    void StateStatistics::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
    }

    void StateStatistics::draw(
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

        for (const StatBlock & block : m_statBlocks)
        {
            block.draw(t_target, t_states);
        }
    }

    void StateStatistics::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>();
        if (!keyPtr)
        {
            return;
        }

        t_context.state.setChangePending(State::Credits);
    }

} // namespace castlecrawl