#ifndef STATETREASURE_HPP_INCLUDED
#define STATETREASURE_HPP_INCLUDED
//
// state-treasure.hpp
//
#include "state.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
{
    struct Context;

    class StateTreasure : public StateBase
    {
      public:
        StateTreasure();
        virtual ~StateTreasure() final {}

        virtual void onEnter(const Context & context) final;
        virtual State which() const final { return State::Fight; }
        virtual void update(const Context & context, const float frameTimeSec) final;

        virtual void draw(
            const Context & context,
            sf::RenderTarget & target,
            sf::RenderStates states) const final;

        virtual void handleEvent(const Context & context, const sf::Event & event) final;

      private:
        sf::RectangleShape m_fadeRectangle;
    };

} // namespace castlecrawl

#endif // STATETREASURE_HPP_INCLUDED
