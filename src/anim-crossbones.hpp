#ifndef ANIM_CROSSBONES_HPP_INCLUDED
#define ANIM_CROSSBONES_HPP_INCLUDED
//
// anim-crossbones.hpp
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

    struct CrossbonesParticle
    {
        CrossbonesParticle(
            const Context & t_context, const sf::Texture & t_texture, const MapPos_t & t_mapPos);

        bool update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        
        bool is_alive;
        float age_sec;
        float age_max_sec;
        sf::Sprite sprite;
    };

    //

    class CrossbonesAnimationManager
    {
      public:
        CrossbonesAnimationManager();

        void setup(const GameConfig & t_config);
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void add(const Context & t_context, const MapPos_t & t_mapPos);
        inline void clear() { m_particles.clear(); }
        [[nodiscard]] inline std::size_t particleCount() const { return m_particles.size(); }

      private:
        sf::Texture m_texture;
        std::vector<CrossbonesParticle> m_particles;
    };

} // namespace castlecrawl

#endif // ANIM_CROSSBONES_HPP_INCLUDED