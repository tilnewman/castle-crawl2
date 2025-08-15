// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster-stats-database.cpp
//
#include "monster-stats-database.hpp"

#include "check-macros.hpp"
#include "stats-display.hpp"
#include "util.hpp"

#include <fstream>
#include <vector>

namespace castlecrawl
{

    int MonsterStats::value() const
    {
        int value = 0;

        value += health_max;
        value += mana_max;

        value += armor;

        value += strength;
        value += dexterity;
        value += arcane;
        value += accuracy;
        value += luck;

        if (is_undead)
        {
            value += 20;
        }

        if (is_immune_to_nonmagical_weapons)
        {
            value += 100;
        }

        value += static_cast<int>(breathe_fire_attack_ratio * 200.0f);
        value += static_cast<int>(poison_attack_ratio * 200.0f);
        value += static_cast<int>(acid_attack_ratio * 200.0f);
        value += static_cast<int>(spell_attack_ratio * 200.0f);
        value += static_cast<int>(break_attack_ratio * 2000.0f);
        value += static_cast<int>(devour_attack_ratio * 2000.0f);

        return value;
    }

    //

    MonsterStatsDatabase::MonsterStatsDatabase()
        : m_imageStatsMap{}
    {

        //
        // weak ones
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Madman,
            MonsterStats{ .health_max = 12,
                          .mana_max   = 0,
                          .strength   = 10,
                          .dexterity  = 10,
                          .arcane     = 0,
                          .accuracy   = 10,
                          .luck       = 10 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Kobold,
            MonsterStats{ .health_max = 15,
                          .mana_max   = 0,
                          .armor      = 3,
                          .strength   = 15,
                          .dexterity  = 15,
                          .arcane     = 0,
                          .accuracy   = 15,
                          .luck       = 12 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::KoboldBrute,
            MonsterStats{ .health_max = 18,
                          .mana_max   = 0,
                          .armor      = 6,
                          .strength   = 18,
                          .dexterity  = 12,
                          .arcane     = 0,
                          .accuracy   = 15,
                          .luck       = 10 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RabidRodent,
            MonsterStats{ .health_max = 10,
                          .mana_max   = 0,
                          .strength   = 14,
                          .dexterity  = 16,
                          .arcane     = 0,
                          .accuracy   = 15,
                          .luck       = 10 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Bat,
            MonsterStats{ .health_max = 8,
                          .mana_max   = 0,
                          .strength   = 8,
                          .dexterity  = 17,
                          .arcane     = 0,
                          .accuracy   = 15,
                          .luck       = 11,
                          .is_flying  = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FireBat,
            MonsterStats{ .health_max                    = 14,
                          .mana_max                      = 0,
                          .armor                         = 3,
                          .strength                      = 14,
                          .dexterity                     = 14,
                          .arcane                        = 0,
                          .accuracy                      = 14,
                          .luck                          = 14,
                          .is_flying                     = true,
                          .is_strong_to_fire_weak_to_ice = true,
                          .breathe_fire_attack_ratio     = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RustCrab,
            MonsterStats{ .health_max         = 18,
                          .mana_max           = 0,
                          .armor              = 5,
                          .strength           = 17,
                          .dexterity          = 11,
                          .arcane             = 0,
                          .accuracy           = 16,
                          .luck               = 5,
                          .break_attack_ratio = 0.002f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GiantLeech,
            MonsterStats{ .health_max          = 16,
                          .mana_max            = 0,
                          .strength            = 17,
                          .dexterity           = 13,
                          .arcane              = 0,
                          .accuracy            = 16,
                          .luck                = 1,
                          .devour_attack_ratio = 0.0025f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Scorpion,
            MonsterStats{ .health_max          = 16,
                          .mana_max            = 0,
                          .armor               = 4,
                          .strength            = 14,
                          .dexterity           = 19,
                          .arcane              = 0,
                          .accuracy            = 15,
                          .luck                = 2,
                          .poison_attack_ratio = 0.09f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GoldScorpion,
            MonsterStats{ .health_max = 32,
                          .mana_max   = 0,
                          .armor      = 8,
                          .strength   = 28,
                          .dexterity  = 25,
                          .arcane     = 0,
                          .accuracy   = 25,
                          .luck       = 34 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Antlion,
            MonsterStats{ .health_max = 28,
                          .mana_max   = 0,
                          .armor      = 5,
                          .strength   = 20,
                          .dexterity  = 18,
                          .arcane     = 0,
                          .accuracy   = 18,
                          .luck       = 2 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Quasit,
            MonsterStats{ .health_max = 14,
                          .mana_max   = 0,
                          .strength   = 9,
                          .dexterity  = 27,
                          .arcane     = 0,
                          .accuracy   = 15,
                          .luck       = 10 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::OctoCrawler,
            MonsterStats{ .health_max = 24,
                          .mana_max   = 0,
                          .strength   = 19,
                          .dexterity  = 15,
                          .arcane     = 0,
                          .accuracy   = 15,
                          .luck       = 9 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BogSlave,
            MonsterStats{ .health_max = 29,
                          .mana_max   = 0,
                          .strength   = 18,
                          .dexterity  = 14,
                          .arcane     = 0,
                          .accuracy   = 16,
                          .luck       = 8 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BruteWitch,
            MonsterStats{ .health_max         = 26,
                          .mana_max           = 35,
                          .strength           = 18,
                          .dexterity          = 12,
                          .arcane             = 24,
                          .accuracy           = 15,
                          .luck               = 15,
                          .spell_attack_ratio = 0.088f,
                          .spells             = { Spell::Spark } }));

        //
        // beholders
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Beholder,
            MonsterStats{ .health_max         = 30,
                          .mana_max           = 60,
                          .strength           = 20,
                          .dexterity          = 14,
                          .arcane             = 60,
                          .accuracy           = 20,
                          .luck               = 20,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.1f,
                          .spells             = { Spell::Terrorize, Spell::HeartAttack } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BeholderSpawn,
            MonsterStats{ .health_max         = 15,
                          .mana_max           = 30,
                          .strength           = 10,
                          .dexterity          = 20,
                          .arcane             = 40,
                          .accuracy           = 15,
                          .luck               = 13,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.05f,
                          .spells             = { Spell::Slow } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BeholderMite,
            MonsterStats{ .health_max         = 12,
                          .mana_max           = 22,
                          .strength           = 10,
                          .dexterity          = 18,
                          .arcane             = 30,
                          .accuracy           = 15,
                          .luck               = 12,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.06f,
                          .spells             = { Spell::Slow } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SlimeBeholder,
            MonsterStats{ .health_max         = 19,
                          .mana_max           = 24,
                          .strength           = 11,
                          .dexterity          = 19,
                          .arcane             = 33,
                          .accuracy           = 16,
                          .luck               = 11,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.04f,
                          .spells             = { Spell::Slow } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WalkingBeholder,
            MonsterStats{ .health_max         = 26,
                          .mana_max           = 50,
                          .strength           = 24,
                          .dexterity          = 18,
                          .arcane             = 40,
                          .accuracy           = 17,
                          .luck               = 17,
                          .is_flying          = false,
                          .spell_attack_ratio = 0.075f,
                          .spells             = { Spell::Stun } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ArcaneBeholder,
            MonsterStats{ .health_max         = 28,
                          .mana_max           = 85,
                          .strength           = 16,
                          .dexterity          = 12,
                          .arcane             = 85,
                          .accuracy           = 16,
                          .luck               = 30,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.15f,
                          .spells = { Spell::Jolt, Spell::FreezingWind, Spell::Stun } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WanderingEye,
            MonsterStats{ .health_max         = 36,
                          .mana_max           = 40,
                          .armor              = 4,
                          .strength           = 20,
                          .dexterity          = 12,
                          .arcane             = 25,
                          .accuracy           = 18,
                          .luck               = 14,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.111f,
                          .spells             = { Spell::Immobillize } }));

        //
        // slimes
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SkullSlime,
            MonsterStats{ .health_max        = 33,
                          .mana_max          = 0,
                          .armor             = 2,
                          .strength          = 18,
                          .dexterity         = 10,
                          .arcane            = 0,
                          .accuracy          = 17,
                          .luck              = 8,
                          .is_undead         = true,
                          .acid_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::AquaSlime,
            MonsterStats{ .health_max                      = 24,
                          .mana_max                        = 0,
                          .strength                        = 14,
                          .dexterity                       = 8,
                          .arcane                          = 0,
                          .accuracy                        = 15,
                          .luck                            = 12,
                          .is_immune_to_nonmagical_weapons = true,
                          .acid_attack_ratio               = 0.05f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Ooze,
            MonsterStats{ .health_max                      = 20,
                          .mana_max                        = 0,
                          .strength                        = 16,
                          .dexterity                       = 11,
                          .arcane                          = 0,
                          .accuracy                        = 17,
                          .luck                            = 14,
                          .is_immune_to_nonmagical_weapons = true,
                          .acid_attack_ratio               = 0.12f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RedJelly,
            MonsterStats{ .health_max                    = 16,
                          .mana_max                      = 0,
                          .armor                         = 1,
                          .strength                      = 14,
                          .dexterity                     = 9,
                          .arcane                        = 0,
                          .accuracy                      = 15,
                          .luck                          = 15,
                          .is_strong_to_fire_weak_to_ice = true,
                          .acid_attack_ratio             = 0.06f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GiantAmoeba,
            MonsterStats{ .health_max                      = 25,
                          .mana_max                        = 0,
                          .strength                        = 15,
                          .dexterity                       = 9,
                          .arcane                          = 0,
                          .accuracy                        = 17,
                          .luck                            = 15,
                          .is_immune_to_nonmagical_weapons = true,
                          .acid_attack_ratio               = 0.04f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WailingSlime,
            MonsterStats{ .health_max                      = 40,
                          .mana_max                        = 0,
                          .strength                        = 20,
                          .dexterity                       = 13,
                          .arcane                          = 0,
                          .accuracy                        = 17,
                          .luck                            = 14,
                          .is_immune_to_nonmagical_weapons = true,
                          .acid_attack_ratio               = 0.13f,
                          .devour_attack_ratio             = 0.002f }));

        //
        // dragons
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Dragon,
            MonsterStats{ .health_max                = 60,
                          .mana_max                  = 0,
                          .armor                     = 15,
                          .strength                  = 50,
                          .dexterity                 = 25,
                          .arcane                    = 0,
                          .accuracy                  = 41,
                          .luck                      = 43,
                          .is_flying                 = true,
                          .breathe_fire_attack_ratio = 0.25f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BoneDragon,
            MonsterStats{ .health_max                = 65,
                          .mana_max                  = 0,
                          .armor                     = 10,
                          .strength                  = 55,
                          .dexterity                 = 29,
                          .arcane                    = 0,
                          .accuracy                  = 39,
                          .luck                      = 42,
                          .is_flying                 = true,
                          .is_undead                 = true,
                          .breathe_fire_attack_ratio = 0.26f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::DragonWarlord,
            MonsterStats{ .health_max                      = 91,
                          .mana_max                        = 0,
                          .armor                           = 20,
                          .strength                        = 80,
                          .dexterity                       = 40,
                          .arcane                          = 0,
                          .accuracy                        = 60,
                          .luck                            = 44,
                          .is_flying                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .is_strong_to_fire_weak_to_ice   = true,
                          .breathe_fire_attack_ratio       = 0.333f,
                          .break_attack_ratio              = 0.0013f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BoneHydra,
            MonsterStats{ .health_max                = 95,
                          .mana_max                  = 0,
                          .armor                     = 18,
                          .strength                  = 75,
                          .dexterity                 = 33,
                          .arcane                    = 0,
                          .accuracy                  = 41,
                          .luck                      = 49,
                          .is_flying                 = false,
                          .is_undead                 = true,
                          .breathe_fire_attack_ratio = 0.24f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MothDragon,
            MonsterStats{ .health_max                = 37,
                          .mana_max                  = 0,
                          .armor                     = 6,
                          .strength                  = 37,
                          .dexterity                 = 37,
                          .arcane                    = 0,
                          .accuracy                  = 37,
                          .luck                      = 37,
                          .is_flying                 = true,
                          .breathe_fire_attack_ratio = 0.0f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::QuicksilverDragon,
            MonsterStats{ .health_max                = 57,
                          .mana_max                  = 0,
                          .armor                     = 14,
                          .strength                  = 38,
                          .dexterity                 = 51,
                          .arcane                    = 0,
                          .accuracy                  = 47,
                          .luck                      = 54,
                          .is_flying                 = true,
                          .breathe_fire_attack_ratio = 0.034f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GoldenDragon,
            MonsterStats{ .health_max                      = 72,
                          .mana_max                        = 0,
                          .armor                           = 28,
                          .strength                        = 67,
                          .dexterity                       = 44,
                          .arcane                          = 0,
                          .accuracy                        = 36,
                          .luck                            = 49,
                          .is_flying                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .breathe_fire_attack_ratio       = 0.5f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SkiteWing,
            MonsterStats{ .health_max                = 29,
                          .mana_max                  = 0,
                          .armor                     = 7,
                          .strength                  = 17,
                          .dexterity                 = 28,
                          .arcane                    = 0,
                          .accuracy                  = 23,
                          .luck                      = 33,
                          .is_flying                 = true,
                          .breathe_fire_attack_ratio = 0.5f }));

        //
        // brutes
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Cyclops,
            MonsterStats{ .health_max         = 55,
                          .mana_max           = 35,
                          .armor              = 3,
                          .strength           = 55,
                          .dexterity          = 20,
                          .arcane             = 18,
                          .accuracy           = 35,
                          .luck               = 2,
                          .spell_attack_ratio = 0.0932f,
                          .break_attack_ratio = 0.002f,
                          .spells             = { Spell::Immobillize } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FireGiant,
            MonsterStats{ .health_max                    = 65,
                          .mana_max                      = 0,
                          .armor                         = 4,
                          .strength                      = 65,
                          .dexterity                     = 27,
                          .arcane                        = 0,
                          .accuracy                      = 38,
                          .luck                          = 10,
                          .is_strong_to_fire_weak_to_ice = true,
                          .break_attack_ratio            = 0.003f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::TwoHeadedOgre,
            MonsterStats{ .health_max         = 49,
                          .mana_max           = 0,
                          .armor              = 2,
                          .strength           = 47,
                          .dexterity          = 9,
                          .arcane             = 0,
                          .accuracy           = 17,
                          .luck               = 4,
                          .break_attack_ratio = 0.002f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Juggernaut,
            MonsterStats{ .health_max         = 75,
                          .mana_max           = 0,
                          .armor              = 5,
                          .strength           = 75,
                          .dexterity          = 22,
                          .arcane             = 0,
                          .accuracy           = 21,
                          .luck               = 8,
                          .break_attack_ratio = 0.0075f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::IronGiant,
            MonsterStats{ .health_max         = 70,
                          .mana_max           = 0,
                          .armor              = 4,
                          .strength           = 70,
                          .dexterity          = 19,
                          .arcane             = 0,
                          .accuracy           = 19,
                          .luck               = 9,
                          .break_attack_ratio = 0.004f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FrostGiant,
            MonsterStats{ .health_max                    = 65,
                          .mana_max                      = 0,
                          .armor                         = 7,
                          .strength                      = 65,
                          .dexterity                     = 27,
                          .arcane                        = 0,
                          .accuracy                      = 38,
                          .luck                          = 10,
                          .is_strong_to_ice_weak_to_fire = true,
                          .break_attack_ratio            = 0.003f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::TwoHeadedGiant,
            MonsterStats{ .health_max         = 59,
                          .mana_max           = 0,
                          .armor              = 2,
                          .strength           = 59,
                          .dexterity          = 14,
                          .arcane             = 0,
                          .accuracy           = 19,
                          .luck               = 5,
                          .break_attack_ratio = 0.0021f }));

        //
        // creepers
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FleshCreeper,
            MonsterStats{ .health_max = 40,
                          .mana_max   = 0,
                          .armor      = 5,
                          .strength   = 20,
                          .dexterity  = 20,
                          .arcane     = 0,
                          .accuracy   = 20,
                          .luck       = 4 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WailingCreeper,
            MonsterStats{ .health_max = 30,
                          .mana_max   = 0,
                          .armor      = 4,
                          .strength   = 16,
                          .dexterity  = 18,
                          .arcane     = 0,
                          .accuracy   = 24,
                          .luck       = 3 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BloodCreeper,
            MonsterStats{ .health_max = 50,
                          .mana_max   = 0,
                          .armor      = 2,
                          .strength   = 25,
                          .dexterity  = 25,
                          .arcane     = 0,
                          .accuracy   = 25,
                          .luck       = 3 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BloatedCreeper,
            MonsterStats{ .health_max = 60,
                          .mana_max   = 0,
                          .armor      = 3,
                          .strength   = 30,
                          .dexterity  = 17,
                          .arcane     = 0,
                          .accuracy   = 26,
                          .luck       = 1 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SpikeCreeper,
            MonsterStats{ .health_max = 40,
                          .mana_max   = 0,
                          .armor      = 5,
                          .strength   = 30,
                          .dexterity  = 25,
                          .arcane     = 0,
                          .accuracy   = 20,
                          .luck       = 8 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::AntCreeper,
            MonsterStats{ .health_max = 24,
                          .mana_max   = 0,
                          .armor      = 3,
                          .strength   = 16,
                          .dexterity  = 16,
                          .arcane     = 0,
                          .accuracy   = 16,
                          .luck       = 7 }));

        //
        // snakes
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::CoillingViper,
            MonsterStats{ .health_max          = 20,
                          .mana_max            = 0,
                          .strength            = 16,
                          .dexterity           = 30,
                          .arcane              = 0,
                          .accuracy            = 30,
                          .luck                = 7,
                          .poison_attack_ratio = 0.123f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GreenSnake,
            MonsterStats{ .health_max          = 16,
                          .mana_max            = 0,
                          .strength            = 13,
                          .dexterity           = 25,
                          .arcane              = 0,
                          .accuracy            = 25,
                          .luck                = 6,
                          .poison_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Serpent,
            MonsterStats{ .health_max          = 35,
                          .mana_max            = 0,
                          .armor               = 2,
                          .strength            = 22,
                          .dexterity           = 38,
                          .arcane              = 0,
                          .accuracy            = 28,
                          .luck                = 15,
                          .poison_attack_ratio = 0.05f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::DessertSnake,
            MonsterStats{ .health_max          = 13,
                          .mana_max            = 0,
                          .strength            = 13,
                          .dexterity           = 20,
                          .arcane              = 0,
                          .accuracy            = 15,
                          .luck                = 8,
                          .poison_attack_ratio = 0.075f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RacerSnake,
            MonsterStats{ .health_max          = 21,
                          .mana_max            = 0,
                          .strength            = 19,
                          .dexterity           = 28,
                          .arcane              = 0,
                          .accuracy            = 23,
                          .luck                = 10,
                          .poison_attack_ratio = 0.08f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::StripedSnake,
            MonsterStats{ .health_max          = 15,
                          .mana_max            = 0,
                          .strength            = 15,
                          .dexterity           = 15,
                          .arcane              = 0,
                          .accuracy            = 15,
                          .luck                = 5,
                          .poison_attack_ratio = 0.5f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ManaCobra,
            MonsterStats{ .health_max          = 30,
                          .mana_max            = 30,
                          .armor               = 2,
                          .strength            = 20,
                          .dexterity           = 30,
                          .arcane              = 30,
                          .accuracy            = 20,
                          .luck                = 20,
                          .poison_attack_ratio = 0.1f,
                          .spell_attack_ratio  = 0.1f,
                          .spells = { Spell::Flare, Spell::FreezingWind, Spell::Jolt } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GuardianCobra,
            MonsterStats{ .health_max          = 50,
                          .mana_max            = 0,
                          .armor               = 3,
                          .strength            = 29,
                          .dexterity           = 33,
                          .arcane              = 0,
                          .accuracy            = 29,
                          .luck                = 10,
                          .poison_attack_ratio = 0.0975f }));

        //
        // spiders
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Spider,
            MonsterStats{ .health_max          = 11,
                          .mana_max            = 0,
                          .strength            = 15,
                          .dexterity           = 20,
                          .arcane              = 0,
                          .accuracy            = 13,
                          .luck                = 10,
                          .poison_attack_ratio = 0.05f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::CaveSpider,
            MonsterStats{ .health_max          = 22,
                          .mana_max            = 0,
                          .armor               = 3,
                          .strength            = 23,
                          .dexterity           = 28,
                          .arcane              = 0,
                          .accuracy            = 26,
                          .luck                = 15,
                          .poison_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WidowSpider,
            MonsterStats{ .health_max          = 25,
                          .mana_max            = 0,
                          .strength            = 25,
                          .dexterity           = 25,
                          .arcane              = 0,
                          .accuracy            = 25,
                          .luck                = 12,
                          .poison_attack_ratio = 0.25f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SpiderHorror,
            MonsterStats{ .health_max          = 36,
                          .mana_max            = 0,
                          .strength            = 36,
                          .dexterity           = 20,
                          .arcane              = 0,
                          .accuracy            = 20,
                          .luck                = 11,
                          .poison_attack_ratio = 0.3f }));

        //
        // wights
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GreenWight,
            MonsterStats{ .health_max         = 28,
                          .mana_max           = 20,
                          .strength           = 14,
                          .dexterity          = 40,
                          .arcane             = 20,
                          .accuracy           = 17,
                          .luck               = 14,
                          .is_flying          = true,
                          .is_undead          = true,
                          .spell_attack_ratio = 0.131f,
                          .spells             = { Spell::Scare } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SoulEater,
            MonsterStats{ .health_max                      = 77,
                          .mana_max                        = 50,
                          .strength                        = 43,
                          .dexterity                       = 34,
                          .arcane                          = 50,
                          .accuracy                        = 24,
                          .luck                            = 10,
                          .is_flying                       = true,
                          .is_undead                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.072f,
                          .spells                          = { Spell::HeartAttack } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Siren,
            MonsterStats{ .health_max         = 34,
                          .mana_max           = 40,
                          .strength           = 18,
                          .dexterity          = 22,
                          .arcane             = 40,
                          .accuracy           = 20,
                          .luck               = 23,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.1f,
                          .spells             = { Spell::Terrorize } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Specter,
            MonsterStats{ .health_max                      = 48,
                          .mana_max                        = 30,
                          .strength                        = 38,
                          .dexterity                       = 38,
                          .arcane                          = 30,
                          .accuracy                        = 19,
                          .luck                            = 18,
                          .is_flying                       = true,
                          .is_undead                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.0975f,
                          .spells                          = { Spell::Terrorize } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ShadowFiend,
            MonsterStats{ .health_max                      = 68,
                          .mana_max                        = 45,
                          .strength                        = 58,
                          .dexterity                       = 48,
                          .arcane                          = 45,
                          .accuracy                        = 38,
                          .luck                            = 28,
                          .is_flying                       = true,
                          .is_undead                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.0875f,
                          .spells = { Spell::Terrorize, Spell::HeartAttack } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Revenant,
            MonsterStats{ .health_max                      = 77,
                          .mana_max                        = 70,
                          .strength                        = 68,
                          .dexterity                       = 41,
                          .arcane                          = 50,
                          .accuracy                        = 48,
                          .luck                            = 34,
                          .is_undead                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.1f,
                          .spells = { Spell::Terrorize, Spell::HeartAttack } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Lorocyproca,
            MonsterStats{ .health_max                      = 42,
                          .mana_max                        = 35,
                          .strength                        = 22,
                          .dexterity                       = 22,
                          .arcane                          = 20,
                          .accuracy                        = 22,
                          .luck                            = 22,
                          .is_flying                       = true,
                          .is_undead                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.1f,
                          .spells                          = { Spell::Terrorize } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::HellWing,
            MonsterStats{ .health_max         = 60,
                          .mana_max           = 40,
                          .armor              = 5,
                          .strength           = 60,
                          .dexterity          = 48,
                          .arcane             = 40,
                          .accuracy           = 38,
                          .luck               = 22,
                          .is_flying          = true,
                          .is_undead          = true,
                          .spell_attack_ratio = 0.1f,
                          .spells             = { Spell::HeartAttack } }));

        //
        // misc
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Wollynaut,
            MonsterStats{ .health_max          = 80,
                          .mana_max            = 0,
                          .armor               = 9,
                          .strength            = 60,
                          .dexterity           = 15,
                          .arcane              = 0,
                          .accuracy            = 25,
                          .luck                = 4,
                          .break_attack_ratio  = 0.003f,
                          .devour_attack_ratio = 0.002f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ElephantDemon,
            MonsterStats{ .health_max          = 90,
                          .mana_max            = 0,
                          .armor               = 8,
                          .strength            = 70,
                          .dexterity           = 20,
                          .arcane              = 0,
                          .accuracy            = 30,
                          .luck                = 4,
                          .break_attack_ratio  = 0.003f,
                          .devour_attack_ratio = 0.002f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RottingChomper,
            MonsterStats{ .health_max          = 51,
                          .mana_max            = 0,
                          .strength            = 32,
                          .dexterity           = 13,
                          .arcane              = 0,
                          .accuracy            = 29,
                          .luck                = 0,
                          .is_undead           = true,
                          .poison_attack_ratio = 0.111f,
                          .devour_attack_ratio = 0.003f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FleshChomper,
            MonsterStats{ .health_max          = 54,
                          .mana_max            = 0,
                          .strength            = 33,
                          .dexterity           = 12,
                          .arcane              = 0,
                          .accuracy            = 26,
                          .luck                = 0,
                          .devour_attack_ratio = 0.003f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SwampThing,
            MonsterStats{ .health_max                      = 41,
                          .mana_max                        = 0,
                          .strength                        = 33,
                          .dexterity                       = 11,
                          .arcane                          = 0,
                          .accuracy                        = 19,
                          .luck                            = 10,
                          .is_immune_to_nonmagical_weapons = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::IceKnight,
            MonsterStats{ .health_max                      = 77,
                          .mana_max                        = 0,
                          .armor                           = 30,
                          .strength                        = 47,
                          .dexterity                       = 17,
                          .arcane                          = 0,
                          .accuracy                        = 27,
                          .luck                            = 20,
                          .is_immune_to_nonmagical_weapons = true,
                          .is_strong_to_ice_weak_to_fire   = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SkitterMite,
            MonsterStats{ .health_max = 23,
                          .mana_max   = 0,
                          .strength   = 21,
                          .dexterity  = 22,
                          .arcane     = 0,
                          .accuracy   = 24,
                          .luck       = 11 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WindHowler,
            MonsterStats{ .health_max                      = 32,
                          .mana_max                        = 0,
                          .strength                        = 34,
                          .dexterity                       = 31,
                          .arcane                          = 0,
                          .accuracy                        = 23,
                          .luck                            = 0,
                          .is_immune_to_nonmagical_weapons = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MudDemon,
            MonsterStats{ .health_max                      = 41,
                          .mana_max                        = 0,
                          .strength                        = 42,
                          .dexterity                       = 14,
                          .arcane                          = 0,
                          .accuracy                        = 19,
                          .luck                            = 0,
                          .is_immune_to_nonmagical_weapons = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::InvisibleMan,
            MonsterStats{ .health_max = 38,
                          .mana_max   = 0,
                          .strength   = 29,
                          .dexterity  = 81,
                          .arcane     = 0,
                          .accuracy   = 18,
                          .luck       = 18 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Kracklin,
            MonsterStats{ .health_max         = 60,
                          .mana_max           = 60,
                          .armor              = 11,
                          .strength           = 60,
                          .dexterity          = 30,
                          .arcane             = 30,
                          .accuracy           = 30,
                          .luck               = 30,
                          .spell_attack_ratio = 0.1f,
                          .spells = { Spell::Flare, Spell::FreezingWind, Spell::Lightning } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Caterhorror,
            MonsterStats{ .health_max = 40,
                          .mana_max   = 0,
                          .armor      = 7,
                          .strength   = 30,
                          .dexterity  = 20,
                          .arcane     = 0,
                          .accuracy   = 17,
                          .luck       = 3 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::VineShambler,
            MonsterStats{ .health_max        = 35,
                          .mana_max          = 0,
                          .strength          = 27,
                          .dexterity         = 16,
                          .arcane            = 0,
                          .accuracy          = 16,
                          .luck              = 10,
                          .acid_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SlimeShambler,
            MonsterStats{ .health_max        = 60,
                          .mana_max          = 0,
                          .strength          = 38,
                          .dexterity         = 19,
                          .arcane            = 0,
                          .accuracy          = 19,
                          .luck              = 20,
                          .acid_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SpellWalker,
            MonsterStats{ .health_max         = 48,
                          .mana_max           = 40,
                          .armor              = 6,
                          .strength           = 10,
                          .dexterity          = 20,
                          .arcane             = 80,
                          .accuracy           = 10,
                          .luck               = 30,
                          .spell_attack_ratio = 0.1f,
                          .spells = { Spell::Flare, Spell::FreezingWind, Spell::Lightning } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BoneHound,
            MonsterStats{ .health_max = 44,
                          .mana_max   = 0,
                          .armor      = 3,
                          .strength   = 31,
                          .dexterity  = 26,
                          .arcane     = 0,
                          .accuracy   = 19,
                          .luck       = 11,
                          .is_undead  = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::HellHound,
            MonsterStats{ .health_max = 50,
                          .mana_max   = 0,
                          .strength   = 38,
                          .dexterity  = 25,
                          .arcane     = 0,
                          .accuracy   = 20,
                          .luck       = 10 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Firebrand,
            MonsterStats{ .health_max                    = 45,
                          .mana_max                      = 0,
                          .armor                         = 8,
                          .strength                      = 33,
                          .dexterity                     = 23,
                          .arcane                        = 0,
                          .accuracy                      = 23,
                          .luck                          = 7,
                          .is_strong_to_fire_weak_to_ice = true,
                          .breathe_fire_attack_ratio     = 0.222f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RustDevil,
            MonsterStats{ .health_max = 40,
                          .mana_max   = 0,
                          .strength   = 30,
                          .dexterity  = 16,
                          .arcane     = 0,
                          .accuracy   = 22,
                          .luck       = 7 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RedDemon,
            MonsterStats{ .health_max                    = 66,
                          .mana_max                      = 0,
                          .armor                         = 6,
                          .strength                      = 44,
                          .dexterity                     = 33,
                          .arcane                        = 0,
                          .accuracy                      = 22,
                          .luck                          = 11,
                          .is_flying                     = true,
                          .is_strong_to_fire_weak_to_ice = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::OrangeDemon,
            MonsterStats{ .health_max = 46,
                          .mana_max   = 0,
                          .armor      = 3,
                          .strength   = 24,
                          .dexterity  = 23,
                          .arcane     = 0,
                          .accuracy   = 19,
                          .luck       = 6 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MutantBull,
            MonsterStats{ .health_max         = 60,
                          .mana_max           = 30,
                          .strength           = 41,
                          .dexterity          = 25,
                          .arcane             = 37,
                          .accuracy           = 25,
                          .luck               = 16,
                          .spell_attack_ratio = 0.5f,
                          .spells             = { Spell::Terrorize } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MoonTroll,
            MonsterStats{ .health_max                      = 60,
                          .mana_max                        = 0,
                          .strength                        = 36,
                          .dexterity                       = 26,
                          .arcane                          = 0,
                          .accuracy                        = 26,
                          .luck                            = 26,
                          .is_immune_to_nonmagical_weapons = true,
                          .is_strong_to_ice_weak_to_fire   = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Hippogriff,
            MonsterStats{ .health_max = 40,
                          .mana_max   = 0,
                          .strength   = 30,
                          .dexterity  = 27,
                          .arcane     = 0,
                          .accuracy   = 27,
                          .luck       = 10,
                          .is_flying  = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Hellion,
            MonsterStats{ .health_max                    = 80,
                          .mana_max                      = 0,
                          .strength                      = 78,
                          .dexterity                     = 36,
                          .arcane                        = 0,
                          .accuracy                      = 36,
                          .luck                          = 36,
                          .is_undead                     = true,
                          .is_strong_to_fire_weak_to_ice = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GreenBullber,
            MonsterStats{ .health_max          = 50,
                          .mana_max            = 0,
                          .strength            = 36,
                          .dexterity           = 12,
                          .arcane              = 0,
                          .accuracy            = 18,
                          .luck                = 5,
                          .poison_attack_ratio = 0.0975f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::OrangeClamber,
            MonsterStats{ .health_max         = 80,
                          .mana_max           = 0,
                          .armor              = 12,
                          .strength           = 67,
                          .dexterity          = 14,
                          .arcane             = 0,
                          .accuracy           = 40,
                          .luck               = 10,
                          .break_attack_ratio = 0.0025f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SunWeaver,
            MonsterStats{ .health_max                      = 70,
                          .mana_max                        = 70,
                          .armor                           = 5,
                          .strength                        = 45,
                          .dexterity                       = 35,
                          .arcane                          = 70,
                          .accuracy                        = 30,
                          .luck                            = 60,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.175f,
                          .spells                          = { Spell::Flare, Spell::Fireball } }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FireElemental,
            MonsterStats{ .health_max                      = 50,
                          .mana_max                        = 0,
                          .strength                        = 60,
                          .dexterity                       = 1,
                          .arcane                          = 0,
                          .accuracy                        = 1,
                          .luck                            = 20,
                          .is_immune_to_nonmagical_weapons = true,
                          .is_strong_to_fire_weak_to_ice   = true,
                          .breathe_fire_attack_ratio       = 1.0f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Draconian,
            MonsterStats{ .health_max = 66,
                          .mana_max   = 0,
                          .strength   = 66,
                          .dexterity  = 33,
                          .arcane     = 0,
                          .accuracy   = 33,
                          .luck       = 15,
                          .is_flying  = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Fungosite,
            MonsterStats{ .health_max          = 44,
                          .mana_max            = 0,
                          .strength            = 30,
                          .dexterity           = 20,
                          .arcane              = 0,
                          .accuracy            = 20,
                          .luck                = 20,
                          .poison_attack_ratio = 0.087f,
                          .acid_attack_ratio   = 0.0475f }));
    }

    void MonsterStatsDatabase::setup() { verifyAll(); }

    void MonsterStatsDatabase::dumpInfo(const sf::Font & t_font) const
    {
        // write all to spreadsheet
        {
            std::ofstream csvFileStream("monster-stats.csv", std::ios_base::trunc);

            csvFileStream
                << "name,value,health,armor,mana,str,dex,arc,acc,lck,flying,undead,immune,"
                   "breathe fire,poison,acid,cast,break,devour,of ice,of fire,spells\n";

            for (const auto & pair : m_imageStatsMap)
            {
                csvFileStream << tileImageToName(pair.first) << ',';
                csvFileStream << pair.second.value() << ',';
                csvFileStream << pair.second.health_max << ',';
                csvFileStream << pair.second.armor << ',';
                csvFileStream << pair.second.mana_max << ',';
                csvFileStream << pair.second.strength << ',';
                csvFileStream << pair.second.dexterity << ',';
                csvFileStream << pair.second.arcane << ',';
                csvFileStream << pair.second.accuracy << ',';
                csvFileStream << pair.second.luck << ',';

                if (pair.second.is_flying)
                {
                    csvFileStream << "flying";
                }
                csvFileStream << ',';

                if (pair.second.is_undead)
                {
                    csvFileStream << "undead";
                }
                csvFileStream << ',';

                if (pair.second.is_immune_to_nonmagical_weapons)
                {
                    csvFileStream << "immune";
                }
                csvFileStream << ',';

                csvFileStream << pair.second.breathe_fire_attack_ratio << ',';
                csvFileStream << pair.second.poison_attack_ratio << ',';
                csvFileStream << pair.second.acid_attack_ratio << ',';
                csvFileStream << pair.second.spell_attack_ratio << ',';
                csvFileStream << pair.second.break_attack_ratio << ',';
                csvFileStream << pair.second.devour_attack_ratio << ',';

                if (pair.second.is_strong_to_ice_weak_to_fire)
                {
                    csvFileStream << "of ice";
                }
                csvFileStream << ',';

                if (pair.second.is_strong_to_fire_weak_to_ice)
                {
                    csvFileStream << "of fire";
                }
                csvFileStream << ',';

                for (const Spell spell : pair.second.spells)
                {
                    csvFileStream << spellToName(spell) << '/';
                }
                csvFileStream << '\n';
            }
        }

        // calc some statistics
        std::cout << std::endl << "Monster Statistics:" << std::endl;

        struct MonsterValue
        {
            std::string name{};
            int value{};
        };

        std::vector<MonsterValue> values;
        std::vector<int> rawValues;

        std::size_t undeadCount        = 0;
        std::size_t flyingCount        = 0;
        std::size_t breatheFireCount   = 0;
        std::size_t immuneCount        = 0;
        std::size_t spellCasterCount   = 0;
        const std::size_t monsterCount = m_imageStatsMap.size();

        for (const auto & pair : m_imageStatsMap)
        {
            if (pair.second.is_undead)
            {
                ++undeadCount;
            }

            if (pair.second.is_flying)
            {
                ++flyingCount;
            }

            if (pair.second.breathe_fire_attack_ratio > 0.0f)
            {
                ++breatheFireCount;
            }

            if (pair.second.is_immune_to_nonmagical_weapons)
            {
                ++immuneCount;
            }

            if (pair.second.isSpellCaster())
            {
                ++spellCasterCount;
            }

            MonsterValue value;
            value.name  = tileImageToName(pair.first);
            value.value = pair.second.value();
            values.push_back(value);

            rawValues.push_back(value.value);
        }

        std::cout << "\tTotal of " << monsterCount << " monsters\n";

        std::cout << "\tUndead count = " << undeadCount << " / "
                  << util::makePercentString(undeadCount, monsterCount) << '\n';

        std::cout << "\tFlying count = " << flyingCount << " / "
                  << util::makePercentString(flyingCount, monsterCount) << '\n';

        std::cout << "\tBreathe fire count = " << breatheFireCount << " / "
                  << util::makePercentString(breatheFireCount, monsterCount) << '\n';

        std::cout << "\tImmune to nonmagical weapons count = " << immuneCount << " / "
                  << util::makePercentString(immuneCount, monsterCount) << '\n';

        std::cout << "\tSpellcaster count = " << spellCasterCount << " / "
                  << util::makePercentString(spellCasterCount, monsterCount) << '\n';

        // list all monsters by values
        std::cout << "\n\t--- Monster Values ---\n";

        std::sort(
            std::begin(values),
            std::end(values),
            [](const MonsterValue & a, const MonsterValue & b) { return (a.value < b.value); });

        for (const MonsterValue & value : values)
        {
            std::cout << "\t\t" << value.value << "\t" << value.name << '\n';
        }

        // make a picture of the graph of monster values
        std::sort(std::begin(rawValues), std::end(rawValues));
        util::StatsDisplay<int>::makeAndSavePNG("monster-values", t_font, rawValues);
    }

    const MonsterStats MonsterStatsDatabase::find(const TileImage & t_tileImage) const
    {
        M_CHECK(
            isTileImageMonster(t_tileImage),
            "MonsterStatsDatabase query was not a monster: " << tileImageToName(t_tileImage));

        const auto foundIter = m_imageStatsMap.find(t_tileImage);

        M_CHECK(
            (foundIter != std::end(m_imageStatsMap)),
            "MonsterStatsDatabase failed to find this monster: " << tileImageToName(t_tileImage));

        return foundIter->second;
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
                << m_imageStatsMap.size() << " but should have exactly " << count);

        // verify all are valid
        for (const auto & pair : m_imageStatsMap)
        {
            const TileImage & tileImage = pair.first;
            const MonsterStats & stats  = pair.second;
            const std::string_view name = tileImageToName(pair.first);

            M_CHECK(
                isTileImageMonster(tileImage),
                "MonsterStatsDatabase had a non-monster in it: " << name);

            M_CHECK(
                ((stats.health_max > 0) && (stats.strength > 0) && (stats.dexterity > 0) &&
                 (stats.accuracy > 0)),
                "MonsterStatsDatabase had invalid (zero value) stats for: " << name);

            if (stats.mana_max > 0)
            {
                M_CHECK((stats.arcane > 0), "Monster had mana_max>0 but arcane=0: " << name);
            }

            if (stats.arcane > 0)
            {
                M_CHECK((stats.mana_max > 0), "Monster had arcane>0 but mana_max=0: " << name);
            }

            if (stats.spell_attack_ratio > 0.0f)
            {
                M_CHECK(
                    (stats.mana_max > 0),
                    "Monster casts the stun spell but had zero mana_max: " << name);

                M_CHECK(
                    (stats.arcane > 0),
                    "Monster casts the stun spell but had zero arcane stat: " << name);
            }

            if ((stats.mana_max > 0) || (stats.arcane > 0))
            {
                M_CHECK(!stats.spells.empty(), "Monster spellcaster has no spells: " << name);
            }

            if (stats.is_strong_to_fire_weak_to_ice)
            {
                M_CHECK(
                    !stats.is_strong_to_ice_weak_to_fire,
                    "Monster is both OF FIRE and OF ICE: " << name);
            }

            if (stats.is_strong_to_ice_weak_to_fire)
            {
                M_CHECK(
                    !stats.is_strong_to_fire_weak_to_ice,
                    "Monster is both OF FIRE and OF ICE: " << name);
            }

            M_CHECK((stats.armor >= 0), "Monster armor was negative: " << name);

            M_CHECK(
                (stats.armor <= MonsterStats::stat_max), "Monster armor was too high: " << name);

            M_CHECK(
                (stats.health_max <= MonsterStats::stat_max),
                "Monster health_max is invalid: " << name);

            M_CHECK(
                (stats.mana_max <= MonsterStats::stat_max),
                "Monster mana_max is invalid: " << name);

            M_CHECK(
                (stats.strength <= MonsterStats::stat_max),
                "Monster strength is invalid: " << name);

            M_CHECK(
                (stats.dexterity <= MonsterStats::stat_max),
                "Monster dexterity is invalid: " << name);

            M_CHECK(
                (stats.arcane <= MonsterStats::stat_max), "Monster arcane is invalid: " << name);

            M_CHECK(
                (stats.accuracy <= MonsterStats::stat_max),
                "Monster accuracy is invalid: " << name);

            M_CHECK((stats.luck <= MonsterStats::stat_max), "Monster luck is invalid: " << name);

            M_CHECK(
                !(stats.breathe_fire_attack_ratio > 1.0f),
                "Monster breathe_fire_attack_ratio is invalid: " << name);

            M_CHECK(
                !(stats.poison_attack_ratio > 1.0f),
                "Monster poison_attack_ratio is invalid: " << name);

            M_CHECK(
                !(stats.acid_attack_ratio > 1.0f),
                "Monster acid_attack_ratio is invalid: " << name);

            M_CHECK(
                !(stats.spell_attack_ratio > 1.0f),
                "Monster spell_attack_ratio is invalid: " << name);

            M_CHECK(
                !(stats.break_attack_ratio > 1.0f),
                "Monster break_attack_ratio is invalid: " << name);

            M_CHECK(
                !(stats.devour_attack_ratio > 1.0f),
                "Monster devour_attack_ratio is invalid: " << name);
        }
    }

} // namespace castlecrawl