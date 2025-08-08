// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster-stats-database.cpp
//
#include "monster-stats-database.hpp"

#include "check-macros.hpp"
#include "util.hpp"

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
            MonsterStats{ .health    = 12,
                          .mana      = 0,
                          .strength  = 10,
                          .dexterity = 10,
                          .arcane    = 0,
                          .accuracy  = 10,
                          .luck      = 10 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Kobold,
            MonsterStats{ .health    = 15,
                          .mana      = 0,
                          .strength  = 15,
                          .dexterity = 15,
                          .arcane    = 0,
                          .accuracy  = 15,
                          .luck      = 12 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::KoboldBrute,
            MonsterStats{ .health    = 18,
                          .mana      = 0,
                          .strength  = 18,
                          .dexterity = 12,
                          .arcane    = 0,
                          .accuracy  = 15,
                          .luck      = 10 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RabidRodent,
            MonsterStats{ .health    = 10,
                          .mana      = 0,
                          .strength  = 14,
                          .dexterity = 16,
                          .arcane    = 0,
                          .accuracy  = 15,
                          .luck      = 10 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Bat,
            MonsterStats{ .health    = 8,
                          .mana      = 0,
                          .strength  = 8,
                          .dexterity = 17,
                          .arcane    = 0,
                          .accuracy  = 15,
                          .luck      = 11,
                          .is_flying = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FireBat,
            MonsterStats{ .health    = 14,
                          .mana      = 0,
                          .strength  = 14,
                          .dexterity = 14,
                          .arcane    = 0,
                          .accuracy  = 14,
                          .luck      = 14,
                          .is_flying = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RustCrab,
            MonsterStats{ .health             = 18,
                          .mana               = 0,
                          .strength           = 17,
                          .dexterity          = 11,
                          .arcane             = 0,
                          .accuracy           = 16,
                          .luck               = 5,
                          .break_attack_ratio = 0.02f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GiantLeech,
            MonsterStats{ .health              = 16,
                          .mana                = 0,
                          .strength            = 17,
                          .dexterity           = 13,
                          .arcane              = 0,
                          .accuracy            = 16,
                          .luck                = 1,
                          .devour_attack_ratio = 0.025f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Scorpion,
            MonsterStats{ .health              = 16,
                          .mana                = 0,
                          .strength            = 14,
                          .dexterity           = 19,
                          .arcane              = 0,
                          .accuracy            = 15,
                          .luck                = 2,
                          .poison_attack_ratio = 0.09f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GoldScorpion,
            MonsterStats{ .health    = 32,
                          .mana      = 0,
                          .strength  = 28,
                          .dexterity = 25,
                          .arcane    = 0,
                          .accuracy  = 25,
                          .luck      = 34 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Antlion,
            MonsterStats{ .health    = 28,
                          .mana      = 0,
                          .strength  = 20,
                          .dexterity = 18,
                          .arcane    = 0,
                          .accuracy  = 18,
                          .luck      = 2 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Quasit,
            MonsterStats{ .health    = 14,
                          .mana      = 0,
                          .strength  = 9,
                          .dexterity = 27,
                          .arcane    = 0,
                          .accuracy  = 15,
                          .luck      = 10 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::OctoCrawler,
            MonsterStats{ .health    = 24,
                          .mana      = 0,
                          .strength  = 19,
                          .dexterity = 15,
                          .arcane    = 0,
                          .accuracy  = 15,
                          .luck      = 9 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BogSlave,
            MonsterStats{ .health    = 29,
                          .mana      = 0,
                          .strength  = 18,
                          .dexterity = 14,
                          .arcane    = 0,
                          .accuracy  = 16,
                          .luck      = 8 }));

        // TODO needs more spells to cast
        m_imageStatsMap.insert(std::make_pair(
            TileImage::BruteWitch,
            MonsterStats{ .health             = 26,
                          .mana               = 35,
                          .strength           = 18,
                          .dexterity          = 12,
                          .arcane             = 24,
                          .accuracy           = 15,
                          .luck               = 15,
                          .spell_attack_ratio = 0.088f }));

        //
        // beholders
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Beholder,
            MonsterStats{ .health             = 30,
                          .mana               = 60,
                          .strength           = 20,
                          .dexterity          = 14,
                          .arcane             = 60,
                          .accuracy           = 20,
                          .luck               = 20,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BeholderSpawn,
            MonsterStats{ .health             = 15,
                          .mana               = 30,
                          .strength           = 10,
                          .dexterity          = 20,
                          .arcane             = 40,
                          .accuracy           = 15,
                          .luck               = 13,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.05f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BeholderMite,
            MonsterStats{ .health             = 12,
                          .mana               = 22,
                          .strength           = 10,
                          .dexterity          = 18,
                          .arcane             = 30,
                          .accuracy           = 15,
                          .luck               = 12,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.06f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SlimeBeholder,
            MonsterStats{ .health             = 19,
                          .mana               = 24,
                          .strength           = 11,
                          .dexterity          = 19,
                          .arcane             = 33,
                          .accuracy           = 16,
                          .luck               = 11,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.04f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WalkingBeholder,
            MonsterStats{ .health             = 26,
                          .mana               = 50,
                          .strength           = 24,
                          .dexterity          = 18,
                          .arcane             = 40,
                          .accuracy           = 17,
                          .luck               = 17,
                          .is_flying          = false,
                          .spell_attack_ratio = 0.075f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ArcaneBeholder,
            MonsterStats{ .health             = 28,
                          .mana               = 85,
                          .strength           = 16,
                          .dexterity          = 12,
                          .arcane             = 85,
                          .accuracy           = 16,
                          .luck               = 30,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.15f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WanderingEye,
            MonsterStats{ .health             = 36,
                          .mana               = 40,
                          .strength           = 20,
                          .dexterity          = 12,
                          .arcane             = 25,
                          .accuracy           = 18,
                          .luck               = 14,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.111f }));

        //
        // slimes
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SkullSlime,
            MonsterStats{ .health            = 33,
                          .mana              = 0,
                          .strength          = 18,
                          .dexterity         = 10,
                          .arcane            = 0,
                          .accuracy          = 17,
                          .luck              = 8,
                          .is_undead         = true,
                          .acid_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::AquaSlime,
            MonsterStats{ .health                          = 24,
                          .mana                            = 0,
                          .strength                        = 14,
                          .dexterity                       = 8,
                          .arcane                          = 0,
                          .accuracy                        = 15,
                          .luck                            = 12,
                          .is_immune_to_nonmagical_weapons = true,
                          .acid_attack_ratio               = 0.05f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Ooze,
            MonsterStats{ .health                          = 20,
                          .mana                            = 0,
                          .strength                        = 16,
                          .dexterity                       = 11,
                          .arcane                          = 0,
                          .accuracy                        = 17,
                          .luck                            = 14,
                          .is_immune_to_nonmagical_weapons = true,
                          .acid_attack_ratio               = 0.12f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RedJelly,
            MonsterStats{ .health            = 16,
                          .mana              = 0,
                          .strength          = 14,
                          .dexterity         = 9,
                          .arcane            = 0,
                          .accuracy          = 15,
                          .luck              = 15,
                          .acid_attack_ratio = 0.06f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GiantAmoeba,
            MonsterStats{ .health                          = 25,
                          .mana                            = 0,
                          .strength                        = 15,
                          .dexterity                       = 9,
                          .arcane                          = 0,
                          .accuracy                        = 17,
                          .luck                            = 15,
                          .is_immune_to_nonmagical_weapons = true,
                          .acid_attack_ratio               = 0.04f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WailingSlime,
            MonsterStats{ .health                          = 40,
                          .mana                            = 0,
                          .strength                        = 20,
                          .dexterity                       = 13,
                          .arcane                          = 0,
                          .accuracy                        = 17,
                          .luck                            = 14,
                          .is_immune_to_nonmagical_weapons = true,
                          .acid_attack_ratio               = 0.13f,
                          .devour_attack_ratio             = 0.02f }));

        //
        // dragons
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Dragon,
            MonsterStats{ .health                    = 60,
                          .mana                      = 0,
                          .strength                  = 50,
                          .dexterity                 = 25,
                          .arcane                    = 0,
                          .accuracy                  = 41,
                          .luck                      = 43,
                          .is_flying                 = true,
                          .breathe_fire_attack_ratio = 0.25f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BoneDragon,
            MonsterStats{ .health                    = 65,
                          .mana                      = 0,
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
            MonsterStats{ .health                          = 91,
                          .mana                            = 0,
                          .strength                        = 80,
                          .dexterity                       = 40,
                          .arcane                          = 0,
                          .accuracy                        = 60,
                          .luck                            = 44,
                          .is_flying                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .breathe_fire_attack_ratio       = 0.333f,
                          .break_attack_ratio              = 0.013f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BoneHydra,
            MonsterStats{ .health                    = 95,
                          .mana                      = 0,
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
            MonsterStats{ .health                    = 37,
                          .mana                      = 0,
                          .strength                  = 37,
                          .dexterity                 = 37,
                          .arcane                    = 0,
                          .accuracy                  = 37,
                          .luck                      = 37,
                          .is_flying                 = true,
                          .breathe_fire_attack_ratio = 0.0f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::QuicksilverDragon,
            MonsterStats{ .health                    = 57,
                          .mana                      = 0,
                          .strength                  = 38,
                          .dexterity                 = 51,
                          .arcane                    = 0,
                          .accuracy                  = 47,
                          .luck                      = 54,
                          .is_flying                 = true,
                          .breathe_fire_attack_ratio = 0.034f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GoldenDragon,
            MonsterStats{ .health                          = 72,
                          .mana                            = 0,
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
            MonsterStats{ .health                    = 29,
                          .mana                      = 0,
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
            MonsterStats{ .health             = 55,
                          .mana               = 35,
                          .strength           = 55,
                          .dexterity          = 20,
                          .arcane             = 18,
                          .accuracy           = 35,
                          .luck               = 2,
                          .spell_attack_ratio = 0.0932f,
                          .break_attack_ratio = 0.02f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FireGiant,
            MonsterStats{ .health             = 65,
                          .mana               = 0,
                          .strength           = 65,
                          .dexterity          = 27,
                          .arcane             = 0,
                          .accuracy           = 38,
                          .luck               = 10,
                          .break_attack_ratio = 0.03f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::TwoHeadedOgre,
            MonsterStats{ .health             = 49,
                          .mana               = 0,
                          .strength           = 47,
                          .dexterity          = 9,
                          .arcane             = 0,
                          .accuracy           = 17,
                          .luck               = 4,
                          .break_attack_ratio = 0.02f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Juggernaut,
            MonsterStats{ .health             = 75,
                          .mana               = 0,
                          .strength           = 75,
                          .dexterity          = 22,
                          .arcane             = 0,
                          .accuracy           = 21,
                          .luck               = 8,
                          .break_attack_ratio = 0.075f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::IronGiant,
            MonsterStats{ .health             = 70,
                          .mana               = 0,
                          .strength           = 70,
                          .dexterity          = 19,
                          .arcane             = 0,
                          .accuracy           = 19,
                          .luck               = 9,
                          .break_attack_ratio = 0.04f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FrostGiant,
            MonsterStats{ .health             = 65,
                          .mana               = 0,
                          .strength           = 65,
                          .dexterity          = 27,
                          .arcane             = 0,
                          .accuracy           = 38,
                          .luck               = 10,
                          .break_attack_ratio = 0.03f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::TwoHeadedGiant,
            MonsterStats{ .health             = 59,
                          .mana               = 0,
                          .strength           = 59,
                          .dexterity          = 14,
                          .arcane             = 0,
                          .accuracy           = 19,
                          .luck               = 5,
                          .break_attack_ratio = 0.021f }));

        //
        // creepers
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FleshCreeper,
            MonsterStats{ .health    = 40,
                          .mana      = 0,
                          .strength  = 20,
                          .dexterity = 20,
                          .arcane    = 0,
                          .accuracy  = 20,
                          .luck      = 4 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WailingCreeper,
            MonsterStats{ .health    = 30,
                          .mana      = 0,
                          .strength  = 16,
                          .dexterity = 18,
                          .arcane    = 0,
                          .accuracy  = 24,
                          .luck      = 3 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BloodCreeper,
            MonsterStats{ .health    = 50,
                          .mana      = 0,
                          .strength  = 25,
                          .dexterity = 25,
                          .arcane    = 0,
                          .accuracy  = 25,
                          .luck      = 3 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BloatedCreeper,
            MonsterStats{ .health    = 60,
                          .mana      = 0,
                          .strength  = 30,
                          .dexterity = 17,
                          .arcane    = 0,
                          .accuracy  = 26,
                          .luck      = 1 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SpikeCreeper,
            MonsterStats{ .health    = 40,
                          .mana      = 0,
                          .strength  = 30,
                          .dexterity = 25,
                          .arcane    = 0,
                          .accuracy  = 20,
                          .luck      = 8 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::AntCreeper,
            MonsterStats{ .health    = 24,
                          .mana      = 0,
                          .strength  = 16,
                          .dexterity = 16,
                          .arcane    = 0,
                          .accuracy  = 16,
                          .luck      = 7 }));

        //
        // snakes
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::CoillingViper,
            MonsterStats{ .health              = 20,
                          .mana                = 0,
                          .strength            = 16,
                          .dexterity           = 30,
                          .arcane              = 0,
                          .accuracy            = 30,
                          .luck                = 7,
                          .poison_attack_ratio = 0.123f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GreenSnake,
            MonsterStats{ .health              = 16,
                          .mana                = 0,
                          .strength            = 13,
                          .dexterity           = 25,
                          .arcane              = 0,
                          .accuracy            = 25,
                          .luck                = 6,
                          .poison_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Serpent,
            MonsterStats{ .health              = 35,
                          .mana                = 0,
                          .strength            = 22,
                          .dexterity           = 38,
                          .arcane              = 0,
                          .accuracy            = 28,
                          .luck                = 15,
                          .poison_attack_ratio = 0.05f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::DessertSnake,
            MonsterStats{ .health              = 13,
                          .mana                = 0,
                          .strength            = 13,
                          .dexterity           = 20,
                          .arcane              = 0,
                          .accuracy            = 15,
                          .luck                = 8,
                          .poison_attack_ratio = 0.075f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RacerSnake,
            MonsterStats{ .health              = 21,
                          .mana                = 0,
                          .strength            = 19,
                          .dexterity           = 28,
                          .arcane              = 0,
                          .accuracy            = 23,
                          .luck                = 10,
                          .poison_attack_ratio = 0.08f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::StripedSnake,
            MonsterStats{ .health              = 15,
                          .mana                = 0,
                          .strength            = 15,
                          .dexterity           = 15,
                          .arcane              = 0,
                          .accuracy            = 15,
                          .luck                = 5,
                          .poison_attack_ratio = 0.5f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ManaCobra,
            MonsterStats{ .health              = 30,
                          .mana                = 30,
                          .strength            = 20,
                          .dexterity           = 30,
                          .arcane              = 30,
                          .accuracy            = 20,
                          .luck                = 20,
                          .poison_attack_ratio = 0.1f,
                          .spell_attack_ratio  = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GuardianCobra,
            MonsterStats{ .health              = 50,
                          .mana                = 0,
                          .strength            = 29,
                          .dexterity           = 33,
                          .arcane              = 0,
                          .accuracy            = 29,
                          .luck                = 10,
                          .poison_attack_ratio = 0.0975f }));

        //
        // Spider
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Spider,
            MonsterStats{ .health              = 11,
                          .mana                = 0,
                          .strength            = 15,
                          .dexterity           = 20,
                          .arcane              = 0,
                          .accuracy            = 13,
                          .luck                = 10,
                          .poison_attack_ratio = 0.05f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::CaveSpider,
            MonsterStats{ .health              = 22,
                          .mana                = 0,
                          .strength            = 23,
                          .dexterity           = 28,
                          .arcane              = 0,
                          .accuracy            = 26,
                          .luck                = 15,
                          .poison_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WidowSpider,
            MonsterStats{ .health              = 25,
                          .mana                = 0,
                          .strength            = 25,
                          .dexterity           = 25,
                          .arcane              = 0,
                          .accuracy            = 25,
                          .luck                = 12,
                          .poison_attack_ratio = 0.25f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SpiderHorror,
            MonsterStats{ .health              = 36,
                          .mana                = 0,
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
            MonsterStats{ .health             = 28,
                          .mana               = 20,
                          .strength           = 14,
                          .dexterity          = 40,
                          .arcane             = 20,
                          .accuracy           = 17,
                          .luck               = 14,
                          .is_flying          = true,
                          .is_undead          = true,
                          .spell_attack_ratio = 0.131f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SoulEater,
            MonsterStats{ .health                          = 77,
                          .mana                            = 50,
                          .strength                        = 43,
                          .dexterity                       = 34,
                          .arcane                          = 50,
                          .accuracy                        = 24,
                          .luck                            = 10,
                          .is_flying                       = true,
                          .is_undead                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.072f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Siren,
            MonsterStats{ .health             = 34,
                          .mana               = 40,
                          .strength           = 18,
                          .dexterity          = 22,
                          .arcane             = 40,
                          .accuracy           = 20,
                          .luck               = 23,
                          .is_flying          = true,
                          .spell_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Specter,
            MonsterStats{ .health                          = 48,
                          .mana                            = 30,
                          .strength                        = 38,
                          .dexterity                       = 38,
                          .arcane                          = 30,
                          .accuracy                        = 19,
                          .luck                            = 18,
                          .is_flying                       = true,
                          .is_undead                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.0975f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ShadowFiend,
            MonsterStats{ .health                          = 68,
                          .mana                            = 45,
                          .strength                        = 58,
                          .dexterity                       = 48,
                          .arcane                          = 45,
                          .accuracy                        = 38,
                          .luck                            = 28,
                          .is_flying                       = true,
                          .is_undead                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.0875f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Revenant,
            MonsterStats{ .health                          = 77,
                          .mana                            = 70,
                          .strength                        = 68,
                          .dexterity                       = 41,
                          .arcane                          = 50,
                          .accuracy                        = 48,
                          .luck                            = 34,
                          .is_undead                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Lorocyproca,
            MonsterStats{ .health                          = 42,
                          .mana                            = 35,
                          .strength                        = 22,
                          .dexterity                       = 22,
                          .arcane                          = 20,
                          .accuracy                        = 22,
                          .luck                            = 22,
                          .is_flying                       = true,
                          .is_undead                       = true,
                          .is_immune_to_nonmagical_weapons = true,
                          .spell_attack_ratio              = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::HellWing,
            MonsterStats{ .health             = 60,
                          .mana               = 40,
                          .strength           = 60,
                          .dexterity          = 48,
                          .arcane             = 40,
                          .accuracy           = 38,
                          .luck               = 22,
                          .is_flying          = true,
                          .is_undead          = true,
                          .spell_attack_ratio = 0.1f }));

        //
        // misc
        //

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Wollynaut,
            MonsterStats{ .health              = 80,
                          .mana                = 0,
                          .strength            = 60,
                          .dexterity           = 15,
                          .arcane              = 0,
                          .accuracy            = 25,
                          .luck                = 4,
                          .break_attack_ratio  = 0.03f,
                          .devour_attack_ratio = 0.02f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::ElephantDemon,
            MonsterStats{ .health              = 90,
                          .mana                = 0,
                          .strength            = 70,
                          .dexterity           = 20,
                          .arcane              = 0,
                          .accuracy            = 30,
                          .luck                = 4,
                          .break_attack_ratio  = 0.03f,
                          .devour_attack_ratio = 0.02f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RottingChomper,
            MonsterStats{ .health              = 51,
                          .mana                = 0,
                          .strength            = 32,
                          .dexterity           = 13,
                          .arcane              = 0,
                          .accuracy            = 29,
                          .luck                = 0,
                          .is_undead           = true,
                          .poison_attack_ratio = 0.111f,
                          .devour_attack_ratio = 0.03f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FleshChomper,
            MonsterStats{ .health              = 54,
                          .mana                = 0,
                          .strength            = 33,
                          .dexterity           = 12,
                          .arcane              = 0,
                          .accuracy            = 26,
                          .luck                = 0,
                          .devour_attack_ratio = 0.03f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SwampThing,
            MonsterStats{ .health                          = 41,
                          .mana                            = 0,
                          .strength                        = 33,
                          .dexterity                       = 11,
                          .arcane                          = 0,
                          .accuracy                        = 19,
                          .luck                            = 10,
                          .is_immune_to_nonmagical_weapons = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::IceKnight,
            MonsterStats{ .health                          = 77,
                          .mana                            = 0,
                          .strength                        = 47,
                          .dexterity                       = 17,
                          .arcane                          = 0,
                          .accuracy                        = 27,
                          .luck                            = 20,
                          .is_immune_to_nonmagical_weapons = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SkitterMite,
            MonsterStats{ .health    = 23,
                          .mana      = 0,
                          .strength  = 21,
                          .dexterity = 22,
                          .arcane    = 0,
                          .accuracy  = 24,
                          .luck      = 11 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::WindHowler,
            MonsterStats{ .health                          = 32,
                          .mana                            = 0,
                          .strength                        = 34,
                          .dexterity                       = 31,
                          .arcane                          = 0,
                          .accuracy                        = 23,
                          .luck                            = 0,
                          .is_immune_to_nonmagical_weapons = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MudDemon,
            MonsterStats{ .health                          = 41,
                          .mana                            = 0,
                          .strength                        = 42,
                          .dexterity                       = 14,
                          .arcane                          = 0,
                          .accuracy                        = 19,
                          .luck                            = 0,
                          .is_immune_to_nonmagical_weapons = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::InvisibleMan,
            MonsterStats{ .health    = 38,
                          .mana      = 0,
                          .strength  = 29,
                          .dexterity = 81,
                          .arcane    = 0,
                          .accuracy  = 18,
                          .luck      = 18 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Kracklin,
            MonsterStats{ .health             = 60,
                          .mana               = 60,
                          .strength           = 60,
                          .dexterity          = 30,
                          .arcane             = 30,
                          .accuracy           = 30,
                          .luck               = 30,
                          .spell_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Caterhorror,
            MonsterStats{ .health    = 40,
                          .mana      = 0,
                          .strength  = 30,
                          .dexterity = 20,
                          .arcane    = 0,
                          .accuracy  = 17,
                          .luck      = 3 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::VineShambler,
            MonsterStats{ .health            = 35,
                          .mana              = 0,
                          .strength          = 27,
                          .dexterity         = 16,
                          .arcane            = 0,
                          .accuracy          = 16,
                          .luck              = 10,
                          .acid_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SlimeShambler,
            MonsterStats{ .health            = 60,
                          .mana              = 0,
                          .strength          = 38,
                          .dexterity         = 19,
                          .arcane            = 0,
                          .accuracy          = 19,
                          .luck              = 20,
                          .acid_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SpellWalker,
            MonsterStats{ .health             = 48,
                          .mana               = 40,
                          .strength           = 10,
                          .dexterity          = 20,
                          .arcane             = 80,
                          .accuracy           = 10,
                          .luck               = 30,
                          .spell_attack_ratio = 0.1f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::BoneHound,
            MonsterStats{ .health    = 44,
                          .mana      = 0,
                          .strength  = 31,
                          .dexterity = 26,
                          .arcane    = 0,
                          .accuracy  = 19,
                          .luck      = 11,
                          .is_undead = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::HellHound,
            MonsterStats{ .health    = 50,
                          .mana      = 0,
                          .strength  = 38,
                          .dexterity = 25,
                          .arcane    = 0,
                          .accuracy  = 20,
                          .luck      = 10 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Firebrand,
            MonsterStats{ .health                    = 45,
                          .mana                      = 0,
                          .strength                  = 33,
                          .dexterity                 = 23,
                          .arcane                    = 0,
                          .accuracy                  = 23,
                          .luck                      = 7,
                          .breathe_fire_attack_ratio = 0.222f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RustDevil,
            MonsterStats{ .health    = 40,
                          .mana      = 0,
                          .strength  = 30,
                          .dexterity = 16,
                          .arcane    = 0,
                          .accuracy  = 22,
                          .luck      = 7 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::RedDemon,
            MonsterStats{ .health    = 66,
                          .mana      = 0,
                          .strength  = 44,
                          .dexterity = 33,
                          .arcane    = 0,
                          .accuracy  = 22,
                          .luck      = 11,
                          .is_flying = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::OrangeDemon,
            MonsterStats{ .health    = 46,
                          .mana      = 0,
                          .strength  = 24,
                          .dexterity = 23,
                          .arcane    = 0,
                          .accuracy  = 19,
                          .luck      = 6 }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MutantBull,
            MonsterStats{ .health             = 60,
                          .mana               = 30,
                          .strength           = 41,
                          .dexterity          = 25,
                          .arcane             = 37,
                          .accuracy           = 25,
                          .luck               = 16,
                          .spell_attack_ratio = 0.5f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::MoonTroll,
            MonsterStats{ .health                          = 60,
                          .mana                            = 0,
                          .strength                        = 36,
                          .dexterity                       = 26,
                          .arcane                          = 0,
                          .accuracy                        = 26,
                          .luck                            = 26,
                          .is_immune_to_nonmagical_weapons = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Hippogriff,
            MonsterStats{ .health    = 40,
                          .mana      = 0,
                          .strength  = 30,
                          .dexterity = 27,
                          .arcane    = 0,
                          .accuracy  = 27,
                          .luck      = 10,
                          .is_flying = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Hellion,
            MonsterStats{ .health    = 80,
                          .mana      = 0,
                          .strength  = 78,
                          .dexterity = 36,
                          .arcane    = 0,
                          .accuracy  = 36,
                          .luck      = 36,
                          .is_undead = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::GreenBullber,
            MonsterStats{ .health              = 50,
                          .mana                = 0,
                          .strength            = 36,
                          .dexterity           = 12,
                          .arcane              = 0,
                          .accuracy            = 18,
                          .luck                = 5,
                          .poison_attack_ratio = 0.0975f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::OrangeClamber,
            MonsterStats{ .health             = 80,
                          .mana               = 0,
                          .strength           = 67,
                          .dexterity          = 14,
                          .arcane             = 0,
                          .accuracy           = 40,
                          .luck               = 10,
                          .break_attack_ratio = 0.025f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::SunWeaver,
            MonsterStats{ .health                          = 70,
                          .mana                            = 70,
                          .strength                        = 45,
                          .dexterity                       = 35,
                          .arcane                          = 70,
                          .accuracy                        = 30,
                          .luck                            = 60,
                          .is_immune_to_nonmagical_weapons = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::FireElemental,
            MonsterStats{ .health                          = 50,
                          .mana                            = 0,
                          .strength                        = 1,
                          .dexterity                       = 1,
                          .arcane                          = 0,
                          .accuracy                        = 40,
                          .luck                            = 20,
                          .is_immune_to_nonmagical_weapons = true,
                          .breathe_fire_attack_ratio       = 1.0f }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Draconian,
            MonsterStats{ .health    = 66,
                          .mana      = 0,
                          .strength  = 66,
                          .dexterity = 33,
                          .arcane    = 0,
                          .accuracy  = 33,
                          .luck      = 15,
                          .is_flying = true }));

        m_imageStatsMap.insert(std::make_pair(
            TileImage::Fungosite,
            MonsterStats{ .health              = 44,
                          .mana                = 0,
                          .strength            = 30,
                          .dexterity           = 20,
                          .arcane              = 0,
                          .accuracy            = 20,
                          .luck                = 20,
                          .poison_attack_ratio = 0.087f,
                          .acid_attack_ratio   = 0.0475f }));
    }

    void MonsterStatsDatabase::setup() { verifyAll(); }

    void MonsterStatsDatabase::dumpInfo() const
    {
        // write all to spreadsheet
        {
            std::ofstream csvFileStream("monster-stats.csv", std::ios_base::trunc);

            csvFileStream
                << "name,health,mana,str,dex,arc,acc,lck,flying,undead,immune,breathe fire,"
                   "poison,acid,stun,break,devour\n";

            for (const auto & pair : m_imageStatsMap)
            {
                csvFileStream << tileImageToName(pair.first) << ',';
                csvFileStream << pair.second.health << ',';
                csvFileStream << pair.second.mana << ',';
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
                csvFileStream << pair.second.devour_attack_ratio << '\n';
            }
        }

        // calc some statistics
        std::cout << std::endl << "Monster Statistics:" << std::endl;
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

        std::cout << std::endl;
    }

    const MonsterStats MonsterStatsDatabase::find(const TileImage & t_tileImage) const
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

        // verify all are valid
        for (const auto & pair : m_imageStatsMap)
        {
            M_CHECK(
                isTileImageMonster(pair.first),
                "MonsterStatsDatabase had a non-monster in it: " << tileImageToName(pair.first));

            M_CHECK(
                pair.second.isValid(),
                "MonsterStatsDatabase had invalid stats in it for: "
                    << tileImageToName(pair.first));

            if (pair.second.mana > 0)
            {
                M_CHECK(
                    (pair.second.arcane > 0),
                    "MonsterStats invalid.  Mana was > 0 but arcane=0, for: "
                        << tileImageToName(pair.first));
            }

            if (pair.second.mana > 0)
            {
                M_CHECK(
                    (pair.second.arcane > 0),
                    "Monster had mana>0 but zero arcane: " << tileImageToName(pair.first));
            }

            if (pair.second.arcane > 0)
            {
                M_CHECK(
                    (pair.second.mana > 0),
                    "Monster had arcane>0 but zero mana: " << tileImageToName(pair.first));
            }

            if (pair.second.spell_attack_ratio > 0.0f)
            {
                M_CHECK(
                    (pair.second.mana > 0),
                    "Monster casts the stun spell but had zero mana:"
                        << tileImageToName(pair.first));

                M_CHECK(
                    (pair.second.arcane > 0),
                    "Monster casts the stun spell but had zero arcane stat:"
                        << tileImageToName(pair.first));
            }
        }
    }

} // namespace castlecrawl