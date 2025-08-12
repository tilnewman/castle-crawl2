// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// inferno.cpp
//
#include "inferno.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "random.hpp"
#include "sfml-util.hpp"
#include "smoke.hpp"
#include "texture-loader.hpp"

#include <algorithm>

namespace castlecrawl
{

    InfernoAnimation::InfernoAnimation(
        const Context & t_context, const sf::Texture & t_texture, const MapPos_t & t_mapPos)
        : is_horiz_flipped{ t_context.random.boolean() }
        , map_pos{ t_mapPos }
        , frame_time_sec{ 0.0f }
        , time_between_frames_sec{ t_context.random.fromTo(0.02f, 0.06f) }
        , frame_index{ t_context.random.zeroToOneLessThan(frame_count) }
        , sprite{ t_texture, frameRect(frame_index) }
    {
        const sf::Vector2f cellScreenPos =
            t_context.maps.current().mapPosToScreenPos(t_context, map_pos);

        const sf::Vector2f cellSize = t_context.layout.cellSize();

        util::fitAndCenterInside(sprite, { cellScreenPos, cellSize });

        if (is_horiz_flipped)
        {
            sprite.scale({ -1.0f, 1.0f });
            sprite.move({ cellSize.x, 0.0f });
        }
    }

    void InfernoAnimation::update(const Context &, const float t_elapsedTimeSec)
    {
        frame_time_sec += t_elapsedTimeSec;
        if (frame_time_sec > time_between_frames_sec)
        {
            frame_time_sec -= time_between_frames_sec;

            ++frame_index;
            if (frame_index >= frame_count)
            {
                frame_index = 0;
            }

            sprite.setTextureRect(frameRect(frame_index));
        }
    }

    void InfernoAnimation::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(sprite, t_states);
    }

    const sf::IntRect InfernoAnimation::frameRect(const std::size_t t_index) const
    {
        sf::IntRect rect{ { 0, 0 }, { 64, 64 } };

        rect.position.x = ((static_cast<int>(t_index) % 8) * 64);
        rect.position.y = ((static_cast<int>(t_index) / 8) * 64);

        // the logic above is perfect, but a flaw in the art means we need to add one
        // maybe someday I'll spend the hour in photoshop required to fix the art...
        ++rect.position.y;

        return rect;
    }

    //

    InfernoAnimationManager::InfernoAnimationManager()
        : m_texture{}
    {}

    void InfernoAnimationManager::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(
            m_texture,
            (t_config.media_path / "image" / "animation" / "inferno-64x" / "inferno.png"),
            false);
    }

    void InfernoAnimationManager::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        for (InfernoAnimation & animation : m_animations)
        {
            animation.update(t_context, t_elapsedTimeSec);
        }
    }

    void InfernoAnimationManager::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const InfernoAnimation & animation : m_animations)
        {
            animation.draw(t_target, t_states);
        }
    }

    void InfernoAnimationManager::add(const Context & t_context, const MapPos_t & t_mapPos)
    {
        m_animations.emplace_back(t_context, m_texture, t_mapPos);
        t_context.anim.smoke().add(t_context, t_mapPos);
    }

    void InfernoAnimationManager::remove(const Context & t_context, const MapPos_t & t_mapPos)
    {
        std::erase_if(m_animations, [&](const InfernoAnimation & animation) {
            return (t_mapPos == animation.map_pos);
        });

        t_context.anim.smoke().remove(t_mapPos);
    }

} // namespace castlecrawl