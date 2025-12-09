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
        const sf::Color map_background_color   = sf::Color(16, 16, 16);
        const sf::Color stage_background_color = sf::Color(0, 0, 0, 200);
        const sf::Color error_message_color    = sf::Color(200, 100, 100);
        const float music_volume               = 40.0f;
        const unsigned int framerate_limit     = 0;
        const float top_panel_height_ratio     = 0.1f;

        const float turn_delay_after_player_misc      = 0.25f;
        const float turn_delay_after_player_move      = 0.0f;
        const float turn_delay_after_player_attack    = 1.5f;
        const float turn_delay_after_nonplayer_move   = 0.0f;
        const float turn_delay_after_nonplayer_attack = 1.5f;

        const sf::Color message_color_attack_kill = sf::Color(255, 32, 32);
        const sf::Color message_color_attack_miss = sf::Color(255, 200, 100);
        const sf::Color message_color_attack_hit  = sf::Color(255, 200, 200);
        const sf::Color message_color_cast_spell  = sf::Color(220, 100, 220);
        const sf::Color message_color_coins       = sf::Color(255, 200, 100);
        const sf::Color message_color_poison      = sf::Color(100, 255, 100);
        const sf::Color message_color_item        = sf::Color(160, 82, 45);
        const sf::Color message_color_popup       = sf::Color(220, 220, 220);

        const sf::Color state_color_title       = sf::Color::White;
        const sf::Color state_color_subtitle    = sf::Color(180, 160, 120);
        const sf::Color state_color_instruction = sf::Color(170, 170, 200);

        const sf::Color spell_color_fire   = sf::Color(255, 192, 192);
        const sf::Color spell_color_ice    = sf::Color(192, 192, 255);
        const sf::Color spell_color_energy = sf::Color(192, 240, 240);
        const sf::Color spell_color_grip   = sf::Color(225, 175, 130);
        const sf::Color spell_color_fear   = sf::Color(210, 170, 240);

        const std::size_t turns_per_health_increase = 50;
        const std::size_t turns_per_mana_increase   = 35;

        const int barrel_contains_monster_chance = 12;
        const int coffin_contains_monster_chance = 6;

        const int barrel_is_empty_chance = 8;
        const int coffin_is_empty_chance = 16;

        // DON'T CHANGE UNLESS YOU ALSO CHECK EVERYTHING IN MAPS.CPP
        const sf::Vector2i map_size_max = { 41, 23 };
    };

} // namespace castlecrawl

#endif // GAMECONFIG_INCLUDED
