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

        m_titleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_titleText.getGlobalBounds().size.x * 0.5f)),
              (botRect.position.y + (botRect.size.y * 0.05f)) });

        // spell category rectangles
        const sf::FloatRect fireCategoryRect{ { 500.0f, 500.0f }, { 300.0f, 200.0f } };

        m_fireRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context, "Fire Spells", sf::Color(255, 192, 192), fireCategoryRect);
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
    }

    void StateCast::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto * mouseMovePtr = t_event.getIf<sf::Event::MouseMoved>())
        {
            const sf::Vector2f mousePos{ static_cast<float>(mouseMovePtr->position.x),
                                         static_cast<float>(mouseMovePtr->position.y) };

            m_fireRectangleUPtr->setFocus(
                m_fireRectangleUPtr->rectangle.getGlobalBounds().contains(mousePos));
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