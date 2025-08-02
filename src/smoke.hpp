#ifndef SMOKE_HPP_INCLUDED
#define SMOKE_HPP_INCLUDED
//
// smoke.hpp
//
#include "map-types.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

namespace castlecrawl
{

    struct GameConfig;
    struct Context;

    //

    struct SmokeParticle
    {
        SmokeParticle(
            const Context & t_context,
            const sf::Texture & t_texture,
            const sf::IntRect & t_textureRect,
            const MapPos_t & t_mapPos);

        void update(const Context & t_context, const float t_elapsedTimeSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const;
        void reset(const Context & t_context);

        MapPos_t map_pos;
        float move_speed;
        float scale_speed;
        float alpha_reduction_timer_sec;
        float alpha_reduction_interval_sec;
        sf::Sprite sprite;
    };

    //

    struct SmokeEffect
    {
        SmokeEffect(
            const Context & t_context,
            const sf::Texture & t_texture,
            const sf::IntRect & t_textureRect,
            const MapPos_t & t_mapPos);

        void update(const Context & t_context, const float t_elapsedTimeSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const;

        std::vector<SmokeParticle> particles;
    };

    //

    class SmokeEffectManager
    {
      public:
        SmokeEffectManager();

        void setup(const GameConfig & t_config);
        void update(const Context & t_context, const float t_elapsedTimeSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const;

        void add(const Context & t_context, const MapPos_t & t_mapPos);
        void remove(const MapPos_t & t_mapPos);
        inline void clear() { m_effects.clear(); }

      private:
        [[nodiscard]] const sf::IntRect imageRect(const std::size_t index) const;

      private:
        sf::Texture m_texture;
        std::vector<SmokeEffect> m_effects;
    };

} // namespace castlecrawl

#endif // SMOKE_HPP_INCLUDED