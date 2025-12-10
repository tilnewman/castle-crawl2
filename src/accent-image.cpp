// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// accent-image.cpp
//
#include "accent-image.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "random.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

#include <string>

namespace castlecrawl
{

    AccentImage::AccentImage()
        : m_texture{}
        , m_sprite{ m_texture }
    {}

    void AccentImage::setup(const Context & t_context, const sf::FloatRect & t_rect)
    {
        std::string fileName = "accent-";
        fileName += std::to_string(t_context.random.fromTo(0, 46));
        fileName += ".png";

        util::TextureLoader::load(
            m_texture, (t_context.config.media_path / "image/accent" / fileName), true);

        m_sprite.setTexture(m_texture, true);
        m_sprite.setColor(sf::Color(255, 255, 255, 16));
        util::fitAndCenterInside(m_sprite, t_rect);

        if (t_context.random.boolean())
        {
            m_sprite.scale({ -1.0f, 1.0f });
            m_sprite.move({ m_sprite.getGlobalBounds().size.x, 0.0f });
        }
    }

    void AccentImage::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_sprite, t_states);
    }

} // namespace castlecrawl
