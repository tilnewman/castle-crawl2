#ifndef TURN_KEEPER_HPP_INCLUDED
#define TURN_KEEPER_HPP_INCLUDED
//
// turn-keeper.hpp
//
#include <string_view>

namespace castlecrawl
{

    struct Context;

    //

    enum class TurnOwner
    {
        Player,
        PlayerDelay,
        Monster,
        MonsterDelay,
        Npc,
        NpcDelay
    };

    [[nodiscard]] inline constexpr std::string_view toString(const TurnOwner t_turnOwner) noexcept
    {
        // clang-format off
        switch (t_turnOwner)
        {
            case TurnOwner::Player:         { return "Player";       }
            case TurnOwner::PlayerDelay:    { return "PlayerDelay";  }
            case TurnOwner::Monster:        { return "Monster";      }
            case TurnOwner::MonsterDelay:   { return "MonsterDelay"; }
            case TurnOwner::Npc:            { return "Npc";          }
            case TurnOwner::NpcDelay:       { return "NpcDelay";     }
            default:             { return "unknown_TurnOwner_error"; }
        }
        // clang-format on
    }

    //

    class TurnKeeper
    {
      public:
        TurnKeeper();

        [[nodiscard]] inline TurnOwner owner() const noexcept { return m_owner; }

        [[nodiscard]] inline bool isPlayerTurn() const noexcept
        {
            return (m_owner == TurnOwner::Player);
        }

        // what is the number of this turn?
        [[nodiscard]] inline std::size_t turnCount() const noexcept { return m_turnCount; }

        void advance(const Context & t_context, const float t_delaySec = 0.0f);
        void reset();

        void update(const Context & t_context, const float t_elapsedSec);

      private:
        void turnDurationActions(const Context & t_context);

      private:
        TurnOwner m_owner;
        float m_elapsedSec;
        float m_delaySec;
        std::size_t m_turnCount;
    };

} // namespace castlecrawl

#endif // TURN_KEEPER_HPP_INCLUDED