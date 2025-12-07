#ifndef STATE_LOOK_EVENT_HPP_INCLUDED
#define STATE_LOOK_EVENT_HPP_INCLUDED
//
// state-look-event.hpp
//
#include "look-event.hpp"
#include "state.hpp"
#include "text-layout.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace castlecrawl
{
    struct Context;

    //

    class StateLookEvent : public StateBase
    {
      public:
        StateLookEvent();
        virtual ~StateLookEvent() final {}

        virtual void onEnter(const Context & t_context) final;
        virtual void onExit(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::LookEvent; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

        static void setEvent(const LookEvent & t_lookEvent) { m_lookEvent = t_lookEvent; }

      private:
        static inline LookEvent m_lookEvent{};

        sf::RectangleShape m_backgroundRectangle;
        TextLayoutPack m_textLayout;
    };

} // namespace castlecrawl

#endif // STATE_LOOK_EVENT_HPP_INCLUDED
