// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// top-panel.cpp
//
#include "top-panel.hpp"

#include "context.hpp"
#include "layout.hpp"
#include "util.hpp"

namespace castlecrawl2
{

    TopPanel::TopPanel()
        : m_titleTexture()
        , m_titleSprite()
    {}

    void TopPanel::setup(const Context & context)
    {
        m_titleTexture.loadFromFile((context.config.media_path / "image" / "title.png").string());
        m_titleTexture.setSmooth(true);

        m_titleSprite.setTexture(m_titleTexture);

        const sf::FloatRect screenRect = context.layout.screenRect();

        util::fit(
            m_titleSprite,
            { (screenRect.width * 0.4f),
              (screenRect.height * context.config.top_panel_height_ratio) });

        m_titleSprite.setPosition(
            ((screenRect.width * 0.5f) - (m_titleSprite.getGlobalBounds().width * 0.5f)), 0.0f);
    }

    void TopPanel::draw(const Context &, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_titleSprite, states);
    }

} // namespace castlecrawl2
