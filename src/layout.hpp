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

        [[nodiscard]] inline sf::FloatRect screenRegion() const { return m_screenRect; }
        [[nodiscard]] inline sf::FloatRect topRegion() const { return m_topRect; }
        [[nodiscard]] inline sf::FloatRect botRegion() const { return m_botRect; }
        [[nodiscard]] inline sf::FloatRect mapRect() const { return m_mapRect; }
        [[nodiscard]] inline sf::Vector2f cellSize() const { return m_cellSize; }
        [[nodiscard]] inline sf::Vector2i cellCount() const { return m_cellCount; }

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
