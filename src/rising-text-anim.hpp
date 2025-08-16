#ifndef RISING_TEXT_ANIM_HPP_INCLUDED
#define RISING_TEXT_ANIM_HPP_INCLUDED
//
// rising-text-anim.hpp
//
#include "map-types.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>
#include <vector>

namespace castlecrawl
{
    struct Context;

    struct RisingTextAnimation
    {
        RisingTextAnimation(
            const Context & t_context, const sf::Text & t_text, const MapPos_t & t_mapPos);

        bool is_alive;
        float age_sec;
        MapPos_t map_pos;
        sf::Vector2f screen_pos;
        sf::Text text;
    };

    class RisingTextAnimationManager
    {
      public:
        RisingTextAnimationManager();

        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

        void
            add(const Context & t_context,
                const std::string & t_message,
                const sf::Color & t_color,
                const MapPos_t & t_mapPos);

        void remove(const MapPos_t & t_mapPos);
        inline void clear() { m_animations.clear(); }
        [[nodiscard]] inline std::size_t particleCount() const { return m_animations.size(); }

      private:
        std::vector<RisingTextAnimation> m_animations;
    };

} // namespace castlecrawl

#endif // RISING_TEXT_ANIM_HPP_INCLUDED