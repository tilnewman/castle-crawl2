#ifndef STATE_LEVELUP_HPP_INCLUDED
#define STATE_LEVELUP_HPP_INCLUDED
//
// state-levelup.hpp
//
#include "state.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <memory>
#include <string>

namespace castlecrawl
{
    struct Context;

    //

    class StateLevelUp : public StateBase
    {
      public:
        StateLevelUp();
        virtual ~StateLevelUp() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::LevelUp; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        void showErrorMessage(const Context & t_context, const std::string & t_message);

      private:
        sf::RectangleShape m_bgFadeRectangle;
        sf::Text m_titleText;
        sf::Text m_subTitleText;
        sf::Text m_instructionText;
        sf::Text m_errorText;
        float m_errorTimerSec;
        bool haveAllStatPointsBeenAwarded;
    };

} // namespace castlecrawl

#endif // STATE_LEVELUP_HPP_INCLUDED