#ifndef TURN_KEEPER_HPP_INCLUDED
#define TURN_KEEPER_HPP_INCLUDED
//
// turn-keeper.hpp
//

namespace castlecrawl
{

    class TurnKeeper
    {
      public:
        TurnKeeper();

        [[nodiscard]] inline bool isPlayerTurn() const noexcept { return m_isPlayerTurn; }

        void advance();
        void reset();

      private:
        bool m_isPlayerTurn;
    };

} // namespace castlecawl

#endif // TURN_KEEPER_HPP_INCLUDED