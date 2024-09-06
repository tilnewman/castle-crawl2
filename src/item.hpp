#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED
//
// item.hpp
//
#include "item-enums.hpp"
#include "strong-types.hpp"

#include <compare>
#include <iosfwd>
#include <string>
#include <tuple>
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

        // misc item constructor (all misc items are magical)
        Item(
            const Misc t_misc,
            const MiscMaterial t_material,
            const UseStrength t_strength,
            const UseEffect & t_useEffect,
            const EquipEffect & t_equipEffect);

        [[nodiscard]] inline std::string name() const { return m_fullName; }

        [[nodiscard]] inline Weapon weaponType() const { return m_weapon; }
        [[nodiscard]] inline Armor armorType() const { return m_armor; }
        [[nodiscard]] inline Misc miscType() const { return m_misc; }

        [[nodiscard]] inline Armor_t armorRating() const { return m_armorRating; }
        [[nodiscard]] inline int damageMin() const { return m_damageMin; }
        [[nodiscard]] inline int damageMax() const { return m_damageMax; }
        [[nodiscard]] inline int value() const { return m_value; }

        [[nodiscard]] inline ArmorMaterial armorMaterial() const { return m_armorMaterial; }
        [[nodiscard]] inline WeaponMaterial weaponMaterial() const { return m_weaponMaterial; }
        [[nodiscard]] inline MiscMaterial miscMaterial() const { return m_miscMaterial; }

        // these three are mutually exclusive but one of them must return true
        [[nodiscard]] inline bool isWeapon() const { return (m_weapon != Weapon::Count); }
        [[nodiscard]] inline bool isArmor() const { return (m_armor != Armor::Count); }
        [[nodiscard]] inline bool isMisc() const { return ((m_misc != Misc::Count)); }

        [[nodiscard]] inline bool isUseable() const { return isMiscUseable(m_misc); }
        [[nodiscard]] inline std::size_t equipCount() const { return miscEquipCount(m_misc); }
        [[nodiscard]] inline bool isEquipable() const { return isMiscEquipable(m_misc); }

        [[nodiscard]] inline UseEffect useEffect() const { return m_useEffect; }
        [[nodiscard]] inline EquipEffect equipEffect() const { return m_equipEffect; }

        [[nodiscard]] inline bool isMagical() const
        {
            return (!m_useEffect.empty() || !m_equipEffect.empty());
        }

        [[nodiscard]] inline std::string description() const { return m_description; }

        auto operator<=>(const Item &) const = default;
        friend std::ostream & operator<<(std::ostream & t_os, const Item & t_item);

      private:
        [[nodiscard]] int calcValue() const;
        [[nodiscard]] std::string makeFullName() const;
        [[nodiscard]] std::string makeDescription() const;
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

        [[nodiscard]] inline bool empty() const { return ((0 == gold) && items.empty()); }
        std::string description() const;
    };

} // namespace castlecrawl::item

#endif // ITEM_HPP_INCLUDED
