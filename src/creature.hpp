#ifndef CREATURE_HPP_INCLUDED
#define CREATURE_HPP_INCLUDED
//
// creature.hpp
//
#include "map-types.hpp"
#include "tile-image-enum.hpp"

namespace castlecrawl
{
    struct Context;

    // base class for NPCs and Monsters
    class Creature
    {
      public:
        Creature(const MapPos_t & t_mapPos, const TileImage t_tileImage);
        virtual ~Creature() = default;

        [[nodiscard]] inline const MapPos_t mapPosition() const noexcept { return m_mapPos; }
        [[nodiscard]] inline TileImage tileImage() const noexcept { return m_tileImage; }

        // returns true if m_mapPos was changed
        virtual bool takeTurn(const Context & t_context) = 0;

      protected:
        [[nodiscard]] bool isPlayerAdjacent(const Context & t_context) const;
        
        // returns true if actually moved (might not if not possible)
        bool moveToward(const Context & t_context, const MapPos_t & t_targetMapPos);
        
        void moveTo(const Context & t_context, const MapPos_t & t_newMapPos);

      private:
        MapPos_t m_mapPos;
        TileImage m_tileImage;
    };

} // namespace castlecrawl

#endif // CREATURE_HPP_INCLUDED