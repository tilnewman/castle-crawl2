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
        , m_tileImages{}
        , m_splatImages{}
        , m_layout{}
        , m_maps{}
        , m_mapDisplay{}
        , m_stateManager{}
        , m_player{}
        , m_playerDisplayUPtr{}
        , m_random{}
        , m_sfx{ m_random }
        , m_music{}
        , m_fonts{}
        , m_enemies{}
        , m_framerateUPtr{}
        , m_topPanelUPtr{}
        , m_itemFactory{}
        , m_dustParticleManager{}
        , m_sparkleParticleManager{}
        , m_campfireAnimationManager{}
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

        m_sfx.setMediaPath((m_config.media_path / "sfx").string());
        m_sfx.loadAll();

        m_playerDisplayUPtr = std::make_unique<PlayerDisplay>();
        m_framerateUPtr     = std::make_unique<FramerateText>();
        m_topPanelUPtr      = std::make_unique<TopPanel>();

        m_contextUPtr = std::make_unique<Context>(
            m_config,
            m_tileImages,
            m_splatImages,
            m_layout,
            m_maps,
            m_mapDisplay,
            m_stateManager,
            m_player,
            *m_playerDisplayUPtr,
            m_random,
            m_sfx,
            m_music,
            m_fonts,
            m_enemies,
            *m_framerateUPtr,
            *m_topPanelUPtr,
            m_itemFactory,
            m_dustParticleManager,
            m_sparkleParticleManager,
            m_campfireAnimationManager);

        m_itemFactory.setup();

        m_fonts.setup(m_config);
        m_enemies.setup(m_config);
        m_tileImages.setup(m_config);
        m_splatImages.setup(m_config);
        m_dustParticleManager.setup(m_config);
        m_sparkleParticleManager.setup(m_config);
        m_campfireAnimationManager.setup(m_config);
        m_layout.setup(m_config);
        m_maps.setup(*m_contextUPtr);
        m_maps.change(*m_contextUPtr, MapName::Level_1_Cell, { 3, 2 });
        m_playerDisplayUPtr->setup(*m_contextUPtr);
        m_framerateUPtr->setup(*m_contextUPtr);
        m_topPanelUPtr->setup(*m_contextUPtr);

        // m_itemFactory.dumpInfo(m_fonts.font());

        m_stateManager.change(*m_contextUPtr, State::Splash);

        m_music.setup((m_config.media_path / "music").string());
        m_music.start("music.ogg", m_config.music_volume);
    }

    void LoopCoordinator::teardown()
    {
        util::SfmlDefaults::instance().teardown();
        m_sfx.stopAll();
        m_music.stopAll();
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
            m_stateManager.change(*m_contextUPtr, State::Quit);
        }
        else
        {
            m_stateManager.current().handleEvent(*m_contextUPtr, t_event);
        }
    }

    void LoopCoordinator::draw()
    {
        m_renderWindow.clear(m_config.background_color);
        m_stateManager.current().draw(*m_contextUPtr, m_renderWindow, m_renderStates);
        m_renderWindow.display();
    }

    void LoopCoordinator::update(const float t_frameTimeSec)
    {
        m_stateManager.current().update(*m_contextUPtr, t_frameTimeSec);
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
