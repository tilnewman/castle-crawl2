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

    StatAwardBlock::StatAwardBlock(
        const Context & t_context, const std::string & t_name, const sf::FloatRect & t_rect)
        : m_rect{ t_rect }
        , m_rectangle{}
        , m_name{ t_name }
        , m_nameText{ util::SfmlDefaults::instance().font() }
        , m_valueText{ util::SfmlDefaults::instance().font() }
        , m_awardedPoints{ 0 }
        , m_isSelected{ t_name == "Strength" }
    {
        m_rectangle.setSize(m_rect.size);
        m_rectangle.setPosition(m_rect.position);
        m_rectangle.setOutlineThickness(0.0f);

        const float pad = (t_context.layout.screenRegion().size.x * 0.01f);

        m_nameText = t_context.fonts.makeText(FontSize::Medium, m_name);
        util::centerInside(m_nameText, m_rect);

        m_nameText.setPosition(
            { (m_rect.position.x + pad), m_nameText.getGlobalBounds().position.y });

        m_valueText =
            t_context.fonts.makeText(FontSize::Medium, std::to_string(stat(t_context).current()));

        util::centerInside(m_valueText, m_rect);

        m_valueText.setPosition({ util::right(m_rect), m_valueText.getGlobalBounds().position.y });

        select(m_isSelected);
    }

    bool StatAwardBlock::addPoint(const Context & t_context)
    {
        if (m_awardedPoints < m_perStatAwardPointMax)
        {
            ++m_awardedPoints;

            stat(t_context).adjNormal(1);
            stat(t_context).adjCurrent(1);

            m_valueText.setString(std::to_string(stat(t_context).current()));
            util::setOriginToPosition(m_valueText);

            return true;
        }
        else
        {
            return false;
        }
    }

    bool StatAwardBlock::removePoint(const Context & t_context)
    {
        if (m_awardedPoints > 0)
        {
            --m_awardedPoints;

            stat(t_context).adjNormal(-1);
            stat(t_context).adjCurrent(-1);

            m_valueText.setString(std::to_string(stat(t_context).current()));
            util::setOriginToPosition(m_valueText);

            return true;
        }
        else
        {
            return false;
        }
    }

    void StatAwardBlock::select(const bool t_isSelected)
    {
        m_isSelected = t_isSelected;

        if (m_isSelected)
        {
            m_rectangle.setFillColor(sf::Color(32, 32, 32));
        }
        else
        {
            m_rectangle.setFillColor(sf::Color::Transparent);
        }
    }

    void StatAwardBlock::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_rectangle, t_states);
        t_target.draw(m_nameText, t_states);
        t_target.draw(m_valueText, t_states);
    }

    Stat & StatAwardBlock::stat(const Context & t_context) const
    {
        if (m_name == "Strength")
        {
            return t_context.player.strength();
        }
        else if (m_name == "Dexterity")
        {
            return t_context.player.dexterity();
        }
        else if (m_name == "Accuracy")
        {
            return t_context.player.accuracy();
        }
        else if (m_name == "Luck")
        {
            return t_context.player.luck();
        }
        else
        {
            return t_context.player.arcane();
        }
    }

    //

    StateLevelUp::StateLevelUp()
        : m_bgFadeRectangle{}
        , m_titleText{ util::SfmlDefaults::instance().font() }
        , m_subTitleText{ util::SfmlDefaults::instance().font() }
        , m_instructionText1{ util::SfmlDefaults::instance().font() }
        , m_instructionText2{ util::SfmlDefaults::instance().font() }
        , m_errorText{ util::SfmlDefaults::instance().font() }
        , m_errorTimerSec{ 0.0f }
        , m_statPointsAwarded{ 0 }
        , m_statPointsAwardedMax{ 10 }
        , m_statBlocks{}
        , m_selectionIndex{ 0 }
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
            "Congradulations!  You have earned enough experience to advance to level ";

        subTitleStr += std::to_string(t_context.player.level());
        subTitleStr += '!';

        m_subTitleText = t_context.fonts.makeText(
            FontSize::Medium, subTitleStr, t_context.config.state_color_subtitle);

        m_subTitleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_subTitleText.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_titleText) + (pad * 0.25f)) });

        // navigation instruction text
        m_instructionText1 = t_context.fonts.makeText(
            FontSize::Small,
            "Use the up/down arrow keys to select a stat, then left/right to add/remove points.",
            t_context.config.state_color_subtitle);

        m_instructionText1.setStyle(sf::Text::Italic);

        m_instructionText1.setPosition(
            { ((botRect.size.x * 0.5f) - (m_instructionText1.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_subTitleText) + (pad * 0.75f)) });

        // points remaining instruciton text
        m_instructionText2 = t_context.fonts.makeText(
            FontSize::Small,
            "Distribute your remaining 10 points, then press Enter.",
            t_context.config.state_color_subtitle);

        m_instructionText2.setStyle(sf::Text::Italic);

        m_instructionText2.setPosition(
            { ((botRect.size.x * 0.5f) - (m_instructionText2.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_instructionText1) + (pad * 0.1f)) });

        // stat blocks
        const float blockWidth  = screenRect.size.x * 0.1f;
        const float blockHeight = screenRect.size.y * 0.03f;

        sf::FloatRect blockRect{ { ((screenRect.size.x * 0.5f) - (blockWidth * 0.5f)),
                                   (util::bottom(m_instructionText2) +
                                    m_instructionText2.getGlobalBounds().size.y) },
                                 { blockWidth, blockHeight } };

        m_statBlocks.push_back(StatAwardBlock(t_context, "Strength", blockRect));

        blockRect.position.y += blockHeight;
        m_statBlocks.push_back(StatAwardBlock(t_context, "Dexterity", blockRect));

        blockRect.position.y += blockHeight;
        m_statBlocks.push_back(StatAwardBlock(t_context, "Accuracy", blockRect));

        blockRect.position.y += blockHeight;
        m_statBlocks.push_back(StatAwardBlock(t_context, "Luck", blockRect));

        blockRect.position.y += blockHeight;
        m_statBlocks.push_back(StatAwardBlock(t_context, "Arcane", blockRect));

        // error text
        m_errorText =
            t_context.fonts.makeText(FontSize::Large, "", t_context.config.error_message_color);
    }

    void StateLevelUp::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);

        if (!m_errorText.getString().isEmpty())
        {
            m_errorTimerSec += t_elapsedSec;
            const float errorTextDurationSec{ 5.0f };
            if (m_errorTimerSec < errorTextDurationSec)
            {
                const int alpha{ 255 -
                                 util::map(m_errorTimerSec, 0.0f, errorTextDurationSec, 0, 255) };

                sf::Color color{ m_errorText.getFillColor() };
                color.a = static_cast<uint8_t>(alpha);
                m_errorText.setFillColor(color);
            }
            else
            {
                m_errorText.setString("");
            }
        }
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
        t_target.draw(m_instructionText1, t_states);
        t_target.draw(m_instructionText2, t_states);

        for (const StatAwardBlock & block : m_statBlocks)
        {
            block.draw(t_target, t_states);
        }

        t_target.draw(m_errorText, t_states);
    }

    void StateLevelUp::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>();
        if (!keyPtr)
        {
            return;
        }

        if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
        {
            showErrorMessage(t_context, "Award all your stat points and then press enter.");
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Enter)
        {
            if (m_statPointsAwarded == m_statPointsAwardedMax)
            {
                t_context.state.setChangePending(State::Play);
            }
            else
            {
                showErrorMessage(t_context, "You haven't awarded all your stat points yet.");
            }
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Up)
        {
            if (m_selectionIndex > 0)
            {
                --m_selectionIndex;

                for (std::size_t index{ 0 }; index < m_statBlocks.size(); ++index)
                {
                    m_statBlocks.at(index).select(m_selectionIndex == index);
                }

                t_context.sfx.play("gui-tink");
            }
            else
            {
                t_context.sfx.play("error-1");
            }
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Down)
        {
            if (m_selectionIndex < (m_statBlocks.size() - 1))
            {
                ++m_selectionIndex;

                for (std::size_t index{ 0 }; index < m_statBlocks.size(); ++index)
                {
                    m_statBlocks.at(index).select(m_selectionIndex == index);
                }

                t_context.sfx.play("gui-tink");
            }
            else
            {
                t_context.sfx.play("error-1");
            }
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Left)
        {
            if (m_statPointsAwarded > 0)
            {
                if (m_statBlocks.at(m_selectionIndex).removePoint(t_context))
                {
                    --m_statPointsAwarded;
                    updateDescriptionText(t_context);
                    t_context.sfx.play("tick-off-2");
                }
                else
                {
                    showErrorMessage(t_context, "You cannot reduce a stat from where it started.");
                }
            }
            else
            {
                t_context.sfx.play("error-1");
            }
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Right)
        {
            if (m_statPointsAwarded < m_statPointsAwardedMax)
            {
                if (m_statBlocks.at(m_selectionIndex).addPoint(t_context))
                {
                    ++m_statPointsAwarded;
                    updateDescriptionText(t_context);
                    t_context.sfx.play("tick-off-1");
                }
                else
                {
                    std::string errorMessageStr = "You can't add more than ";
                    errorMessageStr += std::to_string(StatAwardBlock::m_perStatAwardPointMax);
                    errorMessageStr += " points to any one stat.";

                    showErrorMessage(t_context, errorMessageStr);
                }
            }
            else
            {
                t_context.sfx.play("error-1");
            }
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

        t_context.sfx.play("error-2");
    }

    void StateLevelUp::updateDescriptionText(const Context & t_context)
    {
        const int pointsRemaining = (m_statPointsAwardedMax - m_statPointsAwarded);

        std::string str;
        
        if (pointsRemaining > 0)
        {
            str += "Distribute your remaining ";
            str += std::to_string(pointsRemaining);
            str += " points, then press Enter.";
        }
        else
        {
            str = "That's it!  All done.  Press Enter.";
        }

        m_instructionText2.setString(str);
        util::setOriginToPosition(m_instructionText2);

        const sf::FloatRect botRect{ t_context.layout.botRegion() };
        const float pad{ botRect.size.y * 0.05f };

        m_instructionText2.setPosition(
            { ((botRect.size.x * 0.5f) - (m_instructionText2.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_instructionText1) + (pad * 0.1f)) });
    }

} // namespace castlecrawl