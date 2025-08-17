#ifndef MANA_BAR_HPP_INCLUDED
#define MANA_BAR_HPP_INCLUDED
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

        void setup(const Context & t_context);
        void update(const Context & t_context);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

      private:
        StatBar m_statBar;
    };

} // namespace castlecrawl

#endif // MANA_BAR_HPP_INCLUDED
