#ifndef STAT_HPP_INCLUDED
#define STAT_HPP_INCLUDED
//
// stat.hpp
//
#include <algorithm>

namespace castlecrawl
{

    // Tracks a player's stat (i.e. strength) which is the m_normal value that
    // is always clamped between a min and max, but can be temporarily changed
    // by magical items etc so this also tracks a m_current value that can
    // fluctuate higher or lower than m_normal.
    class Stat
    {
      public:
        constexpr Stat(const int t_value, const int t_min, const int t_max) noexcept
            : m_current{ t_value }
            , m_normal{ t_value }
            , m_min{ t_min }
            , m_max{ t_max }
        {}

        [[nodiscard]] constexpr int current() const noexcept { return m_current; }
        [[nodiscard]] constexpr int normal() const noexcept { return m_normal; }

        [[nodiscard]] constexpr int min() const noexcept { return m_min; }
        [[nodiscard]] constexpr int max() const noexcept { return m_max; }

        constexpr void adjCurrent(const int adjustment) noexcept
        {
            current(m_current + adjustment);
        }

        constexpr void adjNormal(const int adjustment) noexcept { normal(m_normal + adjustment); }

        constexpr void adjCurrentNormalClamped(const int adjustment) noexcept
        {
            adjCurrent(adjustment);
            m_current = std::clamp(m_current, m_min, m_normal);
        }

        constexpr void current(const int newValue) noexcept
        {
            m_current = newValue;
            m_current = std::clamp(m_current, m_min, m_max);
        }

        constexpr void normal(const int newValue) noexcept
        {
            m_normal = newValue;
            m_normal = std::clamp(m_normal, m_min, m_max);
        }

        constexpr void reset() noexcept { m_current = m_normal; }

        [[nodiscard]] constexpr float ratio() const noexcept
        {
            if (0 == m_normal)
            {
                return 0.0f;
            }
            else
            {
                return (static_cast<float>(m_current) / static_cast<float>(m_normal));
            }
        }

      private:
        int m_current;
        int m_normal;
        int m_min;
        int m_max;
    };

} // namespace castlecrawl

#endif // STAT_HPP_INCLUDED
