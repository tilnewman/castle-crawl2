#ifndef STATEMANAGER_HPP_INCLUDED
#define STATEMANAGER_HPP_INCLUDED
//
// state-manager.hpp
//
#include "state.hpp"

#include <memory>

namespace castlecrawl
{
    struct Context;

    class StateManager
    {
      public:
        StateManager();

        [[nodiscard]] inline IState & current() const { return *m_stateUPtr; }
        void change(const Context & t_context, const State t_newState);

      private:
        [[nodiscard]] std::unique_ptr<IState> factory(const State t_state) const;

      private:
        std::unique_ptr<IState> m_stateUPtr;
    };

} // namespace castlecrawl

#endif // STATEMANAGER_HPP_INCLUDED
