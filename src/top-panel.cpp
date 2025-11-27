// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// top-panel.cpp
//
#include "top-panel.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

namespace castlecrawl
{

    TopPanel::TopPanel()
        : m_titleTexture{}
        , m_titleSprite{ m_titleTexture }
        , m_healthBar{}
        , m_manaBar{}
        , m_experienceBar{}
    {}

    void TopPanel::setup(const Context & t_context)
    {
        util::TextureLoader::load(
            m_titleTexture, (t_context.config.media_path / "image" / "title.png"), true);

        m_titleSprite.setTexture(m_titleTexture, true);

        const sf::FloatRect topRect{ t_context.layout.topRect() };

        util::fit(m_titleSprite, { (topRect.size.x * 0.3f), topRect.size.y });

        // m_titleSprite.setPosition(
        //     { ((topRect.size.x * 0.5f) - (m_titleSprite.getGlobalBounds().size.x * 0.5f)), 0.0f
        //     });

        m_healthBar.setup(t_context);
        m_manaBar.setup(t_context);
        m_experienceBar.setup(t_context);
    }

    void TopPanel::update(const Context & t_context)
    {
        m_healthBar.update(t_context);
        m_manaBar.update(t_context);
        m_experienceBar.setup(t_context);
    }

    void TopPanel::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(m_titleSprite, t_states);
        t_target.draw(m_healthBar, t_states);
        t_target.draw(m_manaBar, t_states);
        t_target.draw(m_experienceBar, t_states);
    }

} // namespace castlecrawl
