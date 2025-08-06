#ifndef NPC_MANAGER_HPP_INCLUDED
#define NPC_MANAGER_HPP_INCLUDED
//
// npc-manager.hpp
//
#include "map-types.hpp"
#include "npc.hpp"
#include "tile-image-enum.hpp"

#include <vector>

namespace castlecrawl
{
    struct Context;

    class NpcManager
    {
      public:
        NpcManager();

        void add(const Context & t_context, const MapPos_t & t_mapPos, const char t_mapChar);
        inline void reset() { m_npcs.clear(); }
        
        // returns true if any monsters change map position
        bool takeTurns(const Context & t_context);

      private:
        std::vector<Npc>::iterator findFromMapPos(const MapPos_t & t_mapPos);

      private:
        std::vector<Npc> m_npcs;
    };

} // namespace castlecrawl

#endif // NPC_MANAGER_HPP_INCLUDED