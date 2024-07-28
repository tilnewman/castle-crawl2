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
        : m_baseName()
        , m_fullName()
        , m_description()
        , m_weapon(Weapon::Count)
        , m_armor(Armor::Count)
        , m_misc(Misc::Count)
        , m_armorMaterial(ArmorMaterial::Count)
        , m_weaponMaterial(WeaponMaterial::Count)
        , m_miscMaterial(MiscMaterial::Count)
        , m_useStrength(UseStrength::Normal)
        , m_armorRating(0)
        , m_value(0)
        , m_damageMin(0)
        , m_damageMax(0)
        , m_useEffect()
        , m_equipEffect()
    {
        setup();
    }

    Item::Item(const Weapon weapon, const WeaponMaterial material)
        : m_baseName(toString(weapon))
        , m_fullName()
        , m_description()
        , m_weapon(weapon)
        , m_armor(Armor::Count)
        , m_misc(Misc::Count)
        , m_armorMaterial(ArmorMaterial::Count)
        , m_weaponMaterial(material)
        , m_miscMaterial(MiscMaterial::Count)
        , m_useStrength(UseStrength::Normal)
        , m_armorRating(0)
        , m_value(0)
        , m_damageMin(baseWeaponDamage(weapon).x + weaponMaterialDamage(material))
        , m_damageMax(baseWeaponDamage(weapon).y + weaponMaterialDamage(material))
        , m_useEffect()
        , m_equipEffect()
    {
        setup();
    }

    Item::Item(
        const Weapon weapon,
        const WeaponMaterial material,
        const std::string & uniqueName,
        const EquipEffect & effect)
        : m_baseName(uniqueName)
        , m_fullName()
        , m_description()
        , m_weapon(weapon)
        , m_armor(Armor::Count)
        , m_misc(Misc::Count)
        , m_armorMaterial(ArmorMaterial::Count)
        , m_weaponMaterial(material)
        , m_miscMaterial(MiscMaterial::Count)
        , m_useStrength(UseStrength::Normal)
        , m_armorRating(0)
        , m_value(0)
        , m_damageMin(baseWeaponDamage(weapon).x + weaponMaterialDamage(material))
        , m_damageMax(baseWeaponDamage(weapon).y + weaponMaterialDamage(material))
        , m_useEffect()
        , m_equipEffect(effect)
    {
        setup();
    }

    Item::Item(const Armor armor, const ArmorMaterial material)
        : m_baseName(toString(armor))
        , m_fullName()
        , m_description()
        , m_weapon(Weapon::Count)
        , m_armor(armor)
        , m_misc(Misc::Count)
        , m_armorMaterial(material)
        , m_weaponMaterial(WeaponMaterial::Count)
        , m_miscMaterial(MiscMaterial::Count)
        , m_useStrength(UseStrength::Normal)
        , m_armorRating(baseArmorRating(armor) + armorMaterialRating(material))
        , m_value(0)
        , m_damageMin(0)
        , m_damageMax(0)
        , m_useEffect()
        , m_equipEffect()
    {
        setup();
    }

    Item::Item(
        const Armor armor,
        const ArmorMaterial material,
        const std::string & uniqueName,
        const EquipEffect & effect)
        : m_baseName(uniqueName)
        , m_fullName()
        , m_description()
        , m_weapon(Weapon::Count)
        , m_armor(armor)
        , m_misc(Misc::Count)
        , m_armorMaterial(material)
        , m_weaponMaterial(WeaponMaterial::Count)
        , m_miscMaterial(MiscMaterial::Count)
        , m_useStrength(UseStrength::Normal)
        , m_armorRating(baseArmorRating(armor) + armorMaterialRating(material))
        , m_value(0)
        , m_damageMin(0)
        , m_damageMax(0)
        , m_useEffect()
        , m_equipEffect(effect)
    {
        setup();
    }

    Item::Item(
        const Misc misc,
        const MiscMaterial material,
        const UseStrength strength,
        const UseEffect & useEffect,
        const EquipEffect & equipEffect)
        : m_baseName(toString(misc))
        , m_fullName()
        , m_description()
        , m_weapon(Weapon::Count)
        , m_armor(Armor::Count)
        , m_misc(misc)
        , m_armorMaterial(ArmorMaterial::Count)
        , m_weaponMaterial(WeaponMaterial::Count)
        , m_miscMaterial(material)
        , m_useStrength(strength)
        , m_armorRating(0)
        , m_value(0)
        , m_damageMin(0)
        , m_damageMax(0)
        , m_useEffect(useEffect)
        , m_equipEffect(equipEffect)
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
        else // must be misc
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
                else
                {
                    str += "Mana ";
                }
            }
            else
            {
                str += toString(m_miscMaterial);
                str += ' ';
            }
        }

        str += m_baseName;
        return str;
    }

    const std::string Item::makeDescription() const
    {
        std::string str;
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
        else // must be a misc item
        {
            str += " a magical item";

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
    // As of 2024-7-28, the values range from 5 to 9289, with 558 unique values of 883 total.
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

    std::ostream & operator<<(std::ostream & os, const Item & item)
    {
        os << '[' << item.name();

        if (item.isArmor())
        {
            os << ",Armor";
        }

        if (item.isWeapon())
        {
            os << ",Weapon";
        }

        if (item.isMisc())
        {
            os << ",Misc";
        }

        if (item.armorRating() != 0_armor)
        {
            os << ",armorRating=" << item.armorRating();
        }

        if ((item.damageMin() != 0) || (item.damageMax() != 0))
        {
            os << ",damage=" << item.damageMin() << '-' << item.damageMax();
        }

        if (item.isUseable())
        {
            os << ",useable";
        }

        if (item.isMisc() && item.equipCount() > 0)
        {
            os << ",equipMax=" << item.equipCount();
        }

        const EquipEffect & ef = item.equipEffect();
        const UseEffect & uf   = item.useEffect();

        // clang-format off
        if (ef.acc > 0) { os << ",+" << ef.acc << "acc"; }
        if (ef.arc > 0) { os << ",+" << ef.arc << "arc"; }
        if (ef.dex > 0) { os << ",+" << ef.dex << "dex"; }
        if (ef.dmg > 0) { os << ",+" << ef.dmg << "dmg"; }
        if (ef.lck > 0) { os << ",+" << ef.lck << "lck"; }
        if (ef.str > 0) { os << ",+" << ef.str << "str"; }
        //
        if (uf.health > 0) { os << ",+" << uf.health << "health"; }
        if (uf.mana > 0)   { os << ",+" << uf.mana << "mana";     }
        // clang-format on

        os << ",value=" << item.value();

        os << ']';
        return os;
    }

} // namespace castlecrawl::item
