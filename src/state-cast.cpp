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
        const std::string & t_name,
        const sf::Color & t_color,
        const sf::FloatRect & t_screenRegion)
        : text{ t_context.fonts.makeText(FontSize::Medium, t_name, t_color) }
        , color{ t_color }
        , rectangle{}
        , has_focus{ false }
    {
        rectangle.setPosition(t_screenRegion.position);
        rectangle.setSize(t_screenRegion.size);
        rectangle.setOutlineThickness(1.0f);
        rectangle.setOutlineColor(t_color);

        util::centerInside(text, rectangle.getGlobalBounds());

        setFocus(false);
    }

    void SpellCategoryRectangle::setFocus(const bool t_hasFocus)
    {
        has_focus = t_hasFocus;
        if (has_focus)
        {
            rectangle.setFillColor(sf::Color(color.r, color.g, color.b, 64));
            text.setFillColor(color);
        }
        else
        {
            rectangle.setFillColor(sf::Color(color.r, color.g, color.b, 32));
            text.setFillColor(color - sf::Color(100, 100, 100, 0));
        }
    }

    void SpellCategoryRectangle::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(rectangle, t_states);
        t_target.draw(text, t_states);
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
        , m_fireSprite{ m_fireTexture }
        , m_iceSprite{ m_iceTexture }
        , m_energySprite{ m_energyTexture }
        , m_gripSprite{ m_gripTexture }
        , m_fearSprite{ m_fearTexture }
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
            m_fireTexture, (t_context.config.media_path / "image" / "fire-icon.png"), false);

        util::TextureLoader::load(
            m_iceTexture, (t_context.config.media_path / "image" / "ice-icon.png"), false);

        util::TextureLoader::load(
            m_energyTexture, (t_context.config.media_path / "image" / "energy-icon.png"), false);

        util::TextureLoader::load(
            m_gripTexture, (t_context.config.media_path / "image" / "grip-icon.png"), false);

        util::TextureLoader::load(
            m_fearTexture, (t_context.config.media_path / "image" / "fear-icon.png"), false);

        m_fireSprite.setTexture(m_fireTexture, true);
        m_iceSprite.setTexture(m_iceTexture, true);
        m_energySprite.setTexture(m_energyTexture, true);
        m_gripSprite.setTexture(m_gripTexture, true);
        m_fearSprite.setTexture(m_fearTexture, true);

        // spell category rectangles
        const sf::Color fireColor{ 255, 192, 192 };
        const sf::Color iceColor{ 192, 192, 255 };
        const sf::Color energyColor{ 192, 240, 240 };
        const sf::Color gripColor{ 225, 175, 130 };
        const sf::Color fearColor{ 190, 150, 240 };

        const float categoryRectsPosTop{ util::bottom(m_titleText) + pad };
        const float categoryRectsPosBottom{ util::bottom(botRect) - pad };
        const float categoryRectsHeight{ (categoryRectsPosBottom - categoryRectsPosTop) / 6.0f };
        const float categoryRectsWidth{ botRect.size.x * 0.15f };
        const float categoryRectPosLeft{ botRect.size.x * 0.2f };

        const sf::Vector2f categoryRectSize{ categoryRectsWidth, categoryRectsHeight };

        m_fireRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            "Fire Spells",
            fireColor,
            sf::FloatRect{ { categoryRectPosLeft, categoryRectsPosTop }, categoryRectSize });

        m_iceRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            "Ice Spells",
            iceColor,
            sf::FloatRect{
                { categoryRectPosLeft, (util::bottom(m_fireRectangleUPtr->rectangle) + 1.0f) },
                categoryRectSize });

        m_energyRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            "Energy Spells",
            energyColor,
            sf::FloatRect{
                { categoryRectPosLeft, (util::bottom(m_iceRectangleUPtr->rectangle) + 1.0f) },
                categoryRectSize });

        m_gripRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            "Grip Spells",
            gripColor,
            sf::FloatRect{
                { categoryRectPosLeft, (util::bottom(m_energyRectangleUPtr->rectangle) + 1.0f) },
                categoryRectSize });

        m_fearRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            "Fear Spells",
            fearColor,
            sf::FloatRect{
                { categoryRectPosLeft, (util::bottom(m_gripRectangleUPtr->rectangle) + 1.0f) },
                categoryRectSize });
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
                m_fireRectangleUPtr->rectangle.getGlobalBounds().contains(mousePos));

            m_iceRectangleUPtr->setFocus(
                m_iceRectangleUPtr->rectangle.getGlobalBounds().contains(mousePos));

            m_energyRectangleUPtr->setFocus(
                m_energyRectangleUPtr->rectangle.getGlobalBounds().contains(mousePos));

            m_gripRectangleUPtr->setFocus(
                m_gripRectangleUPtr->rectangle.getGlobalBounds().contains(mousePos));

            m_fearRectangleUPtr->setFocus(
                m_fearRectangleUPtr->rectangle.getGlobalBounds().contains(mousePos));
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