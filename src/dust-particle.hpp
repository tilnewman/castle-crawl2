#ifndef DUST_PARTICLE_HPP_INCLUDED
#define DUST_PARTICLE_HPP_INCLUDED
//
// dust-particle.hpp
//
#include "map-types.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <SFML/Graphics/Color.hpp>

#include <vector>

namespace castlecrawl
{

    struct GameConfig;
    struct Context;

    //

    struct DustParticleEffect
    {
        DustParticleEffect();

        void update(const Context & t_context, const float t_frameTimeSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const;

        bool is_alive;
        float age_sec;
        float age_max_sec;
        float scale_at_age_max;
        float rotate_speed;
        sf::Sprite sprite;
    };

    //

    class DustParticleManager
    {
      public:
        DustParticleManager();

        void setup(const GameConfig & t_config);
        void update(const Context & t_context, const float t_frameTimeSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const;
        void add(const Context & t_context, const MapPos_t & t_mapPos);
        // there is no remove() because they remove themselves in update()
        void clear() { m_effects.clear(); }

      private:
        std::vector<sf::Texture> m_textures;
        std::vector<DustParticleEffect> m_effects;
    };

} // namespace castlecrawl

#endif // DUST_PARTICLE_HPP_INCLUDED