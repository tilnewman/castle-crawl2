#ifndef ITEMENUMS_HPP_INCLUDED
#define ITEMENUMS_HPP_INCLUDED
//
// item-enums.hpp
//
#include <compare>
#include <string>

#include <SFML/System/Vector2.hpp>

namespace castlecrawl::item
{

    struct UseEffect
    {
        int health{ 0 };
        int mana{ 0 };

        constexpr int total() const noexcept { return (health + mana); }
        constexpr bool empty() const noexcept { return (total() == 0); }
        auto operator<=>(const UseEffect &) const noexcept = default;
    };

    //

    struct EquipEffect
    {
        int acc{ 0 };
        int arc{ 0 };
        int dex{ 0 };
        int dmg{ 0 };
        int lck{ 0 };
        int str{ 0 };

        constexpr int total() const noexcept { return (acc + arc + dex + dmg + lck + str); }
        constexpr bool empty() const noexcept { return (total() == 0); }

        constexpr inline EquipEffect & operator+=(const EquipEffect & t_right) noexcept
        {
            acc += t_right.acc;
            arc += t_right.arc;
            dex += t_right.dex;
            dmg += t_right.dmg;
            lck += t_right.lck;
            str += t_right.str;
            return *this;
        }

        friend constexpr inline EquipEffect
            operator+(EquipEffect t_left, const EquipEffect & t_right) noexcept
        {
            t_left += t_right;
            return t_left;
        }

        auto operator<=>(const EquipEffect &) const noexcept = default;
    };

    //

    enum class Weapon : unsigned char
    {
        Dagger = 0,
        Handaxe,
        Spear,
        Halberd,
        Mace,
        Warhammer,
        Shortsword,
        Longsword,
        Claymore,
        Waraxe,
        Scythe,
        Count
    };

    inline constexpr std::string_view toString(const Weapon t_weapon) noexcept
    {
        // clang-format off
        switch (t_weapon)
        {
            case Weapon::Dagger:        { return "Dagger"; }
            case Weapon::Handaxe:       { return "Handaxe"; }
            case Weapon::Spear:         { return "Spear"; }
            case Weapon::Halberd:       { return "Halberd"; }
            case Weapon::Mace:          { return "Mace"; }
            case Weapon::Warhammer:     { return "Warhammer"; }
            case Weapon::Shortsword:    { return "Shortsword"; }
            case Weapon::Longsword:     { return "Longsword"; }
            case Weapon::Claymore:      { return "Claymore"; }
            case Weapon::Waraxe:        { return "Waraxe"; }
            case Weapon::Scythe:        { return "Scythe"; }
            case Weapon::Count:
            default:                    { return "unknown_weapon_error"; }
        }
        // clang-format on
    }

    inline const sf::Vector2i baseWeaponDamage(const Weapon t_weapon) noexcept
    {
        // clang-format off
        switch (t_weapon)
        {
            case Weapon::Dagger:     { return {  2,  4 }; }
            case Weapon::Handaxe:    { return {  3,  6 }; }
            case Weapon::Spear:      { return {  5,  8 }; }
            case Weapon::Halberd:    { return {  7, 12 }; }
            case Weapon::Mace:       { return {  9, 13 }; }
            case Weapon::Warhammer:  { return { 10, 16 }; }
            case Weapon::Shortsword: { return {  6, 10 }; }
            case Weapon::Longsword:  { return {  9, 13 }; }
            case Weapon::Claymore:   { return { 10, 16 }; }
            case Weapon::Waraxe:     { return { 12, 18 }; }
            case Weapon::Scythe:     { return { 13, 20 }; }
            case Weapon::Count:
            default:                 { return {  0,  0 }; }
        }
        // clang-format on
    }

    enum class WeaponMaterial : unsigned char
    {
        Bronze = 0,
        Steel,
        Obsidian,
        Silver,
        Platinum,
        Gold,
        Diamond,
        Count
    };

    inline constexpr std::string_view toString(const WeaponMaterial t_material) noexcept
    {
        // clang-format off
        switch (t_material)
        {
            case WeaponMaterial::Bronze:    { return "Bronze"; }
            case WeaponMaterial::Steel:     { return "Steel"; }
            case WeaponMaterial::Obsidian:  { return "Obsidian"; }
            case WeaponMaterial::Silver:    { return "Silver"; }
            case WeaponMaterial::Platinum:  { return "Platinum"; }
            case WeaponMaterial::Gold:      { return "Gold"; }
            case WeaponMaterial::Diamond:   { return "Diamond"; }
            case WeaponMaterial::Count:
            default:                        { return "unknown_weapon_material_error"; }
        }
        // clang-format on
    }

    inline constexpr int weaponMaterialDamage(const WeaponMaterial t_material) noexcept
    {
        // clang-format off
        switch (t_material)
        {
            case WeaponMaterial::Bronze:    { return 0; }
            case WeaponMaterial::Steel:     { return 1; }
            case WeaponMaterial::Obsidian:  { return 2; }
            case WeaponMaterial::Silver:    { return 3; }
            case WeaponMaterial::Platinum:  { return 4; }
            case WeaponMaterial::Gold:      { return 5; }
            case WeaponMaterial::Diamond:   { return 7; }
            case WeaponMaterial::Count:
            default:                        { return 0; }
        }
        // clang-format on
    }

    enum class Armor : unsigned char
    {
        Helm = 0,
        Cuirass,
        Bracers,
        Gauntlets,
        Greaves,
        Boots,
        Count
    };

    inline constexpr std::string_view toString(const Armor t_armor) noexcept
    {
        // clang-format off
        switch (t_armor)
        {
            case Armor::Helm:       { return "Helm"; }
            case Armor::Cuirass:    { return "Cuirass"; }
            case Armor::Bracers:    { return "Bracers"; }
            case Armor::Gauntlets:  { return "Gauntlets"; }
            case Armor::Greaves:    { return "Greaves"; }
            case Armor::Boots:      { return "Boots"; }
            case Armor::Count:
            default:                { return "unknown_armor_error"; }
        }
        // clang-format on
    }

    inline constexpr int baseArmorRating(const Armor t_armor) noexcept
    {
        // clang-format off
        switch (t_armor)
        {
            case Armor::Helm:       { return 5; }
            case Armor::Cuirass:    { return 9; }
            case Armor::Bracers:    { return 3; }
            case Armor::Gauntlets:  { return 2; }
            case Armor::Greaves:    { return 6; }
            case Armor::Boots:      { return 1; }
            case Armor::Count:
            default:                { return 0; }
        }
        // clang-format on
    }

    enum class ArmorMaterial : unsigned char
    {
        Leather = 0,
        Bronze,
        Steel,
        Silver,
        Platinum,
        Gold,
        DragonScale,
        Count
    };

    inline constexpr std::string_view toString(const ArmorMaterial t_material) noexcept
    {
        // clang-format off
        switch (t_material)
        {
            case ArmorMaterial::Leather:    { return "Leather"; }
            case ArmorMaterial::Bronze:     { return "Bronze"; }
            case ArmorMaterial::Steel:      { return "Steel"; }
            case ArmorMaterial::Silver:     { return "Silver"; }
            case ArmorMaterial::Platinum:   { return "Platinum"; }
            case ArmorMaterial::Gold:       { return "Gold"; }
            case ArmorMaterial::DragonScale:{ return "Dragon Scale"; }
            case ArmorMaterial::Count:
            default:                        { return "unknown_armor_material_error"; }
        }
        // clang-format on
    }

    inline constexpr int armorMaterialRating(const ArmorMaterial t_material) noexcept
    {
        // clang-format off
        switch (t_material)
        {
            case ArmorMaterial::Leather:    { return 0; }
            case ArmorMaterial::Bronze:     { return 1; }
            case ArmorMaterial::Steel:      { return 2; }
            case ArmorMaterial::Silver:     { return 4; }
            case ArmorMaterial::Platinum:   { return 5; }
            case ArmorMaterial::Gold:       { return 6; }
            case ArmorMaterial::DragonScale:{ return 9; }
            case ArmorMaterial::Count:
            default:                        { return 0; }
        }
        // clang-format on
    }

    // there are only equipable and useable misc items
    enum class Misc : unsigned char
    {
        Amulet,
        Ankh,
        Armband,
        Brooch,
        Chime,
        Conch,
        Crown,
        CyclopsEye,
        Doll,
        DriedHead,
        Egg,
        Feather,
        Figurine,
        GnomeNose,
        Goblet,
        Headdress,
        Herbs,
        Horn,
        Horseshoe,
        Hourglass,
        ImpTail,
        Key,
        MagnifyingGlass,
        Mask,
        Mirror,
        Necklace,
        Orb,
        Pin,
        PixieBell,
        Potion,
        Puppet,
        Rainmaker,
        RatJuju,
        RavenClaw,
        Scepter,
        Scroll,
        Talisman,
        Tooth,
        Totem,
        Veil,
        Vial,
        Wand,
        Whistle,
        Wolfpelt,
        Ring,
        Count
    };

    inline constexpr int miscBaseValue(const Misc t_misc) noexcept
    {
        // clang-format off
        switch (t_misc)
        {
            case Misc::Feather:         { return 1;  }
            case Misc::Tooth:           { return 2;  }
            case Misc::Doll:            { return 3;  }
            case Misc::Figurine:        { return 4;  }
            case Misc::Puppet:          { return 5;  }
            case Misc::Chime:           { return 6;  }
            case Misc::Whistle:         { return 7;  }
            case Misc::Ankh:            { return 8;  }
            case Misc::Egg:             { return 9;  }
            case Misc::Key:             { return 10; }
            case Misc::Ring:            { return 11; }
            case Misc::Armband:         { return 12; }
            case Misc::Mask:            { return 13; }
            case Misc::Mirror:          { return 14; }
            case Misc::Pin:             { return 15; }
            case Misc::PixieBell:       { return 16; }
            case Misc::Talisman:        { return 17; }
            case Misc::Brooch:          { return 18; }
            case Misc::Necklace:        { return 19; }
            case Misc::Goblet:          { return 20; }
            case Misc::DriedHead:       { return 21; }
            case Misc::Wolfpelt:        { return 22; }
            case Misc::Herbs:           { return 23; }
            case Misc::Horn:            { return 24; }
            case Misc::Horseshoe:       { return 25; }
            case Misc::Hourglass:       { return 26; }
            case Misc::MagnifyingGlass: { return 27; }
            case Misc::Scroll:          { return 28; }
            case Misc::Vial:            { return 29; }
            case Misc::Amulet:          { return 30; }
            case Misc::Potion:          { return 31; }
            case Misc::Conch:           { return 32; }
            case Misc::CyclopsEye:      { return 33; }
            case Misc::GnomeNose:       { return 34; }
            case Misc::ImpTail:         { return 35; }
            case Misc::RatJuju:         { return 36; }
            case Misc::Totem:           { return 37; }
            case Misc::RavenClaw:       { return 38; }
            case Misc::Crown:           { return 39; }
            case Misc::Headdress:       { return 40; }
            case Misc::Veil:            { return 41; }
            case Misc::Orb:             { return 42; }
            case Misc::Rainmaker:       { return 43; }
            case Misc::Scepter:         { return 44; }
            case Misc::Wand:            { return 45; }
            case Misc::Count:
            default:                    { return 0;  }
        }
        // clang-format on
    }

    inline constexpr std::string_view toString(const Misc t_misc) noexcept
    {
        // clang-format off
        switch (t_misc)
        {
            case Misc::Amulet:          { return "Amulet"; }
            case Misc::Ankh:            { return "Ankh"; }
            case Misc::Armband:         { return "Armband"; }
            case Misc::Brooch:          { return "Brooch"; }
            case Misc::Chime:           { return "Chime"; }
            case Misc::Conch:           { return "Conch"; }
            case Misc::Crown:           { return "Crown"; }
            case Misc::CyclopsEye:      { return "Cyclops Eye"; }
            case Misc::Doll:            { return "Doll"; }
            case Misc::DriedHead:       { return "Dried Head"; }
            case Misc::Egg:             { return "Egg"; }
            case Misc::Feather:         { return "Feather"; }
            case Misc::Figurine:        { return "Figurine"; }
            case Misc::GnomeNose:       { return "Gnome Nose"; }
            case Misc::Goblet:          { return "Goblet"; }
            case Misc::Headdress:       { return "Headdress"; }
            case Misc::Herbs:           { return "Herbs"; }
            case Misc::Horn:            { return "Horn"; }
            case Misc::Horseshoe:       { return "Horseshoe"; }
            case Misc::Hourglass:       { return "Hourglass"; }
            case Misc::ImpTail:         { return "Imp Tail"; }
            case Misc::Key:             { return "Key"; }
            case Misc::MagnifyingGlass: { return "Magnifying Glass"; }
            case Misc::Mask:            { return "Mask"; }
            case Misc::Mirror:          { return "Mirror"; }
            case Misc::Necklace:        { return "Necklace"; }
            case Misc::Orb:             { return "Orb"; }
            case Misc::Pin:             { return "Pin"; }
            case Misc::PixieBell:       { return "Pixie Bell"; }
            case Misc::Potion:          { return "Potion"; }
            case Misc::Puppet:          { return "Puppet"; }
            case Misc::Rainmaker:       { return "Rainmaker"; }
            case Misc::RatJuju:         { return "Rat Juju"; }
            case Misc::RavenClaw:       { return "Raven Claw"; }
            case Misc::Scepter:         { return "Scepter"; }
            case Misc::Scroll:          { return "Scroll"; }
            case Misc::Talisman:        { return "Talisman"; }
            case Misc::Tooth:           { return "Tooth"; }
            case Misc::Totem:           { return "Totem"; }
            case Misc::Veil:            { return "Veil"; }
            case Misc::Vial:            { return "Vial"; }
            case Misc::Wand:            { return "Wand"; }
            case Misc::Whistle:         { return "Whistle"; }
            case Misc::Wolfpelt:        { return "Wolfpelt"; }
            case Misc::Ring:            { return "Ring"; }
            case Misc::Count:
            default:                    { return "unknown_misc_item_error"; }
        }
        // clang-format on
    }

    // if not misc, then it's either weapon/armor which can only equip one of
    inline constexpr std::size_t miscEquipCount(const Misc t_misc) noexcept
    {
        // clang-format off
        switch (t_misc)
        {
            case Misc::Ring:       
            case Misc::Armband:  { return 2; }
            //
            case Misc::Amulet:
            case Misc::Ankh:
            case Misc::Brooch:
            case Misc::Chime:
            case Misc::Conch:
            case Misc::Crown:
            case Misc::CyclopsEye:
            case Misc::Doll:
            case Misc::DriedHead:
            case Misc::Egg:
            case Misc::Feather:
            case Misc::Figurine:
            case Misc::GnomeNose:
            case Misc::Goblet:
            case Misc::Headdress:
            case Misc::Horn:
            case Misc::Horseshoe:
            case Misc::Hourglass:
            case Misc::ImpTail:
            case Misc::Key:
            case Misc::MagnifyingGlass:
            case Misc::Mask:
            case Misc::Mirror:
            case Misc::Necklace:
            case Misc::Orb:
            case Misc::Pin:
            case Misc::PixieBell:
            case Misc::Puppet:
            case Misc::Rainmaker:
            case Misc::RatJuju:
            case Misc::RavenClaw:
            case Misc::Scepter:
            case Misc::Scroll:
            case Misc::Talisman:
            case Misc::Tooth:
            case Misc::Totem:
            case Misc::Veil:
            case Misc::Vial:
            case Misc::Wand:
            case Misc::Whistle:
            case Misc::Wolfpelt:  { return 1; }
            //
            case Misc::Potion:
            case Misc::Herbs:     { return 0; }
            case Misc::Count:
            default:              { return 1; } //must be 1 so that non-misc are equipable
        }
        // clang-format on
    }

    inline constexpr bool isMiscEquipable(const Misc t_misc) noexcept
    {
        return (miscEquipCount(t_misc) > 0);
    }

    // misc items are either Useable or Equipable but never both and never neither
    inline constexpr bool isMiscUseable(const Misc t_misc) noexcept
    {
        return !isMiscEquipable(t_misc);
    }

    enum class MiscMaterial : unsigned char
    {
        Iron = 0,
        Pewter,
        Glass,
        Bronze,
        Bone,
        Tribal,
        Fanged,
        Jade,
        Amethyst,
        Emerald,
        Ruby,
        Obsidian,
        Lazuli,
        Bloody,
        Jeweled,
        Magic, // must be last! see ItemFactory::makeMisc()
        Count
    };

    inline constexpr std::string_view toString(const MiscMaterial t_material) noexcept
    {
        // clang-format off
        switch (t_material)
        {
            case MiscMaterial::Iron:     { return "Iron"; }
            case MiscMaterial::Pewter:   { return "Pewter"; }
            case MiscMaterial::Glass:    { return "Glass"; }
            case MiscMaterial::Bronze:   { return "Bronze"; }
            case MiscMaterial::Bone:     { return "Bone"; }
            case MiscMaterial::Tribal:   { return "Tribal"; }
            case MiscMaterial::Fanged:   { return "Fanged"; }
            case MiscMaterial::Jade:     { return "Jade"; }
            case MiscMaterial::Amethyst: { return "Amethyst"; }
            case MiscMaterial::Emerald:  { return "Emerald"; }
            case MiscMaterial::Ruby:     { return "Ruby"; }
            case MiscMaterial::Obsidian: { return "Obsidian"; }
            case MiscMaterial::Lazuli:   { return "Lazuli"; }
            case MiscMaterial::Bloody:   { return "Bloody"; }
            case MiscMaterial::Jeweled:  { return "Jeweled"; }
            case MiscMaterial::Magic:    { return "Magic"; }
            case MiscMaterial::Count:
            default:                     { return "unknown_misc_material_error"; }
        }
        // clang-format on
    }

    inline constexpr EquipEffect miscMaterialEquipEffect(const MiscMaterial t_material) noexcept
    {
        // clang-format off
        switch (t_material)
        {
            case MiscMaterial::Iron:     { return { .str=2 }; }
            case MiscMaterial::Pewter:   { return { .str=1 }; }
            case MiscMaterial::Glass:    { return { .arc=1, .lck=1 }; }
            case MiscMaterial::Bronze:   { return { .arc=1, .str=1 }; }
            case MiscMaterial::Bone:     { return { .arc=1, .dmg=1 }; }
            case MiscMaterial::Tribal:   { return { .arc=3, .lck=1 }; }
            case MiscMaterial::Fanged:   { return { .dmg=5 }; }
            case MiscMaterial::Jade:     { return { .lck=1 }; }
            case MiscMaterial::Amethyst: { return { .arc=1 }; }
            case MiscMaterial::Emerald:  { return { .arc=1, .lck=1 }; }
            case MiscMaterial::Ruby:     { return { .arc=2, .lck=2 }; }
            case MiscMaterial::Obsidian: { return { .arc=3, .dmg=3 }; }
            case MiscMaterial::Lazuli:   { return { .arc=5, .lck=3 }; }
            case MiscMaterial::Bloody:   { return { .dmg=10 }; }
            case MiscMaterial::Jeweled:  { return { .arc=10, .lck=5 }; }
            case MiscMaterial::Magic:
            case MiscMaterial::Count:
            default:                     { return {}; }
        }
        // clang-format on
    }

    // useable misc items (potions & herbs) can only have the "Magic" material
    inline constexpr MiscMaterial requiredMiscMaterial(const Misc t_misc) noexcept
    {
        MiscMaterial material = MiscMaterial::Count;

        if (isMiscUseable(t_misc))
        {
            material = MiscMaterial::Magic;
        }

        return material;
    }

    enum class UseStrength : unsigned char
    {
        Weak,
        Normal,
        Strong
    };

    inline constexpr std::string_view toString(const UseStrength t_strength) noexcept
    {
        // clang-format off
        switch (t_strength)
        {
            case UseStrength::Weak:     { return "Weak"; }
            case UseStrength::Strong:   { return "Strong"; }
            case UseStrength::Normal:   { return ""; } //prevent 'normal' in item names
            default:                    { return "unknown_use_strength_error"; }
        }
        // clang-format on
    }

} // namespace castlecrawl::item

#endif // ITEMENUMS_HPP_INCLUDED
