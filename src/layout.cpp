// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// layout.hpp
//
#include "layout.hpp"

#include "check-macros.hpp"
#include "util.hpp"

#include <algorithm>
#include <iostream>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace castlecrawl2
{

    Layout::Layout()
        : m_screenRect(0.0f, 0.0f, 0.0f, 0.0f)
        , m_topRect(0.0f, 0.0f, 0.0f, 0.0f)
        , m_botRect(0.0f, 0.0f, 0.0f, 0.0f)
        , m_mapRect(0.0f, 0.0f, 0.0f, 0.0f)
        , m_cellSize(0.0f, 0.0f)
        , m_cellCount(0, 0)
    {}

    void Layout::setup(const GameConfig & config)
    {
        m_screenRect.width  = static_cast<float>(config.video_mode.width);
        m_screenRect.height = static_cast<float>(config.video_mode.height);

        m_topRect        = m_screenRect;
        m_topRect.height = std::floor(m_screenRect.height * config.top_panel_height_ratio);

        m_botRect     = m_screenRect;
        m_botRect.top = m_topRect.height;
        m_botRect.height -= m_botRect.top;

        m_cellSize.x = std::min(
            std::floor(m_botRect.width / static_cast<float>(config.map_size_max.x)),
            std::floor(m_botRect.height / static_cast<float>(config.map_size_max.y)));

        m_cellSize.y = m_cellSize.x;
    }

    void Layout::setupNewMap(const sf::Vector2i & cellCountParam)
    {
        m_cellCount = cellCountParam;

        const sf::Vector2f boardSize{ sf::Vector2i(m_cellSize) * cellCountParam };
        const sf::Vector2f boardPos{ util::center(m_botRect) - (boardSize / 2.0f) };
        m_mapRect = sf::FloatRect(boardPos, boardSize);
    }

} // namespace castlecrawl2
