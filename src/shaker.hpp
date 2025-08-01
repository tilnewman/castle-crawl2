#ifndef SHAKER_HPP_INCLUDED
#define SHAKER_HPP_INCLUDED
//
// shaker.hpp
//

namespace castlecrawl
{

    class Shaker
    {
      public:
        Shaker();

        void setup(const float t_range, float t_speed);
        float update(const float t_frameTimeSec);
        [[nodiscard]] inline float adjustment() const { return m_current; }

      private:
        float m_range;
        float m_speed;
        float m_elapsedTimeSec;
        float m_current;
    };

} // namespace castlecrawl

#endif // STATE_HPP_INCLUDED
