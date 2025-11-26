// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// anim-sparkle-particle.cpp
//
#include "anim-sparkle-particle.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "random.hpp"
#include "sfml-defaults.hpp"
#include "texture-loader.hpp"

namespace castlecrawl
{

    SparkleParticle::SparkleParticle()
        : is_alive{ false }
        , age_sec{ 0.0f }
        , age_max_sec{ 0.0f }
        , rotation_speed{ 0.0f }
        , full_scale{ 0.0f }
        , sprite{ util::SfmlDefaults::instance().texture() }
    {}

    void SparkleParticle::update(const Context &, const float t_elapsedSec)
    {
        age_sec += t_elapsedSec;
        if (age_sec > age_max_sec)
        {
            is_alive = false;
            return;
        }

        const float halfAgeMax = (age_max_sec * 0.5f);
        if (age_sec < halfAgeMax)
        {
            // growing
            const float frameScale = (full_scale * util::mapToRatio(age_sec, 0.0f, halfAgeMax));
            sprite.setScale({ frameScale, frameScale });
        }
        else
        {
            // shrinking
            const float frameScale =
                (full_scale * (1.0f - util::mapToRatio(age_sec, halfAgeMax, age_max_sec)));

            sprite.setScale({ frameScale, frameScale });
        }

        sprite.rotate(sf::degrees(rotation_speed * t_elapsedSec));
    }

    void SparkleParticle::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_states.blendMode = sf::BlendAdd;
        t_target.draw(sprite, t_states);
    }

    //

    SparkleParticleEffect::SparkleParticleEffect()
        : map_pos{ -1, -1 } // both are negative to make it invalid by default
        , particles{}
    {}

    void SparkleParticleEffect::update(const Context & t_context, const float t_elapsedSec)
    {
        for (SparkleParticle & particle : particles)
        {
            particle.update(t_context, t_elapsedSec);

            if (!particle.is_alive)
            {
                resetParticle(t_context, particle);
            }
        }
    }

    void SparkleParticleEffect::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const SparkleParticle & particle : particles)
        {
            particle.draw(t_target, t_states);
        }
    }

    void SparkleParticleEffect::resetParticle(
        const Context & t_context, SparkleParticle & particle) const
    {
        particle.is_alive       = true;
        particle.age_sec        = 0.0f;
        particle.age_max_sec    = t_context.random.fromTo(1.0f, 3.0f);
        particle.rotation_speed = t_context.random.fromTo(-50.0f, 50.0f);

        particle.sprite.setRotation(sf::degrees(t_context.random.fromTo(0.0f, 360.0f)));

        const sf::Vector2f screenPosOfCellCorner =
            t_context.maps.current().mapPosToScreenPos(t_context, map_pos);

        const sf::Vector2f cellSize = t_context.layout.cellSize();

        util::fit(particle.sprite, { screenPosOfCellCorner, cellSize });
        const float scale = t_context.random.fromTo(0.1f, 0.25f);
        particle.sprite.scale({ scale, scale });
        particle.full_scale = scale;

        const sf::Vector2f screenPos{
            screenPosOfCellCorner.x + t_context.random.fromTo(0.0f, cellSize.x),
            screenPosOfCellCorner.y + t_context.random.fromTo(0.0f, cellSize.y)
        };

        particle.sprite.setPosition(screenPos);
    }

    //

    SparkleParticleManager::SparkleParticleManager()
        : m_texture{}
        , m_effects{}
    {}

    void SparkleParticleManager::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(m_texture, (t_config.media_path / "image" / "star.png"), true);
    }

    void SparkleParticleManager::update(const Context & t_context, const float t_elapsedSec)
    {
        for (SparkleParticleEffect & effect : m_effects)
        {
            effect.update(t_context, t_elapsedSec);
        }
    }

    void SparkleParticleManager::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const SparkleParticleEffect & effect : m_effects)
        {
            effect.draw(t_target, t_states);
        }
    }

    void SparkleParticleManager::add(const Context & t_context, const MapPos_t & t_mapPos)
    {
        SparkleParticleEffect effect;
        effect.map_pos = t_mapPos;

        const std::size_t sparkleParticleCount = t_context.random.fromTo(4_st, 7_st);
        for (std::size_t i{ 0 }; i < sparkleParticleCount; ++i)
        {
            SparkleParticle particle;
            particle.sprite.setTexture(m_texture);

            const int randomImageIndex = t_context.random.fromTo(0, 3);
            if (0 == randomImageIndex)
            {
                particle.sprite.setTextureRect({ { 0, 0 }, { 128, 128 } });
            }
            else if (1 == randomImageIndex)
            {
                particle.sprite.setTextureRect({ { 128, 0 }, { 128, 128 } });
            }
            else if (2 == randomImageIndex)
            {
                particle.sprite.setTextureRect({ { 0, 128 }, { 128, 128 } });
            }
            else
            {
                particle.sprite.setTextureRect({ { 128, 128 }, { 128, 128 } });
            }

            util::setOriginToCenter(particle.sprite);
            particle.sprite.setColor(sf::Color(255, 220, 127));

            effect.particles.push_back(particle);
        }

        m_effects.push_back(effect);
    }

    void SparkleParticleManager::remove(const MapPos_t & t_mapPos)
    {
        std::erase_if(m_effects, [&](const SparkleParticleEffect & effect) {
            return (t_mapPos == effect.map_pos);
        });
    }

    std::size_t SparkleParticleManager::particleCount() const
    {
        std::size_t count = 0;

        for (const SparkleParticleEffect & effect : m_effects)
        {
            count += effect.particles.size();
        }

        return count;
    }

} // namespace castlecrawl
