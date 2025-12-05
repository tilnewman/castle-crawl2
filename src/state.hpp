#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED
//
// state.hpp
//
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <ostream>
#include <string_view>

namespace castlecrawl
{
    struct Context;

    enum class State
    {
        Init,
        Splash,
        Play,
        Inventory,
        Fight,
        Treasure,
        Quit,
        Death,
        Credits,
        Editor,
        Cast,
        LevelUp,
        Statistics,
        Look,
        TextPopup
    };

    constexpr std::string_view toString(const State t_state) noexcept
    {
        switch (t_state)
        {
                // clang-format off
            case State::Init:       { return "Init"; }
            case State::Splash:     { return "Splash"; }
            case State::Play:       { return "Play"; }
            case State::Inventory:  { return "Inventory"; }
            case State::Fight:      { return "Fight"; }
            case State::Treasure:   { return "Treasure"; }
            case State::Quit:       { return "Quit"; }
            case State::Death:      { return "Death"; }
            case State::Credits:    { return "Credits"; }
            case State::Editor:     { return "Editor"; }
            case State::Cast:       { return "Cast"; }
            case State::LevelUp:    { return "LevelUp"; }
            case State::Statistics: { return "Statistics"; }
            case State::Look:       { return "Look"; }
            case State::TextPopup:  { return "TextPopup"; }
            default:                { return "unknown_state_error"; }
                // clang-format on
        }
    }

    inline std::ostream & operator<<(std::ostream & t_os, const State t_state)
    {
        t_os << toString(t_state);
        return t_os;
    }

    struct IState
    {
        virtual ~IState() {}

        [[nodiscard]] virtual State which() const = 0;

        virtual void onEnter(const Context & t_context)                          = 0;
        virtual void onExit(const Context & t_context)                           = 0;
        virtual void update(const Context & t_context, const float t_elapsedSec) = 0;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const = 0;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) = 0;
    };

    class StateBase : public IState
    {
      public:
        StateBase() {}
        virtual ~StateBase() override {}

        virtual void onEnter(const Context &) override {}
        virtual void onExit(const Context &) override {}
        virtual void update(const Context &, const float) override {}
        virtual void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const override {}
        virtual void handleEvent(const Context &, const sf::Event &) override {}
    };

    class StateInit : public StateBase
    {
      public:
        StateInit() {}
        virtual ~StateInit() final {}
        virtual State which() const final { return State::Init; }
    };

    class StateQuit : public StateBase
    {
      public:
        StateQuit() {}
        virtual ~StateQuit() final {}
        virtual State which() const final { return State::Quit; }
    };

} // namespace castlecrawl

#endif // STATE_HPP_INCLUDED
