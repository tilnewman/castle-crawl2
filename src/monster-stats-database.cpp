// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster-stats-database.cpp
//
#include "monster-stats-database.hpp"

#include "check-macros.hpp"

#include <fstream>

namespace castlecrawl
{

    MonsterStatsDatabase::MonsterStatsDatabase()
        : m_imageStatsMap{}
    {

        //
        // the weak
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Madman,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Kobold,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::KoboldBrute,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RabidRodent,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Bat,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FireBat,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        //
        // beholders
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Beholder,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BeholderSpawn,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SlimeBeholder,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WalkingBeholder,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BeholderMite,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ArcaneBeholder,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WanderingEye,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WanderingEye,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        //
        // slimes
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SkullSlime,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::AquaSlime,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Ooze,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RedJelly,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GiantAmoeba,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WailingSlime,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        //
        // dragons
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Dragon,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BoneDragon,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::DragonWarlord,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BoneHydra,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MothDragon,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::QuicksilverDragon,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GoldenDragon,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SkiteWing,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        //
        // brutes
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Cyclops,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FireGiant,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::TwoHeadedOgre,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Juggernaut,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::IronGiant,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FrostGiant,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::TwoHeadedGiant,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        //
        // creepers
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FleshCreeper,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WailingCreeper,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BloodCreeper,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BloatedCreeper,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SpikeCreeper,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::AntCreeper,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        //
        // snakes
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::CoillingViper,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GreenSnake,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Serpent,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::DessertSnake,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RacerSnake,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::StripedSnake,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ManaViper,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GuardianCobra,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        //
        // Spider
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Spider,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::CaveSpider,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WidowSpider,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SpiderHorror,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        //
        // misc
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Wollynaut,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ElephantDemon,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SwampThing,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::IceKnight,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RottingChomper,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SkitterMite,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WindHowler,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MudDemon,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::InvisibleMan,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Kracklin,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Catterhorror,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::VineShambler,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SlimeShambler,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SpellWalker,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GreenWight,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SoulEater,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BoneHound,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Siren,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Specter,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ShadowFiend,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Scorpion,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Firebrand,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RustDevil,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Revenant,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RedDemon,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Antlion,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Quasit,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::OrangeDemon,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::OctoCrawler,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BogSlave,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MutantBull,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MoonTroll,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Lorocyproca,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FleshChomper,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Hippogriff,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::HellWing,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Hellion,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::HellHound,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GoldScorpion,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GreenBullber,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GiantLeech,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::OrangeClamber,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SunWeaver,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FireElemental,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RustCrab,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BruteWitch,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Draconian,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Fungosite,
            MonsterStats{ .health    = 0,
                          .mana      = 0,
                          .strength  = 0,
                          .dexterity = 0,
                          .arcane    = 0,
                          .accuracy  = 0,
                          .luck      = 0 }));
    }

    void MonsterStatsDatabase::setup() { verifyAll(); }

    void MonsterStatsDatabase::dumpInfo() const
    {
        // write all to spreadsheet
        {
            std::ofstream csvFileStream("monster-stats.csv", std::ios_base::trunc);
            csvFileStream << "name,health,mana,str,dex,arc,acc,lck\n";
            for (const auto & pair : m_imageStatsMap)
            {
                csvFileStream << tileImageToName(pair.first) << ',';
                csvFileStream << pair.second.health << ',';
                csvFileStream << pair.second.mana << ',';
                csvFileStream << pair.second.strength << ',';
                csvFileStream << pair.second.dexterity << ',';
                csvFileStream << pair.second.arcane << ',';
                csvFileStream << pair.second.accuracy << ',';
                csvFileStream << pair.second.luck << '\n';
            }
        }
    }

    const MonsterStats MonsterStatsDatabase::stats(const TileImage & t_tileImage) const
    {
        M_CHECK(
            isTileImageMonster(t_tileImage),
            "MonsterStatsDatabase query was not a monster: " << tileImageToName(t_tileImage));

        const auto foundIter = m_imageStatsMap.find(t_tileImage);
        if (foundIter == std::end(m_imageStatsMap))
        {
            return {}; // default constructed stats are invalid
        }
        else
        {
            return foundIter->second;
        }
    }

    void MonsterStatsDatabase::verifyAll() const
    {
        // verify none are missing
        std::size_t count = 0;
        for (std::size_t index{}; index <= static_cast<std::size_t>(TileImage::BookSpeaker);
             ++index)
        {
            if (isTileImageMonster(static_cast<TileImage>(index)))
            {
                ++count;
            }
        }

        M_CHECK(
            (m_imageStatsMap.size() == count),
            "MonsterStatsDatabase has missing or extra entries.  Has "
                << m_imageStatsMap.size() << " but should have " << count);

        // uncomment after all monsters have stats
        //  verify all are valid
        // for (const auto & pair : m_imageStatsMap)
        //{
        //     M_CHECK(
        //         isTileImageMonster(pair.first),
        //         "MonsterStatsDatabase had a non-monster in it: " << tileImageToName(pair.first));
        //
        //     M_CHECK(
        //         pair.second.isValid(),
        //         "MonsterStatsDatabase had invalid stats in it for: "
        //             << tileImageToName(pair.first));
        // }
    }

} // namespace castlecrawl