#ifndef ITEMFACTORY_HPP_INCLUDED
#define ITEMFACTORY_HPP_INCLUDED
//
// item-factory.hpp
//
#include "item.hpp"

#include <SFML/Graphics/Font.hpp>

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

        void setup(const sf::Font & font);
        const TextExtent textExtents() const { return m_textExtent; }
        const Treasure randomTreasureFind(const Context & context) const;
        const Treasure randomHerbFind(const Context & context) const;
        const ItemVec_t & allItems() const { return m_allItems; }

      private:
        void makeAll();
        void makeWeapons(ItemVec_t & items) const;
        void makeArmor(ItemVec_t & items) const;
        void makeMisc(ItemVec_t & items) const;
        void makeCustom(ItemVec_t & items) const;

        const TextExtent findTextExtents() const;
        void validate() const;
        void throwIfInvalid(const Item & item) const;
        void dumpInfo(const sf::Font & font) const;

      private:
        TextExtent m_textExtent;
        ItemVec_t m_allItems;
    };

} // namespace castlecrawl::item

#endif // ITEMFACTORY_HPP_INCLUDED
