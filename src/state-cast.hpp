#ifndef STATE_CAST_HPP_INCLUDED
#define STATE_CAST_HPP_INCLUDED
//
// state-cast.hpp
//
#include "direction-select-display.hpp"
#include "spells.hpp"
#include "state.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>

namespace castlecrawl
{
    struct Context;

    //

    struct SpellCategoryRectangle
    {
        SpellCategoryRectangle(
            const Context & t_context,
            const sf::Texture & t_texture,
            const SpellCategory t_category,
            const std::string & t_spellName1,
            const std::string & t_spellName2,
            const std::string & t_spellName3,
            const sf::Color & t_color,
            const sf::Vector2f & t_position);

        void setFocus(const Context & t_context, const bool t_hasFocus);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

        SpellCategory category;
        sf::Sprite sprite;
        sf::Text title_text;
        sf::Text spell_text1;
        sf::Text spell_text2;
        sf::Text spell_text3;
        sf::FloatRect spell_rect1;
        sf::FloatRect spell_rect2;
        sf::FloatRect spell_rect3;
        sf::FloatRect full_rect;
        std::size_t spell_index;
        sf::Color color;
        bool has_focus;
    };

    //

    class StateCast : public StateBase
    {
      public:
        StateCast();
        virtual ~StateCast() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::Cast; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        void handleKeystrokesBeforeSpellSelection(
            const Context & t_context, const sf::Event::KeyPressed & t_key);

        void handleKeystrokesAfterSpellSelection(
            const Context & t_context, const sf::Event::KeyPressed & t_key);

        void castSpell(const Context & t_context, const MapPos_t & t_mapPos, const Spell t_spell);

        [[nodiscard]] Spell selectedSpell(const Context & t_context);

        void showErrorMessage(const Context & t_context, const std::string & t_message);

        void updateDescription(const Context & t_context);

        std::unique_ptr<SpellCategoryRectangle> & focusedCategory(const Context & t_context);

      private:
        sf::RectangleShape m_bgFadeRectangle;
        sf::Text m_titleText;
        std::unique_ptr<SpellCategoryRectangle> m_fireRectangleUPtr;
        std::unique_ptr<SpellCategoryRectangle> m_iceRectangleUPtr;
        std::unique_ptr<SpellCategoryRectangle> m_energyRectangleUPtr;
        std::unique_ptr<SpellCategoryRectangle> m_gripRectangleUPtr;
        std::unique_ptr<SpellCategoryRectangle> m_fearRectangleUPtr;
        sf::Texture m_fireTexture;
        sf::Texture m_iceTexture;
        sf::Texture m_energyTexture;
        sf::Texture m_gripTexture;
        sf::Texture m_fearTexture;
        bool m_hasSpellBeenSelected;
        DirectionSelectDisplay m_directionSelectDisplay;
        sf::Text m_errorText;
        float m_errorTimerSec;
        sf::Text m_descriptionText;
        sf::Text m_instructionText;
        sf::Sprite m_categroyAnimSprite;
        bool m_isAnimatingCategorySelection;
        float m_gategoryAnimTimerSec;

        static inline Spell m_prevCastSpell{ Spell::Spark };
    };

} // namespace castlecrawl

#endif // STATE_CAST_HPP_INCLUDED