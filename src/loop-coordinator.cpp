// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// loop-coordinator.cpp
//
#include "loop-coordinator.hpp"

#include "check-macros.hpp"
#include "sfml-util.hpp"

#include <SFML/Graphics/VertexBuffer.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include <iostream>

namespace castlecrawl
{

    LoopCoordinator::LoopCoordinator(const GameConfig & config)
        : m_renderWindow{}
        , m_renderStates{}
        , m_config{ config }
        , m_tileImages{}
        , m_layout{}
        , m_maps{}
        , m_mapDisplay{}
        , m_stateManager{}
        , m_player{}
        , m_playerDisplay{}
        , m_random{}
        , m_sfx{ m_random }
        , m_music{}
        , m_fonts{}
        , m_enemies{}
        , m_framerate{}
        , m_topPanel{}
        , m_itemFactory{}
        , m_context{ m_config,     m_tileImages,   m_layout,   m_maps,
                     m_mapDisplay, m_stateManager, m_player,   m_playerDisplay,
                     m_random,     m_sfx,          m_music,    m_fonts,
                     m_enemies,    m_framerate,    m_topPanel, m_itemFactory }
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

        m_sfx.setMediaPath((m_config.media_path / "sfx").string());
        m_sfx.loadAll();

        m_itemFactory.setup();

        m_fonts.setup(m_config);
        m_enemies.setup(m_config);
        m_tileImages.setup(m_config);
        m_layout.setup(m_config);
        m_maps.setup(m_context);
        m_maps.change(m_context, MapName::Level_1_Cell, { 3, 2 });
        m_playerDisplay.setup(m_context);
        m_framerate.setup(m_context);
        m_topPanel.setup(m_context);

        // m_itemFactory.dumpInfo(m_fonts.font());

        m_stateManager.change(m_context, State::Splash);

        m_music.setup((m_config.media_path / "music").string());
        m_music.start("music.ogg", m_config.music_volume);
    }

    void LoopCoordinator::teardown()
    {
        m_sfx.stopAll();
        m_music.stopAll();
        m_renderWindow.close();
    }

    void LoopCoordinator::runLoop()
    {
        sf::Clock frameClock;
        while (m_renderWindow.isOpen() && (m_context.state.current().which() != State::Quit))
        {
            handleEvents();
            update(frameClock.restart().asSeconds());
            draw();
        }
    }

    void LoopCoordinator::handleEvents()
    {
        sf::Event event;
        while (m_renderWindow.pollEvent(event))
        {
            handleEvent(event);
        }
    }

    void LoopCoordinator::handleEvent(const sf::Event & t_event)
    {
        if (t_event.type == sf::Event::Closed)
        {
            m_stateManager.change(m_context, State::Quit);
        }
        else
        {
            m_stateManager.current().handleEvent(m_context, t_event);
        }
    }

    void LoopCoordinator::draw()
    {
        m_renderWindow.clear(m_config.background_color);
        m_stateManager.current().draw(m_context, m_renderWindow, m_renderStates);
        m_renderWindow.display();
    }

    void LoopCoordinator::update(const float t_frameTimeSec)
    {
        m_stateManager.current().update(m_context, t_frameTimeSec);
    }

    void LoopCoordinator::setupRenderWindow(sf::VideoMode & t_videoMode)
    {
        std::cout << "Attempting video mode " << t_videoMode << "...";

        if (!m_config.video_mode.isValid())
        {
            std::cout << "but that is an invalid mode.  Valid video modes at "
                      << sf::VideoMode::getDesktopMode().bitsPerPixel << "bpp:" << std::endl
                      << util::makeSupportedVideoModesString(true) << std::endl;

            t_videoMode = util::findVideoModeClosestTo(t_videoMode);
            setupRenderWindow(t_videoMode);
            return;
        }

        m_renderWindow.create(t_videoMode, "CastleCrawl2", sf::Style::Fullscreen);

        // sometimes the resolution of the window created does not match what was specified
        const unsigned actualWidth  = m_renderWindow.getSize().x;
        const unsigned actualHeight = m_renderWindow.getSize().y;
        if ((m_config.video_mode.width == actualWidth) &&
            (m_config.video_mode.height == actualHeight))
        {
            std::cout << "Success." << std::endl;
        }
        else
        {
            std::cout << "Failed"
                      << ".  ";

            m_config.video_mode.width  = actualWidth;
            m_config.video_mode.height = actualHeight;

            std::cout << "Using " << m_config.video_mode << " instead." << std::endl;
        }

        if (m_config.framerate_limit > 0)
        {
            m_renderWindow.setFramerateLimit(m_config.framerate_limit);
        }
    }

} // namespace castlecrawl
