#ifndef STATE_STATISTICS_HPP_INCLUDED
#define STATE_STATISTICS_HPP_INCLUDED
//
// state-statistics.hpp
//
#include "state.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <string>
#include <vector>

namespace castlecrawl
{
    struct Context;

    //

    class StatBlock
    {
      public:
        StatBlock(
            const Context & t_context,
            const std::string & t_name,
            const std::size_t t_value,
            const sf::FloatRect & t_rect);

        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

      private:
        sf::FloatRect m_rect;
        std::string m_name;
        sf::Text m_nameText;
        sf::Text m_valueText;
    };

    //

    class StateStatistics : public StateBase
    {
      public:
        StateStatistics();
        virtual ~StateStatistics() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::LevelUp; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        sf::RectangleShape m_bgFadeRectangle;
        sf::Text m_titleText;
        sf::Text m_subTitleText;
        std::vector<StatBlock> m_statBlocks;
    };

} // namespace castlecrawl

#endif // STATE_STATISTICS_HPP_INCLUDED