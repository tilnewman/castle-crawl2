// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-cast.cpp
//
#include "state-cast.hpp"

#include "animation-manager.hpp"
#include "animation-player.hpp"
#include "context.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "player-display.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "texture-loader.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    SpellCategoryRectangle::SpellCategoryRectangle(
        const Context & t_context,
        const sf::Texture & t_texture,
        const std::string & t_title,
        const std::string & t_spellName1,
        const std::string & t_spellName2,
        const std::string & t_spellName3,
        const sf::Color & t_color,
        const sf::Vector2f & t_position)
        : sprite{ t_texture }
        , title_text{ t_context.fonts.makeText(FontSize::Large, t_title, t_color) }
        , spell_text1{ t_context.fonts.makeText(
              FontSize::Medium, t_spellName1, spell_color_focus_on) }
        , spell_text2{ t_context.fonts.makeText(
              FontSize::Medium, t_spellName2, spell_color_focus_on) }
        , spell_text3{ t_context.fonts.makeText(
              FontSize::Medium, t_spellName3, spell_color_focus_on) }
        , spell_rect1{}
        , spell_rect2{}
        , spell_rect3{}
        , full_rect{}
        , spell_index{ 0 }
        , color{ t_color }
        , has_focus{ false }
    {
        const sf::FloatRect botRect{ t_context.layout.botRect() };
        const float imageSize{ botRect.size.x / 7.0f };

        const sf::FloatRect imageRect{ { (t_position.x - (imageSize * 0.5f)), t_position.y },
                                       { imageSize, imageSize } };

        util::fitAndCenterInside(sprite, imageRect);

        sprite.setColor(t_color);

        title_text.setStyle(sf::Text::Underlined);

        title_text.setPosition(
            { (t_position.x - (title_text.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(imageRect) + (title_text.getGlobalBounds().size.y * 0.5f)) });

        const float pad{ title_text.getGlobalBounds().size.y * 0.2f };

        spell_text1.setPosition(
            { (t_position.x - (spell_text1.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(title_text) + title_text.getGlobalBounds().size.y) });

        const sf::Vector2f nameRectSize{ imageRect.size.x,
                                         (spell_text1.getGlobalBounds().size.y + pad) };

        spell_rect1 = sf::FloatRect(
            { imageRect.position.x, (spell_text1.getGlobalBounds().position.y - (pad * 0.5f)) },
            nameRectSize);

        spell_text2.setPosition({ (t_position.x - (spell_text2.getGlobalBounds().size.x * 0.5f)),
                                  (util::bottom(spell_text1) + pad) });

        spell_rect2 = sf::FloatRect(
            { imageRect.position.x, (spell_text2.getGlobalBounds().position.y - (pad * 0.5f)) },
            nameRectSize);

        spell_text3.setPosition({ (t_position.x - (spell_text3.getGlobalBounds().size.x * 0.5f)),
                                  (util::bottom(spell_text2) + pad) });

        spell_rect3 = sf::FloatRect(
            { imageRect.position.x, (spell_text3.getGlobalBounds().position.y - (pad * 0.5f)) },
            nameRectSize);

        full_rect = sf::FloatRect(
            imageRect.position,
            { imageRect.size.x, ((util::bottom(spell_rect3) - imageRect.position.y) + pad) });

        setFocus(false);
    }

    void SpellCategoryRectangle::setFocus(const bool t_hasFocus)
    {
        has_focus = t_hasFocus;

        if (has_focus)
        {
            sprite.setColor(color);
            title_text.setFillColor(color);
            spell_text1.setFillColor(spell_color_focus_on);
            spell_text2.setFillColor(spell_color_focus_on);
            spell_text3.setFillColor(spell_color_focus_on);
        }
        else
        {
            sprite.setColor(color - sf::Color(100, 100, 100, 0));
            title_text.setFillColor(color - sf::Color(100, 100, 100, 0));
            spell_text1.setFillColor(spell_color_focus_off);
            spell_text2.setFillColor(spell_color_focus_off);
            spell_text3.setFillColor(spell_color_focus_off);
        }
    }

    void SpellCategoryRectangle::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        if (has_focus)
        {
            sf::RectangleShape rectangle;
            rectangle.setFillColor(sf::Color(16, 16, 16));
            rectangle.setOutlineColor(sf::Color(92, 92, 92));
            rectangle.setOutlineThickness(1.0f);
            rectangle.setPosition(full_rect.position);
            rectangle.setSize(full_rect.size);

            t_target.draw(rectangle, t_states);
        }

        t_target.draw(sprite, t_states);
        t_target.draw(title_text, t_states);

        if (has_focus)
        {
            const sf::FloatRect currentSpellRect = [&]() {
                if (0 == spell_index)
                {
                    return spell_rect1;
                }
                else if (1 == spell_index)
                {
                    return spell_rect2;
                }
                else
                {
                    return spell_rect3;
                }
            }();

            sf::RectangleShape rectangle;
            rectangle.setFillColor(sf::Color(32, 32, 32));
            rectangle.setOutlineColor(sf::Color::White);
            rectangle.setOutlineThickness(1.0f);
            rectangle.setPosition(currentSpellRect.position);
            rectangle.setSize(currentSpellRect.size);

            t_target.draw(rectangle, t_states);
        }

        t_target.draw(spell_text1, t_states);
        t_target.draw(spell_text2, t_states);
        t_target.draw(spell_text3, t_states);
    }

    //

    StateCast::StateCast()
        : m_bgFadeRectangle{}
        , m_titleText{ util::SfmlDefaults::instance().font() }
        , m_fireRectangleUPtr{}
        , m_iceRectangleUPtr{}
        , m_energyRectangleUPtr{}
        , m_gripRectangleUPtr{}
        , m_fearRectangleUPtr{}
        , m_fireTexture{}
        , m_iceTexture{}
        , m_energyTexture{}
        , m_gripTexture{}
        , m_fearTexture{}
        , m_hasSpellBeenSelected{ false }
        , m_directionSelectDisplay{}
    {}

    void StateCast::onEnter(const Context & t_context)
    {
        // background fade
        const sf::FloatRect botRect{ t_context.layout.botRect() };
        m_bgFadeRectangle.setPosition(botRect.position);
        m_bgFadeRectangle.setSize(botRect.size);
        m_bgFadeRectangle.setFillColor(t_context.config.stage_background_color);

        // title
        m_titleText = t_context.fonts.makeText(FontSize::Huge, "Cast Spell");

        const float pad{ botRect.size.y * 0.05f };

        m_titleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_titleText.getGlobalBounds().size.x * 0.5f)),
              (botRect.position.y + pad) });

        // spell category images
        util::TextureLoader::load(
            m_fireTexture, (t_context.config.media_path / "image" / "fire-icon.png"), true);

        util::TextureLoader::load(
            m_iceTexture, (t_context.config.media_path / "image" / "ice-icon.png"), true);

        util::TextureLoader::load(
            m_energyTexture, (t_context.config.media_path / "image" / "energy-icon.png"), true);

        util::TextureLoader::load(
            m_gripTexture, (t_context.config.media_path / "image" / "grip-icon.png"), true);

        util::TextureLoader::load(
            m_fearTexture, (t_context.config.media_path / "image" / "fear-icon.png"), true);

        // spell category columbs
        const sf::Color fireColor{ 255, 192, 192 };
        const sf::Color iceColor{ 192, 192, 255 };
        const sf::Color energyColor{ 192, 240, 240 };
        const sf::Color gripColor{ 225, 175, 130 };
        const sf::Color fearColor{ 190, 150, 240 };

        const float categoryColumbWidth{ botRect.size.x / 6.0f };
        const float categoryPositionTop{ util::bottom(m_titleText) + pad };

        m_fireRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_fireTexture,
            "Fire Spells",
            "Spark",
            "Flare",
            "Fireball",
            fireColor,
            sf::Vector2f{ (categoryColumbWidth * 1.0f), categoryPositionTop });

        m_iceRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_iceTexture,
            "Ice Spells",
            "Frostbite",
            "Freezing Wind",
            "Ice Shards",
            iceColor,
            sf::Vector2f{ (categoryColumbWidth * 2.0f), categoryPositionTop });

        m_energyRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_energyTexture,
            "Energy Spells",
            "Zap",
            "Jolt",
            "Lightning",
            energyColor,
            sf::Vector2f{ (categoryColumbWidth * 3.0f), categoryPositionTop });

        m_gripRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_gripTexture,
            "Grip Spells",
            "Slow",
            "Stun",
            "Immobalize",
            gripColor,
            sf::Vector2f{ (categoryColumbWidth * 4.0f), categoryPositionTop });

        m_fearRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_fearTexture,
            "Fear Spells",
            "Scare",
            "Terrorize",
            "Heart Attack",
            fearColor,
            sf::Vector2f{ (categoryColumbWidth * 5.0f), categoryPositionTop });

        m_fireRectangleUPtr->setFocus(true);

        //
        m_directionSelectDisplay.setup(t_context);
    }

    void StateCast::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
        m_directionSelectDisplay.update(t_context, t_elapsedSec);
    }

    void StateCast::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(t_context.top_panel, t_states);
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.monsters.drawHealthLines(t_context, t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.anim.draw(t_target, t_states);
        t_context.framerate.draw(t_target, t_states);

        if (m_hasSpellBeenSelected)
        {
            m_directionSelectDisplay.draw(t_target, t_states);
        }
        else
        {
            t_target.draw(m_bgFadeRectangle, t_states);
            t_target.draw(m_titleText, t_states);

            m_fireRectangleUPtr->draw(t_target, t_states);
            m_iceRectangleUPtr->draw(t_target, t_states);
            m_energyRectangleUPtr->draw(t_target, t_states);
            m_gripRectangleUPtr->draw(t_target, t_states);
            m_fearRectangleUPtr->draw(t_target, t_states);
        }
    }

    void StateCast::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>();
        if (!keyPtr)
        {
            return;
        }

        if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
        {
            t_context.state.setChangePending(State::Play);
            return;
        }

        if (m_hasSpellBeenSelected)
        {
            handleKeystrokesAfterSpellSelection(t_context, *keyPtr);
        }
        else
        {
            handleKeystrokesBeforeSpellSelection(t_context, *keyPtr);
        }
    }

    void StateCast::handleKeystrokesAfterSpellSelection(
        const Context & t_context, const sf::Event::KeyPressed & t_key)
    {
        const MapPos_t mapPos{ t_context.player_display.position() };
        const MapPos_t upPos{ mapPos.x, (mapPos.y - 1) };
        const MapPos_t downPos{ mapPos.x, (mapPos.y + 1) };
        const MapPos_t leftPos{ (mapPos.x - 1), mapPos.y };
        const MapPos_t rightPos{ (mapPos.x + 1), mapPos.y };

        if ((t_key.scancode == sf::Keyboard::Scancode::Up) &&
            t_context.maps.current().isPosValid(upPos))
        {
            pickCategoryAndIndex(t_context, upPos);
        }
        else if (
            (t_key.scancode == sf::Keyboard::Scancode::Down) &&
            t_context.maps.current().isPosValid(downPos))
        {
            pickCategoryAndIndex(t_context, downPos);
        }
        else if (
            (t_key.scancode == sf::Keyboard::Scancode::Left) &&
            t_context.maps.current().isPosValid(leftPos))
        {
            pickCategoryAndIndex(t_context, leftPos);
        }
        else if (
            (t_key.scancode == sf::Keyboard::Scancode::Right) &&
            t_context.maps.current().isPosValid(rightPos))
        {
            pickCategoryAndIndex(t_context, rightPos);
        }
        else
        {
            t_context.sfx.play("error-1");
        }
    }

    void StateCast::pickCategoryAndIndex(const Context & t_context, const MapPos_t & t_mapPos)
    {
        if (m_fireRectangleUPtr->has_focus)
        {
            castSpell(t_context, t_mapPos, SpellCategory::Fire, m_fireRectangleUPtr->spell_index);
        }
        else if (m_iceRectangleUPtr->has_focus)
        {
            castSpell(t_context, t_mapPos, SpellCategory::Ice, m_iceRectangleUPtr->spell_index);
        }
        else if (m_energyRectangleUPtr->has_focus)
        {
            castSpell(
                t_context, t_mapPos, SpellCategory::Energy, m_energyRectangleUPtr->spell_index);
        }
        else if (m_gripRectangleUPtr->has_focus)
        {
            castSpell(t_context, t_mapPos, SpellCategory::Grip, m_gripRectangleUPtr->spell_index);
        }
        else if (m_fearRectangleUPtr->has_focus)
        {
            castSpell(t_context, t_mapPos, SpellCategory::Fear, m_fearRectangleUPtr->spell_index);
        }
    }

    void StateCast::castSpell(
        const Context & t_context,
        const MapPos_t & t_mapPos,
        const SpellCategory t_spellCategory,
        const std::size_t t_spellIndex)
    {
        const sf::Vector2f screenPos{ t_context.maps.current().mapPosToScreenPos(
            t_context, t_mapPos) };

        const sf::FloatRect animRect{ screenPos, t_context.layout.cellSize() };

        if (t_spellCategory == SpellCategory::Fire)
        {
            if (t_spellIndex == 0)
            {
                t_context.anim.player().play("spark", util::scaleRectInPlaceCopy(animRect, 1.25f));
            }
            else if (t_spellIndex == 1)
            {
                t_context.anim.player().play("flare", util::scaleRectInPlaceCopy(animRect, 1.25f));
            }
            else if (t_spellIndex == 2)
            {
                t_context.anim.player().play(
                    "fireball", util::scaleRectInPlaceCopy(animRect, 1.5f));
            }
        }
        else if (t_spellCategory == SpellCategory::Ice)
        {
            if (t_spellIndex == 0)
            {
                util::AnimConfig config(0.5f);

                t_context.anim.player().play(
                    "frostbite", util::scaleRectInPlaceCopy(animRect, 1.5f), config);
            }
            else if (t_spellIndex == 1)
            {
                t_context.anim.player().play(
                    "freezing-wind", util::scaleRectInPlaceCopy(animRect, 2.5f));
            }
            else if (t_spellIndex == 2)
            {
                t_context.anim.player().play(
                    "ice-shards", util::scaleRectInPlaceCopy(animRect, 2.0f));
            }
        }
        else if (t_spellCategory == SpellCategory::Energy)
        {
            if (t_spellIndex == 0)
            {
                util::AnimConfig config(0.5f);
                t_context.anim.player().play(
                    "frostbite", util::scaleRectInPlaceCopy(animRect, 2.0f), config);
            }
            else if (t_spellIndex == 1)
            {
                t_context.anim.player().play("jolt", animRect);
            }
            else if (t_spellIndex == 2)
            {
                t_context.anim.player().play(
                    "lightning", util::scaleRectInPlaceCopy(animRect, 2.0f));
            }
        }
        else if (t_spellCategory == SpellCategory::Grip)
        {
            util::AnimConfig config(0.75f, sf::Color(255, 205, 160));

            if (t_spellIndex == 0)
            {
                t_context.anim.player().play("orb-charge", animRect, config);
            }
            else if (t_spellIndex == 1)
            {
                t_context.anim.player().play("orb-charge", animRect, config);
            }
            else if (t_spellIndex == 2)
            {
                t_context.anim.player().play("orb-charge", animRect, config);
            }
        }
        else if (t_spellCategory == SpellCategory::Fear)
        {
            util::AnimConfig config(1.75f, sf::Color(205, 165, 255));

            if (t_spellIndex == 0)
            {
                t_context.anim.player().play("spell", animRect, config);
            }
            else if (t_spellIndex == 1)
            {
                t_context.anim.player().play("spell", animRect, config);
            }
            else if (t_spellIndex == 2)
            {
                t_context.anim.player().play("spell", animRect, config);
            }
        }

        t_context.state.setChangePending(State::Play);
    }

    void StateCast::handleKeystrokesBeforeSpellSelection(
        const Context & t_context, const sf::Event::KeyPressed & t_key)
    {
        if (t_key.scancode == sf::Keyboard::Scancode::Enter)
        {
            m_hasSpellBeenSelected = true;
        }
        else if (t_key.scancode == sf::Keyboard::Scancode::Up)
        {
            const auto indexDecrement = [](SpellCategoryRectangle & scr) {
                if (scr.spell_index == 0)
                {
                    return false;
                }
                else
                {
                    --scr.spell_index;
                    return true;
                }
            };

            if (m_fireRectangleUPtr->has_focus)
            {
                if (indexDecrement(*m_fireRectangleUPtr))
                {
                    t_context.sfx.play("tick-on");
                }
            }
            else if (m_iceRectangleUPtr->has_focus)
            {
                if (indexDecrement(*m_iceRectangleUPtr))
                {
                    t_context.sfx.play("tick-on");
                }
            }
            else if (m_energyRectangleUPtr->has_focus)
            {
                if (indexDecrement(*m_energyRectangleUPtr))
                {
                    t_context.sfx.play("tick-on");
                }
            }
            else if (m_gripRectangleUPtr->has_focus)
            {
                if (indexDecrement(*m_gripRectangleUPtr))
                {
                    t_context.sfx.play("tick-on");
                }
            }
            else if (m_fearRectangleUPtr->has_focus)
            {
                if (indexDecrement(*m_fearRectangleUPtr))
                {
                    t_context.sfx.play("tick-on");
                }
            }
        }
        else if (t_key.scancode == sf::Keyboard::Scancode::Down)
        {
            const auto indexIncrement = [](SpellCategoryRectangle & scr) {
                if (scr.spell_index == 2)
                {
                    return false;
                }
                else
                {
                    ++scr.spell_index;
                    return true;
                }
            };

            if (m_fireRectangleUPtr->has_focus)
            {
                if (indexIncrement(*m_fireRectangleUPtr))
                {
                    t_context.sfx.play("tick-on");
                }
            }
            else if (m_iceRectangleUPtr->has_focus)
            {
                if (indexIncrement(*m_iceRectangleUPtr))
                {
                    t_context.sfx.play("tick-on");
                }
            }
            else if (m_energyRectangleUPtr->has_focus)
            {
                if (indexIncrement(*m_energyRectangleUPtr))
                {
                    t_context.sfx.play("tick-on");
                }
            }
            else if (m_gripRectangleUPtr->has_focus)
            {
                if (indexIncrement(*m_gripRectangleUPtr))
                {
                    t_context.sfx.play("tick-on");
                }
            }
            else if (m_fearRectangleUPtr->has_focus)
            {
                if (indexIncrement(*m_fearRectangleUPtr))
                {
                    t_context.sfx.play("tick-on");
                }
            }
        }
        else if (t_key.scancode == sf::Keyboard::Scancode::Right)
        {
            if (m_fireRectangleUPtr->has_focus)
            {
                m_fireRectangleUPtr->setFocus(false);
                m_iceRectangleUPtr->setFocus(true);
                t_context.sfx.play("tick-on");
            }
            else if (m_iceRectangleUPtr->has_focus)
            {
                m_iceRectangleUPtr->setFocus(false);
                m_energyRectangleUPtr->setFocus(true);
                t_context.sfx.play("tick-on");
            }
            else if (m_energyRectangleUPtr->has_focus)
            {
                m_energyRectangleUPtr->setFocus(false);
                m_gripRectangleUPtr->setFocus(true);
                t_context.sfx.play("tick-on");
            }
            else if (m_gripRectangleUPtr->has_focus)
            {
                m_gripRectangleUPtr->setFocus(false);
                m_fearRectangleUPtr->setFocus(true);
                t_context.sfx.play("tick-on");
            }
        }
        else if (t_key.scancode == sf::Keyboard::Scancode::Left)
        {
            if (m_fearRectangleUPtr->has_focus)
            {
                m_fearRectangleUPtr->setFocus(false);
                m_gripRectangleUPtr->setFocus(true);
                t_context.sfx.play("tick-on");
            }
            else if (m_gripRectangleUPtr->has_focus)
            {
                m_gripRectangleUPtr->setFocus(false);
                m_energyRectangleUPtr->setFocus(true);
                t_context.sfx.play("tick-on");
            }
            else if (m_energyRectangleUPtr->has_focus)
            {
                m_energyRectangleUPtr->setFocus(false);
                m_iceRectangleUPtr->setFocus(true);
                t_context.sfx.play("tick-on");
            }
            else if (m_iceRectangleUPtr->has_focus)
            {
                m_iceRectangleUPtr->setFocus(false);
                m_fireRectangleUPtr->setFocus(true);
                t_context.sfx.play("tick-on");
            }
        }
    }

} // namespace castlecrawl