#ifndef CASTLECRAWL2_STATEMANAGER_HPP_INCLUDED
#define CASTLECRAWL2_STATEMANAGER_HPP_INCLUDED
//
// state-manager.hpp
//
#include "state.hpp"

#include <memory>

namespace castlecrawl2
{
    struct Context;

    class StateManager
    {
      public:
        StateManager();

        IState & current() const { return *m_stateUPtr; }
        void change(const Context & context, const State newState);

      private:
        std::unique_ptr<IState> factory(const State state) const;

      private:
        std::unique_ptr<IState> m_stateUPtr;
    };

} // namespace castlecrawl2

#endif // CASTLECRAWL2_STATEMANAGER_HPP_INCLUDED
