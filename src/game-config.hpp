#ifndef CASTLECRAWL2_GAMECONFIG_HPP_INCLUDED
#define CASTLECRAWL2_GAMECONFIG_HPP_INCLUDED
//
// game-config.hpp
//
#include <filesystem>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace castlecrawl2
{

    struct GameConfig
    {
        std::filesystem::path media_path;
        sf::VideoMode video_mode;
        sf::Color background_color   = sf::Color::Black; // sf::Color(16, 16, 16);
        float music_volume           = 40.0f;
        unsigned int framerate_limit = 0;
        float top_panel_height_ratio = 0.1f;

        // DON'T CHANGE UNLESS YOU ALSO CHECK ALL MAPS IN THE GAME
        sf::Vector2i map_size_max = { 41, 23 };
    };

} // namespace castlecrawl2

#endif // CASTLECRAWL2_GAMECONFIG_INCLUDED
