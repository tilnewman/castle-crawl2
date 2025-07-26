// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// splat-images.cpp
//
#include "splat-images.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "random.hpp"
#include "texture-loader.hpp"

namespace castlecrawl
{

    SplatImages::SplatImages()
        : m_texture{}
        , m_sprite1{ m_texture }
        , m_sprite2{ m_texture }
        , m_sprite3{ m_texture }
        , m_sprite4{ m_texture }
        , m_sprite5{ m_texture }
        , m_sprite6{ m_texture }
    {}

    void SplatImages::setup(const GameConfig & t_config)
    {
        util::TextureLoader::load(m_texture, (t_config.media_path / "image" / "splat.png"), true);

        m_sprite1.setTextureRect({ { 0, 0 }, { 64, 64 } });
        m_sprite2.setTextureRect({ { 64, 0 }, { 64, 64 } });
        m_sprite3.setTextureRect({ { 128, 0 }, { 64, 64 } });
        m_sprite4.setTextureRect({ { 0, 64 }, { 64, 64 } });
        m_sprite5.setTextureRect({ { 64, 64 }, { 64, 64 } });
        m_sprite6.setTextureRect({ { 128, 64 }, { 64, 64 } });

        m_sprite1.setColor(sf::Color(255, 0, 0, 127));
        m_sprite2.setColor(sf::Color(255, 0, 0, 127));
        m_sprite3.setColor(sf::Color(255, 0, 0, 127));
        m_sprite4.setColor(sf::Color(255, 0, 0, 127));
        m_sprite5.setColor(sf::Color(255, 0, 0, 127));
        m_sprite6.setColor(sf::Color(255, 0, 0, 127));
    }

    const sf::Sprite & SplatImages::getRandom(const Context & t_context) const
    {
        const int randomNumber = t_context.random.fromTo(1, 6);

        if (1 == randomNumber)
        {
            return m_sprite1;
        }
        else if (2 == randomNumber)
        {
            return m_sprite2;
        }
        else if (3 == randomNumber)
        {
            return m_sprite3;
        }
        else if (4 == randomNumber)
        {
            return m_sprite4;
        }
        else if (5 == randomNumber)
        {
            return m_sprite5;
        }
        else
        {
            return m_sprite6;
        }
    }

} // namespace castlecrawl
