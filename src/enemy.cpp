// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// enemy.cpp
//
#include "enemy.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "layout.hpp"
#include "maps.hpp"
#include "player-display.hpp"
#include "random.hpp"
#include "sfml-util.hpp"
#include "tile-images.hpp"

#include <type_traits>

#include <SFML/Graphics/Sprite.hpp>

namespace castlecrawl
{
    EnemyImage randomEnemyImage(const util::Random & t_random, const Enemy t_enemy)
    {
        EnemyImage enemyImage = defaultEnemyImage(t_enemy);

        if (!isEnemyImageSummoner(enemyImage))
        {
            using T    = std::underlying_type_t<EnemyImage>;
            enemyImage = static_cast<EnemyImage>(T(enemyImage) + t_random.zeroTo(T(5)));
        }

        return enemyImage;
    }

    EnemyInstance::EnemyInstance(
        const util::Random & t_random, const Enemy t_enemy, const MapPos_t & t_pos)
        : enemy{ t_enemy }
        , image{ randomEnemyImage(t_random, t_enemy) }
        , position{ t_pos }
        , timer_sec{ turnTimeSec(t_random, t_enemy) }
        , walk_toward_ratio{ walkToPlayerRatio(t_enemy) }
    {}

    Enemies::Enemies()
        : m_enemies{}
    {}

    void Enemies::setup(const GameConfig & t_config)
    {
        const bool loadResult =
            m_texture.loadFromFile((t_config.media_path / "image" / "enemy.png").string());

        M_CHECK(loadResult, "Unable to load enemy texture file.");

        m_texture.setSmooth(true);
    }

    void Enemies::update(const Context & t_context, const float t_frameTimeSec)
    {
        for (EnemyInstance & enemy : m_enemies)
        {
            enemy.timer_sec -= t_frameTimeSec;
            if (enemy.timer_sec < 0.0f)
            {
                enemy.timer_sec = turnTimeSec(t_context.random, enemy.enemy);
                act(t_context, enemy);
            }
        }

        // add in enemies who were spawned during this update
        for (const EnemyInstance & enemy : m_spawned)
        {
            m_enemies.push_back(enemy);
        }

        m_spawned.clear();
    }

    void Enemies::add(const EnemyInstance & t_enemy) { m_enemies.push_back(t_enemy); }

    void Enemies::remove(const MapPos_t & t_pos)
    {
        std::erase_if(m_enemies, [&](const EnemyInstance & si) { return (si.position == t_pos); });
    }

    void Enemies::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        for (const EnemyInstance & enemy : m_enemies)
        {
            sf::Sprite sprite(m_texture, enemyImageRect(enemy.image));
            util::fit(sprite, t_context.layout.cellSize());

            sprite.setPosition(
                t_context.maps.current().mapPosToScreenPos(t_context, enemy.position));

            t_target.draw(sprite, t_states);
        }
    }

    bool Enemies::isAnyAtMapPos(const MapPos_t & t_pos) const
    {
        for (const EnemyInstance & enemy : m_enemies)
        {
            if (enemy.position == t_pos)
            {
                return true;
            }
        }

        return false;
    }

    void Enemies::act(const Context & t_context, EnemyInstance & t_enemy)
    {
        if (t_enemy.isSummoner())
        {
            spawn(t_context, t_enemy);
        }
        else
        {
            move(t_context, t_enemy);
        }
    }

    void Enemies::move(const Context & t_context, EnemyInstance & t_enemy)
    {
        std::vector<MapCell> possibleMoveCells =
            t_context.maps.current().surroundingCellsHorizVert(t_enemy.position);

        removeSpawnAndMoveObstacles(t_context, possibleMoveCells);

        if (possibleMoveCells.empty())
        {
            return;
        }

        if (t_context.random.zeroTo(1.0f) < t_enemy.walk_toward_ratio)
        {
            auto distance = [](const MapPos_t & A, const MapPos_t & B) {
                return (util::abs(A.x - B.x) + util::abs(A.y - B.y));
            };

            std::ranges::sort(possibleMoveCells, [&](const MapCell & A, const MapCell & B) {
                return (
                    distance(t_context.player_display.position(), A.position) <
                    distance(t_context.player_display.position(), B.position));
            });

            const int shortestDistance =
                distance(possibleMoveCells.front().position, t_context.player_display.position());

            std::erase_if(possibleMoveCells, [&](const MapCell & cell) {
                return (
                    distance(t_context.player_display.position(), cell.position) >
                    shortestDistance);
            });
        }

        t_enemy.position = t_context.random.from(possibleMoveCells).position;
    }

    void Enemies::spawn(const Context & t_context, EnemyInstance & t_enemy)
    {
        std::vector<MapCell> possibleSpawnCells =
            t_context.maps.current().surroundingCellsHorizVert(t_enemy.position);

        removeSpawnAndMoveObstacles(t_context, possibleSpawnCells);

        if (possibleSpawnCells.empty())
        {
            return;
        }

        const MapCell cellToMoveInto = t_context.random.from(possibleSpawnCells);

        const EnemyInstance spawnedInstance(
            t_context.random, spawnType(t_enemy.enemy), cellToMoveInto.position);

        m_spawned.push_back(spawnedInstance);
    }

    void Enemies::removeSpawnAndMoveObstacles(
        const Context & t_context, std::vector<MapCell> & t_cells) const
    {
        // can't move onto obstacles
        std::erase_if(t_cells, [&](const MapCell & cell) { return (cell.object_char != ' '); });

        // can't move onto player
        std::erase_if(t_cells, [&](const MapCell & cell) {
            return (cell.position == t_context.player_display.position());
        });

        // can't move onto other enemies
        std::erase_if(t_cells, [&](const MapCell & cell) {
            for (const EnemyInstance & e : m_enemies)
            {
                if (cell.position == e.position)
                {
                    return true;
                }
            }

            return false;
        });
    }

} // namespace castlecrawl
