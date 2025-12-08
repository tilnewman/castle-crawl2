// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// inventory.cpp
//
#include "inventory.hpp"

#include "check-macros.hpp"

namespace castlecrawl::item
{
    Inventory::Inventory()
        : m_items{}
    {}

    void Inventory::add(const ItemVec_t & t_items)
    {
        for (const Item & item : t_items)
        {
            m_items.push_back(item);
        }
    }

    void Inventory::remove(const std::size_t t_index)
    {
        M_CHECK(
            t_index < m_items.size(), "Tried to remove(" << t_index << ") out of bounds index!");

        m_items.erase(std::begin(m_items) + static_cast<std::ptrdiff_t>(t_index));
    }

    const std::string Inventory::equip(const std::size_t t_index)
    {
        M_CHECK(t_index < m_items.size(), "Tried to equip(" << t_index << ") out of bounds index!");

        const Item & item = m_items[t_index];

        if (item.isWeapon() && hasWeaponEquipped())
        {
            return "Already has a weapon equipped.";
        }
        else if (item.isArmor())
        {
            if (hasEquipped(item.armorType()))
            {
                std::string str;
                str += "Already has ";
                str += toString(item.armorType());
                str += " equipped.";
                return str;
            }
        }
        else if (item.isMisc())
        {
            if (!isMiscEquipable(item.miscType()))
            {
                std::string str;
                str += toString(item.miscType());
                str += " can't be equipped.";
                return str;
            }

            const std::size_t count = miscEquipCount(item.miscType());
            if (countOfEquipped(item.miscType()) >= count)
            {
                std::string str;
                str += "Already has ";
                str += std::to_string(count);
                str += " equipped.";
                return str;
            }
        }

        m_eqItems.push_back(m_items[t_index]);
        m_items.erase(std::begin(m_items) + static_cast<std::ptrdiff_t>(t_index));
        return "";
    }

    void Inventory::unequip(const std::size_t t_index)
    {
        M_CHECK(
            t_index < m_eqItems.size(), "Tried to unequip(" << t_index << ") out of bounds index!");

        m_items.push_back(m_eqItems[t_index]);
        m_eqItems.erase(std::begin(m_eqItems) + static_cast<std::ptrdiff_t>(t_index));
    }

    const EquipEffect Inventory::totalEquipEffects() const
    {
        EquipEffect equipEffect;

        for (const Item & item : m_eqItems)
        {
            equipEffect += item.equipEffect();
        }

        return equipEffect;
    }

    const Armor_t Inventory::armorRating() const
    {
        Armor_t armorRating{ 0_armor };

        for (const Item & item : m_eqItems)
        {
            if (item.isArmor())
            {
                armorRating += item.armorRating();
            }
        }

        return armorRating;
    }

    bool Inventory::hasWeaponEquipped() const
    {
        for (const Item & item : m_eqItems)
        {
            if (item.isWeapon())
            {
                return true;
            }
        }

        return false;
    }

    ItemOpt_t Inventory::weaponEquipped() const
    {
        for (const Item & item : m_eqItems)
        {
            if (item.isWeapon())
            {
                return { item };
            }
        }

        return {};
    }

    bool Inventory::contains(const std::string & t_name) const
    {
        for (const Item & item : m_items)
        {
            if (item.name() == t_name)
            {
                return true;
            }
        }

        for (const Item & item : m_eqItems)
        {
            if (item.name() == t_name)
            {
                return true;
            }
        }

        return false;
    }

    bool Inventory::containsKeyword(const std::string & t_name) const
    {
        for (const Item & item : m_items)
        {
            if (item.name().find(t_name) != std::string::npos)
            {
                return true;
            }
        }

        for (const Item & item : m_eqItems)
        {
            if (item.name().find(t_name) != std::string::npos)
            {
                return true;
            }
        }

        return false;
    }

    bool Inventory::hasEquipped(const Armor t_armor) const
    {
        for (const Item & item : m_eqItems)
        {
            if (item.armorType() == t_armor)
            {
                return true;
            }
        }

        return false;
    }

    std::size_t Inventory::countOfEquipped(const Misc t_misc) const
    {
        std::size_t count = 0;

        for (const Item & item : m_eqItems)
        {
            if (item.miscType() == t_misc)
            {
                ++count;
            }
        }

        return count;
    }

} // namespace castlecrawl::item
