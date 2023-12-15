// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// top-panel.cpp
//
#include "top-panel.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "layout.hpp"
#include "util.hpp"

namespace castlecrawl
{

    TopPanel::TopPanel()
        : m_titleTexture()
        , m_titleSprite()
    {}

    void TopPanel::setup(const Context & context)
    {
        const bool loadResult = m_titleTexture.loadFromFile(
            (context.config.media_path / "image" / "title.png").string());

        M_CHECK(loadResult, "Failed to load top panel title.png");

        m_titleTexture.setSmooth(true);

        m_titleSprite.setTexture(m_titleTexture);

        const sf::FloatRect topRect = context.layout.topRect();

        util::fit(m_titleSprite, { (topRect.width * 0.3f), topRect.height });

        m_titleSprite.setPosition(
            ((topRect.width * 0.5f) - (m_titleSprite.getGlobalBounds().width * 0.5f)), 0.0f);
    }

    void TopPanel::draw(const Context &, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.draw(m_titleSprite, states);
    }

} // namespace castlecrawl
