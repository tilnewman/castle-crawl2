#ifndef STATECREDITS_HPP_INCLUDED
#define STATECREDITS_HPP_INCLUDED
//
// state-credits.hpp
//
#include "state.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>
#include <vector>

namespace castlecrawl
{
    struct Context;

    class Credit : public sf::Drawable
    {
      public:
        Credit(
            const Context & t_context,
            const std::string & t_name,
            const std::string & t_desc,
            const std::string & t_license = "",
            const std::string & t_extra   = "");

        void update(const float t_frameTimeSec);
        void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;
        void vertPosition(const float t_pos);
        [[nodiscard]] float bottom() const;

      private:
        sf::Text m_nameText;
        sf::Text m_descText;
        sf::Text m_licenseText;
        sf::Text m_extraText;
        static const float m_vertPad;
    };

    //

    class StateCredits : public StateBase
    {
      public:
        StateCredits();
        virtual ~StateCredits() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::Credits; }
        virtual void update(const Context & t_context, const float t_frameTimeSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        sf::Texture m_castleTexture;
        sf::Sprite m_castleSprite;
        std::vector<Credit> m_credits;
    };

} // namespace castlecrawl

#endif // STATECREDITS_HPP_INCLUDED
