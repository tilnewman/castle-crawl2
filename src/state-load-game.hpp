#ifndef STATE_LOAD_GAME_HPP_INCLUDED
#define STATE_LOAD_GAME_HPP_INCLUDED
//
// state-load-game.hpp
//
#include "json-wrapper.hpp"
#include "map-types.hpp"
#include "maps.hpp"
#include "player.hpp"
#include "state.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <string>
#include <vector>

namespace castlecrawl
{
    struct Context;

    //

    class StateLoadGame : public StateBase
    {
      public:
        StateLoadGame();
        virtual ~StateLoadGame() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::LoadGame; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        void loadGame(const Context & t_context);

      private:
        sf::RectangleShape m_bgFadeRectangle;
        sf::Text m_titleText;
        sf::Text m_subTitleText;
        sf::Text m_errorText;
    };

} // namespace castlecrawl

#endif // STATE_LOAD_GAME_HPP_INCLUDED