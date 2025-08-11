#ifndef MONSTER_MANAGER_HPP_INCLUDED
#define MONSTER_MANAGER_HPP_INCLUDED
//
// monster-manager.hpp
//
#include "map-types.hpp"
#include "monster.hpp"
#include "tile-image-enum.hpp"

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
        bool takeTurn(const Context & t_context, const std::size_t t_uniqueId);

        void drawHealthLines(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const;

        [[nodiscard]] const MonsterStats stats(const MapPos_t & t_mapPos) const;

        // returns true if killed
        bool damage(const MapPos_t & t_mapPos, const int t_damage);

        // returns true if any were removed
        bool removeDead(const Context & t_context);

        [[nodiscard]] inline std::size_t count() const { return m_monsters.size(); }

      private:
        // these IDs are only unique to each map
        std::size_t m_nextUniqueId;

        std::vector<Monster> m_monsters;
    };

} // namespace castlecrawl

#endif // MONSTER_MANAGER_HPP_INCLUDED