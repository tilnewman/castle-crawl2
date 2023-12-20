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

    class StateFight : public StateBase
    {
      public:
        StateFight();
        virtual ~StateFight() final {}

        virtual void onEnter(const Context & context) final;
        virtual State which() const final { return State::Fight; }
        virtual void update(const Context & context, const float frameTimeSec) final;

        virtual void draw(
            const Context & context,
            sf::RenderTarget & target,
            sf::RenderStates states) const final;

        virtual void handleEvent(const Context & context, const sf::Event & event) final;

      private:
        void handleSelectDirection(const Context & context, const sf::Keyboard::Key key);
        void fight(const Context & context, const MapPos_t & pos);

      private:
        bool m_isDirectionSelected;
        DirectionSelectDisplay m_directionSelectDisplay;
    };

} // namespace castlecrawl

#endif // STATEFIGHT_HPP_INCLUDED
