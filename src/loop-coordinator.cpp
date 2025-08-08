// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// loop-coordinator.cpp
//
#include "loop-coordinator.hpp"

#include "check-macros.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "texture-loader.hpp"

#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include <iostream>

namespace castlecrawl
{

    LoopCoordinator::LoopCoordinator(const GameConfig & t_config)
        : m_renderWindow{}
        , m_renderStates{}
        , m_config{ t_config }
        , m_tileImagesUPtr{}
        , m_splatImagesUPtr{}
        , m_layoutUPtr{}
        , m_mapsUPtr{}
        , m_mapDisplayUPtr{}
        , m_stateManagerUPtr{}
        , m_playerUPtr{}
        , m_playerDisplayUPtr{}
        , m_randomUPtr{}
        , m_sfxUPtr{}
        , m_musicUPtr{}
        , m_fontsUPtr{}
        , m_framerateUPtr{}
        , m_topPanelUPtr{}
        , m_itemFactoryUPtr{}
        , m_monsterManagerUPtr{}
        , m_npcManagerUPtr{}
        , m_animationManagerUPtr{}
        , m_monsterStatsDatabaseUPtr{}
        , m_contextUPtr{}
    {}

    void LoopCoordinator::playGame()
    {
        setup();
        runLoop();
        teardown();
    }

    void LoopCoordinator::setup()
    {
        M_CHECK(
            sf::VertexBuffer::isAvailable(),
            "sf::VertexBuffers are required but not supported by this video driver.");

        setupRenderWindow(m_config.video_mode);

        util::SfmlDefaults::instance().setup();

        m_randomUPtr = std::make_unique<util::Random>();

        m_sfxUPtr = std::make_unique<util::SoundPlayer>(*m_randomUPtr);
        m_sfxUPtr->setMediaPath((m_config.media_path / "sfx").string());
        m_sfxUPtr->loadAll();

        // this order is NOT critical
        m_layoutUPtr         = std::make_unique<Layout>();
        m_mapsUPtr           = std::make_unique<Maps>();
        m_playerUPtr         = std::make_unique<Player>();
        m_mapDisplayUPtr     = std::make_unique<MapDisplay>();
        m_stateManagerUPtr   = std::make_unique<StateManager>();
        m_fontsUPtr          = std::make_unique<FontManager>();
        m_tileImagesUPtr     = std::make_unique<TileImages>();
        m_splatImagesUPtr    = std::make_unique<SplatImages>();
        m_playerDisplayUPtr  = std::make_unique<PlayerDisplay>();
        m_musicUPtr          = std::make_unique<util::MusicPlayer>();
        m_framerateUPtr      = std::make_unique<FramerateText>();
        m_topPanelUPtr       = std::make_unique<TopPanel>();
        m_itemFactoryUPtr    = std::make_unique<item::ItemFactory>();
        m_monsterManagerUPtr = std::make_unique<MonsterManager>();
        m_npcManagerUPtr     = std::make_unique<NpcManager>();

        m_monsterStatsDatabaseUPtr = std::make_unique<MonsterStatsDatabase>();

        m_animationManagerUPtr = std::make_unique<AnimationManager>(
            *m_randomUPtr, (m_config.media_path / "image" / "animation").string());

        m_contextUPtr = std::make_unique<Context>(
            m_config,
            *m_tileImagesUPtr,
            *m_splatImagesUPtr,
            *m_layoutUPtr,
            *m_mapsUPtr,
            *m_mapDisplayUPtr,
            *m_stateManagerUPtr,
            *m_playerUPtr,
            *m_playerDisplayUPtr,
            *m_randomUPtr,
            *m_sfxUPtr,
            *m_musicUPtr,
            *m_fontsUPtr,
            *m_framerateUPtr,
            *m_topPanelUPtr,
            *m_itemFactoryUPtr,
            *m_monsterManagerUPtr,
            *m_npcManagerUPtr,
            *m_animationManagerUPtr,
            *m_monsterStatsDatabaseUPtr);

        // this order IS critical
        m_itemFactoryUPtr->setup();
        m_monsterStatsDatabaseUPtr->setup();
        m_fontsUPtr->setup(m_config);
        m_tileImagesUPtr->setup(m_config);
        m_splatImagesUPtr->setup(m_config);
        m_animationManagerUPtr->setup(m_config);
        m_layoutUPtr->setup(m_config);
        m_mapsUPtr->setup(*m_contextUPtr);
        m_mapsUPtr->change(*m_contextUPtr, MapName::Level_1_Cell, { 3, 2 });
        m_playerDisplayUPtr->setup(*m_contextUPtr);
        m_framerateUPtr->setup(*m_contextUPtr);
        m_topPanelUPtr->setup(*m_contextUPtr);

        m_stateManagerUPtr->change(*m_contextUPtr, State::Splash);

        m_musicUPtr->setup((m_config.media_path / "music").string());
        m_musicUPtr->start("music.ogg", m_config.music_volume);

        // m_itemFactoryUPtr->dumpInfo(m_fonts.font());
        m_monsterStatsDatabaseUPtr->dumpInfo();
    }

    void LoopCoordinator::teardown()
    {
        util::SfmlDefaults::instance().teardown();

        m_contextUPtr.reset();

        // this order is NOT critical
        m_layoutUPtr.reset();
        m_mapsUPtr.reset();
        m_playerUPtr.reset();
        m_mapDisplayUPtr.reset();
        m_stateManagerUPtr.reset();
        m_playerDisplayUPtr.reset();
        m_fontsUPtr.reset();
        m_framerateUPtr.reset();
        m_topPanelUPtr.reset();
        m_tileImagesUPtr.reset();
        m_splatImagesUPtr.reset();
        m_itemFactoryUPtr.reset();
        m_monsterManagerUPtr.reset();
        m_npcManagerUPtr.reset();
        m_animationManagerUPtr.reset();
        m_monsterStatsDatabaseUPtr.reset();

        m_sfxUPtr->stopAll();
        m_sfxUPtr.reset();

        // this reset() must occur AFTER m_sfxUPtr.reset() and m_animationManagerUPtr.reset()
        m_randomUPtr.reset();

        m_musicUPtr->stopAll();
        m_musicUPtr.reset();

        m_renderWindow.close();

        util::TextureLoader::dumpInfo();
    }

    void LoopCoordinator::runLoop()
    {
        sf::Clock frameClock;
        while (m_renderWindow.isOpen() && (m_contextUPtr->state.current().which() != State::Quit))
        {
            handleEvents();
            update(frameClock.restart().asSeconds());
            draw();
        }
    }

    void LoopCoordinator::handleEvents()
    {
        while (const auto eventOpt = m_renderWindow.pollEvent())
        {
            handleEvent(eventOpt.value());
        }
    }

    void LoopCoordinator::handleEvent(const sf::Event & t_event)
    {
        if (t_event.is<sf::Event::Closed>())
        {
            m_stateManagerUPtr->change(*m_contextUPtr, State::Quit);
        }
        else
        {
            m_stateManagerUPtr->current().handleEvent(*m_contextUPtr, t_event);
        }
    }

    void LoopCoordinator::draw()
    {
        m_renderWindow.clear(m_config.background_color);
        m_stateManagerUPtr->current().draw(*m_contextUPtr, m_renderWindow, m_renderStates);
        m_renderWindow.display();
    }

    void LoopCoordinator::update(const float t_frameTimeSec)
    {
        m_stateManagerUPtr->current().update(*m_contextUPtr, t_frameTimeSec);
    }

    void LoopCoordinator::setupRenderWindow(sf::VideoMode & t_videoMode)
    {
        std::cout << "Attempting video mode " << t_videoMode << "...";

        if (!m_config.video_mode.isValid())
        {
            std::cout << "but that is not suported.  Valid video modes at "
                      << sf::VideoMode::getDesktopMode().bitsPerPixel << "bpp:" << std::endl
                      << util::makeSupportedVideoModesString(true) << std::endl;

            t_videoMode = util::findVideoModeClosestTo(t_videoMode);
            setupRenderWindow(t_videoMode);
            return;
        }

        m_renderWindow.create(t_videoMode, "CastleCrawl2", sf::State::Fullscreen);

        // sometimes the resolution of the window created does not match what was specified
        const unsigned actualWidth  = m_renderWindow.getSize().x;
        const unsigned actualHeight = m_renderWindow.getSize().y;
        if ((m_config.video_mode.size.x == actualWidth) &&
            (m_config.video_mode.size.y == actualHeight))
        {
            std::cout << "Success." << std::endl;
        }
        else
        {
            std::cout << "Failed" << ".  ";

            m_config.video_mode.size.x = actualWidth;
            m_config.video_mode.size.y = actualHeight;

            std::cout << "Using " << m_config.video_mode << " instead." << std::endl;
        }

        if (m_config.framerate_limit > 0)
        {
            m_renderWindow.setFramerateLimit(m_config.framerate_limit);
        }
    }

} // namespace castlecrawl
