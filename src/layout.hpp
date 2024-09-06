#ifndef LAYOUT_HPP_INCLUDED
#define LAYOUT_HPP_INCLUDED
//
// layout.hpp
//
#include "game-config.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace castlecrawl
{

    class Layout
    {
      public:
        Layout();

        [[nodiscard]] sf::FloatRect screenRect() const { return m_screenRect; }
        [[nodiscard]] sf::FloatRect topRect() const { return m_topRect; }
        [[nodiscard]] sf::FloatRect botRect() const { return m_botRect; }
        [[nodiscard]] sf::FloatRect mapRect() const { return m_mapRect; }
        [[nodiscard]] sf::Vector2f cellSize() const { return m_cellSize; }
        [[nodiscard]] sf::Vector2i cellCount() const { return m_cellCount; }

        void setup(const GameConfig & t_config);
        void setupNewMap(const sf::Vector2i & t_cellCount);

      private:
        sf::FloatRect m_screenRect;
        sf::FloatRect m_topRect;
        sf::FloatRect m_botRect;
        sf::FloatRect m_mapRect;
        sf::Vector2f m_cellSize;
        sf::Vector2i m_cellCount;
    };

} // namespace castlecrawl

#endif // LAYOUT_HPP_INCLUDED
