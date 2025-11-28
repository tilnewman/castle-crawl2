// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// framerate-text.cpp
//
#include "framerate-text.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "turn-keeper.hpp"

#include <SFML/System/Time.hpp>

#include <string>

namespace castlecrawl
{
    FramerateText::FramerateText()
        : m_text{ util::SfmlDefaults::instance().font() }
        , m_frameCounter{ 0.0f }
        , m_secondClock{}
    {}

    void FramerateText::setup(const Context & t_context)
    {
        m_secondClock.restart();

        m_text.setFont(t_context.fonts.font());
        m_text.setCharacterSize(24);
        m_text.setFillColor(sf::Color(255, 255, 255, 192));

        m_text.setPosition(
            { 0.0f,
              (t_context.layout.botRegion().position.y + t_context.layout.botRegion().size.y) });
    }

    void FramerateText::update(const Context & t_context)
    {
        m_frameCounter += 1.0f;

        const float elapsedTimeSec = m_secondClock.getElapsedTime().asSeconds();
        if (elapsedTimeSec >= 1.0f)
        {
            const std::size_t fps = static_cast<std::size_t>(m_frameCounter / elapsedTimeSec);
            std::string message   = std::to_string(fps) + "FPS, ";
            message += std::to_string(t_context.anim.particleCount());
            message += " Particles, ";
            message += toString(t_context.turn.owner());
            message += "'s Turn";

            m_text.setString(message);
            util::setOriginToPosition(m_text);

            m_text.setPosition(
                { 0.0f,
                  (t_context.layout.botRegion().position.y + t_context.layout.botRegion().size.y) -
                      m_text.getGlobalBounds().size.y });

            m_frameCounter = 0.0f;
            m_secondClock.restart();
        }
    }

    void FramerateText::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_text, t_states);
    }

} // namespace castlecrawl
