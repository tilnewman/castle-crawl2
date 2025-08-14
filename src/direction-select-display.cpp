// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// direction-select-display.cpp
//
#include "direction-select-display.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

namespace castlecrawl
{

    DirectionSelectDisplay::DirectionSelectDisplay()
        : m_topRectangle{}
        , m_botRectangle{}
        , m_leftRectangle{}
        , m_rightRectangle{}
        , m_arrowTexture{ util::SfmlDefaults::instance().texture() }
        , m_arrowSpriteUp{ m_arrowTexture }
        , m_arrowSpriteDown{ m_arrowTexture }
        , m_arrowSpriteLeft{ m_arrowTexture }
        , m_arrowSpriteRight{ m_arrowTexture }
        , m_alphaBouncer{ uint8_t(64), uint8_t(127), 85.0f }
    {}

    void DirectionSelectDisplay::update(const Context &, const float t_elapsedSec)
    {
        sf::Color color{ m_arrowSpriteUp.getColor() };
        color.a = m_alphaBouncer.update(t_elapsedSec);

        m_arrowSpriteUp.setColor(color);
        m_arrowSpriteDown.setColor(color);
        m_arrowSpriteLeft.setColor(color);
        m_arrowSpriteRight.setColor(color);
    }

    void DirectionSelectDisplay::setup(const Context & t_context)
    {
        const MapPos_t mapPos = t_context.player_display.position();

        const MapPos_t topPos{ mapPos.x, (mapPos.y - 1) };
        const MapPos_t botPos{ mapPos.x, (mapPos.y + 1) };
        const MapPos_t leftPos{ (mapPos.x - 1), mapPos.y };
        const MapPos_t rightPos{ (mapPos.x + 1), mapPos.y };

        const sf::Color fillColor{ 0, 255, 255, 16 };
        const sf::Color outlineColor{ 0, 255, 255, 32 };
        const sf::Color arrowColor{ 100, 255, 255, 64 };

        const sf::Vector2f cellSize = t_context.layout.cellSize();

        util::TextureLoader::load(
            m_arrowTexture, (t_context.config.media_path / "image" / "arrow.png"), true);

        m_arrowSpriteUp.setTexture(m_arrowTexture, true);
        m_arrowSpriteDown.setTexture(m_arrowTexture, true);
        m_arrowSpriteLeft.setTexture(m_arrowTexture, true);
        m_arrowSpriteRight.setTexture(m_arrowTexture, true);

        m_arrowSpriteUp.setColor(arrowColor);
        m_arrowSpriteDown.setColor(arrowColor);
        m_arrowSpriteLeft.setColor(arrowColor);
        m_arrowSpriteRight.setColor(arrowColor);

        // put all arrows offscreen unless they are in valid map positions
        const sf::Vector2f offScreenPos{ -1000.0f, -1000.0f };
        m_arrowSpriteUp.setPosition(offScreenPos);
        m_arrowSpriteDown.setPosition(offScreenPos);
        m_arrowSpriteLeft.setPosition(offScreenPos);
        m_arrowSpriteRight.setPosition(offScreenPos);

        const float arrowSpriteShrinkScale{ 0.5f };
        const float arrowMove{ cellSize.x * 0.25f };

        //

        if (t_context.maps.current().isPosValid(topPos))
        {
            m_topRectangle.setFillColor(fillColor);
            m_topRectangle.setOutlineColor(outlineColor);
            m_topRectangle.setOutlineThickness(2.0f);

            m_topRectangle.setPosition(
                t_context.maps.current().mapPosToScreenPos(t_context, topPos));

            m_topRectangle.setSize(cellSize);

            util::setOriginToCenter(m_arrowSpriteUp);
            m_arrowSpriteUp.rotate(sf::degrees(-90));

            util::scale(
                m_arrowSpriteUp,
                util::scaleRectInPlaceCopy(
                    m_topRectangle.getGlobalBounds(), arrowSpriteShrinkScale));

            m_arrowSpriteUp.setPosition(util::center(m_topRectangle.getGlobalBounds()));
            m_arrowSpriteUp.move({ 0.0f, arrowMove });
        }

        if (t_context.maps.current().isPosValid(botPos))
        {
            m_botRectangle.setFillColor(fillColor);
            m_botRectangle.setOutlineColor(outlineColor);
            m_botRectangle.setOutlineThickness(2.0f);

            m_botRectangle.setPosition(
                t_context.maps.current().mapPosToScreenPos(t_context, botPos));

            m_botRectangle.setSize(cellSize);

            util::setOriginToCenter(m_arrowSpriteDown);
            m_arrowSpriteDown.rotate(sf::degrees(90));

            util::scale(
                m_arrowSpriteDown,
                util::scaleRectInPlaceCopy(
                    m_botRectangle.getGlobalBounds(), arrowSpriteShrinkScale));

            m_arrowSpriteDown.setPosition(util::center(m_botRectangle.getGlobalBounds()));

            m_arrowSpriteDown.move({ 0.0f, -arrowMove });
        }

        if (t_context.maps.current().isPosValid(leftPos))
        {
            m_leftRectangle.setFillColor(fillColor);
            m_leftRectangle.setOutlineColor(outlineColor);
            m_leftRectangle.setOutlineThickness(2.0f);

            m_leftRectangle.setPosition(
                t_context.maps.current().mapPosToScreenPos(t_context, leftPos));

            m_leftRectangle.setSize(cellSize);

            util::setOriginToCenter(m_arrowSpriteLeft);
            m_arrowSpriteLeft.rotate(sf::degrees(180));

            util::scale(
                m_arrowSpriteLeft,
                util::scaleRectInPlaceCopy(
                    m_leftRectangle.getGlobalBounds(), arrowSpriteShrinkScale));

            m_arrowSpriteLeft.setPosition(util::center(m_leftRectangle.getGlobalBounds()));

            m_arrowSpriteLeft.move({ (arrowMove * 2.0f), 0.0f });
        }

        if (t_context.maps.current().isPosValid(rightPos))
        {
            m_rightRectangle.setFillColor(fillColor);
            m_rightRectangle.setOutlineColor(outlineColor);
            m_rightRectangle.setOutlineThickness(2.0f);

            m_rightRectangle.setPosition(
                t_context.maps.current().mapPosToScreenPos(t_context, rightPos));

            m_rightRectangle.setSize(cellSize);

            util::fitAndCenterInside(
                m_arrowSpriteRight,
                util::scaleRectInPlaceCopy(
                    m_rightRectangle.getGlobalBounds(), arrowSpriteShrinkScale));

            m_arrowSpriteRight.move({ -(arrowMove * 2.0f), 0.0f });
        }
    }

    void DirectionSelectDisplay::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        // it might look better without these rectangles, so skip drawing for now
        // t_target.draw(m_topRectangle, t_states);
        // t_target.draw(m_botRectangle, t_states);
        // t_target.draw(m_leftRectangle, t_states);
        // t_target.draw(m_rightRectangle, t_states);

        t_target.draw(m_arrowSpriteUp, t_states);
        t_target.draw(m_arrowSpriteDown, t_states);
        t_target.draw(m_arrowSpriteLeft, t_states);
        t_target.draw(m_arrowSpriteRight, t_states);
    }

} // namespace castlecrawl
