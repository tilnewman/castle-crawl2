// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-editor.cpp
//
#include "state-editor.hpp"

#include "campfire.hpp"
#include "context.hpp"
#include "font.hpp"
#include "game-config.hpp"
#include "inferno.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "smoke.hpp"
#include "sound-player.hpp"
#include "sparkle-particle.hpp"
#include "state-manager.hpp"

#include <fstream>

namespace castlecrawl
{

    StateEditor::StateEditor()
        : m_mapChars{}
        , m_editPos{ 0, 0 }
        , m_floor{ Floor::Stone }
        , m_editRectangle{}
        , m_borderRectangle{}
        , m_keyText{ util::SfmlDefaults::instance().font() }
        , m_fadeText{ util::SfmlDefaults::instance().font() }
        , m_fadeTextTimerSec{ 0.0f }
        , m_mouseover{}
        , m_isDragging{ false }
        , m_dragPosStart{ 0.0f, 0.0f }
        , m_dragPosStop{ 0.0f, 0.0f }
        , m_dragRectangle{}
        , m_dragSelectedEntrys{}
        , m_miscButton{}
        , m_doorwayButton{}
        , m_altarButton{}
        , m_statueButton{}
        , m_columnButton{}
        , m_npcButton1{}
        , m_npcButton2{}
        , m_monsterButton1{}
        , m_monsterButton2{}
        , m_monsterButton3{}
        , m_monsterButton4{}
        , m_monsterButton5{}
    {}

    void StateEditor::onEnter(const Context & t_context)
    {
        m_mapChars = std::vector<std::string>(
            static_cast<std::size_t>(t_context.config.map_size_max.y),
            std::string(static_cast<std::size_t>(t_context.config.map_size_max.x), '.'));

        resetMap(t_context);

        m_editRectangle.setFillColor(sf::Color(0, 255, 255, 64));
        m_editRectangle.setOutlineColor(sf::Color(0, 255, 255));
        m_editRectangle.setOutlineThickness(1.0f);
        m_editRectangle.setSize(t_context.layout.cellSize());
        m_editRectangle.setPosition(t_context.layout.mapRect().position);

        m_borderRectangle.setFillColor(sf::Color::Transparent);
        m_borderRectangle.setOutlineColor(sf::Color(255, 255, 255, 64));
        m_borderRectangle.setOutlineThickness(1.0f);
        m_borderRectangle.setPosition(t_context.layout.mapRect().position);
        m_borderRectangle.setSize(t_context.layout.mapRect().size);

        m_dragRectangle.setFillColor(sf::Color(0, 255, 255, 64));

        m_keyText  = t_context.fonts.makeText(FontSize::Small, "", sf::Color::White);
        m_fadeText = t_context.fonts.makeText(FontSize::Large, "", sf::Color::Transparent);

        // clear these in case there were any loaded with the first playable map
        t_context.sparkle_particles.clear();
        t_context.campfire_anims.clear();
        t_context.smoke_anims.clear();
        t_context.inferno_anims.clear();

        const sf::Vector2f cellSize = t_context.layout.cellSize();

        const float tileSelectButtonVertPos =
            (t_context.layout.mapRect().position.y - (t_context.layout.cellSize().y + 5.0f));

        m_miscButton.setup(
            t_context,
            { t_context.layout.mapRect().position.x, tileSelectButtonVertPos },
            { TileImage::Barrel,     TileImage::Sign,          TileImage::Chest,
              TileImage::Door,       TileImage::DoorLocked,    TileImage::Blood,
              TileImage::Key,        TileImage::FountainWater, TileImage::FountainBlood,
              TileImage::Water,      TileImage::Slime,         TileImage::Rock,
              TileImage::RockWeak,   TileImage::Stair_Up,      TileImage::Stair_Down,
              TileImage::Altar,      TileImage::Bag,           TileImage::Coffin,
              TileImage::StoneSpire, TileImage::Lava,          TileImage::Coins });

        m_doorwayButton.setup(
            t_context,
            { (m_miscButton.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            { TileImage::Doorway_Wood,
              TileImage::Doorway_WoodRune,
              TileImage::Doorway_SatanicGray,
              TileImage::Doorway_SatanicRed,
              TileImage::Doorway_RuneOpen,
              TileImage::Doorway_RuneGray,
              TileImage::Doorway_RuneBlue,
              TileImage::Doorway_RuneSkull,
              TileImage::Doorway_MirrorLit,
              TileImage::Doorway_Mirror,
              TileImage::Doorway_SantaicLava,
              TileImage::Doorway_Candle,
              TileImage::Doorway_Ghost,
              TileImage::Doorway_Snake,
              TileImage::Doorway_Oriental,
              TileImage::Doorway_OrientalRed });

        m_altarButton.setup(
            t_context,
            { (m_doorwayButton.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            { TileImage::Altar_Statue,
              TileImage::Altar_Challace,
              TileImage::Altar_Skull,
              TileImage::Altar_Throne,
              TileImage::Altar_Blood,
              TileImage::Altar_Body,
              TileImage::Altar_Demonic,
              TileImage::Altar_Hand,
              TileImage::Altar_King });

        m_statueButton.setup(
            t_context,
            { (m_altarButton.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            { TileImage::Statue_Twins,    TileImage::Statue_Mermaid,  TileImage::Statue_Demonic,
              TileImage::Statue_Wraith,   TileImage::Statue_Sword,    TileImage::Statue_Thresher,
              TileImage::Statue_Orb,      TileImage::Statue_Naga,     TileImage::Statue_Imp,
              TileImage::Statue_Hydra,    TileImage::Statue_Elephant, TileImage::Statue_Dwarf,
              TileImage::Statue_Dragon,   TileImage::Statue_Flamberg, TileImage::Statue_Centaur,
              TileImage::Statue_Cat,      TileImage::Statue_Angel,    TileImage::Statue_Monster,
              TileImage::Statue_Princess, TileImage::Statue_Tengu });

        m_columnButton.setup(
            t_context,
            { (m_statueButton.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            { TileImage::Pillar_CrumbleLeft,
              TileImage::Pillar_Rubble,
              TileImage::Pillar_Complete,
              TileImage::Pillar_Half,
              TileImage::Pillar_Quarter,
              TileImage::Pillar_CrumbleRight });

        m_npcButton1.setup(
            t_context,
            { (m_columnButton.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            {
                TileImage::Gnome,
                TileImage::Faun,
                TileImage::Elfman,
                TileImage::Dwarf,
                TileImage::Wiglaf,
                TileImage::Human,
                TileImage::RedKnight,
                TileImage::Elf,
                TileImage::ElfWarrior,
                TileImage::GreenElf,
                TileImage::GreenElfMage,
                TileImage::BlueClown,
                TileImage::BlueKnight,
                TileImage::Spartan,
            });

        m_npcButton2.setup(
            t_context,
            { (m_npcButton1.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            { TileImage::Satyr,
              TileImage::GoldKnight,
              TileImage::DeepCaster,
              TileImage::OldMan,
              TileImage::GoldClown,
              TileImage::Hag,
              TileImage::CyanKnight,
              TileImage::Elfnee,
              TileImage::Javelinee,
              TileImage::SkullSpeaker,
              TileImage::FolkMage,
              TileImage::Maud,
              TileImage::GreenRanger,
              TileImage::BookSpeaker });

        m_monsterButton1.setup(
            t_context,
            { (m_npcButton2.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            { TileImage::BeholderSpawn,  TileImage::SkullSlime,   TileImage::BoneDragon,
              TileImage::SwampThing,     TileImage::RabidRodent,  TileImage::Bat,
              TileImage::DragonWarlord,  TileImage::AquaSlime,    TileImage::SlimeBeholder,
              TileImage::Cyclops,        TileImage::FleshCreeper, TileImage::Wailing,
              TileImage::CoillingViper,  TileImage::IceKnight,    TileImage::Beholder,
              TileImage::RottingChomper, TileImage::SkitterMite,  TileImage::BloodCreeper,
              TileImage::WindHowler,     TileImage::GreenSnake });

        m_monsterButton2.setup(
            t_context,
            { (m_monsterButton1.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            { TileImage::BloatedCreeper,  TileImage::MudDemon,     TileImage::Serpent,
              TileImage::WalkingBeholder, TileImage::InvisibleMan, TileImage::Kracklin,
              TileImage::Kobold,          TileImage::FireGiant,    TileImage::BeholderMite,
              TileImage::RacerSnake,      TileImage::DessertSnake, TileImage::TwoHeadedOgre,
              TileImage::MothDragon,      TileImage::Catterhorror, TileImage::CaveSpider,
              TileImage::VineShambler,    TileImage::SpikeCreeper, TileImage::SlimeShambler,
              TileImage::Spider,          TileImage::SpellWalker });

        m_monsterButton3.setup(
            t_context,
            { (m_monsterButton2.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            { TileImage::GreenWight,   TileImage::SoulEater,
              TileImage::BoneHound,    TileImage::ArcaneBeholder,
              TileImage::Siren,        TileImage::Specter,
              TileImage::BoneHydra,    TileImage::ShadowFiend,
              TileImage::StripedSnake, TileImage::Scorpion,
              TileImage::Firebrand,    TileImage::RustDevil,
              TileImage::Revenant,     TileImage::WidowSpider,
              TileImage::RedDemon,     TileImage::QuicksilverDragon,
              TileImage::Dragon,       TileImage::Antlion,
              TileImage::Quasit,       TileImage::KoboldBrute });

        m_monsterButton4.setup(
            t_context,
            { (m_monsterButton3.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            { TileImage::SpiderHorror,  TileImage::OrangeDemon,  TileImage::Ooze,
              TileImage::OctoCrawler,   TileImage::Wollynaut,    TileImage::BogSlave,
              TileImage::MutantBeast,   TileImage::MoonTroll,    TileImage::ManaViper,
              TileImage::Lorocyproca,   TileImage::FleshChomper, TileImage::Juggernaut,
              TileImage::ElephantDemon, TileImage::RedJelly,     TileImage::IronGiant,
              TileImage::Hippogriff,    TileImage::HellWing,     TileImage::Hellion,
              TileImage::HellHound,     TileImage::GuardianCobra });

        m_monsterButton5.setup(
            t_context,
            { (m_monsterButton4.globalBounds().position.x + cellSize.x), tileSelectButtonVertPos },
            { TileImage::GoldScorpion, TileImage::GreenBullber,  TileImage::GoldenDragon,
              TileImage::GiantLeech,   TileImage::GiantAmoeba,   TileImage::OrangeClamber,
              TileImage::FrostGiant,   TileImage::AntCreeper,    TileImage::SunWeaver,
              TileImage::SkiteWing,    TileImage::FireElemental, TileImage::RustCrab,
              TileImage::FireBat,      TileImage::WanderingEye,  TileImage::TwoHeadedGiant,
              TileImage::BruteWitch,   TileImage::Draconian,     TileImage::WailingSlime,
              TileImage::Madman,       TileImage::Fungosite });
    }

    void StateEditor::update(const Context & t_context, const float t_frameTimeSec)
    {
        updateHelpText(t_context);
        updateFadeText(t_frameTimeSec);
        m_mouseover.update(t_context, t_frameTimeSec);
        t_context.campfire_anims.update(t_context, t_frameTimeSec);
        t_context.smoke_anims.update(t_context, t_frameTimeSec);
        t_context.inferno_anims.update(t_context, t_frameTimeSec);
        t_context.sparkle_particles.update(t_context, t_frameTimeSec);
    }

    void StateEditor::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);
        t_context.campfire_anims.draw(t_target, t_states);
        t_context.smoke_anims.draw(t_target, t_states);
        t_context.inferno_anims.draw(t_target, t_states);
        t_context.sparkle_particles.draw(t_target, t_states);

        if (!m_keyText.getString().isEmpty())
        {
            t_target.draw(m_keyText, t_states);
        }

        t_target.draw(m_borderRectangle, t_states);
        t_target.draw(m_fadeText, t_states);

        if (m_isDragging)
        {
            t_target.draw(m_dragRectangle);
        }
        else
        {
            t_target.draw(m_editRectangle, t_states);
        }

        for (const MapEntry & entry : m_dragSelectedEntrys)
        {
            sf::RectangleShape rectangle;
            rectangle.setFillColor(sf::Color(0, 255, 255, 64));
            rectangle.setPosition(entry.rect.position);
            rectangle.setSize(entry.rect.size);

            t_target.draw(rectangle);
        }

        m_miscButton.draw(t_target, t_states);
        m_doorwayButton.draw(t_target, t_states);
        m_altarButton.draw(t_target, t_states);
        m_statueButton.draw(t_target, t_states);
        m_columnButton.draw(t_target, t_states);
        m_npcButton1.draw(t_target, t_states);
        m_npcButton2.draw(t_target, t_states);
        m_monsterButton1.draw(t_target, t_states);
        m_monsterButton2.draw(t_target, t_states);
        m_monsterButton3.draw(t_target, t_states);
        m_monsterButton4.draw(t_target, t_states);
        m_monsterButton5.draw(t_target, t_states);

        m_mouseover.draw(t_context, t_target, t_states);
    }

    bool StateEditor::isMouseOverAnyButton(const sf::Vector2f & t_mousePos) const
    {
        return (
            m_miscButton.globalBounds().contains(t_mousePos) ||
            m_doorwayButton.globalBounds().contains(t_mousePos) ||
            m_altarButton.globalBounds().contains(t_mousePos) ||
            m_statueButton.globalBounds().contains(t_mousePos) ||
            m_columnButton.globalBounds().contains(t_mousePos) ||
            m_npcButton1.globalBounds().contains(t_mousePos) ||
            m_npcButton2.globalBounds().contains(t_mousePos) ||
            m_monsterButton1.globalBounds().contains(t_mousePos) ||
            m_monsterButton2.globalBounds().contains(t_mousePos) ||
            m_monsterButton3.globalBounds().contains(t_mousePos) ||
            m_monsterButton4.globalBounds().contains(t_mousePos) ||
            m_monsterButton5.globalBounds().contains(t_mousePos));
    }

    void StateEditor::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto buttonPtr = t_event.getIf<sf::Event::MouseButtonPressed>())
        {
            const sf::Vector2f mousePos{ static_cast<float>(buttonPtr->position.x),
                                         static_cast<float>(buttonPtr->position.y) };

            if (!isMouseOverAnyButton(mousePos))
            {
                startDragging(t_context, mousePos);
            }

            return;
        }

        if (const auto buttonPtr = t_event.getIf<sf::Event::MouseButtonReleased>())
        {
            const sf::Vector2f mousePos{ static_cast<float>(buttonPtr->position.x),
                                         static_cast<float>(buttonPtr->position.y) };

            if (!m_isDragging)
            {
                auto selectFromDropDownButton = [&](TileSelectButton & button) {
                    if (button.globalBounds().contains(mousePos))
                    {
                        const TileImage newTileImage = button.screenPosToTileImage(mousePos);
                        const char newMapChar        = tileImageToChar(newTileImage);
                        editMap(t_context, newMapChar, std::string(tileImageToName(newTileImage)));
                    }
                };

                selectFromDropDownButton(m_miscButton);
                selectFromDropDownButton(m_doorwayButton);
                selectFromDropDownButton(m_altarButton);
                selectFromDropDownButton(m_statueButton);
                selectFromDropDownButton(m_columnButton);
                selectFromDropDownButton(m_npcButton1);
                selectFromDropDownButton(m_npcButton2);
                selectFromDropDownButton(m_monsterButton1);
                selectFromDropDownButton(m_monsterButton2);
                selectFromDropDownButton(m_monsterButton3);
                selectFromDropDownButton(m_monsterButton4);
                selectFromDropDownButton(m_monsterButton5);
            }

            if (!isMouseOverAnyButton(mousePos))
            {
                stopDragging(t_context, mousePos);
            }

            return;
        }

        if (const auto * mouseMovePtr = t_event.getIf<sf::Event::MouseMoved>())
        {
            m_mouseover.handleMouseMovedEvent(
                { mouseMovePtr->position.x, mouseMovePtr->position.y });

            if (m_isDragging)
            {
                updateDragging(
                    t_context,
                    { static_cast<float>(mouseMovePtr->position.x),
                      static_cast<float>(mouseMovePtr->position.y) });
            }
            else
            {
                const sf::Vector2f mousePos{ static_cast<float>(mouseMovePtr->position.x),
                                             static_cast<float>(mouseMovePtr->position.y) };

                m_miscButton.updateMousePos(mousePos);
                m_doorwayButton.updateMousePos(mousePos);
                m_altarButton.updateMousePos(mousePos);
                m_statueButton.updateMousePos(mousePos);
                m_columnButton.updateMousePos(mousePos);
                m_npcButton1.updateMousePos(mousePos);
                m_npcButton2.updateMousePos(mousePos);
                m_monsterButton1.updateMousePos(mousePos);
                m_monsterButton2.updateMousePos(mousePos);
                m_monsterButton3.updateMousePos(mousePos);
                m_monsterButton4.updateMousePos(mousePos);
                m_monsterButton5.updateMousePos(mousePos);

                m_miscButton.setIsDroppedDown(m_miscButton.globalBounds().contains(mousePos));
                m_doorwayButton.setIsDroppedDown(m_doorwayButton.globalBounds().contains(mousePos));
                m_altarButton.setIsDroppedDown(m_altarButton.globalBounds().contains(mousePos));
                m_statueButton.setIsDroppedDown(m_statueButton.globalBounds().contains(mousePos));
                m_columnButton.setIsDroppedDown(m_columnButton.globalBounds().contains(mousePos));
                m_npcButton1.setIsDroppedDown(m_npcButton1.globalBounds().contains(mousePos));
                m_npcButton2.setIsDroppedDown(m_npcButton2.globalBounds().contains(mousePos));

                m_monsterButton1.setIsDroppedDown(
                    m_monsterButton1.globalBounds().contains(mousePos));

                m_monsterButton2.setIsDroppedDown(
                    m_monsterButton2.globalBounds().contains(mousePos));

                m_monsterButton3.setIsDroppedDown(
                    m_monsterButton3.globalBounds().contains(mousePos));

                m_monsterButton4.setIsDroppedDown(
                    m_monsterButton4.globalBounds().contains(mousePos));

                m_monsterButton5.setIsDroppedDown(
                    m_monsterButton5.globalBounds().contains(mousePos));
            }

            return;
        }

        // all remaining events are key pressed events
        if (!t_event.is<sf::Event::KeyPressed>())
        {
            return;
        }

        auto isCntrlPressed = []() {
            return (
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RControl));
        };

        auto isShiftPressed = []() {
            return (
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RShift));
        };

        const auto keyScancode = t_event.getIf<sf::Event::KeyPressed>()->scancode;

        if (keyScancode == sf::Keyboard::Scancode::Escape)
        {
            t_context.state.change(t_context, State::Quit);
        }
        else if ((keyScancode == sf::Keyboard::Scancode::S) && isCntrlPressed())
        {
            fadeText(t_context, "Saving...");
            save(t_context);
        }
        else if ((keyScancode == sf::Keyboard::Scancode::L) && isCntrlPressed())
        {
            fadeText(t_context, "Loading...");
            load(t_context);
        }
        else if ((keyScancode == sf::Keyboard::Scancode::R) && isCntrlPressed())
        {
            m_mapChars = std::vector<std::string>(
                static_cast<std::size_t>(t_context.config.map_size_max.y),
                std::string(static_cast<std::size_t>(t_context.config.map_size_max.x), '.'));

            resetMap(t_context);

            m_editPos = { 0, 0 };
            placeEditCursor(t_context);

            m_dragSelectedEntrys.clear();

            m_borderRectangle.setPosition(t_context.layout.mapRect().position);
            m_borderRectangle.setSize(t_context.layout.mapRect().size);

            t_context.sfx.play("error-4"); // no error here but this sfx sounds right
        }
        else if (keyScancode == sf::Keyboard::Scancode::F)
        {
            if (m_floor == Floor::Dirt)
            {
                m_floor = Floor::Stone;
                fadeText(t_context, "Stone Floor");
            }
            else if (m_floor == Floor::Stone)
            {
                m_floor = Floor::Wood;
                fadeText(t_context, "Wood Floor");
            }
            else if (m_floor == Floor::Wood)
            {
                m_floor = Floor::Dirt;
                fadeText(t_context, "Dirt Floor");
            }

            resetMap(t_context);
            t_context.sfx.play("tick-off-2");
        }
        else if (keyScancode == sf::Keyboard::Scancode::Up)
        {
            if (m_editPos.y > 0)
            {
                --m_editPos.y;
                placeEditCursor(t_context);
                m_dragSelectedEntrys.clear();
                t_context.sfx.play("tick-off-1");
            }
            else
            {
                t_context.sfx.play("tap-wood-low");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::Down)
        {
            if (m_editPos.y < (static_cast<int>(m_mapChars.size()) - 1))
            {
                ++m_editPos.y;
                placeEditCursor(t_context);
                m_dragSelectedEntrys.clear();
                t_context.sfx.play("tick-off-1");
            }
            else
            {
                t_context.sfx.play("tap-wood-low");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::Left)
        {
            if (m_editPos.x > 0)
            {
                --m_editPos.x;
                placeEditCursor(t_context);
                m_dragSelectedEntrys.clear();
                t_context.sfx.play("tick-off-1");
            }
            else
            {
                t_context.sfx.play("tap-wood-low");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::Right)
        {
            if (m_editPos.x < (static_cast<int>(m_mapChars.front().size()) - 1))
            {
                ++m_editPos.x;
                placeEditCursor(t_context);
                m_dragSelectedEntrys.clear();
                t_context.sfx.play("tick-off-1");
            }
            else
            {
                t_context.sfx.play("tap-wood-low");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::Space)
        {
            editMap(t_context, ' ', "Bare Floor");
        }
        else if (keyScancode == sf::Keyboard::Scancode::Period)
        {
            editMap(t_context, '.', "Erase");
        }
        else if (keyScancode == sf::Keyboard::Scancode::R)
        {
            if (isShiftPressed())
            {
                editMap(t_context, 'H', "Breakable Rock");
            }
            else
            {
                editMap(t_context, 'h', "Rock");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::Z)
        {
            editMap(t_context, 'Z', "Breakable Wood Wall");
        }
        else if (keyScancode == sf::Keyboard::Scancode::W)
        {
            editMap(t_context, 'g', "Water");
        }
        else if (keyScancode == sf::Keyboard::Scancode::L)
        {
            editMap(t_context, 'l', "Lava");
        }
        else if (keyScancode == sf::Keyboard::Scancode::E)
        {
            editMap(t_context, 'e', "Blood");
        }
        else if (keyScancode == sf::Keyboard::Scancode::G)
        {
            editMap(t_context, 'G', "Slime");
        }
        else if (keyScancode == sf::Keyboard::Scancode::D)
        {
            if (isShiftPressed())
            {
                editMap(t_context, 'D', "Locked Door");
            }
            else
            {
                editMap(t_context, 'd', "Door");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::C)
        {
            if (isShiftPressed())
            {
                editMap(t_context, '~', "Coins");
            }
            else
            {
                editMap(t_context, 'c', "Chest");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::B)
        {
            if (isShiftPressed())
            {
                editMap(t_context, 'k', "Coffin");
            }
            else
            {
                editMap(t_context, 'b', "Barrel");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::H)
        {
            if (isShiftPressed())
            {
                editMap(t_context, 'F', "Blood Fountain");
            }
            else
            {
                editMap(t_context, 'f', "Water Fountain");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::S)
        {
            if (isShiftPressed())
            {
                editMap(t_context, 'I', "Stairs Down");
            }
            else
            {
                editMap(t_context, 'i', "Stairs Up");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::P)
        {
            if (isShiftPressed())
            {
                editMap(t_context, 'j', "Stone Altar");
            }
            else
            {
                editMap(t_context, 'K', "Stone Spire");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::A)
        {
            if (isShiftPressed())
            {
                editMap(t_context, 'A', "Inferno");
            }
            else
            {
                editMap(t_context, 'a', "Campfire");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::T)
        {
            if (isShiftPressed())
            {
                const std::vector<TileImage> trees{ TileImage::Tree1,
                                                    TileImage::Tree2,
                                                    TileImage::Tree3 };

                editMap(t_context, tileImageToChar(t_context.random.from(trees)), "Tree");
            }
            else
            {
                const std::vector<TileImage> blocks{ TileImage::Block_Emboss1,
                                                     TileImage::Block_Emboss2,
                                                     TileImage::Block_Emboss3,
                                                     TileImage::Block_Emboss4 };

                editMap(t_context, tileImageToChar(t_context.random.from(blocks)), "Block");
            }
        }
    }

    void StateEditor::updateHelpText(const Context & t_context)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Slash))
        {
            const std::string keyText(
                "Esc-Quit\nCNTRL-s-Save\nCNTRL-l-Load\nSpace-Bare Floor\nPeriod-Erase\n"
                "f-Change-Flooring\nr-Rock\nR-Breakable Rock\nZ-Breakable Wood Wall\n"
                "w-Water\nl-Lava\nb-Blood\ng-Slime\nd-Door\nD-Locked Door\nb-Barrel\n"
                "c-Chest\nC-Coins\nf-Water Fountain\nF-Blood Fountain\ns-Stairs Up\n"
                "S-Stairs Down\np-Rock Point\nP-Altar\nT-Random Tree\nt-Random Block Wall");

            m_keyText.setString(keyText);

            m_keyText.setPosition({ ((t_context.layout.topRect().size.x * 0.5f) -
                                     (m_keyText.getGlobalBounds().size.x * 0.5f)),
                                    (t_context.layout.topRect().size.y - 25.0f) });
        }
        else
        {
            m_keyText.setString("");
        }
    }

    void StateEditor::updateFadeText(const float t_elapsedTimeSec)
    {
        const float fadeTimeSec = 3.0f;
        m_fadeTextTimerSec += t_elapsedTimeSec;
        if (m_fadeTextTimerSec < fadeTimeSec)
        {
            const int alpha = (255 - util::map(m_fadeTextTimerSec, 0.0f, fadeTimeSec, 0, 255));
            sf::Color color = m_fadeText.getFillColor();
            color.a         = static_cast<uint8_t>(alpha);
            m_fadeText.setFillColor(color);
        }
    }

    void StateEditor::resetMap(const Context & t_context)
    {
        Map map(MapName::Level_1_Cell, t_context, m_floor, m_mapChars, MapTransitions_t{});
        t_context.maps.forceMapForEditting(t_context, map);
    }

    void StateEditor::placeEditCursor(const Context & t_context)
    {
        m_editRectangle.setPosition(
            t_context.maps.current().mapPosToScreenPos(t_context, m_editPos));
    }

    void StateEditor::setMapChar(const Context &, const char t_ch)
    {
        if (m_dragSelectedEntrys.empty())
        {
            m_mapChars.at(static_cast<std::size_t>(m_editPos.y))
                .at(static_cast<std::size_t>(m_editPos.x)) = t_ch;
        }
        else
        {
            for (const MapEntry & entry : m_dragSelectedEntrys)
            {
                m_mapChars.at(static_cast<std::size_t>(entry.pos.y))
                    .at(static_cast<std::size_t>(entry.pos.x)) = t_ch;
            }
        }
    }

    void StateEditor::editMap(
        const Context & t_context, const char t_newMapChar, const std::string & t_fadeText)
    {
        setMapChar(t_context, t_newMapChar);
        fadeText(t_context, t_fadeText);
        resetMap(t_context);
        t_context.sfx.play("tick-on-1");
    }

    void StateEditor::fadeText(const Context & t_context, const std::string & t_text)
    {
        m_fadeText.setString(t_text);
        m_fadeText.setFillColor(sf::Color::White);

        m_fadeText.setPosition(
            { ((t_context.layout.topRect().size.x * 0.5f) -
               (m_fadeText.getGlobalBounds().size.x * 0.5f)),
              (m_borderRectangle.getPosition().y - (m_fadeText.getGlobalBounds().size.y * 2.0f)) });

        m_fadeTextTimerSec = 0.0f;
    }

    void StateEditor::save(const Context & t_context) const
    {
        std::ofstream fStream("map.txt", std::ios::trunc);

        for (const std::string & rowStr : m_mapChars)
        {
            fStream << '\"' << rowStr << "\"," << std::endl;
        }

        t_context.sfx.play("error-4"); // no error here but this sfx sounds right
    }

    void StateEditor::load(const Context & t_context)
    {
        std::ifstream fStream("map.txt", std::ios::in);

        std::vector<std::string> lines;
        lines.reserve(static_cast<std::size_t>(t_context.config.map_size_max.y));

        std::string line;
        std::size_t lineNumber = 0;
        while (std::getline(fStream, line, '\n'))
        {
            ++lineNumber;

            if (line.size() < 7)
            {
                std::cerr << "Tried to load map.txt but failed because line " << lineNumber
                          << " was too short before removing quotes and other stuff.  Was length "
                          << line.size() << " when minimum is 7." << std::endl;

                t_context.sfx.play("error-2");
                return;
            }

            // remove the leading quote
            if (line[0] != '\"')
            {
                std::cerr << "Tried to load map.txt but failed because line " << lineNumber
                          << " did NOT start with quotes." << std::endl;

                t_context.sfx.play("error-2");
                return;
            }
            else
            {
                line.erase(std::begin(line));
            }

            // remove everything from the end until reaching the trailing quote
            while (!line.empty() && (line.back() != '\"'))
            {
                line.pop_back();
            }

            if (!line.empty())
            {
                line.pop_back();
            }

            if (line.size() < 3)
            {
                std::cerr << "Tried to load map.txt but failed because line " << lineNumber
                          << " was too short between quotes.  Was " << line.size()
                          << " when the minimum is 3." << std::endl;

                t_context.sfx.play("error-2");
                return;
            }

            lines.push_back(line);
        }

        if (lines.size() < 3)
        {
            std::cerr << "Tried to load map.txt but failed because there were too few lines/rows."
                      << "There were only " << lines.size() << "when the minimum is 3."
                      << std::endl;

            t_context.sfx.play("error-2");
            return;
        }

        m_mapChars = lines;
        resetMap(t_context);

        m_editPos = { 0, 0 };
        placeEditCursor(t_context);

        m_dragSelectedEntrys.clear();

        m_borderRectangle.setPosition(t_context.layout.mapRect().position);
        m_borderRectangle.setSize(t_context.layout.mapRect().size);

        t_context.sfx.play("error-4"); // no error here but this sfx sounds right
    }

    void StateEditor::startDragging(const Context & t_context, const sf::Vector2f & t_pos)
    {
        m_dragPosStart = t_pos;
        m_dragPosStop  = t_pos;

        updateDragRect();

        m_isDragging = t_context.layout.mapRect().contains(t_pos);

        updateDragSelectedMapCells(t_context);

        t_context.sfx.play("tick-on-1");
    }

    void StateEditor::stopDragging(const Context & t_context, const sf::Vector2f & t_pos)
    {
        const MapPos_t newMapPos = t_context.maps.current().screenPosToMapPos(t_context, t_pos);

        if (t_context.maps.current().isPosValid(newMapPos))
        {
            m_editPos = newMapPos;
            placeEditCursor(t_context);
            t_context.sfx.play("tick-off-1");
        }

        m_isDragging = false;

        if (t_context.layout.mapRect().contains(t_pos))
        {
            updateDragRect();
        }
        else
        {
            m_dragRectangle.setPosition({ 0.0f, 0.0f });
            m_dragRectangle.setSize({ 0.0f, 0.0f });
        }
    }

    void StateEditor::updateDragging(const Context & t_context, const sf::Vector2f & t_pos)
    {
        m_dragPosStop = t_pos;
        updateDragRect();
        updateDragSelectedMapCells(t_context);
    }

    void StateEditor::updateDragRect()
    {
        m_dragRectangle.setPosition({ util::min(m_dragPosStart.x, m_dragPosStop.x),
                                      util::min(m_dragPosStart.y, m_dragPosStop.y) });

        m_dragRectangle.setSize(sf::Vector2f{ util::abs(m_dragPosStart.x - m_dragPosStop.x),
                                              util::abs(m_dragPosStart.y - m_dragPosStop.y) });
    }

    void StateEditor::updateDragSelectedMapCells(const Context & t_context)
    {
        m_dragSelectedEntrys.clear();

        const sf::FloatRect mapRect = t_context.layout.mapRect();
        const sf::Vector2i mapSize  = t_context.layout.cellCount();

        sf::Vector2f screenPos = mapRect.position;
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const sf::FloatRect screenRect{ screenPos, t_context.layout.cellSize() };

                const sf::FloatRect dragRect{ util::position(m_dragRectangle),
                                              util::size(m_dragRectangle) };

                if (screenRect.findIntersection(dragRect))
                {
                    const MapEntry entry{ { x, y }, screenRect };
                    m_dragSelectedEntrys.push_back(entry);
                }

                screenPos.x += t_context.layout.cellSize().x;
            }

            screenPos.x = mapRect.position.x;
            screenPos.y += t_context.layout.cellSize().y;
        }
    }

} // namespace castlecrawl
