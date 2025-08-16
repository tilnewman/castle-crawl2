#ifndef ANIM_SHAKER_HPP_INCLUDED
#define ANIM_SHAKER_HPP_INCLUDED
//
// anim-shaker.hpp
//

namespace castlecrawl
{

    class Shaker
    {
      public:
        Shaker();

        void setup(const float t_range, float t_speed);
        float update(const float t_elapsedSec);
        [[nodiscard]] inline float adjustment() const { return m_current; }

      private:
        float m_range;
        float m_speed;
        float m_elapsedTimeSec;
        float m_current;
    };

} // namespace castlecrawl

#endif // ANIM_STATE_HPP_INCLUDED
