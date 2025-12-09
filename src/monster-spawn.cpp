// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// monster-spawn.cpp
//
#include "monster-spawn.hpp"

#include "context.hpp"
#include "player.hpp"
#include "random.hpp"

namespace castlecrawl
{

    TileImage MonsterSpawn::randomMonster(const Context & t_context)
    {
        const int playerLevel = t_context.player.level();

        if (playerLevel <= 1)
        {
            return TileImage::Bat;
        }
        else if (playerLevel <= 3)
        {
            return t_context.random.from(
                { TileImage::RabidRodent, TileImage::Madman, TileImage::FireBat });
        }
        else if (playerLevel <= 5)
        {
            return t_context.random.from({ TileImage::Kobold,
                                           TileImage::Quasit,
                                           TileImage::RustCrab,
                                           TileImage::Spider,
                                           TileImage::Spider,
                                           TileImage::GreenSnake });
        }
        else if (playerLevel <= 6)
        {
            return t_context.random.from({ TileImage::KoboldBrute,
                                           TileImage::OctoCrawler,
                                           TileImage::RedJelly,
                                           TileImage::AntCreeper,
                                           TileImage::DessertSnake,
                                           TileImage::Scorpion,
                                           TileImage::SkitterMite });
        }
        else if (playerLevel <= 10)
        {
            return t_context.random.from({ TileImage::RacerSnake,
                                           TileImage::CoillingViper,
                                           TileImage::SkullSlime,
                                           TileImage::BeholderMite,
                                           TileImage::FleshChomper });
        }
        else if (playerLevel <= 15)
        {
            return t_context.random.from({ TileImage::BloatedCreeper,
                                           TileImage::CaveSpider,
                                           TileImage::SlimeBeholder,
                                           TileImage::GoldScorpion,
                                           TileImage::BeholderSpawn });
        }
        else if (playerLevel <= 20)
        {
            return t_context.random.from({ TileImage::Fungosite,
                                           TileImage::WidowSpider,
                                           TileImage::RottingChomper,
                                           TileImage::GuardianCobra });
        }
        else if (playerLevel <= 25)
        {
            return t_context.random.from({ TileImage::AquaSlime,
                                           TileImage::SpiderHorror,
                                           TileImage::GiantAmoeba,
                                           TileImage::WanderingEye,
                                           TileImage::Ooze });
        }
        else
        {
            return t_context.random.from({ TileImage::WalkingBeholder,
                                           TileImage::ManaCobra,
                                           TileImage::WailingSlime,
                                           TileImage::SkiteWing,
                                           TileImage::Beholder });
        }
    }

} // namespace castlecrawl
