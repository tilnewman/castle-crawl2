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

    struct MapEntry_t
    {
        MapPos_t pos;
        sf::FloatRect rect;
    };

    class StateEditor : public StateBase
    {
      public:
        StateEditor();
        virtual ~StateEditor() final {}

        virtual State which() const final { return State::Editor; }
        virtual void onEnter(const Context & context) final;
        virtual void update(const Context & context, const float frameTimeSec) final;

        virtual void draw(
            const Context & context,
            sf::RenderTarget & target,
            sf::RenderStates states) const final;

        virtual void handleEvent(const Context & context, const sf::Event & event) final;

      private:
        void updateHelpText(const Context & context);
        void updateFadeText();
        void resetMap(const Context & context);
        void placeEditCursor(const Context & context);
        void setMapChar(const char ch);
        void editMap(const Context & context, const char upper, const char lower);
        void fadeText(const Context & context, const std::string & text);
        void save() const;
        void load(const Context & context);
        const std::string mapCharToName(const char ch) noexcept;

        void startDragging(const Context & context, const sf::Vector2f & pos);
        void stopDragging(const Context & context, const sf::Vector2f & pos);
        void updateDragging(const Context & context, const sf::Vector2f & pos);
        void updateDragRect();
        void updateDragSelectedMapCells(const Context & context);

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
