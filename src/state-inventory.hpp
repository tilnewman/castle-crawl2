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

        [[nodiscard]] virtual State which() const final { return State::Inventory; }
        virtual void onEnter(const Context & t_context) final;
        virtual void update(const Context & t_context, const float t_frameTimeSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        void updateItemDescText(const Context & t_context);
        void updateStatText(const Context & t_context);
        void updateEquipHintText(const Context & t_context);

        [[nodiscard]] const std::string
            equipHintMessage(const Context & t_context, const item::Item & t_unEquipItem) const;

      private:
        sf::RectangleShape m_fadeRectangle;
        sf::Text m_unTitleText;
        std::unique_ptr<Listbox> m_unListboxUPtr;
        sf::Text m_eqTitleText;
        std::unique_ptr<Listbox> m_eqListboxUPtr;
       
        sf::Text m_itemDescText;
        sf::Text m_itemHintText;

        sf::Text m_errorText;
        float m_errorTextElapsedSec;

        sf::Text m_strTitleText;
        sf::Text m_dexTitleText;
        sf::Text m_accTitleText;
        sf::Text m_lckTitleText;
        sf::Text m_arcTitleText;
        //
        sf::Text m_strValueText;
        sf::Text m_dexValueText;
        sf::Text m_accValueText;
        sf::Text m_lckValueText;
        sf::Text m_arcValueText;
        //
        sf::Text m_goldText;
        sf::Text m_armorText;
        //
        sf::RectangleShape m_statRectangle;
    };

} // namespace castlecrawl

#endif // STATEINVENTORY_HPP_INCLUDED
