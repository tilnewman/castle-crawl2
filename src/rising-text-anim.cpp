// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// rising-text-anim.cpp
//
#include "rising-text-anim.hpp"

#include "context.hpp"
#include "font.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "sfml-util.hpp"

namespace castlecrawl
{

    RisingTextAnimation::RisingTextAnimation(
        const Context & t_context, const sf::Text & t_text, const MapPos_t & t_mapPos)
        : is_alive{ true }
        , age_sec{ 0.0f }
        , map_pos{ t_mapPos }
        , screen_pos{ 0.0f, 0.0f }
        , text{ t_text }
    {
        const sf::Vector2f cellScreenPos =
            t_context.maps.current().mapPosToScreenPos(t_context, t_mapPos);

        const sf::Vector2f cellSize = t_context.layout.cellSize();

        util::centerInside(text, { cellScreenPos, cellSize });
        text.move({ 0.0f, -cellSize.y });

        screen_pos = text.getPosition();
    }

    //

    RisingTextAnimationManager::RisingTextAnimationManager()
        : m_animations{}
    {}

    void RisingTextAnimationManager::update(const Context & t_context, const float t_elapsedSec)
    {
        const float ageMaxSec     = 3.0f;
        const float vertTravelMax = (t_context.layout.cellSize().y * 2.25f);

        for (RisingTextAnimation & animation : m_animations)
        {
            animation.age_sec += t_elapsedSec;
            if (animation.age_sec < ageMaxSec)
            {
                const float vertMove =
                    util::map(animation.age_sec, 0.0f, ageMaxSec, 0.0f, vertTravelMax);

                animation.text.setPosition(
                    { animation.screen_pos.x, (animation.screen_pos.y - vertMove) });

                const int alpha = (255 - util::map(animation.age_sec, 0.0f, ageMaxSec, 0, 255));
                sf::Color color = animation.text.getFillColor();
                color.a         = static_cast<uint8_t>(alpha);
                animation.text.setFillColor(color);
            }
            else
            {
                animation.is_alive = false;
            }
        }

        std::erase_if(m_animations, [](const RisingTextAnimation & animation) {
            return !animation.is_alive;
        });
    }

    void RisingTextAnimationManager::draw(
        sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const RisingTextAnimation & animation : m_animations)
        {
            t_target.draw(animation.text, t_states);
        }
    }

    void RisingTextAnimationManager::add(
        const Context & t_context,
        const std::string & t_message,
        const sf::Color & t_color,
        const MapPos_t & t_mapPos)
    {
        m_animations.emplace_back(
            t_context, t_context.fonts.makeText(FontSize::Medium, t_message, t_color), t_mapPos);
    }

    void RisingTextAnimationManager::remove(const MapPos_t & t_mapPos)
    {
        std::erase_if(m_animations, [&](const RisingTextAnimation & animation) {
            return (animation.map_pos == t_mapPos);
        });
    }

} // namespace castlecrawl