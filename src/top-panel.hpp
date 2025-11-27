#ifndef TOPPANEL_HPP_INCLUDED
#define TOPPANEL_HPP_INCLUDED
//
// top-panel.hpp
//
#include "experience-bar.hpp"
#include "health-bar.hpp"
#include "mana-bar.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl
{
    struct Context;

    class TopPanel : public sf::Drawable
    {
      public:
        TopPanel();

        void setup(const Context & t_context);
        void update(const Context & t_context);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

      private:
        sf::Texture m_titleTexture;
        sf::Sprite m_titleSprite;
        HealthBar m_healthBar;
        ManaBar m_manaBar;
        ExperienceBar m_experienceBar;
    };

} // namespace castlecrawl

#endif // TOPPANEL_HPP_INCLUDED
