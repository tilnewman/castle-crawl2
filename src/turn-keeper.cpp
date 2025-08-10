// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// turn-keeper.cpp
//
#include "turn-keeper.hpp"

namespace castlecrawl
{

    TurnKeeper::TurnKeeper()
        : m_owner{ TurnOwner::Player }
    {}

    void TurnKeeper::advance()
    {
        int nextTurnNumber = (static_cast<int>(m_owner) + 1);

        if (nextTurnNumber > static_cast<int>(TurnOwner::System))
        {
            nextTurnNumber = 0;
        }

        m_owner = static_cast<TurnOwner>(nextTurnNumber);
    }

    void TurnKeeper::reset() { m_owner = TurnOwner::Player; }

} // namespace castlecrawl