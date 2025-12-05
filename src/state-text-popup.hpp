#ifndef STATE_TEXT_POPUP_HPP_INCLUDED
#define STATE_TEXT_POPUP_HPP_INCLUDED
//
// state-text-popup.hpp
//
#include "map-types.hpp"
#include "state.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <string>

namespace castlecrawl
{
    struct Context;

    //

    struct TextPopupInfo
    {
        TextPopupInfo()
            : message{ "" }
            , map_pos{ -1, -1 } // both must be negative to be invalid
            , will_advance_turn{ false }
        {}

        TextPopupInfo(
            const std::string & t_message, const MapPos_t & t_mapPos, const bool t_willAdanceTurn)
            : message{ t_message }
            , map_pos{ t_mapPos }
            , will_advance_turn{ t_willAdanceTurn }
        {}

        std::string message;
        MapPos_t map_pos;
        bool will_advance_turn;
    };

    //

    class StateTextPopup : public StateBase
    {
      public:
        StateTextPopup();
        virtual ~StateTextPopup() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::TextPopup; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

        static void setInfo(const TextPopupInfo & t_info) { m_info = t_info; }

      private:
        static inline TextPopupInfo m_info{};

        sf::RectangleShape m_backgroundRectangle;
        sf::Text m_messageText;
    };

} // namespace castlecrawl

#endif // STATE_TEXT_POPUP_HPP_INCLUDED
