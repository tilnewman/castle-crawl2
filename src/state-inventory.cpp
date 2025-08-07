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
#include "player-display.hpp"
#include "player.hpp"
#include "sfml-defaults.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    StateInventory::StateInventory()
        : m_fadeRectangle{}
        , m_unTitleText{ util::SfmlDefaults::instance().font() }
        , m_unListboxUPtr{}
        , m_eqTitleText{ util::SfmlDefaults::instance().font() }
        , m_eqListboxUPtr{}
        , m_itemDescText{ util::SfmlDefaults::instance().font() }
        , m_errorText{ util::SfmlDefaults::instance().font() }
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
        , m_goldText{ util::SfmlDefaults::instance().font() }
        , m_armorText{ util::SfmlDefaults::instance().font() }
        , m_statRectangle{}
    {}

    void StateInventory::onEnter(const Context & t_context)
    {
        m_unListboxUPtr = std::make_unique<Listbox>(t_context.player.inventory().unItems());
        m_eqListboxUPtr = std::make_unique<Listbox>(t_context.player.inventory().eqItems());

        //

        const sf::FloatRect screenRect = t_context.layout.screenRect();
        const float pad{ screenRect.size.x * 0.0025f };
        const float padLarge{ pad * 10.0f };
        const sf::FloatRect botRect = t_context.layout.botRect();

        //

        m_strTitleText = t_context.fonts.makeText(FontSize::Medium, "Strength");
        m_dexTitleText = t_context.fonts.makeText(FontSize::Medium, "Dexterity");
        m_accTitleText = t_context.fonts.makeText(FontSize::Medium, "Accuracy");
        m_lckTitleText = t_context.fonts.makeText(FontSize::Medium, "Luck");
        m_arcTitleText = t_context.fonts.makeText(FontSize::Medium, "Arcane");

        m_strTitleText.setPosition(
            { (screenRect.size.x * 0.25f), (botRect.position.y + padLarge) });

        const float statTextVertPad = 5.0f; // TODO make this based on m_strTitleText height

        m_dexTitleText.setPosition(
            { m_strTitleText.getPosition().x, (util::bottom(m_strTitleText) + statTextVertPad) });

        m_accTitleText.setPosition(
            { m_strTitleText.getPosition().x, (util::bottom(m_dexTitleText) + statTextVertPad) });

        m_lckTitleText.setPosition(
            { m_strTitleText.getPosition().x, (util::bottom(m_accTitleText) + statTextVertPad) });

        m_arcTitleText.setPosition(
            { m_strTitleText.getPosition().x, (util::bottom(m_lckTitleText) + statTextVertPad) });

        //

        m_strValueText = t_context.fonts.makeText(FontSize::Medium, "");
        m_dexValueText = t_context.fonts.makeText(FontSize::Medium, "");
        m_accValueText = t_context.fonts.makeText(FontSize::Medium, "");
        m_lckValueText = t_context.fonts.makeText(FontSize::Medium, "");
        m_arcValueText = t_context.fonts.makeText(FontSize::Medium, "");

        const float valueTextHorizPos = (util::right(m_dexTitleText) + padLarge);

        m_strValueText.setPosition(
            { valueTextHorizPos, m_strTitleText.getGlobalBounds().position.y - 7.0f });

        m_dexValueText.setPosition(
            { valueTextHorizPos, m_dexTitleText.getGlobalBounds().position.y - 7.0f });

        m_accValueText.setPosition(
            { valueTextHorizPos, m_accTitleText.getGlobalBounds().position.y - 7.0f });

        m_lckValueText.setPosition(
            { valueTextHorizPos, m_lckTitleText.getGlobalBounds().position.y - 7.0f });

        m_arcValueText.setPosition(
            { valueTextHorizPos, m_arcTitleText.getGlobalBounds().position.y - 7.0f });

        updateStatText(t_context);

        //

        m_statRectangle.setFillColor(sf::Color(255, 255, 255, 32));
        m_statRectangle.setOutlineColor(sf::Color(255, 255, 255, 64));
        m_statRectangle.setOutlineThickness(2.0f);

        m_statRectangle.setPosition(
            { (m_strTitleText.getPosition().x - pad), (m_strTitleText.getPosition().y - pad) });

        m_statRectangle.setSize(
            { (screenRect.size.x - (m_statRectangle.getPosition().x * 2.0f)),
              (util::bottom(m_arcValueText) - m_strTitleText.getPosition().y) + pad });

        //

        std::string goldStr{ "Gold: " };
        goldStr += std::to_string(t_context.player.gold());
        m_goldText = t_context.fonts.makeText(FontSize::Medium, goldStr, sf::Color(255, 200, 100));
        util::centerInside(m_goldText, m_statRectangle.getGlobalBounds());
        m_goldText.move({ 0.0f, -m_goldText.getGlobalBounds().size.y });
        m_goldText.move({ 0.0f, -pad });

        //

        std::string armorStr{ "Armor: " };
        armorStr += std::to_string(t_context.player.armor().get());
        m_armorText = t_context.fonts.makeText(FontSize::Medium, armorStr);
        m_armorText.setPosition({ m_goldText.getPosition().x, (util::bottom(m_goldText) + pad) });

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

        m_itemDescText = t_context.fonts.makeText(FontSize::Small, "");
        updateItemDescText(t_context);

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

        m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, 190));
        m_fadeRectangle.setSize(screenRect.size);

        //

        m_errorText = t_context.fonts.makeText(FontSize::Medium, "");
    }

    void StateInventory::update(const Context & t_context, const float t_frameTimeSec)
    {
        t_context.framerate.update();
        t_context.anim.update(t_context, t_frameTimeSec);

        if (m_errorText.getFillColor().a > 0)
        {
            sf::Color color = m_errorText.getFillColor();
            --color.a;
            m_errorText.setFillColor(color);
        }
    }

    void StateInventory::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
        t_context.anim.draw(t_target, t_states);
        t_context.framerate.draw(t_target, t_states);

        t_target.draw(m_fadeRectangle, t_states);
        t_target.draw(t_context.top_panel, t_states);
        t_target.draw(*m_unListboxUPtr, t_states);
        t_target.draw(*m_eqListboxUPtr, t_states);
        t_target.draw(m_itemDescText, t_states);
        t_target.draw(m_errorText, t_states);
        t_target.draw(m_unTitleText, t_states);
        t_target.draw(m_eqTitleText, t_states);

        t_target.draw(m_statRectangle, t_states);

        t_target.draw(m_goldText, t_states);
        t_target.draw(m_armorText, t_states);

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
    }

    void StateInventory::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        // all other handlers are key pressed events
        if (const auto * keyPtr = t_event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPtr->scancode == sf::Keyboard::Scancode::Escape)
            {
                t_context.state.change(t_context, State::Play);
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::E)
            {
                if (m_unListboxUPtr->getFocus() && !m_unListboxUPtr->empty())
                {
                    const std::string resultStr =
                        t_context.player.inventory().equip(m_unListboxUPtr->selectedIndex());

                    if (resultStr.empty())
                    {
                        t_context.player.updateEquipEffects();
                        m_unListboxUPtr->redraw();
                        m_eqListboxUPtr->redraw();
                        updateStatText(t_context);
                        updateItemDescText(t_context);
                        t_context.sfx.play("equip.ogg");
                    }
                    else
                    {
                        m_errorText.setString(resultStr);
                        m_errorText.setFillColor(sf::Color::Red);

                        m_errorText.setPosition({ ((t_context.layout.screenRect().size.x * 0.5f) -
                                                   (m_errorText.getGlobalBounds().size.x * 0.5f)),
                                                  (util::bottom(m_itemDescText) + 20.0f) });

                        t_context.sfx.play("error-1.ogg");
                    }
                }
                else
                {
                    t_context.sfx.play("error-1.ogg");
                }
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::U)
            {
                if (m_eqListboxUPtr->getFocus() && !m_eqListboxUPtr->empty())
                {
                    t_context.player.inventory().unequip(m_eqListboxUPtr->selectedIndex());
                    t_context.player.updateEquipEffects();
                    m_unListboxUPtr->redraw();
                    m_eqListboxUPtr->redraw();
                    updateStatText(t_context);
                    updateItemDescText(t_context);
                    t_context.sfx.play("cloth.ogg");
                }
                else
                {
                    t_context.sfx.play("error-1.ogg");
                }
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::Left)
            {
                if (!m_unListboxUPtr->getFocus())
                {
                    m_unListboxUPtr->setFocus(true);
                    m_eqListboxUPtr->setFocus(false);
                    updateItemDescText(t_context);
                    t_context.sfx.play("tick-on");
                }
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::Right)
            {
                if (!m_eqListboxUPtr->getFocus())
                {
                    m_unListboxUPtr->setFocus(false);
                    m_eqListboxUPtr->setFocus(true);
                    updateItemDescText(t_context);
                    t_context.sfx.play("tick-on");
                }
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::Up)
            {
                if (m_unListboxUPtr->getFocus())
                {
                    m_unListboxUPtr->selectPrev();
                }
                else
                {
                    m_eqListboxUPtr->selectPrev();
                }

                updateItemDescText(t_context);
                t_context.sfx.play("tick-on");
            }
            else if (keyPtr->scancode == sf::Keyboard::Scancode::Down)
            {
                if (m_unListboxUPtr->getFocus())
                {
                    m_unListboxUPtr->selectNext();
                }
                else
                {
                    m_eqListboxUPtr->selectNext();
                }

                updateItemDescText(t_context);
                t_context.sfx.play("tick-on");
            }
        }
    }

    void StateInventory::updateItemDescText(const Context & t_context)
    {
        m_itemDescText.setString("");

        if (m_unListboxUPtr->getFocus() && !m_unListboxUPtr->empty())
        {
            const std::size_t index = m_unListboxUPtr->selectedIndex();
            if (index < t_context.player.inventory().unItems().size())
            {
                m_itemDescText.setString(
                    t_context.player.inventory().unItems().at(index).description());
            }
        }
        else if (m_eqListboxUPtr->getFocus() && !m_eqListboxUPtr->empty())
        {
            const std::size_t index = m_eqListboxUPtr->selectedIndex();
            if (index < t_context.player.inventory().eqItems().size())
            {
                m_itemDescText.setString(
                    t_context.player.inventory().eqItems().at(index).description());
            }
        }

        m_itemDescText.setPosition({ ((t_context.layout.screenRect().size.x * 0.5f) -
                                      (m_itemDescText.getGlobalBounds().size.x * 0.5f)),
                                     util::bottom(*m_unListboxUPtr) });
    }

    void StateInventory::updateStatText(const Context & t_context)
    {
        std::string str;

        str = std::to_string(t_context.player.strength().current());
        str += "/";
        str += std::to_string(t_context.player.strength().max());
        m_strValueText.setString(str);

        str = std::to_string(t_context.player.dexterity().current());
        str += "/";
        str += std::to_string(t_context.player.dexterity().max());
        m_dexValueText.setString(str);

        str = std::to_string(t_context.player.accuracy().current());
        str += "/";
        str += std::to_string(t_context.player.accuracy().max());
        m_accValueText.setString(str);

        str = std::to_string(t_context.player.luck().current());
        str += "/";
        str += std::to_string(t_context.player.luck().max());
        m_lckValueText.setString(str);

        str = std::to_string(t_context.player.arcane().current());
        str += "/";
        str += std::to_string(t_context.player.arcane().max());
        m_arcValueText.setString(str);

        str = "Armor: ";
        str += std::to_string(t_context.player.armor().get());
        m_armorText.setString(str);
    }

} // namespace castlecrawl
