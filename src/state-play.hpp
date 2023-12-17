#ifndef STATEPLAY_HPP_INCLUDED
#define STATEPLAY_HPP_INCLUDED
//
// state-play.hpp
//
#include "fader.hpp"
#include "gui-stat-bar.hpp"
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

        virtual void onEnter(const Context & context) final;
        virtual State which() const final { return State::Play; }
        virtual void update(const Context & context, const float frameTimeSec) final;

        virtual void draw(
            const Context & context,
            sf::RenderTarget & target,
            sf::RenderStates states) const final;

        virtual void handleEvent(const Context & context, const sf::Event & event) final;

      private:
        void handlePlayerMove(const Context & context, const sf::Keyboard::Key key);

        void playMoveSfx(
            const Context & context, const bool didMove, const char mapCharAttempted) const;

        void playMoveMusic(const Context & context) const;
        bool handleMapTransition(const Context & context, const MapPos_t & mapPosAfter);

      private:
        Mouseover m_mouseover;
        Fader m_fader;
        float m_mapFadeDurationSec;
        MapTransition m_transition;
        StatBar m_healthBar;
    };

} // namespace castlecrawl

#endif // STATEPLAY_HPP_INCLUDED
