#ifndef CONDITION_HPP_INCLUDED
#define CONDITION_HPP_INCLUDED
//
// condition.hpp
//
#include <string_view>

namespace castlecrawl
{

    enum class Condition
    {
        Poisoned,
        Scared,
        Terrorized,
        Slowed,
        Stunned,
        Immobillized
    };

    [[nodiscard]] constexpr inline std::string_view toString(const Condition & t_condition)
    {
        // clang-format off
        switch (t_condition)
        {
            case Condition::Poisoned:       { return "Poisoned";     }
            case Condition::Scared:         { return "Scared";       }
            case Condition::Terrorized:     { return "Terrorized";   }
            case Condition::Slowed:         { return "Slowed";       }
            case Condition::Stunned:        { return "Stunned";      }
            case Condition::Immobillized:   { return "Immobillized"; }
            default:             { return "unknown_condition_error"; }
        }
        // clang-format on
    }

} // namespace castlecrawl

#endif // CONDITION_HPP_INCLUDED