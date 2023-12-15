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

        void setup(const float range, float speed);
        float update(const float frameTimeSec);
        float adjustment() const { return m_current; }

      private:
        float m_range;
        float m_speed;
        float m_elapsedTimeSec;
        float m_current;
    };

} // namespace castlecrawl

#endif // STATE_HPP_INCLUDED
