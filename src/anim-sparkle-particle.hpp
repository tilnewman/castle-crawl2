#ifndef ANIM_SPARKLE_PARTICLE_HPP_INCLUDE
#define ANIM_SPARKLE_PARTICLE_HPP_INCLUDE
//
// anim-sparkle-particle.hpp
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

    struct SparkleParticle
    {
        SparkleParticle();

        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

        bool is_alive;
        float age_sec;
        float age_max_sec;
        float rotation_speed;
        float full_scale;
        sf::Sprite sprite;
    };

    //

    struct SparkleParticleEffect
    {
        SparkleParticleEffect();

        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void resetParticle(const Context & t_context, SparkleParticle & particle) const;

        MapPos_t map_pos;
        std::vector<SparkleParticle> particles;
    };

    //

    class SparkleParticleManager
    {
      public:
        SparkleParticleManager();

        void setup(const GameConfig & t_config);
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void add(const Context & t_context, const MapPos_t & t_mapPos);
        void remove(const MapPos_t & t_mapPos);
        inline void clear() { m_effects.clear(); }
        [[nodiscard]] std::size_t particleCount() const;

      private:
        sf::Texture m_texture;
        std::vector<SparkleParticleEffect> m_effects;
    };

} // namespace castlecrawl

#endif // ANIM_SPARKLE_PARTICLE_HPP_INCLUDE