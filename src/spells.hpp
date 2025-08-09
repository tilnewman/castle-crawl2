#ifndef SPELLS_HPP_INCLUDED
#define SPELLS_HPP_INCLUDED
//
// spells.hpp
//
#include <string_view>

namespace castlecrawl
{

    enum class Spell
    {
        // Fear
        Scare,
        Terrorize,
        HeartAttack,

        // Grip
        Slow,
        Stun,
        Immobalize,

        // Energy
        Zap,
        Jolt,
        Lightning,

        // Fire
        Spark,
        Flare,
        Fireball,

        // Ice
        Frostbite,
        FreezingWind,
        IceShards
    };

    inline constexpr std::string_view spellToName(const Spell t_spell) noexcept
    {
        // clang-format off
        switch(t_spell)
        {
            case Spell::Scare:          { return "Scare"; }
            case Spell::Terrorize:      { return "Terrorize"; }
            case Spell::HeartAttack:    { return "Heart Attack"; }

            case Spell::Slow:           { return "Slow"; }
            case Spell::Stun:           { return "Stun"; }
            case Spell::Immobalize:     { return "Immobalize"; }

            case Spell::Zap:            { return "Zap"; }
            case Spell::Jolt:           { return "Jolt"; }
            case Spell::Lightning:      { return "Lightning"; }

            case Spell::Spark:          { return "Spark"; }
            case Spell::Flare:          { return "Flare"; }
            case Spell::Fireball:       { return "Fireball"; }

            case Spell::Frostbite:      { return "Frostbite"; }
            case Spell::FreezingWind:   { return "Freezing Wind"; }
            case Spell::IceShards:
            default:                    { return "Ice Shards"; }         
        }
        // clang-format on
    }

} // namespace castlecrawl

#endif // SPELLS_HPP_INCLUDED
