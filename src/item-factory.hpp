#ifndef ITEMFACTORY_HPP_INCLUDED
#define ITEMFACTORY_HPP_INCLUDED
//
// item-factory.hpp
//
#include "item.hpp"

namespace castlecrawl
{
    struct Context;
}

namespace castlecrawl::item
{

    struct TextExtent
    {
        std::size_t longest_name = 0;
        std::size_t longest_desc = 0;
    };

    class ItemFactory
    {
      public:
        ItemFactory();

        void processAll();
        void printSummaries() const;
        const TextExtent textExtents() const { return m_textExtent; }
        const Treasure randomTreasureFind(const Context & context) const;
        const Treasure randomHerbFind(const Context & context) const;
        const ItemVec_t makeAll() const;

      private:
        const ItemVec_t makeWeapons() const;
        const ItemVec_t makeArmor() const;
        const ItemVec_t makeMisc() const;
        const ItemVec_t makeCustom() const;

        const TextExtent findTextExtents(const ItemVec_t & items) const;
        void validateAll(const ItemVec_t & items) const;
        void throwIfInvalid(const Item & item) const;

      private:
        int m_lowestValue;
        TextExtent m_textExtent;
    };

} // namespace castlecrawl::item

#endif // ITEMFACTORY_HPP_INCLUDED
