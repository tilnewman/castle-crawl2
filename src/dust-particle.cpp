// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// dust-particle.cpp
//
#include "dust-particle.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "random.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

#include <algorithm>
#include <limits>

namespace castlecrawl
{

    DustParticleEffect::DustParticleEffect()
        : is_alive{ false }
        , age_sec{ 0.0f }
        , age_max_sec{ 0.0f }
        , scale_at_age_max{ 0.0f }
        , rotate_speed{ 0.0f }
        , sprite{ util::SfmlDefaults::instance().texture() }
    {}

    void DustParticleEffect::update(const Context &, const float t_frameTimeSec)
    {
        age_sec += t_frameTimeSec;
        if (age_sec > age_max_sec)
        {
            is_alive = false;
        }
        else
        {
            sf::Color color = sprite.getColor();

            color.a =
                (uint8_t(255) - util::map(age_sec, 0.0f, age_max_sec, uint8_t(0), uint8_t(255)));

            sprite.setColor(color);

            const float scale = util::map(age_sec, 0.0f, age_max_sec, 1.0f, scale_at_age_max);
            sprite.setScale({ scale, scale });

            sprite.rotate(sf::degrees(rotate_speed * t_frameTimeSec));
        }
    }

    void DustParticleEffect::draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        t_target.draw(sprite, t_states);
    }

    //

    DustParticleManager::DustParticleManager()
        : m_textures{}
        , m_effects{}
    {}

    void DustParticleManager::setup(const GameConfig & t_config)
    {
        m_textures.resize(3);

        util::TextureLoader::load(
            m_textures[0], (t_config.media_path / "image" / "smoke" / "smoke-1.png"), true);

        util::TextureLoader::load(
            m_textures[1], (t_config.media_path / "image" / "smoke" / "smoke-2.png"), true);

        util::TextureLoader::load(
            m_textures[2], (t_config.media_path / "image" / "smoke" / "smoke-3.png"), true);
    }

    void DustParticleManager::update(const Context & t_context, const float t_frameTimeSec)
    {
        for (DustParticleEffect & effect : m_effects)
        {
            effect.update(t_context, t_frameTimeSec);
        }

        std::erase_if(
            m_effects, [&](const DustParticleEffect & effect) { return !effect.is_alive; });
    }

    void DustParticleManager::draw(sf::RenderTarget & t_target, sf::RenderStates & t_states) const
    {
        for (const DustParticleEffect & effect : m_effects)
        {
            effect.draw(t_target, t_states);
        }
    }

    void DustParticleManager::add(const Context & t_context, const MapPos_t & t_mapPos)
    {
        DustParticleEffect effect;
        effect.is_alive         = true;
        effect.age_sec          = 0.0f;
        effect.age_max_sec      = t_context.random.fromTo(0.5f, 2.0f);
        effect.scale_at_age_max = t_context.random.fromTo(1.25f, 2.25f);
        effect.rotate_speed     = t_context.random.fromTo(-50.0f, 50.0f);

        effect.sprite.setTexture(t_context.random.from(m_textures), true);
        util::setOriginToCenter(effect.sprite);

        effect.sprite.setRotation(sf::degrees(t_context.random.fromTo(0.0f, 360.0f)));

        effect.sprite.setPosition(
            t_context.maps.current().mapPosToScreenPos(t_context, t_mapPos) +
            (t_context.layout.cellSize() * 0.5f));

        m_effects.push_back(effect);
    }

} // namespace castlecrawl