// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// shaker.cpp
//
#include "shaker.hpp"

#include <cmath>

namespace castlecrawl
{

    Shaker::Shaker()
        : m_range{ 0.0f }
        , m_speed{ 0.0f }
        , m_elapsedTimeSec{ 0.0f }
        , m_current{ 0.0f }
    {}

    void Shaker::setup(const float t_range, float t_speed)
    {
        m_range          = t_range; // try (context.layout.cellSize().x * 0.1f)
        m_speed          = t_speed; // try 75.0f
        m_elapsedTimeSec = 0.0f;
        m_current        = 0.0f;
    }

    float Shaker::update(const float t_elapsedSec)
    {
        m_elapsedTimeSec += t_elapsedSec;
        m_current = (static_cast<float>(sin(m_elapsedTimeSec * m_speed)) * m_range);
        return m_current;
    }

} // namespace castlecrawl
