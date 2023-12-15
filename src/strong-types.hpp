#ifndef STRONGTYPES_HPP_INCLUDED
#define STRONGTYPES_HPP_INCLUDED
//
// strong-types.hpp
//
#include "strong-type.hpp"

namespace castlecrawl
{

    // TODO um, make more of these?

    // phantom tags
    struct ArmorTag;

    // strong types
    using Armor_t = util::StrongType<int, ArmorTag>;

    // user defined literals
    inline Armor_t operator"" _armor(unsigned long long armor) { return Armor_t::make(armor); }

} // namespace castlecrawl

#endif // STRONGTYPES_HPP_INCLUDED
