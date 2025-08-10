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
        Monster,
        Npc,
        System // used to play animations and the like
    };

    [[nodiscard]] inline constexpr std::string_view
        turnOwnerToName(const TurnOwner t_turnOwner) noexcept
    {
        if (t_turnOwner == TurnOwner::Player)
        {
            return "Player";
        }
        else if (t_turnOwner == TurnOwner::Monster)
        {
            return "Monster";
        }
        else if (t_turnOwner == TurnOwner::Npc)
        {
            return "Npc";
        }
        else
        {
            return "System";
        }
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

        void advance();
        void reset();

      private:
        TurnOwner m_owner;
    };

} // namespace castlecrawl

#endif // TURN_KEEPER_HPP_INCLUDED