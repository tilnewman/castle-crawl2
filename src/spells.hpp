#ifndef SPELLS_HPP_INCLUDED
#define SPELLS_HPP_INCLUDED
//
// spells.hpp
//
#include <string_view>

namespace castlecrawl
{

    enum class SpellCategory
    {
        Fire,
        Ice,
        Energy,
        Fear,
        Grip
    };

    [[nodiscard]] inline constexpr std::string_view
        toString(const SpellCategory t_spellCategroy) noexcept
    {
        // clang-format off
        switch(t_spellCategroy)
        {
            case SpellCategory::Fire:    { return "Fire";   }
            case SpellCategory::Ice:     { return "Ice";    }
            case SpellCategory::Energy:  { return "Energy"; }
            case SpellCategory::Fear:    { return "Fear";   }
            case SpellCategory::Grip:    { return "Grip";   }
            default:{ return "unknown_SpellCategory_error"; }
        }
        // clang-format on
    }

    //

    enum class Spell
    {
        // Fear
        Scare,
        Terrorize,
        HeartAttack,

        // Grip
        Slow,
        Stun,
        Immobillize,

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

    [[nodiscard]] inline constexpr std::string_view toString(const Spell t_spell) noexcept
    {
        // clang-format off
        switch(t_spell)
        {
            case Spell::Scare:          { return "Scare";         }
            case Spell::Terrorize:      { return "Terrorize";     }
            case Spell::HeartAttack:    { return "Heart Attack";  }

            case Spell::Slow:           { return "Slow";          }
            case Spell::Stun:           { return "Stun";          }
            case Spell::Immobillize:    { return "Immobillize";   }

            case Spell::Zap:            { return "Zap";           }
            case Spell::Jolt:           { return "Jolt";          }
            case Spell::Lightning:      { return "Lightning";     }

            case Spell::Spark:          { return "Spark";         }
            case Spell::Flare:          { return "Flare";         }
            case Spell::Fireball:       { return "Fireball";      }

            case Spell::Frostbite:      { return "Frostbite";     }
            case Spell::FreezingWind:   { return "Freezing Wind"; }
            case Spell::IceShards:      { return "Ice Shards";    }  
            default:              { return "unknown_Spell_error"; }
        }
        // clang-format on
    }

    [[nodiscard]] inline constexpr int toManaCost(const Spell t_spell) noexcept
    {
        // clang-format off
        switch(t_spell)
        {
            case Spell::Scare:          { return 4;  }
            case Spell::Terrorize:      { return 7;  }
            case Spell::HeartAttack:    { return 10; }
                                                
            case Spell::Slow:           { return 3;  }
            case Spell::Stun:           { return 6;  }
            case Spell::Immobillize:    { return 10; }
                                               
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

    [[nodiscard]] constexpr Spell toSpell(const SpellCategory t_category, const std::size_t t_index)
    {
        if (t_category == SpellCategory::Fire)
        {
            if (t_index == 0)
            {
                return Spell::Spark;
            }
            else if (t_index == 1)
            {
                return Spell::Flare;
            }
            else
            {
                return Spell::Fireball;
            }
        }
        else if (t_category == SpellCategory::Ice)
        {
            if (t_index == 0)
            {
                return Spell::Frostbite;
            }
            else if (t_index == 1)
            {
                return Spell::FreezingWind;
            }
            else
            {
                return Spell::IceShards;
            }
        }
        else if (t_category == SpellCategory::Energy)
        {
            if (t_index == 0)
            {
                return Spell::Zap;
            }
            else if (t_index == 1)
            {
                return Spell::Jolt;
            }
            else
            {
                return Spell::Lightning;
            }
        }
        else if (t_category == SpellCategory::Grip)
        {
            if (t_index == 0)
            {
                return Spell::Slow;
            }
            else if (t_index == 1)
            {
                return Spell::Stun;
            }
            else
            {
                return Spell::Immobillize;
            }
        }
        else // if (t_category == SpellCategory::Fear)
        {
            if (t_index == 0)
            {
                return Spell::Scare;
            }
            else if (t_index == 1)
            {
                return Spell::Terrorize;
            }
            else
            {
                return Spell::HeartAttack;
            }
        }
    }

} // namespace castlecrawl

#endif // SPELLS_HPP_INCLUDED
