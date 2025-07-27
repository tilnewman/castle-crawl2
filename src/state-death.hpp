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

namespace castlecrawl
{
    struct Context;

    class StateDeath : public StateBase
    {
      public:
        StateDeath();
        virtual ~StateDeath() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::Death; }
        virtual void update(const Context & t_context, const float t_frameTimeSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        sf::RectangleShape m_fadeRedRectangle;
        sf::RectangleShape m_fadeBlackRectangle;
        sf::Text m_titleText;
        float m_fadeRedTimeSec;
        float m_fadeBlackTimeSec;
    };

} // namespace castlecrawl

#endif // STATEDEATH_HPP_INCLUDED
