#ifndef MANABAR_HPP_INCLUDED
#define MANABAR_HPP_INCLUDED
//
// mana-bar.hpp
//
#include "gui-stat-bar.hpp"

namespace castlecrawl
{
    struct Context;

    class ManaBar : public sf::Drawable
    {
      public:
        ManaBar();

        void setup(const Context & context);
        void update(const Context & context);
        void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

      private:
        StatBar m_statBar;
    };

} // namespace castlecrawl

#endif // MANABAR_HPP_INCLUDED
