// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// enemy.cpp
//
#include "enemy.hpp"

#include "check-macros.hpp"
#include "context.hpp"
#include "layout.hpp"
#include "map.hpp"
#include "player.hpp"
#include "random.hpp"
#include "tile-images.hpp"
#include "util.hpp"

#include <type_traits>

#include <SFML/Graphics/Sprite.hpp>

namespace castlecrawl2
{
    EnemyImage randomEnemyImage(const util::Random & random, const Enemy enemy)
    {
        EnemyImage enemyImage = defaultEnemyImage(enemy);

        if (!isEnemyImageSummoner(enemyImage))
        {
            using T = std::underlying_type_t<EnemyImage>;
            enemyImage = static_cast<EnemyImage>(T(enemyImage) + random.zeroTo(T(5)));
        }

        return enemyImage;
    }

    EnemyInstance::EnemyInstance(const util::Random & random, const Enemy e, const MapPos_t & p)
        : enemy(e)
        , image(randomEnemyImage(random, e))
        , position(p)
        , timer_sec(turnTimeSec(random, e))
    {}

    Enemies::Enemies()
        : m_enemies()
    {}

    void Enemies::setup(const GameConfig & config)
    {
        m_texture.loadFromFile((config.media_path / "image" / "enemies.png").string());
        m_texture.setSmooth(true);
    }

    void Enemies::update(const Context & context, const float frameTimeSec)
    {
        for (EnemyInstance & enemy : m_enemies)
        {
            enemy.timer_sec -= frameTimeSec;
            if (enemy.timer_sec < 0.0f)
            {
                enemy.timer_sec = turnTimeSec(context.random, enemy.enemy);
                act(context, enemy);
            }
        }
    }

    void Enemies::add(const EnemyInstance & enemy) { m_enemies.push_back(enemy); }

    void Enemies::remove(const MapPos_t & pos)
    {
        m_enemies.erase(
            std::remove_if(
                std::begin(m_enemies),
                std::end(m_enemies),
                [&](const EnemyInstance & si) { return (si.position == pos); }),
            std::end(m_enemies));
    }

    void Enemies::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        for (const EnemyInstance & enemy : m_enemies)
        {
            sf::Sprite sprite(m_texture, enemyImageRect(enemy.image));
            util::fit(sprite, context.layout.cellSize());
            sprite.setPosition(context.map.mapPosToScreenPos(context, enemy.position));
            target.draw(sprite, states);
        }
    }

    bool Enemies::isAnyAtMapPos(const MapPos_t & pos) const
    {
        for (const EnemyInstance & enemy : m_enemies)
        {
            if (enemy.position == pos)
            {
                return true;
            }
        }

        return false;
    }

    void Enemies::act(const Context & context, EnemyInstance & enemy)
    {
        if (enemy.isSummoner())
        {
            spawn(context, enemy);
        }
        else
        {
            move(context, enemy);
        }
    }

    void Enemies::move(const Context & context, EnemyInstance & enemy)
    {
        std::vector<MapCell> possibleMoveCells =
            context.map.surroundingCellsHorizVert(enemy.position);

        removeSpawnAndMoveObstacles(context, possibleMoveCells);

        if (possibleMoveCells.empty())
        {
            return;
        }

        // TODO start with simple random move while testing
        const MapCell cellToMoveInto = context.random.from(possibleMoveCells);

        enemy.position = cellToMoveInto.position;
    }

    void Enemies::spawn(const Context & context, EnemyInstance & enemy)
    {
        std::vector<MapCell> possibleMoveCells =
            context.map.surroundingCellsHorizVert(enemy.position);

        removeSpawnAndMoveObstacles(context, possibleMoveCells);

        if (possibleMoveCells.empty())
        {
            return;
        }

        const MapCell cellToMoveInto = context.random.from(possibleMoveCells);

        const EnemyInstance spawnedInstance(
            context.random, spawnType(enemy.enemy), cellToMoveInto.position);

        add(spawnedInstance);
    }

    void Enemies::removeSpawnAndMoveObstacles(
        const Context & context, std::vector<MapCell> & cells) const
    {
        // can't move onto obstacles
        cells.erase(
            std::remove_if(
                std::begin(cells),
                std::end(cells),
                [&](const MapCell & cell) { return (cell.object_char != ' '); }),
            std::end(cells));

        // can't move onto player
        cells.erase(
            std::remove_if(
                std::begin(cells),
                std::end(cells),
                [&](const MapCell & cell) { return (cell.position == context.player.position()); }),
            std::end(cells));

        // can't move onto other enemies
        cells.erase(
            std::remove_if(
                std::begin(cells),
                std::end(cells),
                [&](const MapCell & cell) {
                    for (const EnemyInstance & e : m_enemies)
                    {
                        if (cell.position == e.position)
                        {
                            return true;
                        }
                    }

                    return false;
                }),
            std::end(cells));
    }

} // namespace castlecrawl2
