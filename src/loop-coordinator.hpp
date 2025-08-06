#ifndef LOOPCOORDINATOR_HPP_INCLUDED
#define LOOPCOORDINATOR_HPP_INCLUDED
//
// loop-coordinator.hpp
//
#include "campfire.hpp"
#include "context.hpp"
#include "dust-particle.hpp"
#include "font.hpp"
#include "framerate-text.hpp"
#include "game-config.hpp"
#include "inferno.hpp"
#include "item-factory.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "music-player.hpp"
#include "npc-manager.hpp"
#include "player-display.hpp"
#include "player.hpp"
#include "random.hpp"
#include "rising-text-anim.hpp"
#include "smoke.hpp"
#include "sound-player.hpp"
#include "sparkle-particle.hpp"
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
        std::unique_ptr<TileImages> m_tileImagesUPtr;
        std::unique_ptr<SplatImages> m_splatImagesUPtr;
        Layout m_layout;
        Maps m_maps;
        std::unique_ptr<MapDisplay> m_mapDisplayUPtr;
        std::unique_ptr<StateManager> m_stateManagerUPtr;
        Player m_player;
        std::unique_ptr<PlayerDisplay> m_playerDisplayUPtr;
        util::Random m_random;
        std::unique_ptr<util::SoundPlayer> m_sfxUPtr;
        std::unique_ptr<util::MusicPlayer> m_musicUPtr;
        std::unique_ptr<FontManager> m_fontsUPtr;
        std::unique_ptr<FramerateText> m_framerateUPtr;
        std::unique_ptr<TopPanel> m_topPanelUPtr;
        item::ItemFactory m_itemFactory;
        std::unique_ptr<DustParticleManager> m_dustParticleManagerUPtr;
        std::unique_ptr<SparkleParticleManager> m_sparkleParticleManagerUPtr;
        std::unique_ptr<CampfireAnimationManager> m_campfireAnimationManagerUPtr;
        std::unique_ptr<SmokeEffectManager> m_smokeEffectManagerUPtr;
        std::unique_ptr<InfernoAnimationManager> m_infernoAnimationManagerUPtr;
        std::unique_ptr<MonsterManager> m_monsterManagerUPtr;
        std::unique_ptr<NpcManager> m_npcManagerUPtr;
        std::unique_ptr<RisingTextAnimationManager> m_risingTextAnimationManagerUPtr;

        std::unique_ptr<Context> m_contextUPtr;
    };

} // namespace castlecrawl

#endif // LOOPCOORDINATOR_INCLUDED
