#ifndef STATEDEATH_HPP_INCLUDED
#define STATEDEATH_HPP_INCLUDED
//
// state-death.hpp
//
#include "state.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>

namespace castlecrawl
{
    struct Context;

    class StateDeath : public StateBase
    {
      public:
        StateDeath();
        virtual ~StateDeath() final {}

        virtual void onEnter(const Context & context) final;
        virtual State which() const final { return State::Death; }
        virtual void update(const Context & context, const float frameTimeSec) final;

        virtual void draw(
            const Context & context,
            sf::RenderTarget & target,
            sf::RenderStates states) const final;

        virtual void handleEvent(const Context & context, const sf::Event & event) final;

      private:
        sf::RectangleShape m_fadeRedRectangle;
        sf::RectangleShape m_fadeBlackRectangle;
        sf::Text m_titleText;
    };

} // namespace castlecrawl

#endif // STATEDEATH_HPP_INCLUDED
