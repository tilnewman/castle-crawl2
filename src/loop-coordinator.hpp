#ifndef LOOPCOORDINATOR_HPP_INCLUDED
#define LOOPCOORDINATOR_HPP_INCLUDED
//
// loop-coordinator.hpp
//
#include "context.hpp"
#include "dust-particle.hpp"
#include "enemy.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "item-factory.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "music-player.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "random.hpp"
#include "sound-player.hpp"
#include "splat-images.hpp"
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
        LoopCoordinator(const GameConfig & t_config);

        void playGame();

      private:
        void setup();
        void teardown();
        void runLoop();
        void handleEvents();
        void handleEvent(const sf::Event & t_event);
        void draw();
        void update(const float t_frameTimeSec);
        void setupRenderWindow(sf::VideoMode & t_videoMode);

      private:
        sf::RenderWindow m_renderWindow;
        sf::RenderStates m_renderStates;

        GameConfig m_config;
        TileImages m_tileImages;
        SplatImages m_splatImages;
        Layout m_layout;
        Maps m_maps;
        MapDisplay m_mapDisplay;
        StateManager m_stateManager;
        Player m_player;
        std::unique_ptr<PlayerDisplay> m_playerDisplayUPtr;
        util::Random m_random;
        util::SoundPlayer m_sfx;
        util::MusicPlayer m_music;
        FontManager m_fonts;
        Enemies m_enemies;
        std::unique_ptr<FramerateText> m_framerateUPtr;
        std::unique_ptr<TopPanel> m_topPanelUPtr;
        item::ItemFactory m_itemFactory;
        DustParticleManager m_dustParticleManager;

        std::unique_ptr<Context> m_contextUPtr;
    };

} // namespace castlecrawl

#endif // LOOPCOORDINATOR_INCLUDED
