#ifndef GAMECONFIG_HPP_INCLUDED
#define GAMECONFIG_HPP_INCLUDED
//
// game-config.hpp
//
#include <filesystem>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace castlecrawl
{

    struct GameConfig
    {
        std::filesystem::path media_path;
        sf::VideoMode video_mode;
        sf::Color background_color   = sf::Color::Black;
        float music_volume           = 40.0f;
        unsigned int framerate_limit = 0;
        float top_panel_height_ratio = 0.1f;

        float turn_delay_after_player_misc      = 0.25f;
        float turn_delay_after_player_move      = 0.0f;
        float turn_delay_after_player_attack    = 1.5f;
        float turn_delay_after_nonplayer_move   = 0.0f;
        float turn_delay_after_nonplayer_attack = 1.5f;

        sf::Color message_color_attack_miss = sf::Color(255, 200, 100);
        sf::Color message_color_attack_hit  = sf::Color(255, 200, 200);
        sf::Color message_color_cast_spell  = sf::Color(220, 100, 220);
        sf::Color message_color_coins       = sf::Color(255, 200, 100);
        sf::Color message_color_poison      = sf::Color(100, 255, 100);
        sf::Color message_color_item        = sf::Color(160, 82, 45);

        // DON'T CHANGE UNLESS YOU ALSO CHANGE ALL MAPS IN THE GAME
        sf::Vector2i map_size_max = { 41, 23 };
    };

} // namespace castlecrawl

#endif // GAMECONFIG_INCLUDED
