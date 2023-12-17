#ifndef STATEINVENTORY_HPP_INCLUDED
#define STATEINVENTORY_HPP_INCLUDED
//
// state-inventory.hpp
//
#include "gui-listbox.hpp"
#include "item.hpp"
#include "state.hpp"

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

namespace castlecrawl
{
    struct Context;

    class StateInventory : public StateBase
    {
      public:
        StateInventory();

        virtual State which() const final { return State::Inventory; }
        virtual void onEnter(const Context &) final;
        virtual void update(const Context &, const float) final;
        virtual void draw(const Context &, sf::RenderTarget &, sf::RenderStates) const final;
        virtual void handleEvent(const Context &, const sf::Event &) final;

      private:
        void updateItemDescText(const Context & context);

      private:
        sf::RectangleShape m_fadeRectangle;
        std::unique_ptr<Listbox<item::Item>> m_unListboxUPtr;
        std::unique_ptr<Listbox<item::Item>> m_eqListboxUPtr;
        sf::Text m_itemDescText;
    };

} // namespace castlecrawl

#endif // STATEINVENTORY_HPP_INCLUDED
