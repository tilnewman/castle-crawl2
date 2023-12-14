// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// fader.cpp
//
#include "fader.hpp"

#include "color-range.hpp"
#include "util.hpp"

namespace castlecrawl2
{

    Fader::Fader()
        : m_isFadingIn(true) // anything works here
        , m_rectangle()
        , m_timerSec(0.0f)
        , m_durationSec(0.0f)
        , m_fadeColor(sf::Color::Black)
    {
        reset();
    }

    void Fader::reset()
    {
        m_timerSec = 0.0f;
        m_durationSec = 0.0f;
        m_rectangle.setPosition({ 0.0f, 0.0f });
        m_rectangle.setSize({ 0.0f, 0.0f });
    }

    void Fader::setup(
        const bool isFadingIn,
        const sf::Color & color,
        const float durationSec,
        const sf::FloatRect & rect)
    {
        m_timerSec = 0.0f;
        m_fadeColor = color;
        m_isFadingIn = isFadingIn;
        m_durationSec = durationSec;

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
        m_rectangle.setPosition(util::position(rect));
        m_rectangle.setSize(util::size(rect));
    }

    bool Fader::update(const float frameTimeSec)
    {
        const bool isFadingBefore = isFading();

        m_timerSec += frameTimeSec;
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

    void Fader::draw(sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_rectangle, states);
    }

} // namespace castlecrawl2
