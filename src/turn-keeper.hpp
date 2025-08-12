#ifndef TURN_KEEPER_HPP_INCLUDED
#define TURN_KEEPER_HPP_INCLUDED
//
// turn-keeper.hpp
//
#include <string_view>

namespace castlecrawl
{

    enum class TurnOwner
    {
        Player,
        PlayerDelay,
        Monster,
        MonsterDelay,
        Npc,
        NpcDelay
    };

    [[nodiscard]] inline constexpr std::string_view
        turnOwnerToName(const TurnOwner t_turnOwner) noexcept
    {
        // clang-format off
        switch (t_turnOwner)
        {
            case TurnOwner::Player:         { return "Player"; }
            case TurnOwner::PlayerDelay:    { return "PlayerDelay"; }
            case TurnOwner::Monster:        { return "Monster"; }
            case TurnOwner::MonsterDelay:   { return "MonsterDelay"; }
            case TurnOwner::Npc:            { return "Npc"; }
            case TurnOwner::NpcDelay:       
            default:                        { return "NpcDelay"; }
        }
        // clang-format on
    }

    class TurnKeeper
    {
      public:
        TurnKeeper();

        [[nodiscard]] inline TurnOwner owner() const noexcept { return m_owner; }

        [[nodiscard]] inline bool isPlayerTurn() const noexcept
        {
            return (m_owner == TurnOwner::Player);
        }

        void advance(const float t_delaySec = 0.0f);
        void reset();

        void update(const float t_elapsedTimeSec);

      private:
        TurnOwner m_owner;
        float m_elapsedSec;
        float m_delaySec;
    };

} // namespace castlecrawl

#endif // TURN_KEEPER_HPP_INCLUDED