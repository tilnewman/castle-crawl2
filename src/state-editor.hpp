#ifndef STATEEDITOR_HPP_INCLUDED
#define STATEEDITOR_HPP_INCLUDED
//
// state-editor.hpp
//
#include "map-types.hpp"
#include "mouseover.hpp"
#include "state.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>

namespace castlecrawl
{
    struct Context;

    //

    struct MapEntry_t
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
        virtual void update(const Context & t_context, const float t_frameTimeSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        void updateHelpText(const Context & t_context);
        void updateFadeText();
        void resetMap(const Context & t_context);
        void placeEditCursor(const Context & t_context);
        void setMapChar(const Context & t_context, const char t_ch);
        void editMap(const Context & t_context, const char t_upper, const char t_lower);
        void fadeText(const Context & t_context, const std::string & t_text);
        void save() const;
        void load(const Context & t_context);
        [[nodiscard]] const std::string mapCharToName(const char t_ch) noexcept;

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
        Mouseover m_mouseover;
        bool m_isDragging;
        sf::Vector2f m_dragPosStart;
        sf::Vector2f m_dragPosStop;
        sf::RectangleShape m_dragRectangle;
        std::vector<MapEntry_t> m_dragSelectedEntrys;
    };

} // namespace castlecrawl

#endif // STATEEDITOR_HPP_INCLUDED
