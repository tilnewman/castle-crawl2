#ifndef STATEMANAGER_HPP_INCLUDED
#define STATEMANAGER_HPP_INCLUDED
//
// state-manager.hpp
//
#include "state.hpp"

#include <memory>
#include <optional>

namespace castlecrawl
{
    struct Context;

    class StateManager
    {
      public:
        StateManager();

        [[nodiscard]] inline IState & current() const { return *m_stateUPtr; }

        constexpr void setChangePending(const State t_newState) noexcept { m_pendingStateOpt = t_newState; }

        [[nodiscard]] constexpr bool isChangePending() const noexcept
        {
            return m_pendingStateOpt.has_value();
        }

        void change(const Context & t_context);

      private:
        [[nodiscard]] std::unique_ptr<IState> factory(const State t_state) const;

      private:
        std::optional<State> m_pendingStateOpt;
        std::unique_ptr<IState> m_stateUPtr;
    };

} // namespace castlecrawl

#endif // STATEMANAGER_HPP_INCLUDED
