#ifndef STATE_CAST_HPP_INCLUDED
#define STATE_CAST_HPP_INCLUDED
//
// state-cast.hpp
//
#include "state.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>

namespace castlecrawl
{
    struct Context;

    //

    struct SpellCategoryRectangle
    {
        SpellCategoryRectangle(
            const Context & t_context,
            const std::string & t_name,
            const sf::Color & t_color,
            const sf::FloatRect & t_screenRegion);

        void setFocus(const bool t_hasFocus);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

        sf::Text text;
        sf::Color color;
        sf::RectangleShape rectangle;
        bool has_focus;
    };

    //

    class StateCast : public StateBase
    {
      public:
        StateCast();
        virtual ~StateCast() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::Cast; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        sf::RectangleShape m_bgFadeRectangle;
        sf::Text m_titleText;
        std::unique_ptr<SpellCategoryRectangle> m_fireRectangleUPtr;
    };

} // namespace castlecrawl

#endif // STATE_CAST_HPP_INCLUDED