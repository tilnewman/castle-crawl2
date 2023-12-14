#ifndef CASTLECRAWL2_LAYOUT_HPP_INCLUDED
#define CASTLECRAWL2_LAYOUT_HPP_INCLUDED
//
// layout.hpp
//
#include "game-config.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace castlecrawl2
{

    class Layout
    {
      public:
        Layout();

        const sf::FloatRect screenRect() const { return m_screenRect; }
        const sf::FloatRect topRect() const { return m_topRect; }
        const sf::FloatRect botRect() const { return m_botRect; }
        const sf::FloatRect mapRect() const { return m_mapRect; }
        const sf::Vector2f cellSize() const { return m_cellSize; }
        const sf::Vector2i cellCount() const { return m_cellCount; }

        void setup(const GameConfig & config);
        void setupNewMap(const sf::Vector2i & cellCount);

      private:
        sf::FloatRect m_screenRect;
        sf::FloatRect m_topRect;
        sf::FloatRect m_botRect;
        sf::FloatRect m_mapRect;
        sf::Vector2f m_cellSize;
        sf::Vector2i m_cellCount;
    };

} // namespace castlecrawl2

#endif // CASTLECRAWL2_LAYOUT_HPP_INCLUDED
