#ifndef CASTLECRAWL2_STATESPLASH_HPP_INCLUDED
#define CASTLECRAWL2_STATESPLASH_HPP_INCLUDED
//
// state-splash.hpp
//
#include "fader.hpp"
#include "state.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

namespace castlecrawl2
{
    struct Context;

    class StateSplash : public StateBase
    {
      public:
        StateSplash();
        virtual ~StateSplash() final {}

        virtual State which() const final { return State::Splash; }
        virtual void onEnter(const Context & context) final;
        virtual void update(const Context & context, const float frameTimeSec) final;

        virtual void draw(
            const Context & context,
            sf::RenderTarget & target,
            sf::RenderStates states) const final;

        virtual void handleEvent(const Context & context, const sf::Event & event) final;

      private:
        sf::Texture m_castleTexture;
        sf::Sprite m_castleSprite;
        sf::Texture m_lightningTexture;
        sf::Sprite m_lightningSprite;
        bool m_willShowLightning;
        sf::Clock m_clock;
        float m_timerSec;
        Fader m_fader;
    };

} // namespace castlecrawl2

#endif // CASTLECRAWL2_STATESPLASH_HPP_INCLUDED
