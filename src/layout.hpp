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

        [[nodiscard]] inline const sf::FloatRect screenRegion() const noexcept
        {
            return m_screenRect;
        }

        [[nodiscard]] inline const sf::FloatRect topRegion() const noexcept { return m_topRect; }
        [[nodiscard]] inline const sf::FloatRect botRegion() const noexcept { return m_botRect; }
        [[nodiscard]] inline const sf::FloatRect mapRect() const noexcept { return m_mapRect; }
        [[nodiscard]] inline const sf::Vector2f cellSize() const noexcept { return m_cellSize; }
        [[nodiscard]] inline const sf::Vector2i cellCount() const noexcept { return m_cellCount; }

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
