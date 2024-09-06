// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-credits.cpp
//
#include "state-credits.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "enemy.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "item-factory.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "map.hpp"
#include "music-player.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

#include <string>

namespace castlecrawl
{

    const float Credit::m_vertPad{ 10.0f };

    Credit::Credit(
        const Context & t_context,
        const std::string & t_name,
        const std::string & t_desc,
        const std::string & t_license,
        const std::string & t_extra)
        : m_nameText{}
        , m_descText{}
        , m_licenseText{}
        , m_extraText{}
    {
        const sf::FloatRect screenRect = t_context.layout.screenRect();
        m_nameText                     = t_context.fonts.makeText(FontSize::Large, t_name);

        m_nameText.setPosition(
            ((screenRect.width * 0.5f) - (m_nameText.getGlobalBounds().width * 0.5f)),
            screenRect.height);

        m_descText = t_context.fonts.makeText(FontSize::Medium, t_desc, sf::Color(220, 220, 220));

        m_descText.setPosition(
            ((screenRect.width * 0.5f) - (m_descText.getGlobalBounds().width * 0.5f)),
            util::bottom(m_nameText) + m_vertPad);

        m_licenseText =
            t_context.fonts.makeText(FontSize::Small, t_license, sf::Color(220, 220, 220));

        m_licenseText.setPosition(
            ((screenRect.width * 0.5f) - (m_licenseText.getGlobalBounds().width * 0.5f)),
            util::bottom(m_descText) + m_vertPad);

        m_extraText = t_context.fonts.makeText(FontSize::Small, t_extra, sf::Color(220, 220, 220));

        m_extraText.setPosition(
            ((screenRect.width * 0.5f) - (m_extraText.getGlobalBounds().width * 0.5f)),
            util::bottom(m_licenseText) + m_vertPad);
    }

    void Credit::update(const float t_frameTimeSec)
    {
        const float scrollSpeed = 30.0f;
        m_nameText.move(0.0f, -(t_frameTimeSec * scrollSpeed));
        m_descText.move(0.0f, -(t_frameTimeSec * scrollSpeed));
        m_licenseText.move(0.0f, -(t_frameTimeSec * scrollSpeed));
        m_extraText.move(0.0f, -(t_frameTimeSec * scrollSpeed));
    }

    void Credit::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_nameText, t_states);
        t_target.draw(m_descText, t_states);
        t_target.draw(m_licenseText, t_states);
        t_target.draw(m_extraText, t_states);
    }

    void Credit::vertPosition(const float t_pos)
    {
        m_nameText.setPosition(m_nameText.getGlobalBounds().left, t_pos);

        m_descText.setPosition(
            m_descText.getGlobalBounds().left, util::bottom(m_nameText) + m_vertPad);

        m_licenseText.setPosition(
            m_licenseText.getGlobalBounds().left, util::bottom(m_descText) + m_vertPad);

        m_extraText.setPosition(
            m_extraText.getGlobalBounds().left, util::bottom(m_licenseText) + m_vertPad);
    }

    float Credit::bottom() const { return util::bottom(m_licenseText); }

    StateCredits::StateCredits()
        : m_castleTexture{}
        , m_castleSprite{}
        , m_credits{}
    {}

    void StateCredits::onEnter(const Context & t_context)
    {
        const sf::FloatRect screenRect = t_context.layout.screenRect();

        m_castleTexture.loadFromFile(
            (t_context.config.media_path / "image" / "splash.png").string());

        m_castleTexture.setSmooth(true);

        m_castleSprite.setTexture(m_castleTexture);
        m_castleSprite.setColor(sf::Color(255, 255, 255, 32));

        util::fit(m_castleSprite, { (screenRect.width * 0.2f), screenRect.width });

        m_castleSprite.setPosition(
            ((screenRect.width * 0.5f) - (m_castleSprite.getGlobalBounds().width * 0.5f)),
            ((screenRect.height * 0.5f) - (m_castleSprite.getGlobalBounds().height * 0.5f)));

        Credit & softwareCredit =
            m_credits.emplace_back(t_context, "Ziesche Til Newman", "Software");

        Credit & fontCredit = m_credits.emplace_back(
            t_context, "Gentium-Plus", "Font", "SIL Open Font License", "www.scripts.sil.org/ofl");

        const float vertSpacer = (screenRect.height * 0.125f);
        fontCredit.vertPosition(softwareCredit.bottom() + vertSpacer);

        Credit & tileCredit = m_credits.emplace_back(
            t_context,
            "Daniel Cook's Map Tiles",
            "Images",
            "www.lostgarden.home.blog/2006/07/08/more-free-game-graphic",
            "www.creativecommons.org/licenses/by/3.0");

        tileCredit.vertPosition(fontCredit.bottom() + vertSpacer);

        Credit & iconCredit = m_credits.emplace_back(
            t_context, "game-icons.net", "Images", "www.creativecommons.org/licenses/by/3.0");

        iconCredit.vertPosition(tileCredit.bottom() + vertSpacer);

        Credit & doorSfxCredit = m_credits.emplace_back(
            t_context,
            "door-church-close-e",
            "Sound Effect",
            "www.freesound.org/people/InspectorJ/sounds/339677",
            "www.creativecommons.org/licenses/by/3.0");

        doorSfxCredit.vertPosition(iconCredit.bottom() + vertSpacer);

        Credit & spiderSfxCredit = m_credits.emplace_back(
            t_context,
            "spider-voice",
            "Sound Effect",
            "www.freesound.org/people/columbia23",
            "www.creativecommons.org/licenses/by/3.0");

        spiderSfxCredit.vertPosition(doorSfxCredit.bottom() + vertSpacer);

        Credit & stepsSfxCredit = m_credits.emplace_back(
            t_context,
            "footsteps-wooden-floor-loop",
            "Sound Effect",
            "www.freesound.org/people/sinatra314/sounds/58454",
            "www.creativecommons.org/licenses/by/3.0");

        stepsSfxCredit.vertPosition(spiderSfxCredit.bottom() + vertSpacer);

        Credit & gameOverSfxCredit = m_credits.emplace_back(
            t_context,
            "jingle-lose-00",
            "Sound Effect",
            "Little Robot Sound Factory",
            "www.creativecommons.org/licenses/by/3.0");

        gameOverSfxCredit.vertPosition(stepsSfxCredit.bottom() + vertSpacer);
    }

    void StateCredits::update(const Context & t_context, const float t_frameTimeSec)
    {
        for (Credit & credit : m_credits)
        {
            credit.update(t_frameTimeSec);
        }

        Credit & lastCredit = m_credits.back();
        if (lastCredit.bottom() < 0.0f)
        {
            t_context.state.change(t_context, State::Quit);
        }
    }

    void StateCredits::draw(
        const Context &, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_castleSprite, states);

        for (const Credit & credit : m_credits)
        {
            target.draw(credit, states);
        }
    }

    void StateCredits::handleEvent(const Context & context, const sf::Event & event)
    {
        // all other handlers are key released events
        if (event.type != sf::Event::KeyPressed)
        {
            return;
        }

        if (event.key.code == sf::Keyboard::Escape)
        {
            context.state.change(context, State::Quit);
            return;
        }
    }

} // namespace castlecrawl
