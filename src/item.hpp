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
        Item(const Weapon weapon, const WeaponMaterial material);

        // magical weapon constructor
        Item(
            const Weapon weapon,
            const WeaponMaterial material,
            const std::string & uniqueName,
            const EquipEffect & effect);

        // normal armor constructor
        Item(const Armor armor, const ArmorMaterial material);

        // magical armor constructor
        Item(
            const Armor armor,
            const ArmorMaterial material,
            const std::string & uniqueName,
            const EquipEffect & effect);

        // misc item constructor (all misc items are magical)
        Item(
            const Misc misc,
            const MiscMaterial material,
            const UseStrength strength,
            const UseEffect & useEffect,
            const EquipEffect & equipEffect);

        const std::string name() const { return m_fullName; }

        Weapon weaponType() const { return m_weapon; }
        Armor armorType() const { return m_armor; }
        Misc miscType() const { return m_misc; }

        Armor_t armorRating() const { return m_armorRating; }
        int damageMin() const { return m_damageMin; }
        int damageMax() const { return m_damageMax; }
        int value() const { return m_value; }

        ArmorMaterial armorMaterial() const { return m_armorMaterial; }
        WeaponMaterial weaponMaterial() const { return m_weaponMaterial; }
        MiscMaterial miscMaterial() const { return m_miscMaterial; }

        // these three are mutually exclusive but one must return true
        bool isWeapon() const { return (m_weapon != Weapon::Count); }
        bool isArmor() const { return (m_armor != Armor::Count); }
        bool isMisc() const { return ((m_misc != Misc::Count)); }

        bool isUseable() const { return isMiscUseable(m_misc); }
        std::size_t equipCount() const { return miscEquipCount(m_misc); }
        bool isEquipable() const { return isMiscEquipable(m_misc); }

        const UseEffect & useEffect() const { return m_useEffect; }
        const EquipEffect & equipEffect() const { return m_equipEffect; }

        bool isMagical() const { return (!m_useEffect.empty() || !m_equipEffect.empty()); }

        const std::string description() const { return m_description; }

        auto operator<=>(const Item &) const = default;
        friend std::ostream & operator<<(std::ostream & os, const Item & item);

      private:
        int calcValue() const;
        const std::string makeFullName() const;
        const std::string makeDescription() const;
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

    std::ostream & operator<<(std::ostream & os, const Item & item);

    inline const std::string toString(const item::Item & item) { return item.name(); }

    //

    struct Treasure
    {
        int gold = 0;
        ItemVec_t items;

        bool empty() const { return ((0 == gold) && items.empty()); }
        const std::string description() const;
    };

} // namespace castlecrawl::item

#endif // ITEM_HPP_INCLUDED
