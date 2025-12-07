// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// item-factory.cpp
//
#include "item-factory.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "player.hpp"
#include "random.hpp"
#include "stats-display.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

namespace castlecrawl::item
{

    ItemFactory::ItemFactory()
        : m_textExtent{}
        , m_allItems{}
    {}

    void ItemFactory::makeAll()
    {
        m_allItems.clear();
        m_allItems.reserve(1000); // acutally 883 as of 2024-7-28

        makeWeapons(m_allItems);
        makeArmor(m_allItems);
        makeMisc(m_allItems);
        makeCustom(m_allItems);
    }

    void ItemFactory::makeWeapons(ItemVec_t & t_items) const
    {
        for (int i = 0; i < static_cast<int>(Weapon::Count); ++i)
        {
            const auto type = static_cast<Weapon>(i);
            for (int m = 0; m < static_cast<int>(WeaponMaterial::Count); ++m)
            {
                const auto material = static_cast<WeaponMaterial>(m);
                t_items.emplace_back(type, material);
            }
        }
    }

    void ItemFactory::makeArmor(ItemVec_t & t_items) const
    {
        for (int i = 0; i < static_cast<int>(Armor::Count); ++i)
        {
            const auto type = static_cast<Armor>(i);
            for (int m = 0; m < static_cast<int>(ArmorMaterial::Count); ++m)
            {
                const auto material = static_cast<ArmorMaterial>(m);
                t_items.emplace_back(type, material);
            }
        }
    }

    void ItemFactory::makeMisc(ItemVec_t & t_items) const
    {
        // generate the equipable (non useable) mist items, see below for the others
        for (int i = 0; i < static_cast<int>(Misc::Count); ++i)
        {
            const auto type = static_cast<Misc>(i);
            if (!isMiscEquipable(type))
            {
                continue;
            }

            for (int m = 0; m < static_cast<int>(MiscMaterial::Count); ++m)
            {
                const auto material = static_cast<MiscMaterial>(m);
                if (material == MiscMaterial::Magic)
                {
                    continue;
                }

                t_items.emplace_back(
                    type,
                    material,
                    UseStrength::Normal,
                    UseEffect{},
                    miscMaterialEquipEffect(material));
            }
        }

        // these are the useable misc items not generated above

        // keys (these have no equip effect)
        for (int m = 0; m < static_cast<int>(MiscMaterial::Count); ++m)
        {
            const auto material = static_cast<MiscMaterial>(m);
            if (material == MiscMaterial::Magic)
            {
                continue;
            }

            t_items.emplace_back(Misc::Key, material);
        }

        // useable potions and herbs
        t_items.push_back(
            Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Weak, { .health = 8 }, {}));

        t_items.push_back(
            Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Normal, { .health = 16 }, {}));

        t_items.push_back(
            Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Strong, { .health = 32 }, {}));

        //

        t_items.push_back(
            Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Weak, { .mana = 5 }, {}));

        t_items.push_back(
            Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Normal, { .mana = 10 }, {}));

        t_items.push_back(
            Item(Misc::Potion, MiscMaterial::Magic, UseStrength::Strong, { .mana = 20 }, {}));

        //

        t_items.push_back(
            Item(Misc::Herbs, MiscMaterial::Magic, UseStrength::Weak, { .health = 5 }, {}));

        t_items.push_back(
            Item(Misc::Herbs, MiscMaterial::Magic, UseStrength::Normal, { .health = 10 }, {}));

        t_items.push_back(
            Item(Misc::Herbs, MiscMaterial::Magic, UseStrength::Strong, { .health = 20 }, {}));
    }

    void ItemFactory::makeCustom(ItemVec_t & t_items) const
    {
        // weapons

        for (int i = 0; i < static_cast<int>(Weapon::Count); ++i)
        {
            const auto type = static_cast<Weapon>(i);

            t_items.emplace_back(
                type,
                WeaponMaterial::Obsidian,
                std::string(toString(type)).append(" of Night"),
                EquipEffect{ .arc = 3, .dmg = 3 });
        }

        for (int i = 0; i < static_cast<int>(Weapon::Count); ++i)
        {
            const auto type = static_cast<Weapon>(i);

            t_items.emplace_back(
                type,
                WeaponMaterial::Obsidian,
                std::string("Dark ").append(toString(type)),
                EquipEffect{ .arc = 1, .str = 1, .dmg = 1 });
        }

        for (int i = 0; i < static_cast<int>(Weapon::Count); ++i)
        {
            const auto type = static_cast<Weapon>(i);

            t_items.emplace_back(
                type,
                WeaponMaterial::Steel,
                std::string("Savage ").append(toString(type)),
                EquipEffect{ .acc = 1, .str = 2, .dmg = 4 });
        }

        t_items.push_back(Item(
            Weapon::Dagger, WeaponMaterial::Steel, "Backstabber Dagger", { .acc = 2, .dmg = 7 }));

        t_items.push_back(Item(
            Weapon::Shortsword, WeaponMaterial::Gold, "Lucky Shortsword", { .acc = 4, .lck = 10 }));

        t_items.push_back(
            Item(Weapon::Dagger, WeaponMaterial::Bronze, "Hobo Dagger", { .lck = 2 }));

        t_items.push_back(Item(
            Weapon::Scythe, WeaponMaterial::Gold, "Sythe of the Lich", { .arc = 4, .dmg = 4 }));

        t_items.push_back(
            Item(Weapon::Handaxe, WeaponMaterial::Steel, "Maniac Handaxe", { .dmg = 5 }));

        t_items.push_back(Item(Weapon::Mace, WeaponMaterial::Steel, "Brute Mace", { .dmg = 4 }));

        t_items.push_back(
            Item(Weapon::Warhammer, WeaponMaterial::Silver, "Requiem Warhammer", { .dmg = 6 }));

        t_items.push_back(Item(
            Weapon::Longsword,
            WeaponMaterial::Silver,
            "Knightly Longsword",
            { .acc = 3, .dmg = 6 }));

        t_items.push_back(
            Item(Weapon::Waraxe, WeaponMaterial::Bronze, "Orcish Waraxe", { .dmg = 3 }));

        t_items.push_back(Item(
            Weapon::Claymore, WeaponMaterial::Obsidian, "Macabre Waraxe", { .arc = 2, .dmg = 4 }));

        t_items.push_back(Item(
            Weapon::Shortsword,
            WeaponMaterial::Steel,
            "Scoundrel Shortsword",
            { .lck = 3, .dmg = 6 }));

        t_items.push_back(
            Item(Weapon::Waraxe, WeaponMaterial::Steel, "Wicked Waraxe", { .lck = 1, .dmg = 5 }));

        t_items.push_back(
            Item(Weapon::Dagger, WeaponMaterial::Obsidian, "Diabolic Dagger", { .dmg = 10 }));

        t_items.push_back(Item(
            Weapon::Longsword,
            WeaponMaterial::Silver,
            "Dancing Longsword",
            { .acc = 4, .dmg = 8 }));

        t_items.push_back(Item(
            Weapon::Longsword, WeaponMaterial::Steel, "Samurai Longsword", { .acc = 2, .dmg = 2 }));

        t_items.push_back(
            Item(Weapon::Claymore, WeaponMaterial::Obsidian, "Gloom Claymore", { .dmg = 4 }));

        t_items.push_back(
            Item(Weapon::Dagger, WeaponMaterial::Silver, "Pirate Dagger", { .lck = 2, .dmg = 2 }));

        t_items.push_back(Item(
            Weapon::Longsword, WeaponMaterial::Silver, "Pirate Longsword", { .lck = 2, .dmg = 2 }));

        t_items.push_back(
            Item(Weapon::Dagger, WeaponMaterial::Steel, "Bone Dagger", { .arc = 1, .dmg = 2 }));

        t_items.push_back(Item(
            Weapon::Handaxe, WeaponMaterial::Bronze, "Villan's Handaxe", { .str = 1, .dmg = 1 }));

        // armor

        for (int i = 0; i < static_cast<int>(Armor::Count); ++i)
        {
            const auto type = static_cast<Armor>(i);

            t_items.emplace_back(
                type,
                ArmorMaterial::DragonScale,
                std::string("Dragon Slayer ").append(toString(type)),
                EquipEffect{ .acc = 3, .str = 3, .dmg = 3 });
        }

        for (int i = 0; i < static_cast<int>(Armor::Count); ++i)
        {
            const auto type = static_cast<Armor>(i);

            t_items.emplace_back(
                type,
                ArmorMaterial::Silver,
                std::string(toString(type)).append(" of Nobility"),
                EquipEffect{ .acc = 1, .lck = 2, .str = 3 });
        }

        for (int i = 0; i < static_cast<int>(Armor::Count); ++i)
        {
            const auto type = static_cast<Armor>(i);

            t_items.emplace_back(
                type,
                ArmorMaterial::Steel,
                std::string("Gladiator ").append(toString(type)),
                EquipEffect{ .acc = 1, .str = 1 });
        }

        for (int i = 0; i < static_cast<int>(Armor::Count); ++i)
        {
            const auto type = static_cast<Armor>(i);

            t_items.emplace_back(
                type,
                ArmorMaterial::Gold,
                std::string("Kingly ").append(toString(type)),
                EquipEffect{ .acc = 3, .str = 3 });
        }

        for (int i = 0; i < static_cast<int>(Armor::Count); ++i)
        {
            const auto type = static_cast<Armor>(i);

            t_items.emplace_back(
                type,
                ArmorMaterial::Leather,
                std::string("Druid ").append(toString(type)),
                EquipEffect{ .arc = 2, .lck = 2 });
        }

        for (int i = 0; i < static_cast<int>(Armor::Count); ++i)
        {
            const auto type = static_cast<Armor>(i);

            t_items.emplace_back(
                type,
                ArmorMaterial::Leather,
                std::string("Ranger ").append(toString(type)),
                EquipEffect{ .acc = 2, .lck = 1, .str = 3 });
        }

        t_items.push_back(Item(Armor::Boots, ArmorMaterial::Leather, "Nimble Boots", { .dex = 5 }));

        t_items.push_back(
            Item(Armor::Bracers, ArmorMaterial::Leather, "Swift Bracers", { .dex = 7 }));

        t_items.push_back(
            Item(Armor::Gauntlets, ArmorMaterial::Leather, "Mongoose Gauntlets", { .dex = 9 }));

        t_items.push_back(
            Item(Armor::Gauntlets, ArmorMaterial::Gold, "Glory Gauntlets", { .acc = 3, .str = 5 }));

        t_items.push_back(
            Item(Armor::Cuirass, ArmorMaterial::Silver, "Cuirass of Last Rites", { .arc = 7 }));

        t_items.push_back(
            Item(Armor::Greaves, ArmorMaterial::Leather, "Burglar Greaves", { .lck = 7 }));

        t_items.push_back(
            Item(Armor::Boots, ArmorMaterial::Leather, "Sorcerer Boots", { .arc = 5, .lck = 1 }));

        t_items.push_back(Item(
            Armor::Cuirass, ArmorMaterial::Silver, "Sorcerer Cuirass", { .arc = 5, .lck = 1 }));

        t_items.push_back(Item(
            Armor::Greaves, ArmorMaterial::Silver, "Sorcerer Greaves", { .arc = 5, .lck = 1 }));

        t_items.push_back(Item(Armor::Boots, ArmorMaterial::Leather, "Shaman Boots", { .arc = 2 }));

        t_items.push_back(
            Item(Armor::Cuirass, ArmorMaterial::Leather, "Shaman Cuirass", { .arc = 2 }));

        t_items.push_back(
            Item(Armor::Greaves, ArmorMaterial::Leather, "Shaman Greaves", { .arc = 2 }));

        t_items.push_back(Item(Armor::Helm, ArmorMaterial::Leather, "Monster Helm", { .str = 8 }));

        t_items.push_back(
            Item(Armor::Boots, ArmorMaterial::Leather, "Bearskin Boots", { .str = 1 }));

        t_items.push_back(
            Item(Armor::Bracers, ArmorMaterial::Leather, "Bearskin Bracers", { .str = 1 }));

        t_items.push_back(
            Item(Armor::Cuirass, ArmorMaterial::Leather, "Bearskin Cuirass", { .str = 1 }));

        t_items.push_back(
            Item(Armor::Greaves, ArmorMaterial::Leather, "Bearskin Greaves", { .str = 1 }));

        t_items.push_back(
            Item(Armor::Boots, ArmorMaterial::Leather, "Beastcall Boots", { .arc = 1, .str = 3 }));

        t_items.push_back(Item(
            Armor::Bracers, ArmorMaterial::Leather, "Beastcall Bracers", { .arc = 1, .str = 3 }));

        t_items.push_back(Item(
            Armor::Cuirass, ArmorMaterial::Leather, "Beastcall Cuirass", { .arc = 1, .str = 3 }));

        t_items.push_back(Item(
            Armor::Greaves, ArmorMaterial::Leather, "Beastcall Greaves", { .arc = 1, .str = 3 }));
    }

    void ItemFactory::validate() const
    {
        // throw if any names are the same
        std::set<std::string> names;
        for (const Item & item : m_allItems)
        {
            const auto iter = names.find(item.name());
            M_CHECK((iter == std::end(names)), "Items had the same name: " << item);
            names.insert(item.name());
        }

        // throw if any item is invalid
        for (const Item & item : m_allItems)
        {
            throwIfInvalid(item);
        }
    }

    const TextExtent ItemFactory::findTextExtents() const
    {
        TextExtent extents;

        for (const Item & item : m_allItems)
        {
            if (item.name().size() > extents.longest_name)
            {
                extents.longest_name = item.name().size();
            }

            if (item.description().size() > extents.longest_desc)
            {
                extents.longest_desc = item.description().size();
            }
        }

        return extents;
    }

    void ItemFactory::setup()
    {
        makeAll();

        // sorting by value allows for various optimizations, see randomTreasureFind()
        std::ranges::sort(
            m_allItems, [](const Item & A, const Item & B) { return (A.value() < B.value()); });

        m_textExtent = findTextExtents();
        validate();
    }

    void ItemFactory::dumpInfo(const sf::Font & t_font) const
    {
        // write all items to a spreadsheet
        {
            std::ofstream fileStream("items.csv", std::ios_base::trunc);

            fileStream << "name,value,type,magical,Description\n";

            for (const Item & item : m_allItems)
            {
                fileStream << item.name() << ',';
                fileStream << std::to_string(item.value()) << ',';

                if (item.isArmor())
                {
                    fileStream << "armor,";
                }
                else if (item.isWeapon())
                {
                    fileStream << "weapon,";
                }
                else
                {
                    fileStream << "misc,";
                }

                if (item.isMagical())
                {
                    fileStream << "magical,";
                }
                else
                {
                    fileStream << "normal,";
                }

                fileStream << item.description() << '\n';
            }
        }

        std::cout << std::endl << "Armor/Weapon/Misc Counts and Value:" << std::endl;
        std::size_t miscCount   = 0;
        std::size_t weaponCount = 0;
        std::size_t armorCount  = 0;
        std::size_t miscValue   = 0;
        std::size_t weaponValue = 0;
        std::size_t armorValue  = 0;
        for (const Item & item : m_allItems)
        {
            if (item.isWeapon())
            {
                ++weaponCount;
                weaponValue += static_cast<std::size_t>(item.value());
            }

            if (item.isArmor())
            {
                ++armorCount;
                armorValue += static_cast<std::size_t>(item.value());
            }

            if (item.isMisc())
            {
                ++miscCount;
                miscValue += static_cast<std::size_t>(item.value());
            }
        }
        std::cout << "\tWeapons Count " << weaponCount << " with total value " << weaponValue
                  << " and average " << (weaponValue / weaponCount) << std::endl;

        std::cout << "\tArmor   Count " << armorCount << " with total value " << armorValue
                  << " and average " << (armorValue / armorCount) << std::endl;

        std::cout << "\tMisc    Count " << miscCount << " with total value " << miscValue
                  << " and average " << (miscValue / miscCount) << std::endl;

        std::cout << std::endl << "All Useable:" << std::endl;
        for (const Item & item : m_allItems)
        {
            if (item.isUseable())
            {
                std::cout << '\t' << item.value() << "\t" << item << '\n';
            }
        }

        std::cout << std::endl << "All Non-Magical:" << std::endl;
        for (const Item & item : m_allItems)
        {
            if (!item.isMagical())
            {
                std::cout << '\t' << item.value() << "\t" << item << '\n';
            }
        }

        std::cout << std::endl << "All Magical Weapons and Armor:" << std::endl;
        for (const Item & item : m_allItems)
        {
            if (item.isMagical() && (item.isWeapon() || item.isArmor()))
            {
                std::cout << '\t' << item.value() << '\t' << item.description() << '\n';
            }
        }

        std::cout << std::endl << "Value to Item Count Distribution:" << std::endl;
        std::map<int, std::size_t> valueCountMap;
        std::vector<int> values;
        for (const Item & item : m_allItems)
        {
            values.push_back(item.value());
            ++valueCountMap[item.value()];
        }
        for (const auto pair : valueCountMap)
        {
            if (1 == pair.second)
            {
                continue;
            }

            std::cout << '\t' << pair.first << '\t' << pair.second << " items\n";
        }
        const auto valueStats = util::makeStats(values);
        std::cout << "  Value Statistics: " << valueStats.toString(0) << std::endl;

        std::cout << std::endl << "Armor Rating Distribution:" << std::endl;
        std::map<Armor_t, std::size_t> armorRatingCountMap;
        for (const Item & item : m_allItems)
        {
            if (!item.isArmor())
            {
                continue;
            }

            ++armorRatingCountMap[item.armorRating()];
        }
        for (const auto pair : armorRatingCountMap)
        {
            std::cout << '\t' << pair.first << '\t' << pair.second << " items\n";
        }

        std::cout << std::endl << "Weapon Average Damage Distribution:" << std::endl;
        std::map<int, std::size_t> avgDamageCountMap;
        for (const Item & item : m_allItems)
        {
            if (!item.isWeapon())
            {
                continue;
            }

            ++avgDamageCountMap[item.damageMin() + ((item.damageMax() - item.damageMin()) / 2)];
        }
        for (const auto pair : avgDamageCountMap)
        {
            std::cout << '\t' << pair.first << '\t' << pair.second << " items\n";
        }

        std::vector<int> allValues;
        std::vector<int> weaponValues;
        std::vector<int> armorValues;
        std::vector<int> miscValues;
        std::vector<std::size_t> nameLengths;
        std::vector<std::size_t> descLengths;
        for (const auto & item : m_allItems)
        {
            allValues.push_back(item.value());

            if (item.isWeapon())
                weaponValues.push_back(item.value());

            if (item.isArmor())
                armorValues.push_back(item.value());

            if (item.isMisc())
                miscValues.push_back(item.value());

            nameLengths.push_back(item.name().size());
            descLengths.push_back(item.description().size());
        }
        std::sort(std::begin(nameLengths), std::end(nameLengths));
        std::sort(std::begin(descLengths), std::end(descLengths));
        util::StatsDisplay<int>::makeAndSavePNG("all-item-values", t_font, allValues);
        util::StatsDisplay<int>::makeAndSavePNG("weapon-item-values", t_font, weaponValues);
        util::StatsDisplay<int>::makeAndSavePNG("armor-item-values", t_font, armorValues);
        util::StatsDisplay<int>::makeAndSavePNG("misc-item-values", t_font, miscValues);
        util::StatsDisplay<std::size_t>::makeAndSavePNG("item-name-lengths", t_font, nameLengths);
        util::StatsDisplay<std::size_t>::makeAndSavePNG("item-desc-lengths", t_font, descLengths);

        std::cout << std::endl;
        std::cout << "item count    = " << m_allItems.size() << std::endl;
        std::cout << "unique values = " << valueCountMap.size() << std::endl;
        std::cout << "lowest value  = " << m_allItems.front().value() << std::endl;
        std::cout << "highest value = " << m_allItems.back().value() << std::endl;
        std::cout << "longest name  = " << m_textExtent.longest_name << std::endl;
        std::cout << "longest desc  = " << m_textExtent.longest_desc << std::endl;
        std::cout << "item size     = " << sizeof(Item) << "bytes" << std::endl;
        std::cout << std::endl;
    }

    void ItemFactory::throwIfInvalid(const Item & t_item) const
    {
        const std::size_t typeCount = [&]() {
            std::size_t count{ 0 };
            if (t_item.isArmor())
            {
                ++count;
            }

            if (t_item.isWeapon())
            {
                ++count;
            }

            if (t_item.isMisc())
            {
                ++count;
            }

            return count;
        }();

        M_CHECK(
            (typeCount == 1),
            "Item's basic type count of Weapon/Armor/Misc is "
                << typeCount << " (mutually exclusive so the count must always be 1): " << t_item);

        M_CHECK(!t_item.name().empty(), "Item has no name: " << t_item);

        if (t_item.isUseable())
        {
            M_CHECK(
                !t_item.isEquipable(),
                "Item is Useable AND Equipable (both should never be true): " << t_item);

            M_CHECK(t_item.isMisc(), "Item is Useable but not misc: " << t_item);
        }

        if (t_item.isEquipable())
        {
            M_CHECK(
                !t_item.isUseable(),
                "Item is Equipable AND Useable (both should never be true): " << t_item);
        }

        if (MiscMaterial::Magic == t_item.miscMaterial())
        {
            M_CHECK(
                (t_item.isMagical()), "Item with MiscMaterial::Magical is not magical: " << t_item);
        }

        if (t_item.isArmor())
        {
            M_CHECK(
                (t_item.armorRating() >= 1_armor), "Armor item's amor_rating invalid: " << t_item);

            M_CHECK(
                (t_item.armorMaterial() != ArmorMaterial::Count),
                "Armor item has no material: " << t_item);

            M_CHECK(t_item.isEquipable(), "Armor item SHOULD be Equipable but is not: " << t_item);

            if (t_item.isMagical())
            {
                M_CHECK(
                    (t_item.name() != toString(t_item.armorType())),
                    "Magical armor has a default name:" << t_item);

                M_CHECK(
                    (t_item.equipEffect().total() > 0),
                    "Magical armor has no equip effect:" << t_item);
            }
        }
        else
        {
            M_CHECK(
                (t_item.armorRating() == 0_armor), "Non-Armor item had an amor_rating: " << t_item);

            M_CHECK(
                (t_item.armorMaterial() == ArmorMaterial::Count),
                "Non-Armor item has armor material: " << t_item);
        }

        if (t_item.isWeapon())
        {
            M_CHECK((t_item.damageMin() > 0), "Weapon item's damage_min invalid: " << t_item);

            M_CHECK(
                (t_item.damageMax() >= t_item.damageMin()),
                "Weapon item's damage_max is not >= than the min: " << t_item);

            M_CHECK(
                (t_item.weaponMaterial() != WeaponMaterial::Count),
                "Weapon item has no weapon material: " << t_item);

            M_CHECK(t_item.isEquipable(), "Weapon item SHOULD be Equipable but is not: " << t_item);

            if (t_item.isMagical())
            {
                M_CHECK(
                    (t_item.name() != toString(t_item.weaponType())),
                    "Magical weapon has a default name:" << t_item);

                M_CHECK(
                    (t_item.equipEffect().total() > 0),
                    "Magical weapon has no equip effect:" << t_item);
            }
        }
        else
        {
            M_CHECK((t_item.damageMin() == 0), "Non-Weapon item has a damage_min: " << t_item);
            M_CHECK((t_item.damageMax() == 0), "Non-Weapon item has a damage_max: " << t_item);

            M_CHECK(
                (t_item.weaponMaterial() == WeaponMaterial::Count),
                "Non-Weapon item has weapon material: " << t_item);
        }

        if (t_item.isMisc())
        {
            if (t_item.isUseable() && (t_item.miscMaterial() == MiscMaterial::Magic))
            {
                M_CHECK(
                    (t_item.useEffect().total() > 0),
                    "Useable magical Misc item has no use effects: " << t_item);
            }
            else
            {
                M_CHECK(
                    (t_item.miscMaterial() != MiscMaterial::Magic),
                    "This Misc item must NOT have the material 'Magic': " << t_item);
            }
        }
        else
        {
            M_CHECK(
                (t_item.miscMaterial() == MiscMaterial::Count),
                "Non-Misc item has misc material: " << t_item);
        }

        M_CHECK((t_item.value() > 0), "Item's Value is zero or less: " << t_item);
    }

    const Treasure ItemFactory::randomTreasureFind(const Context & t_context) const
    {
        // establish how much value this random find is worth
        const int valuePerLevel{ 100 };
        int valueRemaining = t_context.player.level() * valuePerLevel;
        valueRemaining += t_context.random.fromTo(0, valuePerLevel);
        valueRemaining = t_context.random.fromTo(0, valueRemaining);

        // determine how much will be gold
        Treasure treasure;
        const int valueOfGold = t_context.random.fromTo(0, valueRemaining);
        treasure.gold         = (valueOfGold / 5);
        valueRemaining -= valueOfGold;

        // use remaining value to add items
        ItemVec_t items;
        items.reserve(m_allItems.size());
        const int lowestValue = m_allItems.front().value();
        while (valueRemaining >= lowestValue)
        {
            // create a vector of items that could still possibly be found
            items.clear();
            for (const Item & item : m_allItems)
            {
                // skip items not allowed in random loot
                if (item.isMisc() && !canMiscBeRandomFoundItem(item.miscType()))
                {
                    continue;
                }

                // skip items worth too much
                if (item.value() > valueRemaining)
                {
                    break; // don't continue because m_allItems is sorted by value
                }

                // skip items already found
                const auto iter = std::find_if(
                    std::begin(treasure.items), std::end(treasure.items), [&](const Item & i) {
                        return (item.name() == i.name());
                    });

                if (std::end(treasure.items) != iter)
                {
                    continue;
                }

                items.push_back(item);
            }

            if (items.empty())
            {
                break;
            }

            const Item & item = treasure.items.emplace_back(t_context.random.from(items));
            valueRemaining -= item.value();
        }

        return treasure;
    }

    const Treasure ItemFactory::randomHerbFind(const Context & t_context) const
    {
        ItemVec_t miscItems;
        miscItems.reserve(100);
        makeMisc(miscItems);

        miscItems.erase(
            std::remove_if(
                std::begin(miscItems),
                std::end(miscItems),
                [](const Item & item) { return (item.miscType() != Misc::Herbs); }),
            std::end(miscItems));

        Treasure treasure;
        treasure.items.push_back(t_context.random.from(miscItems));
        return treasure;
    }

    const std::optional<Item> ItemFactory::find(const std::string & t_itemName) const
    {
        for (const Item & item : m_allItems)
        {
            if (item.name() == t_itemName)
            {
                return item;
            }
        }

        return {};
    }

} // namespace castlecrawl::item
