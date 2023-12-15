// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// main.cpp
//
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>

#include "check-macros.hpp"
#include "game-config.hpp"
#include "loop-coordinator.hpp"

int main(const int argc, const char * const argv[])
{
    try
    {
        using namespace castlecrawl;

        GameConfig config;

        if (argc > 1)
        {
            config.media_path = std::filesystem::current_path() / std::filesystem::path{ argv[1] };
        }
        else
        {
            config.media_path = std::filesystem::current_path() / "media";
        }

        config.media_path = std::filesystem::canonical(config.media_path);

        M_CHECK(
            std::filesystem::exists(config.media_path),
            "Error:  The media path does not exist:"
                << config.media_path
                << "\nPut the media path on the command line or put the 'media' folder here.");

        std::cout << "Using media folder: " << config.media_path.string() << std::endl;

        config.video_mode = sf::VideoMode::getDesktopMode();

        config.video_mode.width  = 1920;
        config.video_mode.height = 1200;

        // sometimes the bpp is detected as zero and I don't know why but this forces a valid value
        if (0 == config.video_mode.bitsPerPixel)
        {
            config.video_mode.bitsPerPixel = 32;
        }

        LoopCoordinator coordinator(config);
        coordinator.playGame();
    }
    catch (const std::exception & ex)
    {
        std::cout << "Standard Exception Error: " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown Exception Error" << std::endl;
    }

    return EXIT_SUCCESS;
}
