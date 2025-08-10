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

    inline constexpr int spellToManaCost(const Spell t_spell) noexcept
    {
        // clang-format off
        switch(t_spell)
        {
            case Spell::Scare:          { return 4;  }
            case Spell::Terrorize:      { return 7;  }
            case Spell::HeartAttack:    { return 10; }
                                                
            case Spell::Slow:           { return 3;  }
            case Spell::Stun:           { return 6;  }
            case Spell::Immobalize:     { return 10; }
                                               
            case Spell::Zap:            { return 3;  }
            case Spell::Jolt:           { return 6;  }
            case Spell::Lightning:      { return 9;  }
                                               
            case Spell::Spark:          { return 2;  }
            case Spell::Flare:          { return 4;  }
            case Spell::Fireball:       { return 9;  }
                                             
            case Spell::Frostbite:      { return 2;  }
            case Spell::FreezingWind:   { return 4;  }
            case Spell::IceShards:             
            default:                    { return 8;  }      
        }
        // clang-format on
    }

} // namespace castlecrawl

#endif // SPELLS_HPP_INCLUDED
