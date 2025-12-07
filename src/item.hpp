#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED
//
// item.hpp
//
#include "item-enums.hpp"
#include "strong-types.hpp"

#include <ostream>
#include <string>
#include <vector>

namespace castlecrawl::item
{

    class Item
    {
      public:
        // the default constructor makes an invalid item
        Item();

        // normal weapon constructor
        Item(const Weapon t_weapon, const WeaponMaterial t_material);

        // magical weapon constructor
        Item(
            const Weapon t_weapon,
            const WeaponMaterial t_material,
            const std::string & t_uniqueName,
            const EquipEffect & t_effect);

        // normal armor constructor
        Item(const Armor t_armor, const ArmorMaterial t_material);

        // magical armor constructor
        Item(
            const Armor t_armor,
            const ArmorMaterial t_material,
            const std::string & t_uniqueName,
            const EquipEffect & t_effect);

        // misc item constructor
        Item(
            const Misc t_misc,
            const MiscMaterial t_material,
            const UseStrength t_strength = UseStrength::Normal,
            const UseEffect & t_useEffect = {},
            const EquipEffect & t_equipEffect = {});

        [[nodiscard]] inline const std::string name() const noexcept { return m_fullName; }

        [[nodiscard]] constexpr Weapon weaponType() const noexcept { return m_weapon; }
        [[nodiscard]] constexpr Armor armorType() const noexcept { return m_armor; }
        [[nodiscard]] constexpr Misc miscType() const noexcept { return m_misc; }

        [[nodiscard]] inline const Armor_t armorRating() const noexcept { return m_armorRating; }
        [[nodiscard]] constexpr int damageMin() const noexcept { return m_damageMin; }
        [[nodiscard]] constexpr int damageMax() const noexcept { return m_damageMax; }
        [[nodiscard]] constexpr int value() const noexcept { return m_value; }

        [[nodiscard]] constexpr ArmorMaterial armorMaterial() const noexcept
        {
            return m_armorMaterial;
        }

        [[nodiscard]] constexpr WeaponMaterial weaponMaterial() const noexcept
        {
            return m_weaponMaterial;
        }

        [[nodiscard]] constexpr MiscMaterial miscMaterial() const noexcept
        {
            return m_miscMaterial;
        }

        // these three are mutually exclusive but one of them must return true
        [[nodiscard]] constexpr bool isWeapon() const noexcept
        {
            return (m_weapon != Weapon::Count);
        }
        [[nodiscard]] constexpr bool isArmor() const noexcept { return (m_armor != Armor::Count); }
        [[nodiscard]] constexpr bool isMisc() const noexcept { return ((m_misc != Misc::Count)); }

        [[nodiscard]] constexpr bool isUseable() const noexcept { return isMiscUseable(m_misc); }

        [[nodiscard]] constexpr std::size_t equipCount() const noexcept
        {
            return miscEquipCount(m_misc);
        }

        [[nodiscard]] constexpr bool isEquipable() const noexcept
        {
            return isMiscEquipable(m_misc);
        }

        [[nodiscard]] inline const UseEffect useEffect() const noexcept { return m_useEffect; }

        [[nodiscard]] inline const EquipEffect equipEffect() const noexcept
        {
            return m_equipEffect;
        }

        [[nodiscard]] constexpr bool isMagical() const noexcept
        {
            return (!m_useEffect.empty() || !m_equipEffect.empty());
        }

        [[nodiscard]] inline const std::string description() const noexcept
        {
            return m_description;
        }

        auto operator<=>(const Item &) const = default;
        friend std::ostream & operator<<(std::ostream & t_os, const Item & t_item);

      private:
        [[nodiscard]] int calcValue() const;
        [[nodiscard]] const std::string makeFullName() const;
        [[nodiscard]] const std::string makeDescription() const;
        void setup();

      private:
        std::string m_baseName; // must be kept unique among all items
        std::string m_fullName; // always includes m_baseName so it will also always be unique
        std::string m_description;

        Weapon m_weapon;
        Armor m_armor;
        Misc m_misc;

        ArmorMaterial m_armorMaterial;
        WeaponMaterial m_weaponMaterial;
        MiscMaterial m_miscMaterial;

        UseStrength m_useStrength;
        Armor_t m_armorRating;

        int m_value;
        int m_damageMin;
        int m_damageMax;

        UseEffect m_useEffect;
        EquipEffect m_equipEffect;
    };

    using ItemVec_t = std::vector<Item>;

    std::ostream & operator<<(std::ostream & t_os, const Item & t_item);

    [[nodiscard]] inline std::string toString(const item::Item & t_item) { return t_item.name(); }

    //

    struct Treasure
    {
        int gold{ 0 };
        ItemVec_t items;

        [[nodiscard]] constexpr bool empty() const noexcept { return ((0 == gold) && items.empty()); }
        [[nodiscard]] const std::string description() const;
    };

} // namespace castlecrawl::item

#endif // ITEM_HPP_INCLUDED
