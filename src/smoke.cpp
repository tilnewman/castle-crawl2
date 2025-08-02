// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// smoke.cpp
//
#include "smoke.hpp"

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

    SmokeParticle::SmokeParticle(
        const Context & t_context,
        const sf::Texture & t_texture,
        const sf::IntRect & t_textureRect,
        const MapPos_t & t_mapPos)
        : map_pos{ t_mapPos }
        , move_speed{ 0.0f }
        , scale_speed{ 0.0f }
        , alpha_reduction_timer_sec{ 0.0f }
        , alpha_reduction_interval_sec{ 0.0f }
        , sprite{ t_texture, t_textureRect }
    {
        reset(t_context);
    }

    void SmokeParticle::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        sprite.move({ 0.0f, -(move_speed * t_elapsedTimeSec) });

        const float scale{ 1.0f + (scale_speed * std::min(t_elapsedTimeSec, (1.0f / 60.0f))) };
        sprite.scale({ scale, scale });

        alpha_reduction_timer_sec += t_elapsedTimeSec;
        if (alpha_reduction_timer_sec > alpha_reduction_interval_sec)
        {
            alpha_reduction_timer_sec -= alpha_reduction_interval_sec;

            sf::Color color = sprite.getColor();
            --color.a;
            sprite.setColor(color);

            if (0 == color.a)
            {
                reset(t_context);
            }
        }
    }

    void SmokeParticle::draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        t_target.draw(sprite, t_states);
    }

    void SmokeParticle::reset(const Context & t_context)
    {
        // rotation
        util::setOriginToCenter(sprite);
        sprite.setRotation(sf::degrees(t_context.random.fromTo(0.0f, 360.0f)));

        // start position
        const sf::Vector2f cellScreenPos =
            t_context.maps.current().mapPosToScreenPos(t_context, map_pos);

        const sf::Vector2f cellSize = t_context.layout.cellSize();
        sf::Vector2f screenPos{ cellScreenPos + (cellSize * 0.5f) };
        screenPos.x += t_context.random.fromTo(-10.0f, 10.0f);
        screenPos.y += t_context.random.fromTo(-10.0f, 10.0f);
        sprite.setPosition(screenPos);

        // fade out speed
        sprite.setColor(
            sf::Color(255, 255, 255, t_context.random.fromTo(uint8_t(64), uint8_t(192))));

        alpha_reduction_timer_sec    = 0.0f;
        alpha_reduction_interval_sec = t_context.random.fromTo(0.001f, 0.01f);

        // lift speed
        move_speed = t_context.random.fromTo(25.0f, 50.0f);

        // starting size
        util::fit(sprite, cellSize);
        const float scale = t_context.random.fromTo(0.1f, 0.2f);
        sprite.scale({ scale, scale });

        // grow speed
        scale_speed = t_context.random.fromTo(1.0f, 1.2f);
    }

    //

    SmokeEffect::SmokeEffect(
        const Context & t_context,
        const sf::Texture & t_texture,
        const sf::IntRect & t_textureRect,
        const MapPos_t & t_mapPos)
        : particles{}
    {
        for (std::size_t i{ 0 }; i < 30; ++i)
        {
            particles.emplace_back(t_context, t_texture, t_textureRect, t_mapPos);
        }
    }

    void SmokeEffect::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        for (SmokeParticle & particle : particles)
        {
            particle.update(t_context, t_elapsedTimeSec);
        }
    }

    void SmokeEffect::draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        for (const SmokeParticle & particle : particles)
        {
            particle.draw(t_target, t_states);
        }
    }

    //

    SmokeEffectManager::SmokeEffectManager()
        : m_texture{}
        , m_effects{}
    {}

    void SmokeEffectManager::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(m_texture, (t_config.media_path / "image" / "smoke.png"), true);
    }

    void SmokeEffectManager::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        for (SmokeEffect & effect : m_effects)
        {
            effect.update(t_context, t_elapsedTimeSec);
        }
    }

    void SmokeEffectManager::draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        for (const SmokeEffect & effect : m_effects)
        {
            effect.draw(t_target, t_states);
        }
    }

    void SmokeEffectManager::add(const Context & t_context, const MapPos_t & t_mapPos)
    {
        remove(t_mapPos);

        m_effects.emplace_back(
            t_context, m_texture, imageRect(t_context.random.fromTo(0_st, 3_st)), t_mapPos);
    }

    void SmokeEffectManager::remove(const MapPos_t & t_mapPos)
    {
        std::erase_if(m_effects, [&](const SmokeEffect & animation) {
            return (t_mapPos == animation.particles.front().map_pos);
        });
    }

    const sf::IntRect SmokeEffectManager::imageRect(const std::size_t index) const
    {
        // clang-format off
        switch (index)
        {
            case 0: { return { {  0,  0 }, { 64, 64 } }; }
            case 1: { return { { 64,  0 }, { 64, 64 } }; }
            case 2: { return { {  0, 64 }, { 64, 64 } }; }
            default:{ return { { 64, 64 }, { 64, 64 } }; }
        }
        // clang-format on
    }

} // namespace castlecrawl