// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// anim-music-notes.cpp
//
#include "anim-music-notes.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "random.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

#include <algorithm>

namespace castlecrawl
{

    NoteParticle::NoteParticle(
        const Context & t_context,
        const sf::Texture & t_texture,
        const sf::IntRect & t_textureRect,
        const MapPos_t & t_mapPos)
        : is_alive{ true }
        , speed{ t_context.random.fromTo(20.0f, 40.0f) }
        , age_sec{ 0.0f }
        , age_max_sec{ t_context.random.fromTo(0.5f, 1.5f) }
        , sprite{ t_texture, t_textureRect }
    {
        const sf::FloatRect mapScreenRect{ t_context.maps.current().mapPosToScreenPos(
                                               t_context, t_mapPos),
                                           t_context.layout.cellSize() };

        util::fitAndCenterInside(
            sprite,
            util::scaleRectInPlaceCopy(mapScreenRect, t_context.random.fromTo(0.25f, 0.75f)));

        // TODO random vary the starting position a bit
    }

    bool NoteParticle::update(const Context &, const float t_elapsedSec)
    {
        age_sec += t_elapsedSec;
        if (age_sec < age_max_sec)
        {
            const int alpha{ 255 - util::map(age_sec, 0.0f, age_max_sec, 0, 255) };
            sf::Color color{ sprite.getColor() };
            color.a = static_cast<uint8_t>(alpha);
            sprite.setColor(color);

            sprite.move({ 0.0f, -(speed * t_elapsedSec) });

            // TODO sway back and forth
            return false;
        }
        else
        {
            is_alive = false;
            return true;
        }
    }

    void NoteParticle::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_states.blendMode = sf::BlendAdd;
        t_target.draw(sprite, t_states);
    }

    //

    MusicAnimation::MusicAnimation(const Context &, const MapPos_t & t_mapPos)
        : m_isAlive{ true }
        , m_timeBetweenEmit{ 0.0f }
        , m_emitTimeSec{ 0.0f }
        , m_ageSec{ 0.0f }
        , m_mapPos{ t_mapPos }
        , m_particles{}
    {}

    bool MusicAnimation::update(
        const Context & t_context, const sf::Texture & t_texture, const float t_elapsedSec)
    {
        m_ageSec += t_elapsedSec;
        if (m_ageSec < 3.0f) // all music animations last this long
        {
            m_emitTimeSec += t_elapsedSec;
            if (m_emitTimeSec > m_timeBetweenEmit)
            {
                m_emitTimeSec -= m_timeBetweenEmit;
                m_timeBetweenEmit = t_context.random.fromTo(0.15f, 0.35f);
                m_particles.emplace_back(t_context, t_texture, randomNoteRect(t_context), m_mapPos);
            }
        }

        bool didAnyParticlesDie{ false };
        for (NoteParticle & particle : m_particles)
        {
            if (particle.update(t_context, t_elapsedSec))
            {
                didAnyParticlesDie = true;
            }
        }

        if (didAnyParticlesDie)
        {
            std::erase_if(
                m_particles, [](const NoteParticle & particle) { return !particle.is_alive; });
        }

        return m_particles.empty();
    }

    void MusicAnimation::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const NoteParticle & particle : m_particles)
        {
            particle.draw(t_target, t_states);
        }
    }

    const sf::IntRect MusicAnimation::randomNoteRect(const Context & t_context) const
    {
        const int index{ t_context.random.fromTo(0, 4) };

        // clang-format off
        switch (index)
        {
            case 0:     { return {{   0,   0 }, {  84, 126 }}; }
            case 1:     { return {{  87,   0 }, {  76, 128 }}; }
            case 2:     { return {{ 192,   0 }, {  64, 128 }}; }
            case 3:     { return {{   8, 128 }, { 120, 128 }}; }
            default:    { return {{ 136, 144 }, { 112,  96 }}; }
        }
        // clang-format on
    }

    //

    MusicAnimationManager::MusicAnimationManager()
        : m_animations{}
    {}

    void MusicAnimationManager::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(m_texture, (t_config.media_path / "image" / "notes.png"), true);
    }

    void MusicAnimationManager::update(const Context & t_context, const float t_elapsedSec)
    {
        bool didAnyAnimationsDie{ false };
        for (MusicAnimation & animation : m_animations)
        {
            if (animation.update(t_context, m_texture, t_elapsedSec))
            {
                didAnyAnimationsDie = true;
            }
        }

        if (didAnyAnimationsDie)
        {
            std::erase_if(m_animations, [](const MusicAnimation & animation) {
                return !animation.isAlive();
            });
        }
    }

    void MusicAnimationManager::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const MusicAnimation & animation : m_animations)
        {
            animation.draw(t_target, t_states);
        }
    }

    void MusicAnimationManager::add(const Context & t_context, const MapPos_t & t_mapPos)
    {
        m_animations.emplace_back(t_context, t_mapPos);
    }

    std::size_t MusicAnimationManager::particleCount() const
    {
        std::size_t count{ 0 };
        for (const MusicAnimation & animation : m_animations)
        {
            count += animation.particleCount();
        }

        return count;
    }

} // namespace castlecrawl