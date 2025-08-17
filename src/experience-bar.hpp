#ifndef EXPERIENCE_BAR_HPP_INCLUDED
#define EXPERIENCE_BAR_HPP_INCLUDED
//
// experience-bar.hpp
//
#include "gui-stat-bar.hpp"

namespace castlecrawl
{
    struct Context;

    class ExperienceBar : public sf::Drawable
    {
      public:
        ExperienceBar();

        void setup(const Context & t_context);
        void update(const Context & t_context);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

      private:
        StatBar m_statBar;
    };

} // namespace castlecrawl

#endif // EXPERIENCE_BAR_HPP_INCLUDED
