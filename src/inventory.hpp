#ifndef INVENTORY_HPP_INCLUDED
#define INVENTORY_HPP_INCLUDED
//
// inventory.hpp
//
#include "item.hpp"

#include <optional>
#include <string>
#include <vector>

namespace castlecrawl::item
{

    class Inventory
    {
      public:
        Inventory();

        inline void add(const Item & t_item) { m_items.push_back(t_item); }
        void add(const ItemVec_t & t_items);
        void remove(const std::size_t t_index);

        // returns an error message if fails
        const std::string equip(const std::size_t t_index);

        void unequip(const std::size_t t_index);

        [[nodiscard]] inline const ItemVec_t & unItems() const noexcept { return m_items; }
        [[nodiscard]] inline const ItemVec_t & eqItems() const noexcept { return m_eqItems; }

        [[nodiscard]] const EquipEffect totalEquipEffects() const;
        [[nodiscard]] const Armor_t armorRating() const;
        [[nodiscard]] bool hasWeaponEquipped() const;
        [[nodiscard]] std::optional<Item> weaponEquipped() const;

      private:
        [[nodiscard]] bool hasEquipped(const Armor armor) const;
        [[nodiscard]] std::size_t countOfEquipped(const Misc misc) const;

      private:
        ItemVec_t m_items;
        ItemVec_t m_eqItems;
    };

} // namespace castlecrawl::item

#endif // INVENTORY_HPP_INCLUDED
