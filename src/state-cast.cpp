// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-cast.cpp
//
#include "state-cast.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "fight-util.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "npc-manager.hpp"
#include "player-display.hpp"
#include "player.hpp"
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
        const SpellCategory t_category,
        const std::string & t_spellName1,
        const std::string & t_spellName2,
        const std::string & t_spellName3,
        const sf::Color & t_color,
        const sf::Vector2f & t_position)
        : category{ t_category }
        , sprite{ t_texture }
        , title_text{ t_context.fonts.makeText(
              FontSize::Large, std::string(toString(t_category)).append(" Spells"), t_color) }
        , spell_text1{ t_context.fonts.makeText(FontSize::Medium, t_spellName1) }
        , spell_text2{ t_context.fonts.makeText(FontSize::Medium, t_spellName2) }
        , spell_text3{ t_context.fonts.makeText(FontSize::Medium, t_spellName3) }
        , spell_rect1{}
        , spell_rect2{}
        , spell_rect3{}
        , full_rect{}
        , spell_index{ 0 }
        , color{ t_color }
        , has_focus{ false }
    {
        const sf::FloatRect botRect{ t_context.layout.botRegion() };
        const float imageSize{ botRect.size.x / 7.5f };

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

        // this is a hack, this is only a hack of the code to fix a draw bug I can't explain
        if (SpellCategory::Fear == category)
        {
            spell_rect3.position.y += (pad * 0.9f);
        }

        full_rect = sf::FloatRect(
            imageRect.position,
            { imageRect.size.x, ((util::bottom(spell_rect3) - imageRect.position.y) + pad) });

        setFocus(t_context, false);
    }

    void SpellCategoryRectangle::setFocus(const Context & t_context, const bool t_hasFocus)
    {
        has_focus = t_hasFocus;

        const sf::Color spellColorAdj{ 100, 100, 100, 0 };
        const sf::Color spellColorFocusOn{ 230, 230, 230 };
        const sf::Color spellColorFocusOff{ 127, 127, 127 };
        const sf::Color spellColorFocusUnknown{ 64, 64, 64 };

        if (has_focus)
        {
            sprite.setColor(color);
            title_text.setFillColor(color);

            if (t_context.player.hasSpell(toSpell(category, 0)))
            {
                spell_text1.setFillColor(spellColorFocusOn);
            }
            else
            {
                spell_text1.setFillColor(spellColorFocusUnknown);
            }

            if (t_context.player.hasSpell(toSpell(category, 1)))
            {
                spell_text2.setFillColor(spellColorFocusOn);
            }
            else
            {
                spell_text2.setFillColor(spellColorFocusUnknown);
            }

            if (t_context.player.hasSpell(toSpell(category, 2)))
            {
                spell_text3.setFillColor(spellColorFocusOn);
            }
            else
            {
                spell_text3.setFillColor(spellColorFocusUnknown);
            }
        }
        else
        {
            sprite.setColor(color - spellColorAdj);
            title_text.setFillColor(color - spellColorAdj);

            if (t_context.player.hasSpell(toSpell(category, 0)))
            {
                spell_text1.setFillColor(spellColorFocusOff);
            }
            else
            {
                spell_text1.setFillColor(spellColorFocusUnknown);
            }

            if (t_context.player.hasSpell(toSpell(category, 1)))
            {
                spell_text2.setFillColor(spellColorFocusOff);
            }
            else
            {
                spell_text2.setFillColor(spellColorFocusUnknown);
            }

            if (t_context.player.hasSpell(toSpell(category, 2)))
            {
                spell_text3.setFillColor(spellColorFocusOff);
            }
            else
            {
                spell_text3.setFillColor(spellColorFocusUnknown);
            }
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
        , m_errorText{ util::SfmlDefaults::instance().font() }
        , m_errorTimerSec{ 0.0f }
        , m_descriptionText{ util::SfmlDefaults::instance().font() }
        , m_instructionText{ util::SfmlDefaults::instance().font() }
        , m_categroyAnimSprite{ util::SfmlDefaults::instance().texture() }
        , m_isAnimatingCategorySelection{ false }
        , m_gategoryAnimTimerSec{ 0.0f }
    {}

    void StateCast::onEnter(const Context & t_context)
    {
        // background fade
        const sf::FloatRect screenRect{ t_context.layout.screenRegion() };
        m_bgFadeRectangle.setPosition(screenRect.position);
        m_bgFadeRectangle.setSize(screenRect.size);
        m_bgFadeRectangle.setFillColor(t_context.config.stage_background_color);

        const sf::FloatRect botRect{ t_context.layout.botRegion() };

        // title
        m_titleText = t_context.fonts.makeText(FontSize::Huge, "Cast Spell");

        const float pad{ botRect.size.y * 0.05f };

        m_titleText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_titleText.getGlobalBounds().size.x * 0.5f)),
              (botRect.position.y + pad) });

        // instruction text
        m_instructionText = t_context.fonts.makeText(
            FontSize::Small,
            "Use the arrow keys to select a spell then press Enter, or press Escape to exit.",
            sf::Color(160, 160, 160));

        m_instructionText.setStyle(sf::Text::Italic);

        m_instructionText.setPosition(
            { ((botRect.size.x * 0.5f) - (m_instructionText.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_titleText) + (pad * 0.25f)) });

        // spell category images
        util::TextureLoader::load(
            m_fireTexture, (t_context.config.media_path / "image" / "spell-icon-fire.png"), true);

        util::TextureLoader::load(
            m_iceTexture, (t_context.config.media_path / "image" / "spell-icon-ice.png"), true);

        util::TextureLoader::load(
            m_energyTexture,
            (t_context.config.media_path / "image" / "spell-icon-energy.png"),
            true);

        util::TextureLoader::load(
            m_gripTexture, (t_context.config.media_path / "image" / "spell-icon-grip.png"), true);

        util::TextureLoader::load(
            m_fearTexture, (t_context.config.media_path / "image" / "spell-icon-fear.png"), true);

        // spell category columbs
        const float categoryColumbWidth{ botRect.size.x / 6.0f };
        const float categoryPositionTop{ util::bottom(m_titleText) + (pad * 1.5f) };

        m_fireRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_fireTexture,
            SpellCategory::Fire,
            "Spark",
            "Flare",
            "Fireball",
            t_context.config.spell_color_fire,
            sf::Vector2f{ (categoryColumbWidth * 1.0f), categoryPositionTop });

        m_iceRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_iceTexture,
            SpellCategory::Ice,
            "Frostbite",
            "Freezing Wind",
            "Ice Shards",
            t_context.config.spell_color_ice,
            sf::Vector2f{ (categoryColumbWidth * 2.0f), categoryPositionTop });

        m_energyRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_energyTexture,
            SpellCategory::Energy,
            "Zap",
            "Jolt",
            "Lightning",
            t_context.config.spell_color_energy,
            sf::Vector2f{ (categoryColumbWidth * 3.0f), categoryPositionTop });

        m_gripRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_gripTexture,
            SpellCategory::Grip,
            "Slow",
            "Stun",
            "Immobalize",
            t_context.config.spell_color_grip,
            sf::Vector2f{ (categoryColumbWidth * 4.0f), categoryPositionTop });

        m_fearRectangleUPtr = std::make_unique<SpellCategoryRectangle>(
            t_context,
            m_fearTexture,
            SpellCategory::Fear,
            "Scare",
            "Terrorize",
            "Heart Attack",
            t_context.config.spell_color_fear,
            sf::Vector2f{ (categoryColumbWidth * 5.0f), categoryPositionTop });

        // error text
        m_errorText =
            t_context.fonts.makeText(FontSize::Large, "", t_context.config.error_message_color);

        // description text
        m_descriptionText =
            t_context.fonts.makeText(FontSize::Medium, "", sf::Color(220, 220, 220));

        m_descriptionText.setStyle(sf::Text::Italic);

        // select the prev cast spell so that recasting is trivial
        const Spell spellLastCast{ t_context.player.spellLastCast() };
        if (spellLastCast == Spell::Spark)
        {
            m_fireRectangleUPtr->setFocus(t_context, true);
            m_fireRectangleUPtr->spell_index = 0;
        }
        else if (spellLastCast == Spell::Flare)
        {
            m_fireRectangleUPtr->setFocus(t_context, true);
            m_fireRectangleUPtr->spell_index = 1;
        }
        else if (spellLastCast == Spell::Fireball)
        {
            m_fireRectangleUPtr->setFocus(t_context, true);
            m_fireRectangleUPtr->spell_index = 2;
        }
        else if (spellLastCast == Spell::Frostbite)
        {
            m_iceRectangleUPtr->setFocus(t_context, true);
            m_iceRectangleUPtr->spell_index = 0;
        }
        else if (spellLastCast == Spell::FreezingWind)
        {
            m_iceRectangleUPtr->setFocus(t_context, true);
            m_iceRectangleUPtr->spell_index = 1;
        }
        else if (spellLastCast == Spell::IceShards)
        {
            m_iceRectangleUPtr->setFocus(t_context, true);
            m_iceRectangleUPtr->spell_index = 2;
        }
        else if (spellLastCast == Spell::Zap)
        {
            m_energyRectangleUPtr->setFocus(t_context, true);
            m_energyRectangleUPtr->spell_index = 0;
        }
        else if (spellLastCast == Spell::Jolt)
        {
            m_energyRectangleUPtr->setFocus(t_context, true);
            m_energyRectangleUPtr->spell_index = 1;
        }
        else if (spellLastCast == Spell::Lightning)
        {
            m_energyRectangleUPtr->setFocus(t_context, true);
            m_energyRectangleUPtr->spell_index = 2;
        }
        else if (spellLastCast == Spell::Slow)
        {
            m_gripRectangleUPtr->setFocus(t_context, true);
            m_gripRectangleUPtr->spell_index = 0;
        }
        else if (spellLastCast == Spell::Stun)
        {
            m_gripRectangleUPtr->setFocus(t_context, true);
            m_gripRectangleUPtr->spell_index = 1;
        }
        else if (spellLastCast == Spell::Immobilize)
        {
            m_gripRectangleUPtr->setFocus(t_context, true);
            m_gripRectangleUPtr->spell_index = 2;
        }
        else if (spellLastCast == Spell::Scare)
        {
            m_fearRectangleUPtr->setFocus(t_context, true);
            m_fearRectangleUPtr->spell_index = 0;
        }
        else if (spellLastCast == Spell::Terrorize)
        {
            m_fearRectangleUPtr->setFocus(t_context, true);
            m_fearRectangleUPtr->spell_index = 1;
        }
        else // if (spellLastCast == Spell::HeartAttack)
        {
            m_fearRectangleUPtr->setFocus(t_context, true);
            m_fearRectangleUPtr->spell_index = 2;
        }

        // initial setup
        m_directionSelectDisplay.setup(t_context);
        updateDescription(t_context);
    }

    void StateCast::update(const Context & t_context, const float t_elapsedSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_elapsedSec);
        m_directionSelectDisplay.update(t_context, t_elapsedSec);

        if (!m_hasSpellBeenSelected && !m_errorText.getString().isEmpty())
        {
            m_errorTimerSec += t_elapsedSec;
            const float errorTextDurationSec{ 5.0f };
            if (m_errorTimerSec < errorTextDurationSec)
            {
                const int alpha{ 255 -
                                 util::map(m_errorTimerSec, 0.0f, errorTextDurationSec, 0, 255) };

                sf::Color color{ m_errorText.getFillColor() };
                color.a = static_cast<uint8_t>(alpha);
                m_errorText.setFillColor(color);
            }
            else
            {
                m_errorText.setString("");
            }
        }

        if (m_isAnimatingCategorySelection)
        {
            m_gategoryAnimTimerSec += t_elapsedSec;
            const float categoryAnimDuration{ 0.5f };
            if (m_gategoryAnimTimerSec < categoryAnimDuration)
            {
                const int alpha{
                    255 - util::map(m_gategoryAnimTimerSec, 0.0f, categoryAnimDuration, 192, 255)
                };

                sf::Color color{ m_categroyAnimSprite.getColor() };
                color.a = static_cast<uint8_t>(alpha);
                m_categroyAnimSprite.setColor(color);

                const float scale{ util::map(
                    m_gategoryAnimTimerSec, 0.0f, categoryAnimDuration, 1.0f, 3.0f) };

                m_categroyAnimSprite.setScale({ scale, scale });
            }
            else
            {
                m_hasSpellBeenSelected = true;
            }
        }
    }

    void StateCast::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_target.draw(t_context.top_panel, t_states);
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.monsters.draw(t_context, t_target, t_states);
        t_context.npcs.draw(t_target, t_states);
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

            t_target.draw(m_instructionText, t_states);
            t_target.draw(m_descriptionText, t_states);
            t_target.draw(m_errorText, t_states);

            if (m_isAnimatingCategorySelection)
            {
                t_states.blendMode = sf::BlendAdd;
                t_target.draw(m_categroyAnimSprite, t_states);
                t_states.blendMode = sf::BlendAlpha;
            }
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
            castSpell(t_context, upPos, selectedSpell(t_context), t_key.scancode);
        }
        else if (
            (t_key.scancode == sf::Keyboard::Scancode::Down) &&
            t_context.maps.current().isPosValid(downPos))
        {
            castSpell(t_context, downPos, selectedSpell(t_context), t_key.scancode);
        }
        else if (
            (t_key.scancode == sf::Keyboard::Scancode::Left) &&
            t_context.maps.current().isPosValid(leftPos))
        {
            castSpell(t_context, leftPos, selectedSpell(t_context), t_key.scancode);
        }
        else if (
            (t_key.scancode == sf::Keyboard::Scancode::Right) &&
            t_context.maps.current().isPosValid(rightPos))
        {
            castSpell(t_context, rightPos, selectedSpell(t_context), t_key.scancode);
        }
        else
        {
            t_context.sfx.play("error-2");
        }
    }

    Spell StateCast::selectedSpell(const Context & t_context)
    {
        auto & categoryRectangleUPtr{ focusedCategory(t_context) };
        return toSpell(categoryRectangleUPtr->category, categoryRectangleUPtr->spell_index);
    }

    void StateCast::castSpell(
        const Context & t_context,
        const MapPos_t & t_mapPos,
        const Spell t_spell,
        const sf::Keyboard::Scancode & t_direction)
    {
        fight::castSpell(t_context, t_spell, t_mapPos, t_direction);
        t_context.state.setChangePending(State::Play);
    }

    std::unique_ptr<SpellCategoryRectangle> & StateCast::focusedCategory(const Context & t_context)
    {
        if (m_fireRectangleUPtr->has_focus)
        {
            return m_fireRectangleUPtr;
        }
        else if (m_iceRectangleUPtr->has_focus)
        {
            return m_iceRectangleUPtr;
        }
        else if (m_energyRectangleUPtr->has_focus)
        {
            return m_energyRectangleUPtr;
        }
        else if (m_gripRectangleUPtr->has_focus)
        {
            return m_gripRectangleUPtr;
        }
        else if (m_fearRectangleUPtr->has_focus)
        {
            return m_fearRectangleUPtr;
        }
        else
        {
            m_fireRectangleUPtr->setFocus(t_context, true);
            return m_fireRectangleUPtr;
        }
    }

    void StateCast::handleKeystrokesBeforeSpellSelection(
        const Context & t_context, const sf::Event::KeyPressed & t_key)
    {
        if (t_key.scancode == sf::Keyboard::Scancode::Enter)
        {
            const Spell spell{ selectedSpell(t_context) };
            if (!t_context.player.hasSpell(spell))
            {
                showErrorMessage(t_context, "You haven't learned that spell yet.");
                t_context.sfx.play("error-2");
                return;
            }

            if (t_context.player.mana() < toManaCost(spell))
            {
                showErrorMessage(t_context, "You don't have enough mana to cast that spell.");
                t_context.sfx.play("error-2");
                return;
            }

            m_categroyAnimSprite = focusedCategory(t_context)->sprite;

            m_categroyAnimSprite.setPosition(
                m_categroyAnimSprite.getGlobalBounds().position +
                (m_categroyAnimSprite.getGlobalBounds().size * 0.5f));

            util::setOriginToCenter(m_categroyAnimSprite);

            m_isAnimatingCategorySelection = true;
            t_context.sfx.play("gui-twing");
            return;
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

            if (indexDecrement(*focusedCategory(t_context)))
            {
                t_context.sfx.play("tick-on");
            }

            updateDescription(t_context);
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

            if (indexIncrement(*focusedCategory(t_context)))
            {
                t_context.sfx.play("tick-on");
            }

            updateDescription(t_context);
        }
        else if (t_key.scancode == sf::Keyboard::Scancode::Right)
        {
            if (m_fireRectangleUPtr->has_focus)
            {
                m_fireRectangleUPtr->setFocus(t_context, false);
                m_iceRectangleUPtr->setFocus(t_context, true);
                t_context.sfx.play("tick-on");
            }
            else if (m_iceRectangleUPtr->has_focus)
            {
                m_iceRectangleUPtr->setFocus(t_context, false);
                m_energyRectangleUPtr->setFocus(t_context, true);
                t_context.sfx.play("tick-on");
            }
            else if (m_energyRectangleUPtr->has_focus)
            {
                m_energyRectangleUPtr->setFocus(t_context, false);
                m_gripRectangleUPtr->setFocus(t_context, true);
                t_context.sfx.play("tick-on");
            }
            else if (m_gripRectangleUPtr->has_focus)
            {
                m_gripRectangleUPtr->setFocus(t_context, false);
                m_fearRectangleUPtr->setFocus(t_context, true);
                t_context.sfx.play("tick-on");
            }

            updateDescription(t_context);
        }
        else if (t_key.scancode == sf::Keyboard::Scancode::Left)
        {
            if (m_fearRectangleUPtr->has_focus)
            {
                m_fearRectangleUPtr->setFocus(t_context, false);
                m_gripRectangleUPtr->setFocus(t_context, true);
                t_context.sfx.play("tick-on");
            }
            else if (m_gripRectangleUPtr->has_focus)
            {
                m_gripRectangleUPtr->setFocus(t_context, false);
                m_energyRectangleUPtr->setFocus(t_context, true);
                t_context.sfx.play("tick-on");
            }
            else if (m_energyRectangleUPtr->has_focus)
            {
                m_energyRectangleUPtr->setFocus(t_context, false);
                m_iceRectangleUPtr->setFocus(t_context, true);
                t_context.sfx.play("tick-on");
            }
            else if (m_iceRectangleUPtr->has_focus)
            {
                m_iceRectangleUPtr->setFocus(t_context, false);
                m_fireRectangleUPtr->setFocus(t_context, true);
                t_context.sfx.play("tick-on");
            }

            updateDescription(t_context);
        }
    }

    void StateCast::updateDescription(const Context & t_context)
    {
        const Spell spell{ selectedSpell(t_context) };

        std::string description;
        if (spell == Spell::Spark)
        {
            description += "A weak but consistent fire attack spell ";
        }
        else if (spell == Spell::Frostbite)
        {
            description += "A weak but consistent ice attack spell ";
        }
        else if (spell == Spell::Zap)
        {
            description += "A low power and less predictable energy attack spell ";
        }
        // TODO finish this and give all spells a description.

        description += "that costs ";
        description += std::to_string(toManaCost(spell));
        description += " mana ";

        const sf::Vector2i damageMinMax{ toDamageMinMax(spell) };
        if ((damageMinMax.x < damageMinMax.y) && !description.empty())
        {
            description += "and does ";
            description += std::to_string(damageMinMax.x);
            description += " to ";
            description += std::to_string(damageMinMax.y);
            description += " damage.";
        }

        m_descriptionText.setString(description);
        util::setOriginToPosition(m_errorText);

        m_descriptionText.setPosition({ ((t_context.layout.botRegion().size.x * 0.5f) -
                                         (m_descriptionText.getGlobalBounds().size.x * 0.5f)),
                                        (t_context.layout.botRegion().size.y * 0.8f) });
    }

    void StateCast::showErrorMessage(const Context & t_context, const std::string & t_message)
    {
        m_errorText.setString(t_message);
        util::setOriginToPosition(m_errorText);

        m_errorText.setPosition({ ((t_context.layout.botRegion().size.x * 0.5f) -
                                   (m_errorText.getGlobalBounds().size.x * 0.5f)),
                                  (t_context.layout.botRegion().size.y * 0.925f) });

        m_errorTimerSec = 0.0f;
    }

} // namespace castlecrawl