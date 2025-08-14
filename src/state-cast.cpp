// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-cast.cpp
//
#include "state-cast.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "monster-manager.hpp"
#include "player-display.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "state-manager.hpp"
#include "texture-loader.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    SpellCategoryRectangle::SpellCategoryRectangle(
        const Context & t_context,
        const sf::Texture & t_texture,
        const std::string & t_title,
        const std::string & t_spellName1,
        const std::string & t_spellName2,
        const std::string & t_spellName3,
        const sf::Color & t_color,
        const sf::Vector2f & t_position)
        : sprite{ t_texture }
        , title_text{ t_context.fonts.makeText(FontSize::Large, t_title, t_color) }
        , name_text1{ t_context.fonts.makeText(
              FontSize::Medium, t_spellName1, name_color_focus_on) }
        , name_text2{ t_context.fonts.makeText(
              FontSize::Medium, t_spellName2, name_color_focus_on) }
        , name_text3{ t_context.fonts.makeText(
              FontSize::Medium, t_spellName3, name_color_focus_on) }
        , color{ t_color }
        , has_focus{ false }
    {
        const sf::FloatRect botRect{ t_context.layout.botRect() };
        const float imageSize{ botRect.size.x / 7.0f };

        const sf::FloatRect imageRect{ { (t_position.x - (imageSize * 0.5f)), t_position.y },
                                       { imageSize, imageSize } };

        util::fitAndCenterInside(sprite, imageRect);

        sprite.setColor(t_color);

        title_text.setStyle(sf::Text::Underlined);

        title_text.setPosition(
            { (t_position.x - (title_text.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(imageRect) + (title_text.getGlobalBounds().size.y * 0.5f)) });

        const float pad{ title_text.getGlobalBounds().size.y * 0.2f };

        name_text1.setPosition(
            { (t_position.x - (name_text1.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(title_text) + title_text.getGlobalBounds().size.y) });

        name_text2.setPosition({ (t_position.x - (name_text2.getGlobalBounds().size.x * 0.5f)),
                                 (util::bottom(name_text1) + pad) });

        name_text3.setPosition({ (t_position.x - (name_text3.getGlobalBounds().size.x * 0.5f)),
                                 (util::bottom(name_text2) + pad) });

        setFocus(false);
    }

    void SpellCategoryRectangle::setFocus(const bool t_hasFocus)
    {
        has_focus = t_hasFocus;

        if (has_focus)
        {
            sprite.setColor(color);
            title_text.setFillColor(color);
            name_text1.setFillColor(name_color_focus_on);
            name_text2.setFillColor(name_color_focus_on);
            name_text3.setFillColor(name_color_focus_on);
        }
        else
        {
            sprite.setColor(color - sf::Color(100, 100, 100, 0));
            title_text.setFillColor(color - sf::Color(100, 100, 100, 0));
            name_text1.setFillColor(name_color_focus_off);
            name_text2.setFillColor(name_color_focus_off);
            name_text3.setFillColor(name_color_focus_off);
        }
    }

    void SpellCategoryRectangle::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(sprite, t_states);
        t_target.draw(title_text, t_states);
        t_target.draw(name_text1, t_states);
        t_target.draw(name_text2, t_states);
        t_target.draw(name_text3, t_states);
    }

    //

    StateCast::StateCast()
        : m_bgFadeRectangle{}
        , m_titleText{ util::SfmlDefaults::instance().font() }
        , m_fireRectangleUPtr{}
        , m_iceRectangleUPtr{}
        , m_energyRectangleUPtr{}
        , m_gripRectangleUPtr{}
        , m_fearRectangleUPtr{}
        , m_fireTexture{}
        , m_iceTexture{}
        , m_energyTexture{}
        , m_gripTexture{}
        , m_fearTexture{}
    {}

    void StateCast::onEnter(const Context & t_context)
    {
        // background fade
        const sf::FloatRect botRect{ t_context.layout.botRect() };
        m_bgFadeRectangle.setPosition(botRect.position);
        m_bgFadeRectangle.setSize(botRect.size);
        m_bgFadeRectangle.setFillColor(t_context.config.stage_background_color);

        // title
        m_titleText = t_context.fonts.makeText(FontSize::Huge, "Cast Spell");

        const float pad{ botRect.size.y * 0.05f };

        m_titleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_titleText.getGlobalBounds().size.x * 0.5f)),
              (botRect.position.y + pad) });

        // spell category images
        util::TextureLoader::load(
            m_fireTexture, (t_context.config.media_path / "image" / "fire-icon.png"), true);

        util::TextureLoader::load(
            m_iceTexture, (t_context.config.media_path / "image" / "ice-icon.png"), true);

        util::TextureLoader::load(
            m_energyTexture, (t_context.config.media_path / "image" / "energy-icon.png"), true);

        util::TextureLoader::load(
            m_gripTexture, (t_context.config.media_path / "image" / "grip-icon.png"), true);

        util::TextureLoader::load(
            m_fearTexture, (t_context.config.media_path / "image" / "fear-icon.png"), true);

        // spell category rectangles
        const sf::Color fireColor{ 255, 192, 192 };
        const sf::Color iceColor{ 192, 192, 255 };
        const sf::Color energyColor{ 192, 240, 240 };
        const sf::Color gripColor{ 225, 175, 130 };
        const sf::Color fearColor{ 190, 150, 240 };

        const float categoryColumbWidth{ botRect.size.x / 6.0f };
        const float categoryPositionTop{ util::bottom(m_titleText) + pad };

        m_fireRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_fireTexture,
            "Fire Spells",
            "Spark",
            "Flare",
            "Fireball",
            fireColor,
            sf::Vector2f{ (categoryColumbWidth * 1.0f), categoryPositionTop });

        m_iceRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_iceTexture,
            "Ice Spells",
            "Frostbite",
            "Freezing Wind",
            "Ice Shards",
            iceColor,
            sf::Vector2f{ (categoryColumbWidth * 2.0f), categoryPositionTop });

        m_energyRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_energyTexture,
            "Energy Spells",
            "Zap",
            "Jolt",
            "Lightning",
            energyColor,
            sf::Vector2f{ (categoryColumbWidth * 3.0f), categoryPositionTop });

        m_gripRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_gripTexture,
            "Grip Spells",
            "Slow",
            "Stun",
            "Immobalize",
            gripColor,
            sf::Vector2f{ (categoryColumbWidth * 4.0f), categoryPositionTop });

        m_fearRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_fearTexture,
            "Fear Spells",
            "Scare",
            "Terrorize",
            "Heart Attack",
            fearColor,
            sf::Vector2f{ (categoryColumbWidth * 5.0f), categoryPositionTop });
    }

    void StateCast::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
    }

    void StateCast::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.monsters.drawHealthLines(t_context, t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.anim.draw(t_target, t_states);
        t_context.framerate.draw(t_target, t_states);

        t_target.draw(t_context.top_panel, t_states);

        t_target.draw(m_bgFadeRectangle, t_states);
        t_target.draw(m_titleText, t_states);

        m_fireRectangleUPtr->draw(t_target, t_states);
        m_iceRectangleUPtr->draw(t_target, t_states);
        m_energyRectangleUPtr->draw(t_target, t_states);
        m_gripRectangleUPtr->draw(t_target, t_states);
        m_fearRectangleUPtr->draw(t_target, t_states);
    }

    void StateCast::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * mouseMovePtr = t_event.getIf<sf::Event::MouseMoved>())
        {
            const sf::Vector2f mousePos{ static_cast<float>(mouseMovePtr->position.x),
                                         static_cast<float>(mouseMovePtr->position.y) };

            m_fireRectangleUPtr->setFocus(
                m_fireRectangleUPtr->sprite.getGlobalBounds().contains(mousePos));

            m_iceRectangleUPtr->setFocus(
                m_iceRectangleUPtr->sprite.getGlobalBounds().contains(mousePos));

            m_energyRectangleUPtr->setFocus(
                m_energyRectangleUPtr->sprite.getGlobalBounds().contains(mousePos));

            m_gripRectangleUPtr->setFocus(
                m_gripRectangleUPtr->sprite.getGlobalBounds().contains(mousePos));

            m_fearRectangleUPtr->setFocus(
                m_fearRectangleUPtr->sprite.getGlobalBounds().contains(mousePos));
        }
        else if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                t_context.state.setChangePending(State::Play);
            }
        }
    }

} // namespace castlecrawl