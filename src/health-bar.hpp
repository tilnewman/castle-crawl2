#ifndef HEALTHBAR_HPP_INCLUDED
#define HEALTHBAR_HPP_INCLUDED
//
// health-bar.hpp
//
#include "gui-stat-bar.hpp"

namespace castlecrawl
{
    struct Context;

    //

    class HealthBar : public sf::Drawable
    {
      public:
        HealthBar();

        void setup(const Context & t_context);
        void update(const Context & t_context);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

      private:
        StatBar m_statBar;
    };

} // namespace castlecrawl

#endif // HEALTHBAR_HPP_INCLUDED
