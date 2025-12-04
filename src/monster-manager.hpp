#ifndef MONSTER_MANAGER_HPP_INCLUDED
#define MONSTER_MANAGER_HPP_INCLUDED
//
// monster-manager.hpp
//
#include "creature.hpp"
#include "map-types.hpp"
#include "monster-stats-database.hpp"
#include "monster.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <vector>

namespace castlecrawl
{
    struct Context;

    class MonsterManager
    {
      public:
        MonsterManager();

        void add(const Context & t_context, const MapPos_t & t_mapPos, const char t_mapChar);
        void reset();

        // returns true if the monster changed map position
        CreatureAction takeTurn(const Context & t_context, const std::size_t t_uniqueId);

        void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const;

        [[nodiscard]] const MonsterStats stats(const MapPos_t & t_mapPos) const;

        // returns true if killed
        bool damage(const MapPos_t & t_mapPos, const int t_damage);

        // returns true if any were removed
        bool removeDead(const Context & t_context);

        [[nodiscard]] inline std::size_t count() const { return m_monsters.size(); }

        [[nodiscard]] std::size_t highestUniqueId() const;

      private:
        std::size_t m_nextUniqueId; // these IDs are only unique to each map
        std::vector<Monster> m_monsters;
    };

} // namespace castlecrawl

#endif // MONSTER_MANAGER_HPP_INCLUDED