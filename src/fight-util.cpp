// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// fight-util.cpp
//
#include "fight-util.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "random.hpp"

#include <algorithm>

namespace castlecrawl
{

    const sf::RectangleShape makeCreatureHealthBar(
        const Context & t_context, const float t_healthRatio, const MapPos_t & t_mapPos)
    {
        const sf::Vector2f cellSize = t_context.layout.cellSize();
        const float height          = (cellSize.y * 0.075f);

        sf::RectangleShape rectangle;

        auto findColor = [&]() {
            sf::Color color = sf::Color::Green;
            if (t_healthRatio < 0.333f)
            {
                color = sf::Color::Red;
            }
            else if (t_healthRatio < 0.666f)
            {
                color = sf::Color::Yellow;
            }

            return color;
        };

        rectangle.setFillColor(findColor());
        rectangle.setOutlineThickness(0.0f);
        rectangle.setSize({ (cellSize.x * t_healthRatio), height });

        const sf::Vector2f cellScreenPos =
            t_context.maps.current().mapPosToScreenPos(t_context, t_mapPos);

        const sf::Vector2f screenPos{ cellScreenPos.x, ((cellScreenPos.y + cellSize.y) - height) };

        rectangle.setPosition(screenPos);

        return rectangle;
    }

    const RollResult rollRivalStats(
        const Context & t_context,
        const int t_challengerValue,
        const int t_defenderValue,
        const int t_challengerLuckValue)
    {
        // check for lucky or unlucky first
        if (t_challengerLuckValue > 0)
        {
            const int luckMin  = 0;
            const int luckMax  = 200;
            const int luckRoll = t_context.random.fromTo(luckMin, luckMax);

            if (luckRoll == luckMin)
            {
                return RollResult{ .result = false };
            }
            else if (luckRoll == luckMax)
            {
                return RollResult{ .result = true, .lucky = true };
            }
            else if (luckRoll < t_challengerLuckValue)
            {
                return RollResult{ .result = true, .lucky = true };
            }
        }

        const int rollMin = 0;
        const int rollMax = 20;
        const int hitRoll = t_context.random.fromTo(rollMin, rollMax);

        if (hitRoll == rollMin)
        {
            return RollResult{ .result = false };
        }
        else if (hitRoll == rollMax)
        {
            return RollResult{ .result = true, .critical = true };
        }
        else
        {
            int adjustedValue = std::clamp((t_challengerValue - t_defenderValue), rollMin, rollMax);

            const int accuracyFloor = (rollMax / 4);
            adjustedValue           = std::clamp((adjustedValue + accuracyFloor), rollMin, rollMax);

            return RollResult{ .result = (hitRoll < adjustedValue) };
        }
    }

} // namespace castlecrawl
