// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// turn-keeper.cpp
//
#include "turn-keeper.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "player.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    TurnKeeper::TurnKeeper()
        : m_owner{ TurnOwner::Player }
        , m_elapsedSec{ 0.0f }
        , m_delaySec{ 0.0f }
        , m_turnCount{ 1 } // why not zero?
    {}

    void TurnKeeper::update(const Context & t_context, const float t_elapsedSec)
    {
        if ((m_owner == TurnOwner::PlayerDelay) || (m_owner == TurnOwner::MonsterDelay) ||
            (m_owner == TurnOwner::NpcDelay))
        {
            m_elapsedSec += t_elapsedSec;
            if (m_elapsedSec > m_delaySec)
            {
                advance(t_context, 0.0f);
            }
        }
    }

    void TurnKeeper::advance(const Context & t_context, const float t_delaySec)
    {
        turnDurationActions(t_context);

        int nextTurnNumber = (static_cast<int>(m_owner) + 1);
        if (nextTurnNumber > static_cast<int>(TurnOwner::Npc)) // why not NpcDelay?
        {
            nextTurnNumber = 0;
        }

        m_owner = static_cast<TurnOwner>(nextTurnNumber);

        m_delaySec   = t_delaySec;
        m_elapsedSec = 0.0f;
    }

    void TurnKeeper::reset() { m_owner = TurnOwner::Player; }

    void TurnKeeper::turnDurationActions(const Context & t_context)
    {
        if (isPlayerTurn())
        {
            if ((m_turnCount % t_context.config.turns_per_health_increase) == 0)
            {
                t_context.player.health().adjCurrent(1);
                t_context.top_panel.update(t_context);
            }

            if ((m_turnCount % t_context.config.turns_per_mana_increase) == 0)
            {
                t_context.player.mana().adjCurrent(1);
                t_context.top_panel.update(t_context);
            }

            ++m_turnCount;
        }
    }

} // namespace castlecrawl