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
        , m_elapsedSec{ 0.0f }
        , m_delaySec{ 0.0f }
    {}

    void TurnKeeper::update(const float t_elapsedTimeSec)
    {
        if ((m_owner == TurnOwner::PlayerDelay) || (m_owner == TurnOwner::MonsterDelay) ||
            (m_owner == TurnOwner::NpcDelay))
        {
            m_elapsedSec += t_elapsedTimeSec;
            if (m_elapsedSec > m_delaySec)
            {
                advance(0.0f);
            }
        }
    }

    void TurnKeeper::advance(const float t_delaySec)
    {
        int nextTurnNumber = (static_cast<int>(m_owner) + 1);

        if (nextTurnNumber > static_cast<int>(TurnOwner::Npc))
        {
            nextTurnNumber = 0;
        }

        m_owner = static_cast<TurnOwner>(nextTurnNumber);

        m_delaySec   = t_delaySec;
        m_elapsedSec = 0.0f;
    }

    void TurnKeeper::reset() { m_owner = TurnOwner::Player; }

} // namespace castlecrawl