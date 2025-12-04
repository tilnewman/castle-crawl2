#ifndef ANIM_DUST_PARTICLE_HPP_INCLUDED
#define ANIM_DUST_PARTICLE_HPP_INCLUDED
//
// anim-dust-particle.hpp
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

    struct DustParticleEffect
    {
        DustParticleEffect();

        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

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
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void add(const Context & t_context, const MapPos_t & t_mapPos);
        // there is no remove() because they remove themselves in update()
        constexpr void clear() noexcept { m_effects.clear(); }

        [[nodiscard]] constexpr std::size_t particleCount() const noexcept
        {
            return m_effects.size();
        }

      private:
        sf::Texture m_texture;
        std::vector<DustParticleEffect> m_effects;
    };

} // namespace castlecrawl

#endif // ANIM_DUST_PARTICLE_HPP_INCLUDED