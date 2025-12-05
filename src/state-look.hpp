#ifndef STATE_LOOK_HPP_INCLUDED
#define STATE_LOOK_HPP_INCLUDED
//
// state-look.hpp
//
#include "direction-select-display.hpp"
#include "map-types.hpp"
#include "state.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace castlecrawl
{
    struct Context;

    //

    class StateLook : public StateBase
    {
      public:
        StateLook();
        virtual ~StateLook() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::Look; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        void handleSelectDirection(const Context & t_context, const sf::Keyboard::Scancode t_key);
        void look(const Context & t_context, const MapPos_t & t_pos);

      private:
        bool m_isDirectionSelected;
        DirectionSelectDisplay m_directionSelectDisplay;
    };

} // namespace castlecrawl

#endif // STATE_LOOK_HPP_INCLUDED
