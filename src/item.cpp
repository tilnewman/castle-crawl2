// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// item.cpp
//
#include "item.hpp"

#include <ostream>

namespace castlecrawl::item
{

    const std::string Treasure::description() const
    {
        std::string str;
        str.reserve(200);

        str += "You find";

        if ((0 == gold) && items.empty())
        {
            str += " nothing.";
            return str;
        }

        if (gold > 0)
        {
            str += ' ';
            str += std::to_string(gold);
            str += " gold";
        }

        if (items.empty())
        {
            str += '.';
        }
        else
        {
            if (gold > 0)
            {
                str += " and";
            }

            str += ":\n";

            for (const Item & item : items)
            {
                str += "    ";
                str += item.name();
                str += '\n';
            }
        }

        return str;
    }

    //

    Item::Item()
        : m_baseName{}
        , m_fullName{}
        , m_description{}
        , m_weapon{ Weapon::Count }
        , m_armor{ Armor::Count }
        , m_misc{ Misc::Count }
        , m_armorMaterial{ ArmorMaterial::Count }
        , m_weaponMaterial{ WeaponMaterial::Count }
        , m_miscMaterial{ MiscMaterial::Count }
        , m_useStrength{ UseStrength::Normal }
        , m_armorRating{ 0 }
        , m_value{ 0 }
        , m_damageMin{ 0 }
        , m_damageMax{ 0 }
        , m_useEffect{}
        , m_equipEffect{}
    {
        setup();
    }

    Item::Item(const Weapon t_weapon, const WeaponMaterial t_material)
        : m_baseName{ toString(t_weapon) }
        , m_fullName{}
        , m_description{}
        , m_weapon{ t_weapon }
        , m_armor{ Armor::Count }
        , m_misc{ Misc::Count }
        , m_armorMaterial{ ArmorMaterial::Count }
        , m_weaponMaterial{ t_material }
        , m_miscMaterial{ MiscMaterial::Count }
        , m_useStrength{ UseStrength::Normal }
        , m_armorRating{ 0 }
        , m_value{ 0 }
        , m_damageMin{ baseWeaponDamage(t_weapon).x + weaponMaterialDamage(t_material) }
        , m_damageMax{ baseWeaponDamage(t_weapon).y + weaponMaterialDamage(t_material) }
        , m_useEffect{}
        , m_equipEffect{}
    {
        setup();
    }

    Item::Item(
        const Weapon t_weapon,
        const WeaponMaterial t_material,
        const std::string & t_uniqueName,
        const EquipEffect & t_effect)
        : m_baseName{ t_uniqueName }
        , m_fullName{}
        , m_description{}
        , m_weapon{ t_weapon }
        , m_armor{ Armor::Count }
        , m_misc{ Misc::Count }
        , m_armorMaterial{ ArmorMaterial::Count }
        , m_weaponMaterial{ t_material }
        , m_miscMaterial{ MiscMaterial::Count }
        , m_useStrength{ UseStrength::Normal }
        , m_armorRating{ 0 }
        , m_value{ 0 }
        , m_damageMin{ baseWeaponDamage(t_weapon).x + weaponMaterialDamage(t_material) }
        , m_damageMax{ baseWeaponDamage(t_weapon).y + weaponMaterialDamage(t_material) }
        , m_useEffect{}
        , m_equipEffect{ t_effect }
    {
        setup();
    }

    Item::Item(const Armor t_armor, const ArmorMaterial t_material)
        : m_baseName{ toString(t_armor) }
        , m_fullName{}
        , m_description{}
        , m_weapon{ Weapon::Count }
        , m_armor{ t_armor }
        , m_misc{ Misc::Count }
        , m_armorMaterial{ t_material }
        , m_weaponMaterial{ WeaponMaterial::Count }
        , m_miscMaterial{ MiscMaterial::Count }
        , m_useStrength{ UseStrength::Normal }
        , m_armorRating{ baseArmorRating(t_armor) + armorMaterialRating(t_material) }
        , m_value{ 0 }
        , m_damageMin{ 0 }
        , m_damageMax{ 0 }
        , m_useEffect{}
        , m_equipEffect{}
    {
        setup();
    }

    Item::Item(
        const Armor t_armor,
        const ArmorMaterial t_material,
        const std::string & t_uniqueName,
        const EquipEffect & t_effect)
        : m_baseName{ t_uniqueName }
        , m_fullName{}
        , m_description{}
        , m_weapon{ Weapon::Count }
        , m_armor{ t_armor }
        , m_misc{ Misc::Count }
        , m_armorMaterial{ t_material }
        , m_weaponMaterial{ WeaponMaterial::Count }
        , m_miscMaterial{ MiscMaterial::Count }
        , m_useStrength{ UseStrength::Normal }
        , m_armorRating{ baseArmorRating(t_armor) + armorMaterialRating(t_material) }
        , m_value{ 0 }
        , m_damageMin{ 0 }
        , m_damageMax{ 0 }
        , m_useEffect{}
        , m_equipEffect{ t_effect }
    {
        setup();
    }

    Item::Item(
        const Misc t_misc,
        const MiscMaterial t_material,
        const UseStrength t_strength,
        const UseEffect & t_useEffect,
        const EquipEffect & t_equipEffect)
        : m_baseName{ toString(t_misc) }
        , m_fullName{}
        , m_description{}
        , m_weapon{ Weapon::Count }
        , m_armor{ Armor::Count }
        , m_misc{ t_misc }
        , m_armorMaterial{ ArmorMaterial::Count }
        , m_weaponMaterial{ WeaponMaterial::Count }
        , m_miscMaterial{ t_material }
        , m_useStrength{ t_strength }
        , m_armorRating{ 0 }
        , m_value{ 0 }
        , m_damageMin{ 0 }
        , m_damageMax{ 0 }
        , m_useEffect{ t_useEffect }
        , m_equipEffect{ t_equipEffect }
    {
        setup();
    }

    void Item::setup()
    {
        m_value       = calcValue();
        m_fullName    = makeFullName();
        m_description = makeDescription();
    }

    const std::string Item::makeFullName() const
    {
        std::string str;
        str.reserve(32); // longest is 25 as of 2024-7-28

        if (isArmor())
        {
            if (!isMagical())
            {
                str += toString(m_armorMaterial);
                str += ' ';
            }
        }
        else if (isWeapon())
        {
            if (!isMagical())
            {
                str += toString(m_weaponMaterial);
                str += ' ';
            }
        }
        else if (isMisc())
        {
            if (isUseable() && (m_useStrength != UseStrength::Normal))
            {
                str += toString(m_useStrength);
                str += ' ';
            }

            if (isUseable())
            {
                if (m_useEffect.health > 0)
                {
                    str += "Healing ";
                }
                else if (m_useEffect.mana > 0)
                {
                    str += "Mana ";
                }
            }

            str += toString(m_miscMaterial);
            str += ' ';
        }

        str += m_baseName;
        return str;
    }

    const std::string Item::makeDescription() const
    {
        std::string str;

        if (m_baseName.empty())
        {
            return str;
        }

        str.reserve(256); // longest is 104 as of 2024-7-28

        str += name();
        str += " is";

        if (isWeapon())
        {
            str += " a";

            if (isMagical())
            {
                str += " magical";
            }

            str += " weapon that does between ";
            str += std::to_string(m_damageMin);
            str += " and ";
            str += std::to_string(m_damageMax);
            str += " damage";
        }
        else if (isArmor())
        {
            if (isMagical())
            {
                str += " magical";
            }

            str += " armor that has a rating of ";
            str += std::to_string(m_armorRating.get());
        }
        else if (isMisc())
        {
            str += " a";

            if (isMagical())
            {
                str += " magical";
            }

            str += " item";

            if (isUseable())
            {
                str += " that is useable";
            }

            const auto eqCount = equipCount();
            if (eqCount > 0)
            {
                str += " that you can equip";

                if (eqCount > 1)
                {
                    str += ' ';
                    str += std::to_string(eqCount);
                    str += " of";
                }
            }
        }

        if (!m_equipEffect.empty())
        {
            str += " and grants ";

            const EquipEffect & ef = m_equipEffect;

            // clang-format off
            if (ef.acc > 0) { str += "+" + std::to_string(ef.acc) + "acc, "; }
            if (ef.arc > 0) { str += "+" + std::to_string(ef.arc) + "arc, "; }
            if (ef.dex > 0) { str += "+" + std::to_string(ef.dex) + "dex, "; }
            if (ef.dmg > 0) { str += "+" + std::to_string(ef.dmg) + "dmg, "; }
            if (ef.lck > 0) { str += "+" + std::to_string(ef.lck) + "lck, "; }
            if (ef.str > 0) { str += "+" + std::to_string(ef.str) + "str, "; }
            // clang-format on

            str.pop_back();
            str.pop_back();
        }

        str += '.';
        return str;
    }

    // This equation full of magic numbers yeilds a good range of values over all items,
    // with the default item having a value of zero and higher values being more and more rare.
    // As of 2024-7-28: values range [5,9289] with 558 unique of 883, and std_dev of 1176.
    int Item::calcValue() const
    {
        int value = 0;

        value += ((m_armorRating * m_armorRating) * 5_armor).get();
        value += ((m_damageMin * m_damageMin) * 5);
        value += ((m_damageMax * m_damageMax) * 5);

        if (WeaponMaterial::Count != m_weaponMaterial)
        {
            value += static_cast<int>(m_weaponMaterial);
        }

        if (ArmorMaterial::Count != m_armorMaterial)
        {
            value += static_cast<int>(m_armorMaterial);
        }

        if (MiscMaterial::Count != m_miscMaterial)
        {
            value += static_cast<int>(m_miscMaterial);
        }

        value += miscBaseValue(m_misc);

        value += (m_equipEffect.total() * m_equipEffect.total());
        value += (m_equipEffect.total() * 250);

        value += ((m_useEffect.total() / 2) * m_useEffect.total());
        value += (m_useEffect.total() * 25);

        return value;
    }

    std::ostream & operator<<(std::ostream & t_os, const Item & t_item)
    {
        t_os << '[' << t_item.name();

        if (t_item.isArmor())
        {
            t_os << ",Armor";
        }

        if (t_item.isWeapon())
        {
            t_os << ",Weapon";
        }

        if (t_item.isMisc())
        {
            t_os << ",Misc";
        }

        if (t_item.armorRating() != 0_armor)
        {
            t_os << ",armorRating=" << t_item.armorRating();
        }

        if ((t_item.damageMin() != 0) || (t_item.damageMax() != 0))
        {
            t_os << ",damage=" << t_item.damageMin() << '-' << t_item.damageMax();
        }

        if (t_item.isUseable())
        {
            t_os << ",useable";
        }

        if (t_item.isMisc() && t_item.equipCount() > 0)
        {
            t_os << ",equipMax=" << t_item.equipCount();
        }

        const EquipEffect ef = t_item.equipEffect();
        const UseEffect uf   = t_item.useEffect();

        // clang-format off
        if (ef.acc > 0) { t_os << ",+" << ef.acc << "acc"; }
        if (ef.arc > 0) { t_os << ",+" << ef.arc << "arc"; }
        if (ef.dex > 0) { t_os << ",+" << ef.dex << "dex"; }
        if (ef.dmg > 0) { t_os << ",+" << ef.dmg << "dmg"; }
        if (ef.lck > 0) { t_os << ",+" << ef.lck << "lck"; }
        if (ef.str > 0) { t_os << ",+" << ef.str << "str"; }
        //
        if (uf.health > 0) { t_os << ",+" << uf.health << "health"; }
        if (uf.mana > 0)   { t_os << ",+" << uf.mana << "mana";     }
        // clang-format on

        t_os << ",value=" << t_item.value();

        t_os << ']';
        return t_os;
    }

} // namespace castlecrawl::item
