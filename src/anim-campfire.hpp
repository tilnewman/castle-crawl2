#ifndef ANIM_CAMPFIRE_HPP_INCLUDED
#define ANIM_CAMPFIRE_HPP_INCLUDED
//
// anim-campfire.hpp
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

    struct CampfireAnimation
    {
        CampfireAnimation(
            const MapPos_t & t_mapPos,
            const std::size_t frameIndex,
            const sf::Texture & t_texture,
            const sf::IntRect & t_textureRect);

        std::size_t frame_index;
        MapPos_t map_pos;
        sf::Sprite sprite;
    };

    //

    class CampfireAnimationManager
    {
      public:
        CampfireAnimationManager();

        void setup(const GameConfig & t_config);
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

        void add(const Context & t_context, const MapPos_t & t_mapPos);
        void remove(const Context & t_context, const MapPos_t & t_mapPos);
        inline void clear() { m_animations.clear(); }
        [[nodiscard]] inline std::size_t particleCount() const { return m_animations.size(); }

      private:
        [[nodiscard]] const sf::IntRect frameRect(const std::size_t index) const;

      private:
        sf::Texture m_texture;
        std::vector<CampfireAnimation> m_animations;
        float m_frameTimeSec;
        const std::size_t m_frameCount;
    };

} // namespace castlecrawl

#endif // ANIM_CAMPFIRE_HPP_INCLUDED