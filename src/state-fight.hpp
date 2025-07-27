#ifndef STATEFIGHT_HPP_INCLUDED
#define STATEFIGHT_HPP_INCLUDED
//
// state-fight.hpp
//
#include "direction-select-display.hpp"
#include "state.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
{
    struct Context;

    //

    class StateFight : public StateBase
    {
      public:
        StateFight();
        virtual ~StateFight() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::Fight; }
        virtual void update(const Context & t_context, const float t_frameTimeSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        void handleSelectDirection(const Context & t_context, const sf::Keyboard::Scancode t_key);
        void fight(const Context & t_context, const MapPos_t & t_pos);

      private:
        bool m_isDirectionSelected;
        DirectionSelectDisplay m_directionSelectDisplay;
    };

} // namespace castlecrawl

#endif // STATEFIGHT_HPP_INCLUDED
