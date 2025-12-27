#ifndef STATE_SAVEGAME_HPP_INCLUDED
#define STATE_SAVEGAME_HPP_INCLUDED
//
// state-save-game.hpp
//
#include "json-wrapper.hpp"
#include "map-types.hpp"
#include "maps.hpp"
#include "player.hpp"
#include "state.hpp"
#include "statistics.hpp"

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

    struct SavedGamePack
    {
        MapPos_t player_position{ invalidMapPos };
        Player player{};
        Maps maps{};
        Statistics statistics{};
    };

    inline void to_json(nlohmann::json & j, const SavedGamePack & sgp)
    {
        j = nlohmann::json{ { "player_position_x", sgp.player_position.x },
                            { "player_position_y", sgp.player_position.y },
                            { "player", sgp.player },
                            { "maps", sgp.maps },
                            { "statistics", sgp.statistics } };
    }

    inline void from_json(const nlohmann::json & j, SavedGamePack & sgp)
    {
        j.at("player_position_x").get_to(sgp.player_position.x);
        j.at("player_position_y").get_to(sgp.player_position.y);
        j.at("player").get_to(sgp.player);
        j.at("maps").get_to(sgp.maps);
        j.at("statistics").get_to(sgp.statistics);
    }

    //

    class StateSaveGame : public StateBase
    {
      public:
        StateSaveGame();
        virtual ~StateSaveGame() final {}

        virtual void onEnter(const Context & t_context) final;
        [[nodiscard]] virtual State which() const final { return State::SaveGame; }
        virtual void update(const Context & t_context, const float t_elapsedSec) final;

        virtual void draw(
            const Context & t_context,
            sf::RenderTarget & t_target,
            sf::RenderStates t_states) const final;

        virtual void handleEvent(const Context & t_context, const sf::Event & t_event) final;

      private:
        void saveGame(const Context & t_context);

      private:
        sf::RectangleShape m_bgFadeRectangle;
        sf::Text m_titleText;
        sf::Text m_subTitleText;
    };

} // namespace castlecrawl

#endif // STATE_SAVEGAME_HPP_INCLUDED