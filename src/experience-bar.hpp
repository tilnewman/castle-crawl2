#ifndef EXPERIENCE_BAR_HPP_INCLUDED
#define EXPERIENCE_BAR_HPP_INCLUDED
//
// experience-bar.hpp
//
#include "gui-stat-bar.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

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
        [[nodiscard]] inline const sf::FloatRect bounds() const noexcept { return m_statBar.bounds(); }

      private:
        StatBar m_statBar;
    };

} // namespace castlecrawl

#endif // EXPERIENCE_BAR_HPP_INCLUDED
