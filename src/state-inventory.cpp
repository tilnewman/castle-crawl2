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
    {}

    void StateInventory::onEnter(const Context & context)
    {
        const sf::FloatRect screenRect = context.layout.screenRect();

        m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, 160));
        m_fadeRectangle.setSize(util::size(screenRect));

        // TODO remove after testing
        using namespace item;
        context.player.inventory().add(Item(Armor::Boots, ArmorMaterial::Bronze));
        context.player.inventory().add(Item(Armor::Bracers, ArmorMaterial::DragonScale));
        context.player.inventory().add(Item(Armor::Cuirass, ArmorMaterial::Gold));
        context.player.inventory().add(Item(Armor::Gauntlets, ArmorMaterial::Leather));
        context.player.inventory().add(Item(Armor::Greaves, ArmorMaterial::Platinum));
        context.player.inventory().add(Item(Armor::Helm, ArmorMaterial::Silver));
        context.player.inventory().add(Item(Weapon::Claymore, WeaponMaterial::Bronze));
        context.player.inventory().add(Item(Weapon::Dagger, WeaponMaterial::Diamond));
        context.player.inventory().add(Item(Weapon::Halberd, WeaponMaterial::Gold));
        context.player.inventory().add(Item(Weapon::Handaxe, WeaponMaterial::Obsidian));
        context.player.inventory().add(Item(Weapon::Longsword, WeaponMaterial::Platinum));
        context.player.inventory().add(Item(Weapon::Mace, WeaponMaterial::Silver));
        context.player.inventory().add(Item(Weapon::Scythe, WeaponMaterial::Steel));

        m_unListboxUPtr =
            std::make_unique<Listbox<item::Item>>(context.player.inventory().unItems());

        m_unListboxUPtr->setup(
            context, FontSize::Medium, context.items.textExtents().longest_name, 8);

        m_eqListboxUPtr =
            std::make_unique<Listbox<item::Item>>(context.player.inventory().eqItems());

        m_eqListboxUPtr->setup(
            context, FontSize::Medium, context.items.textExtents().longest_name, 8);

        const float pad{ screenRect.width * 0.0025f };
        const sf::FloatRect mapRect = context.layout.mapRect();

        m_unListboxUPtr->setPosition(
            { ((screenRect.width * 0.5f) - m_unListboxUPtr->getGlobalBounds().width) - pad,
              (mapRect.top + pad) });

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
    }

    void StateInventory::update(const Context & context, const float)
    {
        context.framerate.update();
    }

    void StateInventory::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.clear(context.config.background_color);
        context.map_display.draw(context, target, states);
        context.enemies.draw(context, target, states);
        context.player_display.draw(context, target, states);
        context.framerate.draw(target, states);
        target.draw(m_fadeRectangle, states);
        context.top_panel.draw(context, target, states);
        target.draw(*m_unListboxUPtr, states);
        target.draw(*m_eqListboxUPtr, states);
        target.draw(m_itemDescText, states);
        target.draw(m_unTitleText, states);
        target.draw(m_eqTitleText, states);
    }

    void StateInventory::handleEvent(const Context & context, const sf::Event & event)
    {
        // all other handlers are key released events
        if (event.type != sf::Event::KeyReleased)
        {
            return;
        }

        if (event.key.code == sf::Keyboard::Escape)
        {
            context.state.change(context, State::Play);
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

} // namespace castlecrawl
