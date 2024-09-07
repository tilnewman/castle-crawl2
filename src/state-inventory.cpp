// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-inventory.cpp
//
#include "state-inventory.hpp"

#include "context.hpp"
#include "enemy.hpp"
#include "framerate-text.hpp"
#include "inventory.hpp"
#include "item-factory.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "top-panel.hpp"

namespace castlecrawl
{

    StateInventory::StateInventory()
        : m_fadeRectangle{}
        , m_unTitleText{}
        , m_unListboxUPtr{}
        , m_eqTitleText{}
        , m_eqListboxUPtr{}
        , m_itemDescText{}
        , m_errorText{}
        , m_strTitleText{}
        , m_dexTitleText{}
        , m_accTitleText{}
        , m_lckTitleText{}
        , m_arcTitleText{}
        , m_strValueText{}
        , m_dexValueText{}
        , m_accValueText{}
        , m_lckValueText{}
        , m_arcValueText{}
        , m_goldText{}
        , m_armorText{}
        , m_statRectangle{}
    {}

    void StateInventory::onEnter(const Context & t_context)
    {
        m_unListboxUPtr = std::make_unique<Listbox>(t_context.player.inventory().unItems());
        m_eqListboxUPtr = std::make_unique<Listbox>(t_context.player.inventory().eqItems());

        //

        const sf::FloatRect screenRect = t_context.layout.screenRect();
        const float pad{ screenRect.width * 0.0025f };
        const float padLarge{ pad * 10.0f };
        const sf::FloatRect botRect = t_context.layout.botRect();

        //

        m_strTitleText = t_context.fonts.makeText(FontSize::Medium, "Strength");
        m_dexTitleText = t_context.fonts.makeText(FontSize::Medium, "Dexterity");
        m_accTitleText = t_context.fonts.makeText(FontSize::Medium, "Accuracy");
        m_lckTitleText = t_context.fonts.makeText(FontSize::Medium, "Luck");
        m_arcTitleText = t_context.fonts.makeText(FontSize::Medium, "Arcane");

        m_strTitleText.setPosition((screenRect.width * 0.25f), (botRect.top + padLarge));

        const float statTextVertPad = 5.0f; // TODO make this based on m_strTitleText height

        m_dexTitleText.setPosition(
            m_strTitleText.getPosition().x, (util::bottom(m_strTitleText) + statTextVertPad));

        m_accTitleText.setPosition(
            m_strTitleText.getPosition().x, (util::bottom(m_dexTitleText) + statTextVertPad));

        m_lckTitleText.setPosition(
            m_strTitleText.getPosition().x, (util::bottom(m_accTitleText) + statTextVertPad));

        m_arcTitleText.setPosition(
            m_strTitleText.getPosition().x, (util::bottom(m_lckTitleText) + statTextVertPad));

        //

        m_strValueText = t_context.fonts.makeText(FontSize::Medium, "");
        m_dexValueText = t_context.fonts.makeText(FontSize::Medium, "");
        m_accValueText = t_context.fonts.makeText(FontSize::Medium, "");
        m_lckValueText = t_context.fonts.makeText(FontSize::Medium, "");
        m_arcValueText = t_context.fonts.makeText(FontSize::Medium, "");

        const float valueTextHorizPos = (util::right(m_dexTitleText) + padLarge);

        m_strValueText.setPosition(valueTextHorizPos, m_strTitleText.getGlobalBounds().top - 7.0f);
        m_dexValueText.setPosition(valueTextHorizPos, m_dexTitleText.getGlobalBounds().top - 7.0f);
        m_accValueText.setPosition(valueTextHorizPos, m_accTitleText.getGlobalBounds().top - 7.0f);
        m_lckValueText.setPosition(valueTextHorizPos, m_lckTitleText.getGlobalBounds().top - 7.0f);
        m_arcValueText.setPosition(valueTextHorizPos, m_arcTitleText.getGlobalBounds().top - 7.0f);

        updateStatText(t_context);

        //

        m_statRectangle.setFillColor(sf::Color(255, 255, 255, 32));
        m_statRectangle.setOutlineColor(sf::Color(255, 255, 255, 64));
        m_statRectangle.setOutlineThickness(2.0f);

        m_statRectangle.setPosition(
            (m_strTitleText.getPosition().x - pad), (m_strTitleText.getPosition().y - pad));

        m_statRectangle.setSize(
            { (screenRect.width - (m_statRectangle.getPosition().x * 2.0f)),
              (util::bottom(m_arcValueText) - m_strTitleText.getPosition().y) + pad });

        //

        std::string goldStr{ "Gold: " };
        goldStr += std::to_string(t_context.player.gold());
        m_goldText = t_context.fonts.makeText(FontSize::Medium, goldStr, sf::Color(255, 200, 100));
        util::centerInside(m_goldText, m_statRectangle.getGlobalBounds());
        m_goldText.move(0.0f, -m_goldText.getGlobalBounds().height);
        m_goldText.move(0.0f, -pad);

        //

        std::string armorStr{ "Armor: " };
        armorStr += std::to_string(t_context.player.armor().get());
        m_armorText = t_context.fonts.makeText(FontSize::Medium, armorStr);
        m_armorText.setPosition(m_goldText.getPosition().x, (util::bottom(m_goldText) + pad));

        //

        m_unListboxUPtr->setup(
            t_context, FontSize::Medium, t_context.items.textExtents().longest_name, 16);

        m_eqListboxUPtr->setup(
            t_context, FontSize::Medium, t_context.items.textExtents().longest_name, 16);

        m_unListboxUPtr->setPosition(
            { ((screenRect.width * 0.5f) - m_unListboxUPtr->getGlobalBounds().width) - pad,
              (util::bottom(m_statRectangle) + (padLarge * 2.0f)) });

        m_eqListboxUPtr->setPosition(
            { ((screenRect.width * 0.5f) + pad), m_unListboxUPtr->getGlobalBounds().top });

        m_unListboxUPtr->setFocus(true);
        m_eqListboxUPtr->setFocus(false);

        m_itemDescText = t_context.fonts.makeText(FontSize::Small, "");
        updateItemDescText(t_context);

        m_unTitleText = t_context.fonts.makeText(
            FontSize::Small, "Unequipped Items:", sf::Color(255, 255, 255, 160));

        m_unTitleText.setPosition(
            m_unListboxUPtr->getGlobalBounds().left,
            (m_unListboxUPtr->getGlobalBounds().top - m_unTitleText.getGlobalBounds().height));

        m_eqTitleText = t_context.fonts.makeText(
            FontSize::Small, "Equipped Items:", sf::Color(255, 255, 255, 160));

        m_eqTitleText.setPosition(
            m_eqListboxUPtr->getGlobalBounds().left, m_unTitleText.getGlobalBounds().top);

        //

        m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, 190));
        m_fadeRectangle.setSize(util::size(screenRect));

        //

        m_errorText = t_context.fonts.makeText(FontSize::Medium, "");
    }

    void StateInventory::update(const Context & t_context, const float)
    {
        t_context.framerate.update();

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
        t_context.enemies.draw(t_context, t_target, t_states);
        t_context.player_display.draw(t_context, t_target, t_states);
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
        if (t_event.type != sf::Event::KeyPressed)
        {
            return;
        }

        if (t_event.key.code == sf::Keyboard::Escape)
        {
            t_context.state.change(t_context, State::Play);
            return;
        }
        else if (t_event.key.code == sf::Keyboard::E)
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
                    return;
                }
                else
                {
                    m_errorText.setString(resultStr);
                    m_errorText.setFillColor(sf::Color::Red);

                    m_errorText.setPosition(
                        ((t_context.layout.screenRect().width * 0.5f) -
                         (m_errorText.getGlobalBounds().width * 0.5f)),
                        (util::bottom(m_itemDescText) + 20.0f));

                    t_context.sfx.play("error-1.ogg");
                    return;
                }
            }
            else
            {
                t_context.sfx.play("error-1.ogg");
                return;
            }
        }
        else if (t_event.key.code == sf::Keyboard::U)
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
                return;
            }

            t_context.sfx.play("error-1.ogg");
            return;
        }
        else if (t_event.key.code == sf::Keyboard::Left)
        {
            if (!m_unListboxUPtr->getFocus())
            {
                m_unListboxUPtr->setFocus(true);
                m_eqListboxUPtr->setFocus(false);
                updateItemDescText(t_context);
                t_context.sfx.play("tick-on");
            }

            return;
        }
        else if (t_event.key.code == sf::Keyboard::Right)
        {
            if (!m_eqListboxUPtr->getFocus())
            {
                m_unListboxUPtr->setFocus(false);
                m_eqListboxUPtr->setFocus(true);
                updateItemDescText(t_context);
                t_context.sfx.play("tick-on");
            }

            return;
        }
        else if (t_event.key.code == sf::Keyboard::Up)
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
            return;
        }
        else if (t_event.key.code == sf::Keyboard::Down)
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
            return;
        }
    }

    void StateInventory::updateItemDescText(const Context & context)
    {
        m_itemDescText.setString("");

        if (m_unListboxUPtr->getFocus() && !m_unListboxUPtr->empty())
        {
            const std::size_t index = m_unListboxUPtr->selectedIndex();
            if (index < context.player.inventory().unItems().size())
            {
                m_itemDescText.setString(
                    context.player.inventory().unItems().at(index).description());
            }
        }
        else if (m_eqListboxUPtr->getFocus() && !m_eqListboxUPtr->empty())
        {
            const std::size_t index = m_eqListboxUPtr->selectedIndex();
            if (index < context.player.inventory().eqItems().size())
            {
                m_itemDescText.setString(
                    context.player.inventory().eqItems().at(index).description());
            }
        }

        m_itemDescText.setPosition(
            ((context.layout.screenRect().width * 0.5f) -
             (m_itemDescText.getGlobalBounds().width * 0.5f)),
            util::bottom(*m_unListboxUPtr));
    }

    void StateInventory::updateStatText(const Context & context)
    {
        std::string str;

        str = std::to_string(context.player.strength().current());
        str += "/";
        str += std::to_string(context.player.strength().max());
        m_strValueText.setString(str);

        str = std::to_string(context.player.dexterity().current());
        str += "/";
        str += std::to_string(context.player.dexterity().max());
        m_dexValueText.setString(str);

        str = std::to_string(context.player.accuracy().current());
        str += "/";
        str += std::to_string(context.player.accuracy().max());
        m_accValueText.setString(str);

        str = std::to_string(context.player.luck().current());
        str += "/";
        str += std::to_string(context.player.luck().max());
        m_lckValueText.setString(str);

        str = std::to_string(context.player.arcane().current());
        str += "/";
        str += std::to_string(context.player.arcane().max());
        m_arcValueText.setString(str);

        str = "Armor: ";
        str += std::to_string(context.player.armor().get());
        m_armorText.setString(str);
    }

} // namespace castlecrawl
