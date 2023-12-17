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
        , m_listboxUPtr()
    {}

    void StateInventory::onEnter(const Context & context)
    {
        m_fadeRectangle.setFillColor(sf::Color(0, 0, 0, 127));
        m_fadeRectangle.setSize(util::size(context.layout.screenRect()));

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

        m_listboxUPtr = std::make_unique<Listbox<item::Item>>(context.player.inventory().unItems());
        m_listboxUPtr->setup(context, FontSize::Small, context.items.textExtents().longest_name, 8);
        m_listboxUPtr->setPosition({ 50.0f, 50.0f });
    }

    void StateInventory::update(const Context & context, const float frameTimeSec)
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
        target.draw(*m_listboxUPtr, states);
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
    }

} // namespace castlecrawl
