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
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "statistics.hpp"
#include "top-panel.hpp"
#include "turn-keeper.hpp"

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
            ++t_context.statistics.monsters_killed;

            const int monsterValue{ t_context.monsters.stats(t_monsterMapPos).value() };

            message += " KILLED +";
            message += std::to_string(monsterValue);
            message += "xp";

            t_context.player.experinceAdj(monsterValue);
            t_context.top_panel.update(t_context);

            t_context.anim.crossbones().add(t_context, t_monsterMapPos);
        }

        const sf::Color messageColor{ (didMonsterDie) ? t_context.config.message_color_attack_kill
                                                      : t_messageColor };

        t_context.anim.risingText().add(
            t_context, message, messageColor, t_context.player_display.position());
    }

    void castSpell(
        const Context & t_context,
        const Spell t_spell,
        const MapPos_t & t_mapPos,
        const sf::Keyboard::Scancode t_direction)
    {
        sf::FloatRect animRect{ t_context.maps.current().mapPosToScreenPos(t_context, t_mapPos),
                                t_context.layout.cellSize() };

        if (t_spell == Spell::Spark)
        {
            t_context.anim.player().play("spark", util::scaleRectInPlaceCopy(animRect, 2.5f));
        }
        else if (t_spell == Spell::Flare)
        {
            util::AnimConfig config(2.5f);

            animRect.position.y -= (animRect.size.y * 0.2f);

            t_context.anim.player().play(
                "flare", util::scaleRectInPlaceCopy(animRect, 1.75f), config);
        }
        else if (t_spell == Spell::Fireball)
        {
            util::AnimConfig config(3.0f);

            t_context.anim.player().play(
                "fireball", util::scaleRectInPlaceCopy(animRect, 2.5f), config);
        }
        else if (t_spell == Spell::Frostbite)
        {
            util::AnimConfig config(1.5f);

            t_context.anim.player().play(
                "frostbite", util::scaleRectInPlaceCopy(animRect, 2.25f), config);
        }
        else if (t_spell == Spell::FreezingWind)
        {
            util::AnimConfig config(2.75f);

            util::scaleRectInPlace(animRect, 3.0f);
            animRect.size.y *= 2.0f;
            animRect.position.y -= (animRect.size.y * 0.25f);

            t_context.anim.player().play("freezing-wind", animRect, config);
        }
        else if (t_spell == Spell::IceShards)
        {
            t_context.anim.player().play("ice-shards", util::scaleRectInPlaceCopy(animRect, 2.75f));
        }
        else if (t_spell == Spell::Zap)
        {
            util::AnimConfig config(1.0f, t_context.config.spell_color_energy);

            // use the frostbite anim for zap because it looks good enough for now
            t_context.anim.player().play(
                "frostbite", util::scaleRectInPlaceCopy(animRect, 2.0f), config);
        }
        else if (t_spell == Spell::Jolt)
        {
            util::AnimConfig config(1.75f, t_context.config.spell_color_energy);

            t_context.anim.player().play(
                "jolt", util::scaleRectInPlaceCopy(animRect, 1.75f), config);
        }
        else if (t_spell == Spell::Lightning)
        {
            util::AnimConfig config(2.0f, t_context.config.spell_color_energy);

            util::scaleRectInPlace(animRect, { 3.5f, 3.0f });
            animRect.position.y -= (animRect.size.y * 0.1f);

            t_context.anim.player().play("lightning", animRect, config);
        }
        else if (t_spell == Spell::Slow)
        {
            util::AnimConfig config(0.75f, t_context.config.spell_color_grip);

            t_context.anim.player().play(
                "orb-charge", util::scaleRectInPlaceCopy(animRect, { 1.25f, 2.0f }), config);
        }
        else if (t_spell == Spell::Stun)
        {
            util::AnimConfig config(1.5f, t_context.config.spell_color_grip);

            t_context.anim.player().play(
                "orb-charge", util::scaleRectInPlaceCopy(animRect, { 1.25f, 2.0f }), config);
        }
        else if (t_spell == Spell::Immobilize)
        {
            util::AnimConfig config(1.75f, t_context.config.spell_color_grip);

            t_context.anim.player().play(
                "orb-charge", util::scaleRectInPlaceCopy(animRect, { 1.25f, 2.0f }), config);
        }
        else if (t_spell == Spell::Scare)
        {
            util::AnimConfig config(2.25f, t_context.config.spell_color_fear);

            t_context.anim.player().play(
                "spell", util::scaleRectInPlaceCopy(animRect, 1.75f), config);
        }
        else if (t_spell == Spell::Terrorize)
        {
            util::AnimConfig config(2.25f, t_context.config.spell_color_fear);

            t_context.anim.player().play(
                "spell", util::scaleRectInPlaceCopy(animRect, 1.75f), config);
        }
        else if (t_spell == Spell::HeartAttack)
        {
            util::AnimConfig config(8.0f, t_context.config.spell_color_fear);

            t_context.anim.player().play(
                "spell", util::scaleRectInPlaceCopy(animRect, 1.75f), config);
        }

        t_context.player.setSpellLastCast(t_spell, t_direction);

        t_context.player.manaAdj(-toManaCost(t_spell));
        t_context.top_panel.update(t_context);

        ++t_context.statistics.spells_cast;

        // apply damage to the monster (if any is at t_mapPos)
        if (isTileImageMonster(
                charToTileImage(t_context.maps.current().cell(t_mapPos).object_char)))
        {
            const sf::Vector2i damageMinMax{ toDamageMinMax(t_spell) };
            if (damageMinMax.x < damageMinMax.y)
            {
                const int damage{ t_context.random.fromTo(damageMinMax.x, damageMinMax.y) };

                fight::damageMonster(
                    t_context,
                    damage,
                    fight::RollResult{},
                    t_mapPos,
                    t_context.config.message_color_cast_spell);
            }
        }

        t_context.sfx.play(std::string(toSfxFilename(t_spell)));
        t_context.turn.advance(t_context, t_context.config.turn_delay_after_player_attack);
    }

    const std::pair<int, int> monsterDamageMinMax(const int t_strength)
    {
        const int damageMin{ 1 + (t_strength / 10) };
        const int damageMax{ std::max((damageMin + 1), t_strength) };
        return { damageMin, damageMax };
    }

} // namespace castlecrawl::fight
