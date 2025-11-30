// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-manager.cpp
//
#include "state-manager.hpp"

#include "check-macros.hpp"
#include "state-cast.hpp"
#include "state-credits.hpp"
#include "state-death.hpp"
#include "state-editor.hpp"
#include "state-fight.hpp"
#include "state-inventory.hpp"
#include "state-levelup.hpp"
#include "state-play.hpp"
#include "state-splash.hpp"
#include "state-treasure.hpp"

namespace castlecrawl
{

    StateManager::StateManager()
        : m_stateUPtr(factory(State::Init))
    {}

    void StateManager::change(const Context & t_context)
    {
        if (!isChangePending())
        {
            return;
        }

        const State currentState{ m_stateUPtr->which() };
        const State pendingState{ m_pendingStateOpt.value() };

        M_CHECK(
            (pendingState != currentState),
            "Tried to change to the same State! (" << pendingState << ")");

        m_stateUPtr->onExit(t_context);
        m_stateUPtr = factory(pendingState);
        m_stateUPtr->onEnter(t_context);

        m_pendingStateOpt.reset();
    }

    std::unique_ptr<IState> StateManager::factory(const State t_state) const
    {
        switch (t_state)
        {
                // clang-format off
            case State::Init:       { return std::make_unique<StateInit>(); } 
            case State::Splash:     { return std::make_unique<StateSplash>(); }
            case State::Play:       { return std::make_unique<StatePlay>(); }
            case State::Inventory:  { return std::make_unique<StateInventory>(); }
            case State::Fight:      { return std::make_unique<StateFight>(); }
            case State::Treasure:   { return std::make_unique<StateTreasure>(); }
            case State::Quit:       { return std::make_unique<StateQuit>(); }
            case State::Death:      { return std::make_unique<StateDeath>(); }
            case State::Credits:    { return std::make_unique<StateCredits>(); }
            case State::Editor:     { return std::make_unique<StateEditor>(); }
            case State::Cast:       { return std::make_unique<StateCast>(); }
            case State::LevelUp:    { return std::make_unique<StateLevelUp>(); }
            default:
            {
                throw std::runtime_error("Error: state-manager::factory() called with unknown state!");
            }
                // clang-format on
        }
    }

} // namespace castlecrawl
