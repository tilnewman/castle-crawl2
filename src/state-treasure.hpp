#ifndef STATETREASURE_HPP_INCLUDED
#define STATETREASURE_HPP_INCLUDED
//
// state-treasure.hpp
//
#include "gui-listbox.hpp"
#include "state.hpp"
#include "treasure.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace castlecrawl
{
    struct Context;

    class StateTreasure : public StateBase
    {
      public:
        StateTreasure();
        virtual ~StateTreasure() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::Treasure; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

        static void setTreasure(const item::Treasure & t_treasure) { m_treasure = t_treasure; }

      private:
        void updateItemDescText(const Context & t_context);

      private:
        static item::Treasure m_treasure;
        sf::RectangleShape m_fadeRectangle;
        std::unique_ptr<Listbox> m_itemListboxUPtr;
        sf::Text m_titleText;
        sf::Text m_descText;
        sf::Text m_itemDescText;
        sf::Text m_helpText;
    };

} // namespace castlecrawl

#endif // STATETREASURE_HPP_INCLUDED
