#ifndef ANIM_MUSIC_NOTES_HPP_INCLUDED
#define ANIM_MUSIC_NOTES_HPP_INCLUDED
//
// anim-music-notes.hpp
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

    struct NoteParticle
    {
        NoteParticle(
            const Context & t_context,
            const sf::Texture & t_texture,
            const sf::IntRect & t_textureRect,
            const MapPos_t & t_mapPos);

        bool update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

        bool is_alive;
        float speed;
        float age_sec;
        float age_max_sec;
        sf::Sprite sprite;
    };

    //

    class MusicAnimation
    {
      public:
        MusicAnimation(const Context & t_context, const MapPos_t & t_mapPos);

        [[nodiscard]] constexpr bool isAlive() const noexcept { return m_isAlive; }

        bool update(
            const Context & t_context, const sf::Texture & t_texture, const float t_elapsedSec);

        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

        [[nodiscard]] constexpr std::size_t particleCount() const noexcept
        {
            return m_particles.size();
        }

      private:
        const sf::IntRect randomNoteRect(const Context & t_context) const;

      private:
        bool m_isAlive;
        float m_timeBetweenEmit;
        float m_emitTimeSec;
        float m_ageSec;
        MapPos_t m_mapPos;
        std::vector<NoteParticle> m_particles;
    };

    //

    class MusicAnimationManager
    {
      public:
        MusicAnimationManager();

        void setup(const GameConfig & t_config);
        void update(const Context & t_context, const float t_elapsedSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;
        void add(const Context & t_context, const MapPos_t & t_mapPos);
        constexpr void clear() noexcept { m_animations.clear(); }
        [[nodiscard]] std::size_t particleCount() const;

      private:
        sf::Texture m_texture;
        std::vector<MusicAnimation> m_animations;
    };

} // namespace castlecrawl

#endif // ANIM_MUSIC_NOTES_HPP_INCLUDED