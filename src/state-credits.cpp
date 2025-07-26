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
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "texture-loader.hpp"
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
        : m_nameText{ util::SfmlDefaults::instance().font() }
        , m_descText{ util::SfmlDefaults::instance().font() }
        , m_licenseText{ util::SfmlDefaults::instance().font() }
        , m_extraText{ util::SfmlDefaults::instance().font() }
    {
        const sf::FloatRect screenRect = t_context.layout.screenRect();
        m_nameText                     = t_context.fonts.makeText(FontSize::Large, t_name);

        m_nameText.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_nameText.getGlobalBounds().size.x * 0.5f)),
              screenRect.size.y });

        m_descText = t_context.fonts.makeText(FontSize::Medium, t_desc, sf::Color(220, 220, 220));

        m_descText.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_descText.getGlobalBounds().size.x * 0.5f)),
              util::bottom(m_nameText) + m_vertPad });

        m_licenseText =
            t_context.fonts.makeText(FontSize::Small, t_license, sf::Color(220, 220, 220));

        m_licenseText.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_licenseText.getGlobalBounds().size.x * 0.5f)),
              util::bottom(m_descText) + m_vertPad });

        m_extraText = t_context.fonts.makeText(FontSize::Small, t_extra, sf::Color(220, 220, 220));

        m_extraText.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_extraText.getGlobalBounds().size.x * 0.5f)),
              util::bottom(m_licenseText) + m_vertPad });
    }

    void Credit::update(const float t_frameTimeSec)
    {
        const float scrollSpeed = 30.0f;
        m_nameText.move({ 0.0f, -(t_frameTimeSec * scrollSpeed) });
        m_descText.move({ 0.0f, -(t_frameTimeSec * scrollSpeed) });
        m_licenseText.move({ 0.0f, -(t_frameTimeSec * scrollSpeed) });
        m_extraText.move({ 0.0f, -(t_frameTimeSec * scrollSpeed) });
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
        m_nameText.setPosition({ m_nameText.getGlobalBounds().position.x, t_pos });

        m_descText.setPosition(
            { m_descText.getGlobalBounds().position.x, util::bottom(m_nameText) + m_vertPad });

        m_licenseText.setPosition(
            { m_licenseText.getGlobalBounds().position.x, util::bottom(m_descText) + m_vertPad });

        m_extraText.setPosition(
            { m_extraText.getGlobalBounds().position.x, util::bottom(m_licenseText) + m_vertPad });
    }

    float Credit::bottom() const { return util::bottom(m_licenseText); }

    StateCredits::StateCredits()
        : m_castleTexture{}
        , m_castleSprite{ m_castleTexture }
        , m_credits{}
    {}

    void StateCredits::onEnter(const Context & t_context)
    {
        const sf::FloatRect screenRect = t_context.layout.screenRect();

        util::TextureLoader::load(
            m_castleTexture, (t_context.config.media_path / "image/splash.png"), true);

        m_castleSprite.setTexture(m_castleTexture, true);
        m_castleSprite.setColor(sf::Color(255, 255, 255, 32));

        util::fit(m_castleSprite, { (screenRect.size.x * 0.2f), screenRect.size.x });

        m_castleSprite.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_castleSprite.getGlobalBounds().size.x * 0.5f)),
              ((screenRect.size.y * 0.5f) - (m_castleSprite.getGlobalBounds().size.y * 0.5f)) });

        m_credits.reserve(16);

        Credit & softwareCredit =
            m_credits.emplace_back(t_context, "Ziesche Til Newman", "Software");

        Credit & sfmlCredit = m_credits.emplace_back(
            t_context,
            "SFML",
            "Simple Fast Multimedia Library",
            "www.sfml-dev.org",
            "zlib/png license");

        const float vertSpacer = (screenRect.size.y * 0.12f);
        sfmlCredit.vertPosition(softwareCredit.bottom() + vertSpacer);

        Credit & fontCredit = m_credits.emplace_back(
            t_context, "Gentium-Plus", "Font", "SIL Open Font License", "www.scripts.sil.org/ofl");

        fontCredit.vertPosition(sfmlCredit.bottom() + vertSpacer);

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
        if (const auto * keyPtr = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                context.state.change(context, State::Quit);
            }
        }
    }

} // namespace castlecrawl
