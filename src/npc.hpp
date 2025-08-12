#ifndef NPC_HPP_INCLUDED
#define NPC_HPP_INCLUDED
//
// npc.hpp
//
#include "creature.hpp"

namespace castlecrawl
{
    struct Context;

    class Npc : public Creature
    {
      public:
        Npc(const MapPos_t & t_mapPos, const TileImage t_tileImage);
        virtual ~Npc() override = default;

        // returns true if m_mapPos was changed
        virtual CreatureAction takeTurn(const Context & t_context) override;
    };

} // namespace castlecrawl

#endif // NPC_HPP_INCLUDED