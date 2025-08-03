#ifndef INFERNO_HPP_INCLUDED
#define INFERNO_HPP_INCLUDED
//
// inferno.hpp
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

    struct InfernoAnimation
    {
        InfernoAnimation(
            const Context & t_context, 
            const sf::Texture & t_texture,
            const MapPos_t & t_mapPos);

        void update(const Context & t_context, const float t_elapsedTimeSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const;
        [[nodiscard]] const sf::IntRect frameRect(const std::size_t t_index) const;

        static inline const std::size_t frame_count{64};

        MapPos_t map_pos;
        float frame_time_sec;
        float time_between_frames_sec;
        std::size_t frame_index;
        sf::Sprite sprite;
    };

    //

    class InfernoAnimationManager
    {
      public:
        InfernoAnimationManager();

        void setup(const GameConfig & t_config);
        void update(const Context & t_context, const float t_elapsedTimeSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const;
        void add(const Context & t_context, const MapPos_t & t_mapPos);
        void remove(const Context & t_context, const MapPos_t & t_mapPos);
        inline void clear() { m_animations.clear(); }

      private:
        sf::Texture m_texture;
        std::vector<InfernoAnimation> m_animations;
    };

} // namespace castlecrawl

#endif // INFERNO_HPP_INCLUDED