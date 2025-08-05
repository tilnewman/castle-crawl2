#ifndef MONSTER_HPP_INCLUDED
#define MONSTER_HPP_INCLUDED
//
// monster.hpp
//
#include "map-types.hpp"
#include "tile-image-enum.hpp"

namespace castlecrawl
{
    struct Context;

    class Monster
    {
      public:
        Monster(const MapPos_t & t_mapPos, const TileImage t_tileImage);

        [[nodiscard]] inline const MapPos_t mapPosition() const noexcept { return m_mapPos; }
        [[nodiscard]] inline TileImage tileImage() const noexcept { return m_tileImage; }
        [[nodiscard]] bool isUndead() const;

        // returns true if m_mapPos was changed
        bool takeTurn(const Context & t_context);

      private:
        [[nodiscard]] bool isPlayerAdjacent(const Context & t_context) const;
        
        // returns true if actually moved (might not if not possible)
        bool moveToward(const Context & t_context, const MapPos_t & t_targetMapPos);
        
        void moveTo(const Context & t_context, const MapPos_t & t_newMapPos);

      private:
        MapPos_t m_mapPos;
        TileImage m_tileImage;
    };

} // namespace castlecrawl

#endif // MONSTER_HPP_INCLUDED