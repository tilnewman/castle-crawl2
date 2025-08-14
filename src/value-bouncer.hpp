#ifndef VALUE_BOUNCER_HPP_INCLUDED
#define VALUE_BOUNCER_HPP_INCLUDED
//
// value-bouncer.hpp
//

namespace castlecrawl
{

    template <typename T>
    class ValueBouncer
    {
      public:
        ValueBouncer(const T t_min, const T t_max, const float t_speed)
            : m_min{ static_cast<float>(t_min) }
            , m_max{ static_cast<float>(t_max) }
            , m_speed{ t_speed }
            , m_value{ m_min }
            , m_isRising{ true }
        {}

        [[nodiscard]] inline T min() const noexcept { return static_cast<T>(m_min); }
        [[nodiscard]] inline T max() const noexcept { return static_cast<T>(m_max); }
        [[nodiscard]] inline float speed() const noexcept { return m_speed; }
        [[nodiscard]] inline bool isRising() const noexcept { return m_isRising; }
        [[nodiscard]] inline T current() const noexcept { return static_cast<T>(m_value); }

        inline T update(const float t_step) noexcept
        {
            if (m_isRising)
            {
                m_value += (t_step * m_speed);
                if (m_value > m_max)
                {
                    m_value    = m_max;
                    m_isRising = false;
                }
            }
            else
            {
                m_value -= (t_step * m_speed);
                if (m_value < m_min)
                {
                    m_value    = m_min;
                    m_isRising = true;
                }
            }

            return current();
        }

      private:
        float m_min;
        float m_max;
        float m_speed;
        float m_value;
        bool m_isRising;
    };

} // namespace castlecrawl

#endif // VALUE_BOUNCER_HPP_INCLUDED