// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// fight-util.cpp
//
#include "fight-util.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "random.hpp"
#include "sound-player.hpp"
#include "top-panel.hpp"

#include <algorithm>

namespace castlecrawl::fight
{

    const HealthBarRectangles makeCreatureHealthBars(
        const Context & t_context, const float t_healthRatio, const MapPos_t & t_mapPos)
    {
        const sf::Vector2f cellSize{ t_context.layout.cellSize() };
        const float height{ cellSize.y * 0.075f };

        HealthBarRectangles rectangles;

        // setup foreground rectangle
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

        rectangles.foreground.setFillColor(findColor());
        rectangles.foreground.setOutlineThickness(0.0f);
        rectangles.foreground.setSize({ (cellSize.x * t_healthRatio), height });

        const sf::Vector2f cellScreenPos =
            t_context.maps.current().mapPosToScreenPos(t_context, t_mapPos);

        const sf::Vector2f screenPos{ cellScreenPos.x, ((cellScreenPos.y + cellSize.y) - height) };

        rectangles.foreground.setPosition(screenPos);

        // setup background rectangle
        rectangles.background = rectangles.foreground;

        sf::Color backgroundColor{ rectangles.background.getFillColor() };
        backgroundColor.a = 64;
        rectangles.background.setFillColor(backgroundColor);

        rectangles.background.setSize({ cellSize.x, height });

        return rectangles;
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

    void damageMonster(
        const Context & t_context,
        const int t_damage,
        const RollResult & t_rollResult,
        const MapPos_t & t_monsterMapPos,
        const sf::Color & t_messageColor)
    {
        const bool didMonsterDie{ t_context.monsters.damage(t_monsterMapPos, t_damage) };

        std::string message{ std::to_string(t_damage) };
        message += " dmg";
        if (t_rollResult.lucky)
        {
            message += " lucky!";
        }
        else if (t_rollResult.critical)
        {
            message += " critical!";
        }

        if (didMonsterDie)
        {
            const int monsterValue{ t_context.monsters.stats(t_monsterMapPos).value() };

            message += " KILLED +";
            message += std::to_string(monsterValue);
            message += "xp";

            t_context.player.experinceAdj(monsterValue);
            t_context.top_panel.update(t_context);
        }

        const sf::Color messageColor{ (didMonsterDie) ? t_context.config.message_color_attack_kill
                                                      : t_messageColor };

        t_context.anim.risingText().add(
            t_context, message, messageColor, t_context.player_display.position());

        t_context.sfx.play("hit");
    }

} // namespace castlecrawl::fight
