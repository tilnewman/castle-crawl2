#ifndef STATETREASURE_HPP_INCLUDED
#define STATETREASURE_HPP_INCLUDED
//
// state-treasure.hpp
//
#include "gui-listbox.hpp"
#include "item.hpp"
#include "state.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include <memory>

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

        static void setTreasure(const item::Treasure & treasure) { m_treasure = treasure; }

      private:
        void updateItemDescText(const Context & context);

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
