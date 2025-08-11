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
        inline void reset() { m_monsters.clear(); }

        // returns true if any monsters change map position
        bool takeTurns(const Context & t_context);

        void drawHealthLines(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const;

        [[nodiscard]] const MonsterStats stats(const MapPos_t & t_mapPos) const;

        // returns true if killed
        bool damage(const MapPos_t & t_mapPos, const int t_damage);

        // returns true if any were removed
        bool removeDead(const Context & t_context);

      private:
        std::vector<Monster> m_monsters;
    };

} // namespace castlecrawl

#endif // MONSTER_MANAGER_HPP_INCLUDED