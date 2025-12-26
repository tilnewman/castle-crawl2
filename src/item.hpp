#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED
//
// item.hpp
//
#include "item-enums.hpp"
#include "json-wrapper.hpp"
#include "strong-types.hpp"

#include <optional>
#include <ostream>
#include <string>
#include <vector>

namespace castlecrawl::item
{

    class Item
    {
      public:
        // the default constructor makes an invalid item and is needed by json
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
            const UseStrength t_strength      = UseStrength::Normal,
            const UseEffect & t_useEffect     = {},
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

        friend void to_json(nlohmann::json & j, const Item & i);
        friend void from_json(const nlohmann::json & j, Item & i);

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
    using ItemOpt_t = std::optional<Item>;

    std::ostream & operator<<(std::ostream & t_os, const Item & t_item);

    [[nodiscard]] inline std::string toString(const item::Item & t_item) { return t_item.name(); }

    inline void to_json(nlohmann::json & j, const Item & i)
    {
        j = nlohmann::json{ { "baseName", i.m_baseName },
                            { "fullName", i.m_fullName },
                            { "description", i.m_description },
                            { "weapon", i.m_weapon },
                            { "armor", i.m_armor },
                            { "misc", i.m_misc },
                            { "armorMaterial", i.m_armorMaterial },
                            { "weaponMaterial", i.m_weaponMaterial },
                            { "miscMaterial", i.m_miscMaterial },
                            { "useStrength", i.m_useStrength },
                            { "armorRating", i.m_armorRating },
                            { "value", i.m_value },
                            { "damageMin", i.m_damageMin },
                            { "damageMax", i.m_damageMax },
                            { "useEffect", i.m_useEffect },
                            { "equipEffect", i.m_equipEffect } };
    }

    inline void from_json(const nlohmann::json & j, Item & i)
    {
        j.at("baseName").get_to(i.m_baseName);
        j.at("fullName").get_to(i.m_fullName);
        j.at("description").get_to(i.m_description);
        j.at("weapon").get_to(i.m_weapon);
        j.at("armor").get_to(i.m_armor);
        j.at("misc").get_to(i.m_misc);
        j.at("armorMaterial").get_to(i.m_armorMaterial);
        j.at("weaponMaterial").get_to(i.m_weaponMaterial);
        j.at("miscMaterial").get_to(i.m_miscMaterial);
        j.at("useStrength").get_to(i.m_useStrength);
        j.at("armorRating").get_to(i.m_armorRating);
        j.at("value").get_to(i.m_value);
        j.at("damageMin").get_to(i.m_damageMin);
        j.at("damageMax").get_to(i.m_damageMax);
        j.at("useEffect").get_to(i.m_useEffect);
        j.at("equipEffect").get_to(i.m_equipEffect);
    }

} // namespace castlecrawl::item

#endif // ITEM_HPP_INCLUDED
