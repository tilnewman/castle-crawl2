#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED
//
// monster.hpp
//
#include "creature.hpp"

namespace castlecrawl
{
    struct Context;

    class Monster : public Creature
    {
      public:
        Monster(const MapPos_t & t_mapPos, const TileImage t_tileImage);
        virtual ~Monster() override = default;

        // returns true if m_mapPos was changed
        virtual bool takeTurn(const Context & t_context) override;

      private:
    };

} // namespace castlecrawl

#endif // MONSTER_HPP_INCLUDED