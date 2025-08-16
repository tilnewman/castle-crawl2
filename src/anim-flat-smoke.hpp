#ifndef ANIM_FLAT_SMOKE_HPP_INCLUDED
#define ANIM_FLAT_SMOKE_HPP_INCLUDED
//
// anim-flat-smoke.hpp
//
#include "map-types.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

namespace castlecrawl
{

    struct Context;
    struct GameConfig;

    //

    struct FlatSmokeAnim
    {
        FlatSmokeAnim(
            const sf::Texture & t_texture,
            const sf::IntRect & t_textureRect,
            const sf::FloatRect & t_screenRect);

        bool is_alive;
        float elapsed_sec;
        std::size_t frame_index;
        sf::Vector2f screen_pos;
        sf::Sprite sprite;
    };

    //

    class FlatSmokeAnimManager
    {
      public:
        FlatSmokeAnimManager();

        void setup(const GameConfig & t_config);
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void add(const Context & t_context, const MapPos_t & t_mapPos);
        inline void clear() { m_animations.clear(); }
        [[nodiscard]] inline std::size_t particleCount() const { return m_animations.size(); }

      private:
        [[nodiscard]] const sf::IntRect frameRect(const std::size_t index) const;

      private:
        std::vector<FlatSmokeAnim> m_animations;
        float m_timeBetweenFramesSec;
        sf::Texture m_texture;
    };

} // namespace castlecrawl

#endif // ANIM_FLAT_SMOKE_HPP_INCLUDED