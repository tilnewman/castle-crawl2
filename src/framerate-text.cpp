// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// framerate-text.cpp
//
#include "framerate-text.hpp"

#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"

#include <string>

namespace castlecrawl
{
    FramerateText::FramerateText()
        : m_text{}
        , m_frameCounter{ 0.0f }
        , m_secondClock{}
    {}

    void FramerateText::setup(const Context & t_context)
    {
        m_secondClock.restart();

        m_text.setFont(t_context.fonts.font());
        m_text.setCharacterSize(30);
        m_text.setFillColor(sf::Color::White);

        m_text.setPosition(
            0.0f, (t_context.layout.botRect().top + t_context.layout.botRect().height) - 50.0f);
    }

    void FramerateText::update()
    {
        m_frameCounter += 1.0f;

        const float elapsedTimeSec = m_secondClock.getElapsedTime().asSeconds();
        if (elapsedTimeSec >= 1.0f)
        {
            const std::size_t fps       = static_cast<std::size_t>(m_frameCounter / elapsedTimeSec);
            const std::string fpsString = std::to_string(fps) + "fps";
            m_text.setString(fpsString);

            m_frameCounter = 0.0f;
            m_secondClock.restart();
        }
    }

    void FramerateText::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_text, t_states);
    }

} // namespace castlecrawl
