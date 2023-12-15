#ifndef LOOPCOORDINATOR_HPP_INCLUDED
#define LOOPCOORDINATOR_HPP_INCLUDED
//
// loop-coordinator.hpp
//
#include "context.hpp"
#include "enemy.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "map.hpp"
#include "maps.hpp"
#include "music-player.hpp"
#include "player-display.hpp"
#include "random.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "tile-images.hpp"
#include "top-panel.hpp"

#include <memory>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

namespace castlecrawl
{
    class LoopCoordinator
    {
      public:
        LoopCoordinator(const GameConfig & config);

        void playGame();

      private:
        void setup();
        void teardown();
        void runLoop();
        void handleEvents();
        void handleEvent(const sf::Event & event);
        void draw();
        void update(const float frameTimeSec);
        void setupRenderWindow(sf::VideoMode & videoMode);

      private:
        sf::RenderWindow m_renderWindow;
        sf::RenderStates m_renderStates;

        GameConfig m_config;
        TileImages m_tileImages;
        Layout m_layout;
        Map m_map;
        Maps m_maps;
        MapDisplay m_mapDisplay;
        StateManager m_stateManager;
        PlayerDisplay m_playerDisplay;
        util::Random m_random;
        util::SoundPlayer m_sfx;
        util::MusicPlayer m_music;
        FontManager m_fonts;
        Enemies m_enemies;
        FramerateText m_framerate;
        TopPanel m_topPanel;

        Context m_context;
    };

} // namespace castlecrawl

#endif // LOOPCOORDINATOR_INCLUDED
