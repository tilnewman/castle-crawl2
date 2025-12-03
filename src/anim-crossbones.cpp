// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// anim-crossbones.cpp
//
#include "anim-crossbones.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

namespace castlecrawl
{

    CrossbonesParticle::CrossbonesParticle(
        const Context & t_context, const sf::Texture & t_texture, const MapPos_t & t_mapPos)
        : is_alive{ true }
        , age_sec{ 0.0f }
        , age_max_sec{ 3.0f }
        , sprite{ t_texture }
    {
        const sf::FloatRect mapScreenRect{ t_context.maps.current().mapPosToScreenPos(
                                               t_context, t_mapPos),
                                           t_context.layout.cellSize() };

        util::fitAndCenterInside(sprite, mapScreenRect);

        sprite.setColor(sf::Color(255,255,255,127));
    }

    bool CrossbonesParticle::update(const Context &, const float t_elapsedSec)
    {
        age_sec += t_elapsedSec;
        if (age_sec < age_max_sec)
        {
            const int alpha{ 255 - util::map(age_sec, 0.0f, age_max_sec, 127, 255) };
            sf::Color color{ sprite.getColor() };
            color.a = static_cast<uint8_t>(alpha);
            sprite.setColor(color);
            return false;
        }
        else
        {
            is_alive = false;
            return true;
        }
    }

    void CrossbonesParticle::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_states.blendMode = sf::BlendAdd;
        t_target.draw(sprite, t_states);
    }

    //

    CrossbonesAnimationManager::CrossbonesAnimationManager()
        : m_texture{}
        , m_particles{}
    {}

    void CrossbonesAnimationManager::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(
            m_texture, (t_config.media_path / "image" / "crossbones.png"), true);
    }

    void CrossbonesAnimationManager::update(const Context & t_context, const float t_elapsedSec)
    {
        bool didAnyParticlesDie{ false };
        for (CrossbonesParticle & particle : m_particles)
        {
            if (particle.update(t_context, t_elapsedSec))
            {
                didAnyParticlesDie = true;
            }
        }

        if (didAnyParticlesDie)
        {
            std::erase_if(m_particles, [](const CrossbonesParticle & particle) {
                return !particle.is_alive;
            });
        }
    }

    void CrossbonesAnimationManager::draw(
        sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const CrossbonesParticle & particle : m_particles)
        {
            particle.draw(t_target, t_states);
        }
    }

    void CrossbonesAnimationManager::add(const Context & t_context, const MapPos_t & t_mapPos) 
    {
        m_particles.emplace_back(t_context, m_texture, t_mapPos);
    }

} // namespace castlecrawl
