#ifndef HEALTHBAR_HPP_INCLUDED
#define HEALTHBAR_HPP_INCLUDED
//
// health-bar.hpp
//
#include "gui-stat-bar.hpp"

namespace castlecrawl
{
    struct Context;

    class HealthBar : public sf::Drawable
    {
      public:
        HealthBar();

        void setup(const Context & context);
        void update(const Context & context);
        void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

      private:
        StatBar m_statBar;
    };

} // namespace castlecrawl

#endif // HEALTHBAR_HPP_INCLUDED
