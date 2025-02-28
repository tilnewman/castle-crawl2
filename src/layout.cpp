// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// layout.hpp
//
#include "layout.hpp"

#include "check-macros.hpp"
#include "sfml-util.hpp"

#include <algorithm>
#include <iostream>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl
{

    Layout::Layout()
        : m_screenRect{ { 0.0f, 0.0f }, { 0.0f, 0.0f } }
        , m_topRect{ { 0.0f, 0.0f }, { 0.0f, 0.0f } }
        , m_botRect{ { 0.0f, 0.0f }, { 0.0f, 0.0f } }
        , m_mapRect{ { 0.0f, 0.0f }, { 0.0f, 0.0f } }
        , m_cellSize{ 0.0f, 0.0f }
        , m_cellCount{ 0, 0 }
    {}

    void Layout::setup(const GameConfig & t_config)
    {
        m_screenRect.size.x = static_cast<float>(t_config.video_mode.size.x);
        m_screenRect.size.y = static_cast<float>(t_config.video_mode.size.y);

        m_topRect        = m_screenRect;
        m_topRect.size.y = std::floor(m_screenRect.size.y * t_config.top_panel_height_ratio);

        m_botRect            = m_screenRect;
        m_botRect.position.y = m_topRect.size.y;
        m_botRect.size.y -= m_botRect.position.y;

        m_cellSize.x = std::min(
            std::floor(m_botRect.size.x / static_cast<float>(t_config.map_size_max.x)),
            std::floor(m_botRect.size.y / static_cast<float>(t_config.map_size_max.y)));

        m_cellSize.y = m_cellSize.x;
    }

    void Layout::setupNewMap(const sf::Vector2i & t_cellCountParam)
    {
        m_cellCount = t_cellCountParam;

        const sf::Vector2f boardSize{ sf::Vector2i(m_cellSize) * t_cellCountParam };
        const sf::Vector2f boardPos{ util::center(m_botRect) - (boardSize / 2.0f) };
        m_mapRect = sf::FloatRect(boardPos, boardSize);
    }

} // namespace castlecrawl
