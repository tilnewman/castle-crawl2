#ifndef ITEMFACTORY_HPP_INCLUDED
#define ITEMFACTORY_HPP_INCLUDED
//
// item-factory.hpp
//
#include "item.hpp"

#include <SFML/Graphics/Font.hpp>

#include <optional>

namespace castlecrawl
{
    struct Context;
}

namespace castlecrawl::item
{

    struct TextExtent
    {
        std::size_t longest_name{ 0 };
        std::size_t longest_desc{ 0 };
    };

    //

    class ItemFactory
    {
      public:
        ItemFactory();

        void setup();

        [[nodiscard]] inline const TextExtent textExtents() const { return m_textExtent; }
        [[nodiscard]] const Treasure randomTreasureFind(const Context & t_context) const;
        [[nodiscard]] const Treasure randomHerbFind(const Context & t_context) const;

        [[nodiscard]] const ItemVec_t & allItems() const { return m_allItems; }
        [[nodiscard]] const std::optional<Item> find(const std::string & t_itemName) const;

        void dumpInfo(const sf::Font & t_font) const;

      private:
        void makeAll();
        void makeWeapons(ItemVec_t & t_items) const;
        void makeArmor(ItemVec_t & t_items) const;
        void makeMisc(ItemVec_t & t_items) const;
        void makeCustom(ItemVec_t & t_items) const;

        [[nodiscard]] const TextExtent findTextExtents() const;
        void validate() const;
        void throwIfInvalid(const Item & t_item) const;

      private:
        TextExtent m_textExtent;
        ItemVec_t m_allItems;
    };

} // namespace castlecrawl::item

#endif // ITEMFACTORY_HPP_INCLUDED
