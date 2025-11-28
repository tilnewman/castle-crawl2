#ifndef CREATURE_HPP_INCLUDED
#define CREATURE_HPP_INCLUDED
//
// creature.hpp
//
#include "map-types.hpp"
#include "tile-image-enum.hpp"

#include <string_view>

namespace castlecrawl
{
    struct Context;

    enum class CreatureAction
    {
        None,
        Move,
        Attack,
        CastSpell,
        AcidSpray,
        PoisonBite,
        BreakWeapon,
        DevourArmor,
        BreatheFire
    };

    inline constexpr std::string_view toString(const CreatureAction t_action) noexcept
    {
        // clang-format off
        switch(t_action)
        {
            case CreatureAction::None:           { return "None";        }
            case CreatureAction::Move:           { return "Move";        }
            case CreatureAction::Attack:         { return "Attack";      }
            case CreatureAction::CastSpell:      { return "CastSpell";   }
            case CreatureAction::AcidSpray:      { return "AcidSpray";   }
            case CreatureAction::PoisonBite:     { return "PoisonBite";  }
            case CreatureAction::BreakWeapon:    { return "BreakWeapon"; }
            case CreatureAction::DevourArmor:    { return "DevourArmor"; }
            case CreatureAction::BreatheFire:    { return "BreatheFire"; }
            default:            { return "unknown_CreatureAction_error"; }
        }
        // clang-format on
    }

    struct CreatureActionEntry
    {
        CreatureActionEntry(const CreatureAction t_action, const float t_min, const float t_max)
            : action{ t_action }
            , min{ t_min }
            , max{ t_max }
        {}

        CreatureAction action;
        float min;
        float max;
    };

    //

    // base class for both NPCs and Monsters
    class Creature
    {
      public:
        Creature(const MapPos_t & t_mapPos, const TileImage t_tileImage);
        virtual ~Creature() = default;

        [[nodiscard]] inline const MapPos_t mapPosition() const noexcept { return m_mapPos; }
        [[nodiscard]] inline TileImage tileImage() const noexcept { return m_tileImage; }

        // returns true if m_mapPos was changed
        virtual CreatureAction takeTurn(const Context & t_context) = 0;

      protected:
        [[nodiscard]] bool isPlayerAdjacent(const Context & t_context) const;

        // returns true if actually moved (might not if not possible)
        bool moveToward(const Context & t_context, const MapPos_t & t_targetMapPos);

        void moveTo(const Context & t_context, const MapPos_t & t_newMapPos);

      private:
        MapPos_t m_mapPos;
        TileImage m_tileImage;
    };

} // namespace castlecrawl

#endif // CREATURE_HPP_INCLUDED