// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-credits.cpp
//
#include "state-credits.hpp"

#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"
#include "music-player.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "state-manager.hpp"
#include "texture-loader.hpp"

#include <string>

namespace castlecrawl
{

    Credit::Credit(
        const Context & t_context,
        const std::string & t_name,
        const std::filesystem::path & t_imagePath,
        const float & t_imageScale,
        const std::string & t_desc,
        const std::string & t_license,
        const std::string & t_extra)
        : m_texture{}
        , m_sprite{ m_texture }
        , m_nameText{ util::SfmlDefaults::instance().font() }
        , m_descText{ util::SfmlDefaults::instance().font() }
        , m_licenseText{ util::SfmlDefaults::instance().font() }
        , m_extraText{ util::SfmlDefaults::instance().font() }
    {
        util::TextureLoader::load(m_texture, t_imagePath, true);

        m_sprite.setTexture(m_texture, true);

        const sf::FloatRect screenRect = t_context.layout.screenRegion();

        const float scale =
            ((screenRect.size.x * t_imageScale) / m_sprite.getGlobalBounds().size.x);

        m_sprite.setScale({ scale, scale });

        m_sprite.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_sprite.getGlobalBounds().size.x * 0.5f)),
              screenRect.size.y });

        m_nameText = t_context.fonts.makeText(FontSize::Large, t_name);

        m_nameText.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_nameText.getGlobalBounds().size.x * 0.5f)),
              util::bottom(m_sprite.getGlobalBounds()) });

        const sf::Color textColor = sf::Color(220, 220, 220);

        m_descText = t_context.fonts.makeText(FontSize::Medium, t_desc, textColor);

        m_descText.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_descText.getGlobalBounds().size.x * 0.5f)),
              util::bottom(m_nameText) });

        m_licenseText = t_context.fonts.makeText(FontSize::Small, t_license, textColor);

        m_licenseText.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_licenseText.getGlobalBounds().size.x * 0.5f)),
              util::bottom(m_descText) });

        m_extraText = t_context.fonts.makeText(FontSize::Small, t_extra, textColor);

        m_extraText.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_extraText.getGlobalBounds().size.x * 0.5f)),
              util::bottom(m_licenseText) });
    }

    void Credit::update(const float t_elapsedSec)
    {
        const float vertScrollAmount = -(t_elapsedSec * 30.0f);
        m_sprite.move({ 0.0f, vertScrollAmount });
        m_nameText.move({ 0.0f, vertScrollAmount });
        m_descText.move({ 0.0f, vertScrollAmount });
        m_licenseText.move({ 0.0f, vertScrollAmount });
        m_extraText.move({ 0.0f, vertScrollAmount });
    }

    void Credit::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_sprite, t_states);
        t_target.draw(m_nameText, t_states);
        t_target.draw(m_descText, t_states);
        t_target.draw(m_licenseText, t_states);
        t_target.draw(m_extraText, t_states);
    }

    void Credit::vertPosition(const Context & t_context, const float t_pos)
    {
        m_sprite.setPosition({ m_sprite.getGlobalBounds().position.x, t_pos });

        m_nameText.setPosition(
            { m_nameText.getGlobalBounds().position.x,
              util::bottom(m_sprite) + (t_context.layout.screenRegion().size.y * 0.0175f) });

        const float vertPadRatio = 0.2f;

        m_descText.setPosition(
            { m_descText.getGlobalBounds().position.x,
              util::bottom(m_nameText) + (m_nameText.getGlobalBounds().size.y * vertPadRatio) });

        m_licenseText.setPosition(
            { m_licenseText.getGlobalBounds().position.x,
              util::bottom(m_descText) + (m_descText.getGlobalBounds().size.y * vertPadRatio) });

        m_extraText.setPosition(
            { m_extraText.getGlobalBounds().position.x,
              util::bottom(m_licenseText) +
                  (m_licenseText.getGlobalBounds().size.y * vertPadRatio) });
    }

    float Credit::bottom() const { return util::bottom(m_extraText); }

    StateCredits::StateCredits()
        : m_castleTexture{}
        , m_castleSprite{ m_castleTexture }
        , m_credits{}
    {}

    void StateCredits::onEnter(const Context & t_context)
    {
        t_context.music.stopAll();
        t_context.music.start("credits.ogg");

        const sf::FloatRect screenRect = t_context.layout.screenRegion();

        util::TextureLoader::load(
            m_castleTexture, (t_context.config.media_path / "image" / "castle.png"), true);

        m_castleSprite.setTexture(m_castleTexture, true);
        m_castleSprite.setColor(sf::Color(255, 255, 255, 32));

        util::fit(m_castleSprite, { (screenRect.size.x * 0.2f), screenRect.size.x });

        m_castleSprite.setPosition(
            { ((screenRect.size.x * 0.5f) - (m_castleSprite.getGlobalBounds().size.x * 0.5f)),
              ((screenRect.size.y * 0.5f) - (m_castleSprite.getGlobalBounds().size.y * 0.5f)) });

        m_credits.reserve(16);

        const float vertSpacer = (screenRect.size.y * 0.12f);

        Credit & softwareCredit = m_credits.emplace_back(
            t_context,
            "Ziesche Til Newman",
            (t_context.config.media_path / "image/credits/avatar.png"),
            0.062f,
            "Design, Programming");

        softwareCredit.vertPosition(t_context, screenRect.size.y);

        Credit & sfmlCredit = m_credits.emplace_back(
            t_context,
            "",
            (t_context.config.media_path / "image/credits/sfml.png"),
            0.136f,
            "Simple Fast Multimedia Library",
            "www.sfml-dev.org",
            "www.opensource.org/license/Zlib");

        sfmlCredit.vertPosition(t_context, softwareCredit.bottom() + vertSpacer);

        Credit & tileCredit = m_credits.emplace_back(
            t_context,
            "Daniel Cook's Map Tiles",
            (t_context.config.media_path / "image/credits/daniel-cook.png"),
            0.0875f,
            "Images",
            "www.lostgarden.home.blog/2006/07/08/more-free-game-graphic",
            "www.creativecommons.org/licenses/by/3.0");

        tileCredit.vertPosition(t_context, sfmlCredit.bottom() + vertSpacer);

        Credit & stoneSoupCredit = m_credits.emplace_back(
            t_context,
            "Chris Hamons Stone Soup Dungeon Crawl Tiles",
            (t_context.config.media_path / "image/credits/stone-soup.png"),
            0.062f,
            "Images",
            "wwww.opengameart.org/content/dungeon-crawl-32x32-tiles",
            "www.creativecommons.org/publicdomain/zero/1.0");

        stoneSoupCredit.vertPosition(t_context, tileCredit.bottom() + vertSpacer);

        Credit & gameIconsCredit = m_credits.emplace_back(
            t_context,
            "Game Icons",
            (t_context.config.media_path / "image/credits/game-icons.png"),
            0.062f,
            "Images",
            "www.game-icons.net",
            "www.creativecommons.org/licenses/by/3.0");

        gameIconsCredit.vertPosition(t_context, stoneSoupCredit.bottom() + vertSpacer);

        Credit & fontCredit = m_credits.emplace_back(
            t_context,
            "Gentium-Plus",
            (t_context.config.media_path / "image/credits/font.png"),
            0.04f,
            "Font",
            "SIL Open Font License",
            "www.scripts.sil.org/ofl");

        fontCredit.vertPosition(t_context, gameIconsCredit.bottom() + vertSpacer);

        Credit & doorSfxCredit = m_credits.emplace_back(
            t_context,
            "door-church-close-e",
            (t_context.config.media_path / "image/credits/freesound.png"),
            0.145f,
            "Sound Effect",
            "www.freesound.org/people/InspectorJ/sounds/339677",
            "www.creativecommons.org/licenses/by/3.0");

        doorSfxCredit.vertPosition(t_context, fontCredit.bottom() + vertSpacer);

        Credit & stepsSfxCredit = m_credits.emplace_back(
            t_context,
            "footsteps-wooden-floor-loop",
            (t_context.config.media_path / "image/credits/freesound.png"),
            0.145f,
            "Sound Effect",
            "www.freesound.org/people/sinatra314/sounds/58454",
            "www.creativecommons.org/licenses/by/3.0");

        stepsSfxCredit.vertPosition(t_context, doorSfxCredit.bottom() + vertSpacer);

        Credit & gameOverSfxCredit = m_credits.emplace_back(
            t_context,
            "jingle-lose-00",
            (t_context.config.media_path / "image/credits/freesound.png"),
            0.145f,
            "Sound Effect",
            "Little Robot Sound Factory",
            "www.creativecommons.org/licenses/by/3.0");

        gameOverSfxCredit.vertPosition(t_context, stepsSfxCredit.bottom() + vertSpacer);

        Credit & creditsMusicCredit = m_credits.emplace_back(
            t_context,
            "Radakan",
            (t_context.config.media_path / "image/credits/open-game-art.png"),
            0.2f,
            "Music",
            "Posted to OpenGameArt.org by Janne Hanhisuanto",
            "www.creativecommons.org/licenses/by/3.0");

        creditsMusicCredit.vertPosition(t_context, gameOverSfxCredit.bottom() + vertSpacer);
    }

    void StateCredits::update(const Context & t_context, const float t_elapsedSec)
    {
        for (Credit & credit : m_credits)
        {
            credit.update(t_elapsedSec);
        }

        Credit & lastCredit = m_credits.back();
        if (lastCredit.bottom() < 0.0f)
        {
            t_context.state.setChangePending(State::Quit);
        }
    }

    void StateCredits::draw(
        const Context &, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_castleSprite, t_states);

        for (const Credit & credit : m_credits)
        {
            t_target.draw(credit, t_states);
        }
    }

    void StateCredits::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                t_context.state.setChangePending(State::Quit);
            }
            else if (
                (keyPtr->scancode == sf::Keyboard::Scancode::Down) ||
                (keyPtr->scancode == sf::Keyboard::Scancode::Up))
            {
                for (Credit & credit : m_credits)
                {
                    credit.update(0.5f);
                }
            }
        }
    }

} // namespace castlecrawl
