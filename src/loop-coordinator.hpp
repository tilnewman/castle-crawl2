#ifndef LOOPCOORDINATOR_HPP_INCLUDED
#define LOOPCOORDINATOR_HPP_INCLUDED
//
// loop-coordinator.hpp
//
#include "animation-manager.hpp"
#include "context.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "item-factory.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "monster-stats-database.hpp"
#include "music-player.hpp"
#include "npc-manager.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "random.hpp"
#include "sound-player.hpp"
#include "splat-images.hpp"
#include "state-manager.hpp"
#include "tile-images.hpp"
#include "top-panel.hpp"
#include "turn-keeper.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <memory>

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
        void update(const float t_elapsedSec);
        void setupRenderWindow(sf::VideoMode & t_videoMode);

      private:
        sf::RenderWindow m_renderWindow;
        sf::RenderStates m_renderStates;

        GameConfig m_config;

        // okay, look.
        // These are all pointers because that way I can better control
        // the order they are created/destroyed in setup() and teardown().
        // Also it keeps this class from being too big for the stack.
        std::unique_ptr<TileImages> m_tileImagesUPtr;
        std::unique_ptr<SplatImages> m_splatImagesUPtr;
        std::unique_ptr<Layout> m_layoutUPtr;
        std::unique_ptr<Maps> m_mapsUPtr;
        std::unique_ptr<MapDisplay> m_mapDisplayUPtr;
        std::unique_ptr<StateManager> m_stateManagerUPtr;
        std::unique_ptr<Player> m_playerUPtr;
        std::unique_ptr<PlayerDisplay> m_playerDisplayUPtr;
        std::unique_ptr<util::Random> m_randomUPtr;
        std::unique_ptr<util::SoundPlayer> m_sfxUPtr;
        std::unique_ptr<util::MusicPlayer> m_musicUPtr;
        std::unique_ptr<FontManager> m_fontsUPtr;
        std::unique_ptr<FramerateText> m_framerateUPtr;
        std::unique_ptr<TopPanel> m_topPanelUPtr;
        std::unique_ptr<item::ItemFactory> m_itemFactoryUPtr;
        std::unique_ptr<MonsterManager> m_monsterManagerUPtr;
        std::unique_ptr<NpcManager> m_npcManagerUPtr;
        std::unique_ptr<AnimationManager> m_animationManagerUPtr;
        std::unique_ptr<MonsterStatsDatabase> m_monsterStatsDatabaseUPtr;
        std::unique_ptr<TurnKeeper> m_turnKeeperUPtr;

        std::unique_ptr<Context> m_contextUPtr;
    };

} // namespace castlecrawl

#endif // LOOPCOORDINATOR_INCLUDED
