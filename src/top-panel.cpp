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
        , m_castleTexture{}
        , m_castleSprite{ m_castleTexture }
        , m_healthBar{}
        , m_manaBar{}
        , m_experienceBar{}
    {}

    void TopPanel::setup(const Context & t_context)
    {
        // title image
        util::TextureLoader::load(
            m_titleTexture, (t_context.config.media_path / "image" / "title.png"), true);

        m_titleSprite.setTexture(m_titleTexture, true);

        sf::FloatRect titleBounds = t_context.layout.topRegion();
        titleBounds.size.x *= 0.3f;
        util::fitAndCenterInside(m_titleSprite, titleBounds);
        m_titleSprite.setPosition({ 0.0f, m_titleSprite.getGlobalBounds().position.y });

        // castle image
        util::TextureLoader::load(
            m_castleTexture, (t_context.config.media_path / "image" / "castle.png"), true);

        m_castleSprite.setTexture(m_castleTexture, true);
        m_castleSprite.setColor(sf::Color(255, 255, 255, 32));

        sf::FloatRect castleBounds = t_context.layout.topRegion();
        castleBounds.size.y -= util::bottom(m_experienceBar.bounds());
        util::fitAndCenterInside(m_castleSprite, castleBounds);

        m_castleSprite.setPosition(
            { (util::right(t_context.layout.topRegion()) - m_castleSprite.getGlobalBounds().size.x),
              0.0f });

        // info bars
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
        t_target.draw(m_castleSprite, t_states);
        t_target.draw(m_healthBar, t_states);
        t_target.draw(m_manaBar, t_states);
        t_target.draw(m_experienceBar, t_states);
    }

} // namespace castlecrawl
