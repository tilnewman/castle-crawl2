#ifndef STATEPLAY_HPP_INCLUDED
#define STATEPLAY_HPP_INCLUDED
//
// state-play.hpp
//
#include "mouseover.hpp"
#include "state.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace castlecrawl
{
    struct Context;

    class StatePlay : public StateBase
    {
      public:
        StatePlay();
        virtual ~StatePlay() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::Play; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        void updateTurn(const Context & t_context);

        [[nodiscard]] bool
            handlePlayerMove(const Context & t_context, const sf::Keyboard::Scancode t_key);

        void playMoveSfx(
            const Context & t_context, const bool t_didMove, const char t_mapCharAttempted) const;

        void playMoveMusic(const Context & t_context) const;
        bool handleMapTransition(const Context & t_context, const MapPos_t & t_mapPosAfter);

      private:
        Mouseover m_mouseover;
        std::size_t m_monsterUniqueId;
    };

} // namespace castlecrawl

#endif // STATEPLAY_HPP_INCLUDED
