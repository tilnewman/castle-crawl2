// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// campfire.cpp
//
#include "campfire.hpp"

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

    CampfireAnimation::CampfireAnimation(
        const MapPos_t & t_mapPos,
        const std::size_t frameIndex,
        const sf::Texture & t_texture,
        const sf::IntRect & t_textureRect)
        : frame_index{ frameIndex }
        , map_pos{ t_mapPos }
        , sprite{ t_texture, t_textureRect }
    {}

    //

    CampfireAnimationManager::CampfireAnimationManager()
        : m_texture{}
        , m_animations{}
        , m_frameTimeSec{ 0.0f }
        , m_frameCount{ 8 }
    {}

    void CampfireAnimationManager::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(
            m_texture, (t_config.media_path / "image" / "campfire.png"), true);
    }

    void CampfireAnimationManager::update(const Context &, const float t_elapsedTimeSec)
    {
        m_frameTimeSec += t_elapsedTimeSec;

        const float timePerFrameSec = 0.1f;
        if (m_frameTimeSec > timePerFrameSec)
        {
            m_frameTimeSec -= timePerFrameSec;

            for (CampfireAnimation & animation : m_animations)
            {
                ++animation.frame_index;
                if (animation.frame_index >= m_frameCount)
                {
                    animation.frame_index = 0;
                }

                animation.sprite.setTextureRect(frameRect(animation.frame_index));
            }
        }
    }

    void
        CampfireAnimationManager::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const CampfireAnimation & animation : m_animations)
        {
            t_target.draw(animation.sprite, t_states);
        }
    }

    void CampfireAnimationManager::add(const Context & t_context, const MapPos_t & t_mapPos)
    {
        const std::size_t frameIndex = t_context.random.zeroToOneLessThan(m_frameCount);

        CampfireAnimation & animation =
            m_animations.emplace_back(t_mapPos, frameIndex, m_texture, frameRect(frameIndex));

        const sf::Vector2f screenPos =
            t_context.maps.current().mapPosToScreenPos(t_context, t_mapPos);

        const sf::Vector2f cellSize = t_context.layout.cellSize();

        util::centerInside(animation.sprite, { screenPos, cellSize });

        t_context.anim.smoke().add(t_context, t_mapPos);
    }

    void CampfireAnimationManager::remove(const Context & t_context, const MapPos_t & t_mapPos)
    {
        std::erase_if(m_animations, [&](const CampfireAnimation & animation) {
            return (t_mapPos == animation.map_pos);
        });

        t_context.anim.smoke().remove(t_mapPos);
    }

    const sf::IntRect CampfireAnimationManager::frameRect(const std::size_t index) const
    {
        // clang-format off
        switch (index)
        {
            case 0: { return sf::IntRect{ { 0,  0}, {32, 32} }; }
            case 1: { return sf::IntRect{ {32,  0}, {32, 32} }; }
            case 2: { return sf::IntRect{ {64,  0}, {32, 32} }; }
            case 3: { return sf::IntRect{ { 0, 32}, {32, 32} }; }
            case 4: { return sf::IntRect{ {32, 32}, {32, 32} }; }
            case 5: { return sf::IntRect{ {64, 32}, {32, 32} }; }
            case 6: { return sf::IntRect{ { 0, 64}, {32, 32} }; }
            default:{ return sf::IntRect{ {32, 64}, {32, 32} }; }
        }
        // clang-format on
    }

} // namespace castlecrawl