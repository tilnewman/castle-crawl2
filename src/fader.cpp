// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// fader.cpp
//
#include "fader.hpp"

#include "color-range.hpp"
#include "sfml-util.hpp"

namespace castlecrawl
{

    Fader::Fader()
        : m_isFadingIn{ true } // anything works here
        , m_rectangle{}
        , m_timerSec{ 0.0f }
        , m_durationSec{ 0.0f }
        , m_fadeColor{ sf::Color::Black }
    {
        reset();
    }

    void Fader::reset()
    {
        m_timerSec    = 0.0f;
        m_durationSec = 0.0f;
        m_rectangle.setPosition({ 0.0f, 0.0f });
        m_rectangle.setSize({ 0.0f, 0.0f });
    }

    void Fader::setup(
        const bool t_isFadingIn,
        const sf::Color & t_color,
        const float t_durationSec,
        const sf::FloatRect & t_rect)
    {
        m_timerSec    = 0.0f;
        m_fadeColor   = t_color;
        m_isFadingIn  = t_isFadingIn;
        m_durationSec = t_durationSec;

        if (m_isFadingIn)
        {
            m_rectangle.setFillColor(m_fadeColor);
        }
        else
        {
            m_rectangle.setFillColor(sf::Color::Transparent);
        }

        m_rectangle.setOutlineColor(sf::Color::Transparent);
        m_rectangle.setOutlineThickness(0.0f);
        m_rectangle.setPosition(t_rect.position);
        m_rectangle.setSize(t_rect.size);
    }

    bool Fader::update(const float t_elapsedSec)
    {
        const bool isFadingBefore = isFading();

        m_timerSec += t_elapsedSec;
        if (m_timerSec > m_durationSec)
        {
            m_timerSec = m_durationSec;
        }

        const bool isFadingAfter = isFading();

        const float ratio(m_timerSec / m_durationSec);

        if (m_isFadingIn)
        {
            m_rectangle.setFillColor(util::colorBlend(ratio, m_fadeColor, sf::Color::Transparent));
        }
        else
        {
            m_rectangle.setFillColor(util::colorBlend(ratio, sf::Color::Transparent, m_fadeColor));
        }

        return (isFadingBefore && !isFadingAfter);
    }

    void Fader::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_rectangle, t_states);
    }

} // namespace castlecrawl
