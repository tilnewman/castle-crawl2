// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// turn-keeper.cpp
//
#include "turn-keeper.hpp"

namespace castlecrawl
{

    TurnKeeper::TurnKeeper()
        : m_isPlayerTurn{ true }
    {}

    void TurnKeeper::advance() { m_isPlayerTurn = !m_isPlayerTurn; }

    void TurnKeeper::reset() { m_isPlayerTurn = true; }

} // namespace castlecrawl