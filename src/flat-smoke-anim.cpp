// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// flat-smoke-anim.cpp
//
#include "flat-smoke-anim.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

#include <algorithm>

namespace castlecrawl
{

    FlatSmokeAnim::FlatSmokeAnim(
        const sf::Texture & t_texture,
        const sf::IntRect & t_textureRect,
        const sf::FloatRect & t_screenRect)
        : is_alive{ true }
        , elapsed_sec{ 0.0f }
        , frame_index{ 0 }
        , screen_pos{ 0.0f, 0.0f }
        , sprite{ t_texture, t_textureRect }
    {
        util::fitAndCenterInside(sprite, t_screenRect);
        screen_pos = sprite.getGlobalBounds().position;
        sprite.setColor(sf::Color(255, 255, 255, 200));
    }

    //

    FlatSmokeAnimManager::FlatSmokeAnimManager()
        : m_animations{}
        , m_timeBetweenFramesSec{ 0.05f }
        , m_texture{}
    {}

    void FlatSmokeAnimManager::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(
            m_texture,
            (t_config.media_path / "image" / "animation" / "flat-smoke-64x" / "flat-smoke.png"),
            true);
    }

    void FlatSmokeAnimManager::update(const Context & t_context, const float t_elapsedTimeSec)
    {
        for (FlatSmokeAnim & animation : m_animations)
        {
            animation.elapsed_sec += t_elapsedTimeSec;
            if (animation.elapsed_sec > m_timeBetweenFramesSec)
            {
                animation.elapsed_sec -= m_timeBetweenFramesSec;

                const std::size_t frameCount{ 25 };
                if (++animation.frame_index >= frameCount)
                {
                    animation.frame_index = 0;
                    animation.is_alive    = false;
                }

                animation.sprite.setTextureRect(frameRect(animation.frame_index));

                const float vertOffset = util::map(
                    animation.frame_index, 0_st, frameCount, 0.0f, t_context.layout.cellSize().y);

                animation.sprite.setPosition(
                    { animation.screen_pos.x, (animation.screen_pos.y + vertOffset) });
            }
        }

        std::erase_if(
            m_animations, [](const FlatSmokeAnim & animation) { return !animation.is_alive; });
    }

    void FlatSmokeAnimManager::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const FlatSmokeAnim & animation : m_animations)
        {
            t_target.draw(animation.sprite, t_states);
        }
    }

    const sf::IntRect FlatSmokeAnimManager::frameRect(const std::size_t t_index) const
    {
        return sf::IntRect{ { ((static_cast<int>(t_index) % 5) * 64),
                              ((static_cast<int>(t_index) / 5) * 64) },
                            { 64, 64 } };
    }

    void FlatSmokeAnimManager::add(const Context & t_context, const MapPos_t & t_mapPos)
    {
        const sf::Vector2f cellSize{ t_context.layout.cellSize() };
        const sf::Vector2f screenSize{ (cellSize * 1.5f) };

        sf::Vector2f screenPos{ (
            t_context.maps.current().mapPosToScreenPos(t_context, t_mapPos) + (cellSize * 0.5f)) };

        screenPos.x -= (screenSize.x * 0.5f);
        screenPos.y -= (cellSize.y * 1.2f);

        m_animations.emplace_back(m_texture, frameRect(0), sf::FloatRect{ screenPos, screenSize });
    }

} // namespace castlecrawl