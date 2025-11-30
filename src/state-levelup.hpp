#ifndef STATE_LEVELUP_HPP_INCLUDED
#define STATE_LEVELUP_HPP_INCLUDED
//
// state-levelup.hpp
//
#include "stat.hpp"
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

    class StatAwardBlock
    {
      public:
        StatAwardBlock(
            const Context & t_context, const std::string & t_name, const sf::FloatRect & t_rect);

        // returns true on success
        bool addPoint(const Context & t_context);
        bool removePoint(const Context & t_context);

        void select(const bool t_isSelected);

        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const;

      private:
        Stat & stat(const Context & t_context) const;

      public:
        const static int m_perStatAwardPointMax = 5;

      private:
        sf::FloatRect m_rect;
        sf::RectangleShape m_rectangle;
        std::string m_name;
        sf::Text m_nameText;
        sf::Text m_valueText;
        int m_awardedPoints;
        bool m_isSelected;
    };

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

        void updateDescriptionText(const Context & t_context);

      private:
        sf::RectangleShape m_bgFadeRectangle;
        sf::Text m_titleText;
        sf::Text m_subTitleText;
        sf::Text m_healthText;
        sf::Text m_manaText;
        sf::Text m_instructionText1;
        sf::Text m_instructionText2;
        sf::Text m_errorText;
        float m_errorTimerSec;
        int m_statPointsAwarded;
        const int m_statPointsAwardedMax;
        std::vector<StatAwardBlock> m_statBlocks;
        std::size_t m_selectionIndex;
    };

} // namespace castlecrawl

#endif // STATE_LEVELUP_HPP_INCLUDED