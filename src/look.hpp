#ifndef LOOK_HPP_INCLUDED
#define LOOK_HPP_INCLUDED
//
// look.hpp
//
#include "map-types.hpp"

namespace castlecrawl
{
    struct Context;

    //

    class Look
    {
      public:
        Look();

        void look(const Context & t_context, const MapPos_t & t_pos, const bool t_willAdvanceTurn);
    };

} // namespace castlecrawl

#endif // STATE_LOOK_HPP_INCLUDED
