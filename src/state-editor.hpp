#ifndef CASTLECRAWL2_STATEEDITOR_HPP_INCLUDED
#define CASTLECRAWL2_STATEEDITOR_HPP_INCLUDED
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

namespace castlecrawl2
{
    struct Context;

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
        const std::string mapCharToName(const char ch) noexcept;

      private:
        MapChars_t m_mapChars;
        MapPos_t m_editPos;
        Floor m_floor;
        sf::RectangleShape m_editRectangle;
        sf::RectangleShape m_borderRectangle;
        sf::Text m_keyText;
        sf::Text m_fadeText;
        Mouseover m_mouseover;
    };

} // namespace castlecrawl2

#endif // CASTLECRAWL2_STATEEDITOR_HPP_INCLUDED
