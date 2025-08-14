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
        sf::VideoMode video_mode;
        std::filesystem::path media_path;

        const sf::Color background_color       = sf::Color::Black;
        const sf::Color stage_background_color = sf::Color(0, 0, 0, 200);
        const float music_volume               = 40.0f;
        const unsigned int framerate_limit     = 0;
        const float top_panel_height_ratio     = 0.1f;

        const float turn_delay_after_player_misc      = 0.25f;
        const float turn_delay_after_player_move      = 0.0f;
        const float turn_delay_after_player_attack    = 1.5f;
        const float turn_delay_after_nonplayer_move   = 0.0f;
        const float turn_delay_after_nonplayer_attack = 1.5f;

        const sf::Color message_color_attack_miss = sf::Color(255, 200, 100);
        const sf::Color message_color_attack_hit  = sf::Color(255, 200, 200);
        const sf::Color message_color_cast_spell  = sf::Color(220, 100, 220);
        const sf::Color message_color_coins       = sf::Color(255, 200, 100);
        const sf::Color message_color_poison      = sf::Color(100, 255, 100);
        const sf::Color message_color_item        = sf::Color(160, 82, 45);

        const std::size_t turns_per_health_increase = 36;
        const std::size_t turns_per_mana_increase   = 12;

        // DON'T CHANGE UNLESS YOU ALSO CHANGE ALL MAPS IN THE GAME
        const sf::Vector2i map_size_max = { 41, 23 };
    };

} // namespace castlecrawl

#endif // GAMECONFIG_INCLUDED
