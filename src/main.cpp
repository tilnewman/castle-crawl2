// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// main.cpp
//
#include <cstdlib>
#include <exception>
#include <iostream>

#include "game-config.hpp"
#include "loop-coordinator.hpp"

int main(void)
{
    try
    {
        using namespace castlecrawl2;

        GameConfig config;
        config.media_path = std::filesystem::current_path() / "media";
        config.video_mode = sf::VideoMode::getDesktopMode();

        // TODO remove after testing
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
