#ifndef STATEEDITOR_HPP_INCLUDED
#define STATEEDITOR_HPP_INCLUDED
//
// state-editor.hpp
//
#include "map-types.hpp"
#include "mouseover.hpp"
#include "state.hpp"
#include "tile-select-button.hpp"

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

    struct MapEntry
    {
        MapPos_t pos;
        sf::FloatRect rect;
    };

    //

    class StateEditor : public StateBase
    {
      public:
        StateEditor();
        virtual ~StateEditor() final {}

        [[nodiscard]] virtual State which() const final { return State::Editor; }
        virtual void onEnter(const Context & t_context) final;
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        [[nodiscard]] bool isMouseOverAnyButton(const sf::Vector2f & t_mousePos) const;
        void updateHelpText(const Context & t_context);
        void updateFadeText(const float t_elapsedSec);
        void resetMap(const Context & t_context);
        void placeEditCursor(const Context & t_context);
        void setMapChar(const Context & t_context, const char t_ch);

        void editMap(
            const Context & t_context, const char t_newMapChar, const std::string & t_fadeText);

        void fadeText(const Context & t_context, const std::string & t_text);
        void save(const Context & t_context) const;
        void load(const Context & t_context);

        void startDragging(const Context & t_context, const sf::Vector2f & t_pos);
        void stopDragging(const Context & t_context, const sf::Vector2f & t_pos);
        void updateDragging(const Context & t_context, const sf::Vector2f & t_pos);
        void updateDragRect();
        void updateDragSelectedMapCells(const Context & t_context);

      private:
        MapChars_t m_mapChars;
        MapPos_t m_editPos;
        Floor m_floor;
        sf::RectangleShape m_editRectangle;
        sf::RectangleShape m_borderRectangle;
        sf::Text m_keyText;
        sf::Text m_fadeText;
        float m_fadeTextTimerSec;
        Mouseover m_mouseover;
        bool m_isDragging;
        sf::Vector2f m_dragPosStart;
        sf::Vector2f m_dragPosStop;
        sf::RectangleShape m_dragRectangle;
        std::vector<MapEntry> m_dragSelectedEntrys;
        TileSelectButton m_miscButton;
        TileSelectButton m_doorwayButton;
        TileSelectButton m_altarButton;
        TileSelectButton m_statueButton;
        TileSelectButton m_columnButton;
        TileSelectButton m_npcButton1;
        TileSelectButton m_npcButton2;
        TileSelectButton m_monsterButton1;
        TileSelectButton m_monsterButton2;
        TileSelectButton m_monsterButton3;
        TileSelectButton m_monsterButton4;
        TileSelectButton m_monsterButton5;
    };

} // namespace castlecrawl

#endif // STATEEDITOR_HPP_INCLUDED
