// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-inventory.cpp
//
#include "state-inventory.hpp"

#include "animation-manager.hpp"
#include "context.hpp"
#include "framerate-text.hpp"
#include "inventory.hpp"
#include "item-factory.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "sfml-defaults.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

#include <iostream>

namespace castlecrawl
{

    StateInventory::StateInventory()
        : m_fadeRectangle{}
        , m_unTitleText{ util::SfmlDefaults::instance().font() }
        , m_unListboxUPtr{}
        , m_eqTitleText{ util::SfmlDefaults::instance().font() }
        , m_eqListboxUPtr{}
        , m_itemDescText{ util::SfmlDefaults::instance().font() }
        , m_itemHintText{ util::SfmlDefaults::instance().font() }
        , m_errorText{ util::SfmlDefaults::instance().font() }
        , m_errorTextElapsedSec{ 0.0f }
        , m_strTitleText{ util::SfmlDefaults::instance().font() }
        , m_dexTitleText{ util::SfmlDefaults::instance().font() }
        , m_accTitleText{ util::SfmlDefaults::instance().font() }
        , m_lckTitleText{ util::SfmlDefaults::instance().font() }
        , m_arcTitleText{ util::SfmlDefaults::instance().font() }
        , m_strValueText{ util::SfmlDefaults::instance().font() }
        , m_dexValueText{ util::SfmlDefaults::instance().font() }
        , m_accValueText{ util::SfmlDefaults::instance().font() }
        , m_lckValueText{ util::SfmlDefaults::instance().font() }
        , m_arcValueText{ util::SfmlDefaults::instance().font() }
        , m_healthText{ util::SfmlDefaults::instance().font() }
        , m_manaText{ util::SfmlDefaults::instance().font() }
        , m_levelText{ util::SfmlDefaults::instance().font() }
        , m_goldText{ util::SfmlDefaults::instance().font() }
        , m_armorText{ util::SfmlDefaults::instance().font() }
        , m_weaponText{ util::SfmlDefaults::instance().font() }
        , m_instructionText1{ util::SfmlDefaults::instance().font() }
        , m_instructionText2{ util::SfmlDefaults::instance().font() }
        , m_instructionText3{ util::SfmlDefaults::instance().font() }
        , m_instructionText4{ util::SfmlDefaults::instance().font() }
        , m_instructionText5{ util::SfmlDefaults::instance().font() }
        , m_statRectangle{}
    {}

    void StateInventory::onEnter(const Context & t_context)
    {
        m_unListboxUPtr = std::make_unique<Listbox>(t_context.player.inventory().unItems());
        m_eqListboxUPtr = std::make_unique<Listbox>(t_context.player.inventory().eqItems());

        // setup constants used throughout
        const sf::FloatRect screenRect{ t_context.layout.screenRect() };
        const float pad{ screenRect.size.x * 0.0025f };
        const float padLarge{ pad * 10.0f };
        const sf::FloatRect botRect = t_context.layout.botRect();

        // establish how tall the stats rows will be
        m_strTitleText = t_context.fonts.makeText(FontSize::Medium, "Dy");

        const float statRowHeight{ m_strTitleText.getGlobalBounds().size.y +
                                   (m_strTitleText.getGlobalBounds().size.y * 0.17f) };

        // setup the stats box background rectangle
        m_statRectangle.setFillColor(sf::Color(255, 255, 255, 32));
        m_statRectangle.setOutlineColor(sf::Color(255, 255, 255, 64));
        m_statRectangle.setOutlineThickness(2.0f);

        m_statRectangle.setPosition(
            { (screenRect.size.x * 0.25f), (botRect.position.y + padLarge) });

        m_statRectangle.setSize(
            { (screenRect.size.x * 0.25f), ((statRowHeight * 5.0f) + (pad * 2.0f)) });

        // place the stats text
        const sf::Color statTextColor{ sf::Color(200, 200, 200) };

        const float statTextPosHoriz{ m_statRectangle.getPosition().x + pad };

        const auto positionStatTextOnRow =
            [&](sf::Text & t_text, const float t_row, const float t_posHoriz) {
                float posVert{ m_statRectangle.getPosition().y + pad };
                posVert += (t_row * statRowHeight);
                posVert -= (statRowHeight * 0.5f);
                posVert -= (t_text.getGlobalBounds().size.y * 0.5f);
                t_text.setPosition({ t_posHoriz, posVert });
            };

        m_strTitleText = t_context.fonts.makeText(FontSize::Medium, "Strength", statTextColor);
        m_dexTitleText = t_context.fonts.makeText(FontSize::Medium, "Dexterity", statTextColor);
        m_accTitleText = t_context.fonts.makeText(FontSize::Medium, "Accuracy", statTextColor);
        m_lckTitleText = t_context.fonts.makeText(FontSize::Medium, "Luck", statTextColor);
        m_arcTitleText = t_context.fonts.makeText(FontSize::Medium, "Arcane", statTextColor);

        positionStatTextOnRow(m_strTitleText, 1.0f, statTextPosHoriz);
        positionStatTextOnRow(m_dexTitleText, 2.0f, statTextPosHoriz);
        positionStatTextOnRow(m_accTitleText, 3.0f, statTextPosHoriz);
        positionStatTextOnRow(m_lckTitleText, 4.0f, statTextPosHoriz);
        positionStatTextOnRow(m_arcTitleText, 5.0f, statTextPosHoriz);

        m_strValueText = t_context.fonts.makeText(FontSize::Medium, "1", statTextColor);
        m_dexValueText = t_context.fonts.makeText(FontSize::Medium, "1", statTextColor);
        m_accValueText = t_context.fonts.makeText(FontSize::Medium, "1", statTextColor);
        m_lckValueText = t_context.fonts.makeText(FontSize::Medium, "1", statTextColor);
        m_arcValueText = t_context.fonts.makeText(FontSize::Medium, "1", statTextColor);

        const float statValueTextPosHoriz{ util::right(m_dexTitleText.getGlobalBounds()) +
                                           (padLarge * 0.2f) };

        positionStatTextOnRow(m_strValueText, 1.0f, statValueTextPosHoriz);
        positionStatTextOnRow(m_dexValueText, 2.0f, statValueTextPosHoriz);
        positionStatTextOnRow(m_accValueText, 3.0f, statValueTextPosHoriz);
        positionStatTextOnRow(m_lckValueText, 4.0f, statValueTextPosHoriz);
        positionStatTextOnRow(m_arcValueText, 5.0f, statValueTextPosHoriz);

        //
        std::string healthStr{ "Health: " };
        healthStr += std::to_string(t_context.player.health().current());
        healthStr += '/';
        healthStr += std::to_string(t_context.player.health().normal());

        m_healthText =
            t_context.fonts.makeText(FontSize::Small, healthStr, sf::Color(255, 180, 180));

        m_healthText.setPosition(
            { (util::right(m_dexValueText) + padLarge), (m_statRectangle.getPosition().y + pad) });

        //
        std::string manaStr{ "Mana: " };
        manaStr += std::to_string(t_context.player.mana().current());
        manaStr += '/';
        manaStr += std::to_string(t_context.player.mana().normal());

        m_manaText = t_context.fonts.makeText(FontSize::Small, manaStr, sf::Color(180, 150, 255));

        m_manaText.setPosition(
            { m_healthText.getPosition().x, (util::bottom(m_healthText) + pad) });

        //
        std::string levelStr{ "Level: " };
        levelStr += std::to_string(t_context.player.level());

        m_levelText = t_context.fonts.makeText(FontSize::Small, levelStr, sf::Color(255, 255, 255));
        m_levelText.setPosition({ m_healthText.getPosition().x, (util::bottom(m_manaText) + pad) });

        //
        std::string goldStr{ "Gold: " };
        goldStr += std::to_string(t_context.player.gold());

        m_goldText = t_context.fonts.makeText(
            FontSize::Small, goldStr, t_context.config.message_color_coins);

        m_goldText.setPosition({ m_healthText.getPosition().x, (util::bottom(m_levelText) + pad) });

        //
        std::string armorStr{ "Armor: " };
        armorStr += std::to_string(t_context.player.armor().get());
        m_armorText = t_context.fonts.makeText(FontSize::Small, armorStr);
        m_armorText.setPosition({ m_healthText.getPosition().x, (util::bottom(m_goldText) + pad) });

        //
        m_weaponText = t_context.fonts.makeText(FontSize::Small, "", sf::Color(220, 220, 220));

        m_weaponText.setPosition(
            { m_healthText.getPosition().x, (util::bottom(m_armorText) + pad) });

        // instruction text
        const sf::Color instTextColor{ sf::Color(170, 170, 200) };

        m_instructionText1 = t_context.fonts.makeText(
            FontSize::Small, "Use arrow keys to navigate item boxes.", instTextColor);

        m_instructionText2 = t_context.fonts.makeText(
            FontSize::Small, "Press 'E' to equip, and 'U' to unequip items.", instTextColor);

        m_instructionText3 = t_context.fonts.makeText(
            FontSize::Small, "Press 'D' to drop unequipped items.", instTextColor);

        m_instructionText4 = t_context.fonts.makeText(
            FontSize::Small,
            "Press 'S' to swap an unequipped item with the equipped one.",
            instTextColor);

        m_instructionText5 = t_context.fonts.makeText(
            FontSize::Small, "Press 'U' to use unequipped items.", instTextColor);

        m_instructionText1.setStyle(sf::Text::Italic);
        m_instructionText2.setStyle(sf::Text::Italic);
        m_instructionText3.setStyle(sf::Text::Italic);
        m_instructionText4.setStyle(sf::Text::Italic);
        m_instructionText5.setStyle(sf::Text::Italic);

        const float instTextHorizCenterPos{ screenRect.size.x * 0.66f };

        m_instructionText1.setPosition(
            { (instTextHorizCenterPos - (m_instructionText1.getGlobalBounds().size.x * 0.5f)),
              (m_statRectangle.getPosition().y + (padLarge * 0.5f)) });

        m_instructionText2.setPosition(
            { (instTextHorizCenterPos - (m_instructionText2.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_instructionText1) + pad) });

        m_instructionText3.setPosition(
            { (instTextHorizCenterPos - (m_instructionText3.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_instructionText2) + pad) });

        m_instructionText4.setPosition(
            { (instTextHorizCenterPos - (m_instructionText4.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_instructionText3) + pad) });

        m_instructionText5.setPosition(
            { (instTextHorizCenterPos - (m_instructionText5.getGlobalBounds().size.x * 0.5f)),
              (util::bottom(m_instructionText4) + pad) });

        //
        m_unListboxUPtr->setup(
            t_context, FontSize::Medium, t_context.items.textExtents().longest_name, 16);

        m_eqListboxUPtr->setup(
            t_context, FontSize::Medium, t_context.items.textExtents().longest_name, 16);

        m_unListboxUPtr->setPosition(
            { ((screenRect.size.x * 0.5f) - m_unListboxUPtr->getGlobalBounds().size.x) - pad,
              (util::bottom(m_statRectangle) + (padLarge * 2.0f)) });

        m_eqListboxUPtr->setPosition(
            { ((screenRect.size.x * 0.5f) + pad), m_unListboxUPtr->getGlobalBounds().position.y });

        m_unListboxUPtr->setFocus(true);
        m_eqListboxUPtr->setFocus(false);

        //
        m_itemDescText = t_context.fonts.makeText(FontSize::Small, "");

        //
        m_itemHintText = t_context.fonts.makeText(FontSize::Small, "");
        m_itemHintText.setFillColor(sf::Color(255, 240, 140));

        //
        m_unTitleText = t_context.fonts.makeText(
            FontSize::Small, "Unequipped Items:", sf::Color(255, 255, 255, 160));

        m_unTitleText.setPosition({ m_unListboxUPtr->getGlobalBounds().position.x,
                                    (m_unListboxUPtr->getGlobalBounds().position.y -
                                     m_unTitleText.getGlobalBounds().size.y) });

        m_eqTitleText = t_context.fonts.makeText(
            FontSize::Small, "Equipped Items:", sf::Color(255, 255, 255, 160));

        m_eqTitleText.setPosition({ m_eqListboxUPtr->getGlobalBounds().position.x,
                                    m_unTitleText.getGlobalBounds().position.y });

        //
        m_fadeRectangle.setFillColor(t_context.config.stage_background_color);
        m_fadeRectangle.setSize(screenRect.size);

        //
        m_errorText = t_context.fonts.makeText(FontSize::Medium, "");

        //
        updateAllAfterListboxChange(t_context);
    }

    void StateInventory::update(const Context & t_context, const float t_frameTimeSec)
    {
        t_context.framerate.update(t_context);
        t_context.anim.update(t_context, t_frameTimeSec);

        const float errorTextFadeDuration{ 5.0f };
        m_errorTextElapsedSec += t_frameTimeSec;
        if (m_errorTextElapsedSec < errorTextFadeDuration)
        {
            sf::Color color{ m_errorText.getFillColor() };

            color.a = static_cast<uint8_t>(
                255 - util::map(m_errorTextElapsedSec, 0.0f, errorTextFadeDuration, 0, 255));

            m_errorText.setFillColor(color);
        }
    }

    void StateInventory::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.monsters.drawHealthLines(t_context, t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.anim.draw(t_target, t_states);
        t_context.framerate.draw(t_target, t_states);

        t_target.draw(m_fadeRectangle, t_states);
        t_target.draw(t_context.top_panel, t_states);
        t_target.draw(*m_unListboxUPtr, t_states);
        t_target.draw(*m_eqListboxUPtr, t_states);
        t_target.draw(m_itemDescText, t_states);
        t_target.draw(m_itemHintText, t_states);
        t_target.draw(m_errorText, t_states);
        t_target.draw(m_unTitleText, t_states);
        t_target.draw(m_eqTitleText, t_states);

        t_target.draw(m_statRectangle, t_states);

        t_target.draw(m_healthText, t_states);
        t_target.draw(m_manaText, t_states);
        t_target.draw(m_levelText, t_states);
        t_target.draw(m_goldText, t_states);
        t_target.draw(m_armorText, t_states);
        t_target.draw(m_weaponText, t_states);

        t_target.draw(m_strTitleText, t_states);
        t_target.draw(m_dexTitleText, t_states);
        t_target.draw(m_accTitleText, t_states);
        t_target.draw(m_lckTitleText, t_states);
        t_target.draw(m_arcTitleText, t_states);

        t_target.draw(m_strValueText, t_states);
        t_target.draw(m_dexValueText, t_states);
        t_target.draw(m_accValueText, t_states);
        t_target.draw(m_lckValueText, t_states);
        t_target.draw(m_arcValueText, t_states);

        t_target.draw(m_instructionText1, t_states);
        t_target.draw(m_instructionText2, t_states);
        t_target.draw(m_instructionText3, t_states);
        t_target.draw(m_instructionText4, t_states);
        t_target.draw(m_instructionText5, t_states);
    }

    void StateInventory::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>();
        if (!keyPtr)
        {
            return;
        }

        if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
        {
            t_context.state.setChangePending(State::Play);
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::E)
        {
            if (!m_unListboxUPtr->getFocus())
            {
                showErrorText(
                    t_context, "First press the left arrow key to select an unequipped item.");

                return;
            }

            if (m_unListboxUPtr->empty())
            {
                showErrorText(t_context, "You have no unequipped items to equip.");
                return;
            }

            const item::Item itemCopy{ t_context.player.inventory().unItems().at(
                m_unListboxUPtr->selectedIndex()) };

            const std::string resultStr{ t_context.player.inventory().equip(
                m_unListboxUPtr->selectedIndex()) };

            if (!resultStr.empty())
            {
                showErrorText(t_context, resultStr);
                return;
            }

            updateAllAfterListboxChange(t_context);

            if (itemCopy.isWeapon())
            {
                t_context.sfx.play("equip-blade");
            }
            else
            {
                t_context.sfx.play("equip-armor");
            }
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::U)
        {
            if (!m_eqListboxUPtr->getFocus())
            {
                showErrorText(
                    t_context, "First press the right arrow key to select an equipped item.");

                return;
            }

            if (m_eqListboxUPtr->empty())
            {
                showErrorText(t_context, "You have no equipped items to unequip.");
                return;
            }

            t_context.player.inventory().unequip(m_eqListboxUPtr->selectedIndex());
            updateAllAfterListboxChange(t_context);
            t_context.sfx.play("cloth");
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::S)
        {
            swapItems(t_context);
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::D)
        {
            if (!m_unListboxUPtr->getFocus())
            {
                showErrorText(
                    t_context, "Only unequipped items can be dropped.  Unequip this item first.");

                return;
            }

            if (m_unListboxUPtr->empty())
            {
                showErrorText(t_context, "You have no unequipped items to drop.");
                return;
            }

            t_context.player.inventory().remove(m_unListboxUPtr->selectedIndex());
            updateAllAfterListboxChange(t_context);
            t_context.sfx.play("drop");
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Left)
        {
            if (!m_unListboxUPtr->getFocus())
            {
                m_unListboxUPtr->setFocus(true);
                m_eqListboxUPtr->setFocus(false);
                updateAllAfterListboxChange(t_context);
                t_context.sfx.play("tick-on");
            }
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Right)
        {
            if (!m_eqListboxUPtr->getFocus())
            {
                m_unListboxUPtr->setFocus(false);
                m_eqListboxUPtr->setFocus(true);
                updateAllAfterListboxChange(t_context);
                t_context.sfx.play("tick-on");
            }
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Up)
        {
            if (m_unListboxUPtr->getFocus())
            {
                if (m_unListboxUPtr->selectPrev())
                {
                    updateAllAfterListboxChange(t_context);
                    t_context.sfx.play("tick-on");
                }
            }
            else if (m_eqListboxUPtr->getFocus())
            {
                if (m_eqListboxUPtr->selectPrev())
                {
                    updateAllAfterListboxChange(t_context);
                    t_context.sfx.play("tick-on");
                }
            }
        }
        else if (keyPtr->scancode == sf::Keyboard::Scancode::Down)
        {
            if (m_unListboxUPtr->getFocus())
            {
                if (m_unListboxUPtr->selectNext())
                {
                    updateAllAfterListboxChange(t_context);
                    t_context.sfx.play("tick-on");
                }
            }
            else if (m_eqListboxUPtr->getFocus())
            {
                if (m_eqListboxUPtr->selectNext())
                {
                    updateAllAfterListboxChange(t_context);
                    t_context.sfx.play("tick-on");
                }
            }
        }
    }

    void StateInventory::updateAllAfterListboxChange(const Context & t_context)
    {
        t_context.player.updateEquipEffects();
        m_unListboxUPtr->redraw();
        m_eqListboxUPtr->redraw();
        updateStatText(t_context);
        updateItemDescText(t_context);
        updateEquipHintText(t_context);
        updateWeaponText(t_context);
    }

    void StateInventory::showErrorText(const Context & t_context, const std::string & t_message)
    {
        m_errorTextElapsedSec = 0.0f;
        m_errorText.setString(t_message);
        m_errorText.setFillColor(sf::Color(255, 100, 100));

        m_errorText.setPosition({ ((t_context.layout.screenRect().size.x * 0.5f) -
                                   (m_errorText.getGlobalBounds().size.x * 0.5f)),
                                  (util::bottom(m_itemDescText) + 20.0f) });

        t_context.sfx.play("error-1");
    }

    void StateInventory::updateItemDescText(const Context & t_context)
    {
        std::string descStr{ "" };

        if (m_unListboxUPtr->getFocus() && !m_unListboxUPtr->empty())
        {
            const std::size_t index{ m_unListboxUPtr->selectedIndex() };
            if (index < t_context.player.inventory().unItems().size())
            {
                descStr = t_context.player.inventory().unItems().at(index).description();
            }
        }
        else if (m_eqListboxUPtr->getFocus() && !m_eqListboxUPtr->empty())
        {
            const std::size_t index{ m_eqListboxUPtr->selectedIndex() };
            if (index < t_context.player.inventory().eqItems().size())
            {
                descStr = t_context.player.inventory().eqItems().at(index).description();
            }
        }

        m_itemDescText.setString(descStr);

        m_itemDescText.setPosition({ ((t_context.layout.screenRect().size.x * 0.5f) -
                                      (m_itemDescText.getGlobalBounds().size.x * 0.5f)),
                                     util::bottom(*m_unListboxUPtr) });
    }

    void StateInventory::updateStatText(const Context & t_context)
    {
        m_strValueText.setString(std::to_string(t_context.player.strength().current()));
        m_dexValueText.setString(std::to_string(t_context.player.dexterity().current()));
        m_accValueText.setString(std::to_string(t_context.player.accuracy().current()));
        m_lckValueText.setString(std::to_string(t_context.player.luck().current()));
        m_arcValueText.setString(std::to_string(t_context.player.arcane().current()));

        std::string str{ "Armor: " };
        str += std::to_string(t_context.player.armor().get());
        m_armorText.setString(str);
    }

    void StateInventory::updateEquipHintText(const Context & t_context)
    {
        if (!m_unListboxUPtr->getFocus() || m_unListboxUPtr->empty())
        {
            m_itemHintText.setString("");
            return;
        }

        const item::Item & unEquippedItem{ t_context.player.inventory().unItems().at(
            m_unListboxUPtr->selectedIndex()) };

        const std::string equipHintStr{ equipHintMessage(t_context, unEquippedItem) };

        if (equipHintStr.empty())
        {
            m_itemHintText.setString("");
            return;
        }

        m_itemHintText.setString(equipHintStr);

        m_itemHintText.setPosition({ ((t_context.layout.screenRect().size.x * 0.5f) -
                                      (m_itemHintText.getGlobalBounds().size.x * 0.5f)),
                                     (util::bottom(m_itemDescText) + 0.0f) });
    }

    void StateInventory::updateWeaponText(const Context & t_context)
    {
        const std::optional<item::Item> eqWeaponOpt{
            t_context.player.inventory().weaponEquipped()
        };

        if (!eqWeaponOpt.has_value())
        {
            m_weaponText.setString("Weapon Damage: 1 to 2 (fists)");
            return;
        }

        const item::Item & weapon{ eqWeaponOpt.value() };

        std::string weaponStr{ "Weapon Damage: " };
        weaponStr += std::to_string(weapon.damageMin());
        weaponStr += " to ";
        weaponStr += std::to_string(weapon.damageMax());

        m_weaponText.setString(weaponStr);
    }

    const std::string StateInventory::equipHintMessage(
        const Context & t_context, const item::Item & t_unEquipItem) const
    {
        if (m_eqListboxUPtr->empty())
        {
            return "";
        }

        const auto & inventory{ t_context.player.inventory() };

        if (t_unEquipItem.isWeapon())
        {
            const std::optional<item::Item> eqWeaponOpt{ inventory.weaponEquipped() };
            if (!eqWeaponOpt.has_value())
            {
                return "Hint: You have no weapon equipped, so you should equip this weapon.";
            }

            if (eqWeaponOpt.value().value() < t_unEquipItem.value())
            {
                return "Hint: This weapon is considered more valuable than the weapon you have "
                       "equipped, so you should consider equipping this one instead.";
            }
        }
        else if (t_unEquipItem.isArmor())
        {
            std::optional<item::Item> eqAmorOfSameType{};
            for (const item::Item & eqItem : inventory.eqItems())
            {
                if (eqItem.isArmor() && eqItem.armorType() == t_unEquipItem.armorType())
                {
                    eqAmorOfSameType = eqItem;
                    break;
                }
            }

            if (!eqAmorOfSameType.has_value())
            {
                std::string message{ "Hint: You have no " };
                message += item::toString(t_unEquipItem.armorType());
                message += " equipped, so you should equip this piece of armor.";
                return message;
            }

            if (eqAmorOfSameType.value().value() < t_unEquipItem.value())
            {
                std::string message{ "Hint: This item is considered more valuable than the " };
                message += item::toString(t_unEquipItem.armorType());
                message += " you have equipped, so you should consider equipping this one instead.";
                return message;
            }
        }

        return "";
    }

    void StateInventory::swapItems(const Context & t_context)
    {
        if (!m_unListboxUPtr->getFocus())
        {
            showErrorText(t_context, "You can only swap unequipped items.");
            return;
        }

        if (m_unListboxUPtr->empty())
        {
            showErrorText(t_context, "You have no unequipped items to swap.");
            return;
        }

        if (m_eqListboxUPtr->empty())
        {
            showErrorText(t_context, "You have no equipped items to swap.");
            return;
        }

        const item::Item unEqItem{ t_context.player.inventory().unItems().at(
            m_unListboxUPtr->selectedIndex()) };

        std::optional<item::Item> eqItemOpt;

        if (unEqItem.isWeapon())
        {
            for (const item::Item & item : t_context.player.inventory().eqItems())
            {
                if (item.isWeapon())
                {
                    eqItemOpt = item;
                    break;
                }
            }

            if (!eqItemOpt.has_value())
            {
                showErrorText(t_context, "You can't swap because there is no equippped weapon.");
                return;
            }
        }
        else if (unEqItem.isArmor())
        {
            for (const item::Item & item : t_context.player.inventory().eqItems())
            {
                if (item.isArmor() && (item.armorType() == unEqItem.armorType()))
                {
                    eqItemOpt = item;
                    break;
                }
            }

            if (!eqItemOpt.has_value())
            {
                std::string message{ "You can't swap because there is no equippped " };
                message += item::toString(unEqItem.armorType());
                message += '.';

                showErrorText(t_context, message);
                return;
            }
        }
        else
        {
            showErrorText(t_context, "You can only swap weapons and armor items.");
            return;
        }

        std::size_t eqIndex{ 0 };
        for (; eqIndex < t_context.player.inventory().eqItems().size(); ++eqIndex)
        {
            if (eqItemOpt.value().name() ==
                t_context.player.inventory().eqItems().at(eqIndex).name())
            {
                break;
            }
        }

        t_context.player.inventory().unequip(eqIndex);

        const std::string equipMessage{ t_context.player.inventory().equip(
            m_unListboxUPtr->selectedIndex()) };

        {
            bool didSelectNextSucceed{ true };
            while (didSelectNextSucceed)
            {
                didSelectNextSucceed = m_unListboxUPtr->selectNext();
            }
        }

        if (!equipMessage.empty())
        {
            t_context.player.inventory().equip(m_unListboxUPtr->selectedIndex());
            updateAllAfterListboxChange(t_context);
            showErrorText(t_context, equipMessage);
            return;
        }

        {
            bool didSelectNextSucceed{ true };
            while (didSelectNextSucceed)
            {
                didSelectNextSucceed = m_eqListboxUPtr->selectNext();
            }
        }

        updateAllAfterListboxChange(t_context);

        if (unEqItem.isWeapon())
        {
            t_context.sfx.play("equip-blade");
        }
        else
        {
            t_context.sfx.play("equip-armor");
        }
    }

} // namespace castlecrawl
