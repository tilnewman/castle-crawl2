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
        : m_fadeRectangle()
        , m_unTitleText()
        , m_unListboxUPtr()
        , m_eqTitleText()
        , m_eqListboxUPtr()
        , m_itemDescText()
        , m_errorText()
        , m_strTitleText()
        , m_dexTitleText()
        , m_accTitleText()
        , m_lckTitleText()
        , m_arcTitleText()
        , m_strValueText()
        , m_dexValueText()
        , m_accValueText()
        , m_lckValueText()
        , m_arcValueText()
        , m_goldText()
        , m_armorText()
        , m_statRectangle()
    {}

    void StateInventory::onEnter(const Context & context)
    {
        m_unListboxUPtr = std::make_unique<Listbox>(context.player.inventory().unItems());
        m_eqListboxUPtr = std::make_unique<Listbox>(context.player.inventory().eqItems());

        //

        const sf::FloatRect screenRect = context.layout.screenRect();
        const float pad{ screenRect.width * 0.0025f };
        const float padLarge{ pad * 10.0f };
        const sf::FloatRect botRect = context.layout.botRect();

        //

        m_strTitleText = context.fonts.makeText(FontSize::Medium, "Strength");
        m_dexTitleText = context.fonts.makeText(FontSize::Medium, "Dexterity");
        m_accTitleText = context.fonts.makeText(FontSize::Medium, "Accuracy");
        m_lckTitleText = context.fonts.makeText(FontSize::Medium, "Luck");
        m_arcTitleText = context.fonts.makeText(FontSize::Medium, "Arcane");

        m_strTitleText.setPosition((screenRect.width * 0.25f), (botRect.top + padLarge));

        const float statTextVertPad = 5.0f; //TODO make this based on m_strTitleText height

        m_dexTitleText.setPosition(
            m_strTitleText.getPosition().x, (util::bottom(m_strTitleText) + statTextVertPad));

        m_accTitleText.setPosition(
            m_strTitleText.getPosition().x, (util::bottom(m_dexTitleText) + statTextVertPad));

        m_lckTitleText.setPosition(
            m_strTitleText.getPosition().x, (util::bottom(m_accTitleText) + statTextVertPad));

        m_arcTitleText.setPosition(
            m_strTitleText.getPosition().x, (util::bottom(m_lckTitleText) + statTextVertPad));

        //

        m_strValueText = context.fonts.makeText(FontSize::Medium, "");
        m_dexValueText = context.fonts.makeText(FontSize::Medium, "");
        m_accValueText = context.fonts.makeText(FontSize::Medium, "");
        m_lckValueText = context.fonts.makeText(FontSize::Medium, "");
        m_arcValueText = context.fonts.makeText(FontSize::Medium, "");

        const float valueTextHorizPos = (util::right(m_dexTitleText) + padLarge);

        m_strValueText.setPosition(valueTextHorizPos, m_strTitleText.getGlobalBounds().top - 7.0f);
        m_dexValueText.setPosition(valueTextHorizPos, m_dexTitleText.getGlobalBounds().top - 7.0f);
        m_accValueText.setPosition(valueTextHorizPos, m_accTitleText.getGlobalBounds().top - 7.0f);
        m_lckValueText.setPosition(valueTextHorizPos, m_lckTitleText.getGlobalBounds().top - 7.0f);
        m_arcValueText.setPosition(valueTextHorizPos, m_arcTitleText.getGlobalBounds().top - 7.0f);

        updateStatText(context);

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
        goldStr += std::to_string(context.player.gold());
        m_goldText = context.fonts.makeText(FontSize::Medium, goldStr, sf::Color(255, 200, 100));
        util::centerInside(m_goldText, m_statRectangle.getGlobalBounds());
        m_goldText.move(0.0f, -m_goldText.getGlobalBounds().height);
        m_goldText.move(0.0f, -pad);

        //

        std::string armorStr{ "Armor: " };
        armorStr += std::to_string(context.player.armor().get());
        m_armorText = context.fonts.makeText(FontSize::Medium, armorStr);
        m_armorText.setPosition(m_goldText.getPosition().x, (util::bottom(m_goldText) + pad));

        //

        m_unListboxUPtr->setup(
            context, FontSize::Medium, context.items.textExtents().longest_name, 16);

        m_eqListboxUPtr->setup(
            context, FontSize::Medium, context.items.textExtents().longest_name, 16);

        m_unListboxUPtr->setPosition(
            { ((screenRect.width * 0.5f) - m_unListboxUPtr->getGlobalBounds().width) - pad,
              (util::bottom(m_statRectangle) + (padLarge * 2.0f)) });

        m_eqListboxUPtr->setPosition(
            { ((screenRect.width * 0.5f) + pad), m_unListboxUPtr->getGlobalBounds().top });

        m_unListboxUPtr->setFocus(true);
        m_eqListboxUPtr->setFocus(false);

        m_itemDescText = context.fonts.makeText(FontSize::Small, "");
        updateItemDescText(context);

        m_unTitleText = context.fonts.makeText(
            FontSize::Small, "Unequipped Items:", sf::Color(255, 255, 255, 160));

        m_unTitleText.setPosition(
            m_unListboxUPtr->getGlobalBounds().left,
            (m_unListboxUPtr->getGlobalBounds().top - m_unTitleText.getGlobalBounds().height));

        m_eqTitleText = context.fonts.makeText(
            FontSize::Small, "Equipped Items:", sf::Color(255, 255, 255, 160));

        m_eqTitleText.setPosition(
            m_eqListboxUPtr->getGlobalBounds().left, m_unTitleText.getGlobalBounds().top);

        //

        m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, 190));
        m_fadeRectangle.setSize(util::size(screenRect));

        //

        m_errorText = context.fonts.makeText(FontSize::Medium, "");
    }

    void StateInventory::update(const Context & context, const float)
    {
        context.framerate.update();

        if (m_errorText.getFillColor().a > 0)
        {
            sf::Color color = m_errorText.getFillColor();
            --color.a;
            m_errorText.setFillColor(color);
        }
    }

    void StateInventory::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        context.map_display.draw(context, target, states);
        context.enemies.draw(context, target, states);
        context.player_display.draw(context, target, states);
        context.framerate.draw(target, states);
        target.draw(m_fadeRectangle, states);
        target.draw(context.top_panel, states);
        target.draw(*m_unListboxUPtr, states);
        target.draw(*m_eqListboxUPtr, states);
        target.draw(m_itemDescText, states);
        target.draw(m_errorText, states);
        target.draw(m_unTitleText, states);
        target.draw(m_eqTitleText, states);

        target.draw(m_statRectangle, states);

        target.draw(m_goldText, states);
        target.draw(m_armorText, states);

        target.draw(m_strTitleText, states);
        target.draw(m_dexTitleText, states);
        target.draw(m_accTitleText, states);
        target.draw(m_lckTitleText, states);
        target.draw(m_arcTitleText, states);

        target.draw(m_strValueText, states);
        target.draw(m_dexValueText, states);
        target.draw(m_accValueText, states);
        target.draw(m_lckValueText, states);
        target.draw(m_arcValueText, states);
    }

    void StateInventory::handleEvent(const Context & context, const sf::Event & event)
    {
        // all other handlers are key pressed events
        if (event.type != sf::Event::KeyPressed)
        {
            return;
        }

        if (event.key.code == sf::Keyboard::Escape)
        {
            context.state.change(context, State::Play);
            return;
        }
        else if (event.key.code == sf::Keyboard::E)
        {
            if (m_unListboxUPtr->getFocus() && !m_unListboxUPtr->empty())
            {
                const std::string resultStr =
                    context.player.inventory().equip(m_unListboxUPtr->selectedIndex());

                if (resultStr.empty())
                {
                    context.player.updateEquipEffects();
                    m_unListboxUPtr->redraw();
                    m_eqListboxUPtr->redraw();
                    updateStatText(context);
                    updateItemDescText(context);
                    context.sfx.play("equip.ogg");
                    return;
                }
                else
                {
                    m_errorText.setString(resultStr);
                    m_errorText.setFillColor(sf::Color::Red);

                    m_errorText.setPosition(
                        ((context.layout.screenRect().width * 0.5f) -
                         (m_errorText.getGlobalBounds().width * 0.5f)),
                        (util::bottom(m_itemDescText) + 20.0f));

                    context.sfx.play("error-1.ogg");
                    return;
                }
            }
            else
            {
                context.sfx.play("error-1.ogg");
                return;
            }
        }
        else if (event.key.code == sf::Keyboard::U)
        {
            if (m_eqListboxUPtr->getFocus() && !m_eqListboxUPtr->empty())
            {
                context.player.inventory().unequip(m_eqListboxUPtr->selectedIndex());
                context.player.updateEquipEffects();
                m_unListboxUPtr->redraw();
                m_eqListboxUPtr->redraw();
                updateStatText(context);
                updateItemDescText(context);
                context.sfx.play("cloth.ogg");
                return;
            }

            context.sfx.play("error-1.ogg");
            return;
        }
        else if (event.key.code == sf::Keyboard::Left)
        {
            if (!m_unListboxUPtr->getFocus())
            {
                m_unListboxUPtr->setFocus(true);
                m_eqListboxUPtr->setFocus(false);
                updateItemDescText(context);
                context.sfx.play("tick-on");
            }

            return;
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            if (!m_eqListboxUPtr->getFocus())
            {
                m_unListboxUPtr->setFocus(false);
                m_eqListboxUPtr->setFocus(true);
                updateItemDescText(context);
                context.sfx.play("tick-on");
            }

            return;
        }
        else if (event.key.code == sf::Keyboard::Up)
        {
            if (m_unListboxUPtr->getFocus())
            {
                m_unListboxUPtr->selectPrev();
            }
            else
            {
                m_eqListboxUPtr->selectPrev();
            }

            updateItemDescText(context);
            context.sfx.play("tick-on");
            return;
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            if (m_unListboxUPtr->getFocus())
            {
                m_unListboxUPtr->selectNext();
            }
            else
            {
                m_eqListboxUPtr->selectNext();
            }

            updateItemDescText(context);
            context.sfx.play("tick-on");
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
