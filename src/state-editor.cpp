// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// state-editor.cpp
//
#include "state-editor.hpp"

#include "context.hpp"
#include "font.hpp"
#include "game-config.hpp"
#include "layout.hpp"
#include "map-display.hpp"
#include "maps.hpp"
#include "sfml-defaults.hpp"
#include "sfml-util.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"

#include <fstream>

namespace castlecrawl
{

    StateEditor::StateEditor()
        : m_mapChars{}
        , m_editPos{ 0, 0 }
        , m_floor{ Floor::Stone }
        , m_editRectangle{}
        , m_borderRectangle{}
        , m_keyText{ util::SfmlDefaults::instance().font() }
        , m_fadeText{ util::SfmlDefaults::instance().font() }
        , m_mouseover{}
        , m_isDragging{ false }
        , m_dragPosStart{ 0.0f, 0.0f }
        , m_dragPosStop{ 0.0f, 0.0f }
        , m_dragRectangle{}
        , m_dragSelectedEntrys{}
    {}

    void StateEditor::onEnter(const Context & t_context)
    {
        m_mapChars = std::vector<std::string>(
            static_cast<std::size_t>(t_context.config.map_size_max.y),
            std::string(static_cast<std::size_t>(t_context.config.map_size_max.x), '.'));

        resetMap(t_context);

        m_editRectangle.setFillColor(sf::Color(0, 255, 255, 64));
        m_editRectangle.setOutlineColor(sf::Color(0, 255, 255));
        m_editRectangle.setOutlineThickness(1.0f);
        m_editRectangle.setSize(t_context.layout.cellSize());
        m_editRectangle.setPosition(t_context.layout.mapRect().position);

        m_borderRectangle.setFillColor(sf::Color::Transparent);
        m_borderRectangle.setOutlineColor(sf::Color(255, 255, 255, 64));
        m_borderRectangle.setOutlineThickness(1.0f);
        m_borderRectangle.setPosition(t_context.layout.mapRect().position);
        m_borderRectangle.setSize(t_context.layout.mapRect().size);

        m_dragRectangle.setFillColor(sf::Color(0, 255, 255, 64));

        m_keyText  = t_context.fonts.makeText(FontSize::Small, "", sf::Color::White);
        m_fadeText = t_context.fonts.makeText(FontSize::Large, "", sf::Color::Transparent);
    }

    void StateEditor::update(const Context & t_context, const float t_frameTimeSec)
    {
        updateHelpText(t_context);
        updateFadeText();
        m_mouseover.update(t_context, t_frameTimeSec);
    }

    void StateEditor::draw(
        const Context & t_context, sf::RenderTarget & t_target, sf::RenderStates t_states) const
    {
        t_context.map_display.draw(t_context, t_target, t_states);

        if (!m_keyText.getString().isEmpty())
        {
            t_target.draw(m_keyText, t_states);
        }

        t_target.draw(m_borderRectangle, t_states);
        t_target.draw(m_fadeText, t_states);

        if (m_isDragging)
        {
            t_target.draw(m_dragRectangle);
        }
        else
        {
            t_target.draw(m_editRectangle, t_states);
        }

        for (const MapEntry_t & entry : m_dragSelectedEntrys)
        {
            sf::RectangleShape rectangle;
            rectangle.setFillColor(sf::Color(0, 255, 255, 64));
            rectangle.setPosition(entry.rect.position);
            rectangle.setSize(entry.rect.size);

            t_target.draw(rectangle);
        }

        m_mouseover.draw(t_context, t_target, t_states);
    }

    void StateEditor::handleEvent(const Context & t_context, const sf::Event & t_event)
    {
        if (const auto buttonPtr = t_event.getIf<sf::Event::MouseButtonPressed>())
        {
            startDragging(
                t_context,
                { static_cast<float>(buttonPtr->position.x),
                  static_cast<float>(buttonPtr->position.y) });

            return;
        }

        if (const auto buttonPtr = t_event.getIf<sf::Event::MouseButtonReleased>())
        {
            stopDragging(
                t_context,
                { static_cast<float>(buttonPtr->position.x),
                  static_cast<float>(buttonPtr->position.y) });

            return;
        }

        if (const auto * mouseMovePtr = t_event.getIf<sf::Event::MouseMoved>())
        {
            m_mouseover.handleMouseMovedEvent(
                { mouseMovePtr->position.x, mouseMovePtr->position.y });

            if (m_isDragging)
            {
                updateDragging(
                    t_context,
                    { static_cast<float>(mouseMovePtr->position.x),
                      static_cast<float>(mouseMovePtr->position.y) });
            }

            return;
        }

        // all remaining events are key pressed events
        if (!t_event.is<sf::Event::KeyPressed>())
        {
            return;
        }

        const auto keyScancode = t_event.getIf<sf::Event::KeyPressed>()->scancode;

        if (keyScancode == sf::Keyboard::Scancode::Escape)
        {
            t_context.state.change(t_context, State::Quit);
        }
        else if (
            (keyScancode == sf::Keyboard::Scancode::S) &&
            (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RControl)))
        {
            fadeText(t_context, "Saving...");
            save();
        }
        else if (
            (keyScancode == sf::Keyboard::Scancode::L) &&
            (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LControl) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RControl)))
        {
            fadeText(t_context, "Loading...");
            load(t_context);
        }
        else if (keyScancode == sf::Keyboard::Scancode::F)
        {
            if (m_floor == Floor::Dirt)
            {
                m_floor = Floor::Stone;
                fadeText(t_context, "Stone Floor");
            }
            else if (m_floor == Floor::Stone)
            {
                m_floor = Floor::Wood;
                fadeText(t_context, "Wood Floor");
            }
            else if (m_floor == Floor::Wood)
            {
                m_floor = Floor::Dirt;
                fadeText(t_context, "Dirt Floor");
            }

            resetMap(t_context);
            t_context.sfx.play("tick-off-2");
        }
        else if (keyScancode == sf::Keyboard::Scancode::Up)
        {
            if (m_editPos.y > 0)
            {
                --m_editPos.y;
                placeEditCursor(t_context);
                m_dragSelectedEntrys.clear();
                t_context.sfx.play("tick-off-1");
            }
            else
            {
                t_context.sfx.play("tap-wood-low");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::Down)
        {
            if (m_editPos.y < (static_cast<int>(m_mapChars.size()) - 1))
            {
                ++m_editPos.y;
                placeEditCursor(t_context);
                m_dragSelectedEntrys.clear();
                t_context.sfx.play("tick-off-1");
            }
            else
            {
                t_context.sfx.play("tap-wood-low");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::Left)
        {
            if (m_editPos.x > 0)
            {
                --m_editPos.x;
                placeEditCursor(t_context);
                m_dragSelectedEntrys.clear();
                t_context.sfx.play("tick-off-1");
            }
            else
            {
                t_context.sfx.play("tap-wood-low");
            }
        }
        else if (keyScancode == sf::Keyboard::Scancode::Right)
        {
            if (m_editPos.x < (static_cast<int>(m_mapChars.front().size()) - 1))
            {
                ++m_editPos.x;
                placeEditCursor(t_context);
                m_dragSelectedEntrys.clear();
                t_context.sfx.play("tick-off-1");
            }
            else
            {
                t_context.sfx.play("tap-wood-low");
            }
        }
        // clang-format off
        else if (keyScancode == sf::Keyboard::Scancode::Space)     { editMap(t_context, ' ', ' '); }
        else if (keyScancode == sf::Keyboard::Scancode::Period)    { editMap(t_context, '.', '.'); }
        else if (keyScancode == sf::Keyboard::Scancode::D)         { editMap(t_context, 'D', 'd'); }
        else if (keyScancode == sf::Keyboard::Scancode::S)         { editMap(t_context, 'S', 's'); }
        else if (keyScancode == sf::Keyboard::Scancode::R)         { editMap(t_context, 'r', 'r'); }
        else if (keyScancode == sf::Keyboard::Scancode::L)         { editMap(t_context, 'l', 'l'); }
        else if (keyScancode == sf::Keyboard::Scancode::W)         { editMap(t_context, 'w', 'w'); }
        else if (keyScancode == sf::Keyboard::Scancode::G)         { editMap(t_context, 'g', 'g'); }
        else if (keyScancode == sf::Keyboard::Scancode::B)         { editMap(t_context, 'b', 'b'); }
        else if (keyScancode == sf::Keyboard::Scancode::C)         { editMap(t_context, 'c', 'c'); }
        else if (keyScancode == sf::Keyboard::Scancode::K)         { editMap(t_context, 'k', 'k'); }
        else if (keyScancode == sf::Keyboard::Scancode::Num0)      { editMap(t_context, '0', '0'); }
        else if (keyScancode == sf::Keyboard::Scancode::Num1)      { editMap(t_context, '!', '1'); }
        else if (keyScancode == sf::Keyboard::Scancode::Num2)      { editMap(t_context, '@', '2'); }
        else if (keyScancode == sf::Keyboard::Scancode::Num3)      { editMap(t_context, '#', '3'); }
        else if (keyScancode == sf::Keyboard::Scancode::Num4)      { editMap(t_context, '$', '4'); }
        else if (keyScancode == sf::Keyboard::Scancode::Num5)      { editMap(t_context, '%', '5'); }
        else if (keyScancode == sf::Keyboard::Scancode::Num6)      { editMap(t_context, '^', '6'); }
        else if (keyScancode == sf::Keyboard::Scancode::Num7)      { editMap(t_context, '&', '7'); }
        else if (keyScancode == sf::Keyboard::Scancode::Num8)      { editMap(t_context, '8', '8'); }
        else if (keyScancode == sf::Keyboard::Scancode::Num9)      { editMap(t_context, '9', '9'); }
        else if (keyScancode == sf::Keyboard::Scancode::Semicolon) { editMap(t_context, ';', ':'); }
        else if (keyScancode == sf::Keyboard::Scancode::LBracket)  { editMap(t_context, '[', '['); }
        else if (keyScancode == sf::Keyboard::Scancode::RBracket)  { editMap(t_context, ']', ']'); }
        // clang-format on
    }

    void StateEditor::updateHelpText(const Context & t_context)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::H) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Slash))
        {
            const std::string keyText(
                "Esc-Quit\nCNTRL-s-Save\nCNTRL-l-Load\nSpace-Bare Floor\nPeriod-Erase\n"
                "f-Change-Flooring\nr-Rock\nl-Lava\nw-Water\nc-Chest\nk-Coffin\n"
                "!-Bag\n@-Altar\n#-StoneSpire\n$-Key\n%^&-Herbs\n"
                "S-Stairs Up\ns-Stair Down\nD-Door Locked\nd-Door Unlocked\n"
                "0-Snake\n1-SnakeBag\n2-Spider\n3-Spiderweb\n4-Goblin\n5-GoblinBarrel\n"
                "6-Bat\n7-BatMask\n8-Skeleton\n9-SkeletonGrave\n:-Demon\n;-DemonDoor\n"
                "[-Dragon\n]-DragonInferno");

            m_keyText.setString(keyText);

            m_keyText.setPosition({ ((t_context.layout.topRect().size.x * 0.5f) -
                                     (m_keyText.getGlobalBounds().size.x * 0.5f)),
                                    (t_context.layout.topRect().size.y + 100.0f) });
        }
        else
        {
            m_keyText.setString("");
        }
    }

    void StateEditor::updateFadeText()
    {
        sf::Color color = m_fadeText.getFillColor();
        if (color.a > 0)
        {
            --color.a;
            m_fadeText.setFillColor(color);
        }
    }

    void StateEditor::resetMap(const Context & t_context)
    {
        Map map(MapName::Level_1_Cell, t_context, m_floor, m_mapChars, MapTransitions_t{});

        t_context.maps.forceMapForEditting(map);
        t_context.map_display.load(t_context);
    }

    void StateEditor::placeEditCursor(const Context & t_context)
    {
        m_editRectangle.setPosition(
            t_context.maps.current().mapPosToScreenPos(t_context, m_editPos));
    }

    void StateEditor::setMapChar(const char t_ch)
    {
        if (m_dragSelectedEntrys.empty())
        {
            m_mapChars.at(static_cast<std::size_t>(m_editPos.y))
                .at(static_cast<std::size_t>(m_editPos.x)) = t_ch;
        }
        else
        {
            for (const MapEntry_t & entry : m_dragSelectedEntrys)
            {
                m_mapChars.at(static_cast<std::size_t>(entry.pos.y))
                    .at(static_cast<std::size_t>(entry.pos.x)) = t_ch;
            }
        }
    }

    void StateEditor::editMap(const Context & t_context, const char t_upper, const char t_lower)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::LShift) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::RShift))
        {
            setMapChar(t_upper);
            fadeText(t_context, mapCharToName(t_upper));
        }
        else
        {
            setMapChar(t_lower);
            fadeText(t_context, mapCharToName(t_lower));
        }

        resetMap(t_context);
        t_context.sfx.play("tick-on-1");
    }

    void StateEditor::fadeText(const Context & t_context, const std::string & t_text)
    {
        m_fadeText.setString(t_text);
        m_fadeText.setFillColor(sf::Color::White);

        m_fadeText.setPosition(
            { ((t_context.layout.topRect().size.x * 0.5f) -
               (m_fadeText.getGlobalBounds().size.x * 0.5f)),
              (m_borderRectangle.getPosition().y - (m_fadeText.getGlobalBounds().size.y * 2.0f)) });
    }

    void StateEditor::save() const
    {
        std::ofstream fStream("map.txt", std::ios::trunc);

        for (const std::string & rowStr : m_mapChars)
        {
            fStream << '\"' << rowStr << "\"," << std::endl;
        }
    }

    void StateEditor::load(const Context & t_context)
    {
        std::ifstream fStream("map.txt", std::ios::in);

        std::vector<std::string> lines;
        lines.reserve(m_mapChars.size());

        std::string line;
        while (std::getline(fStream, line, '\n'))
        {
            if (line.size() < m_mapChars[0].size())
            {
                return;
            }

            // remove the leading quote
            if (line[0] == '\"')
            {
                line.erase(std::begin(line));
            }

            // remove the trailing comma
            if (line[line.size() - 1] == ',')
            {
                line.pop_back();
            }

            // remove the trailing quote
            if (line[line.size() - 1] == '\"')
            {
                line.pop_back();
            }

            if (line.size() != m_mapChars[0].size())
            {
                return;
            }

            lines.push_back(line);
        }

        if (lines.size() != m_mapChars.size())
        {
            return;
        }

        m_mapChars = lines;
        resetMap(t_context);
    }

    const std::string StateEditor::mapCharToName(const char t_ch) noexcept
    {
        // clang-format off
        switch (t_ch)
        {
            case ' ': { return "Bare Floor"; }
            case '.': { return "Erase"; }
            case 'D': { return "Door Locked"; }
            case 'd': { return "Door Unlocked"; }
            case 'S': { return "Stairs Up"; }
            case 's': { return "Stairs Down"; }
            case 'r': { return "Rock"; }
            case 'l': { return "Lava"; }
            case 'w': { return "Water"; }
            case 'g': { return "Slime"; }
            case 'b': { return "Barrel"; }
            case 'c': { return "Chest"; }
            case 'k': { return "Coffin"; }
            case '!': { return "Bag"; }
            case '@': { return "Altar"; }
            case '#': { return "StoneSpire"; }
            case '$': { return "Key"; }
            case '%': { return "Weak Herb"; }
            case '^': { return "Normal Herb"; }
            case '&': { return "Strong Herb"; }
            case '0': { return "Snake"; }
            case '1': { return "Snake Bag"; }
            case '2': { return "Spider"; }
            case '3': { return "Spiderweb"; }
            case '4': { return "Goblin"; }
            case '5': { return "Goblin Barrel"; }
            case '6': { return "Bat"; }
            case '7': { return "Bat Mask"; }
            case '8': { return "Skeleton"; }
            case '9': { return "Skeleton Grave"; }
            case ':': { return "Demon"; }
            case ';': { return "Demon Door"; }
            case '[': { return "Dragon"; }
            case ']': { return "Dragon Inferno"; }
            default:  { return ""; }
        }
        // clang-format on
    }

    void StateEditor::startDragging(const Context & t_context, const sf::Vector2f & t_pos)
    {
        m_dragPosStart = t_pos;
        m_dragPosStop  = t_pos;

        updateDragRect();

        m_isDragging = t_context.layout.mapRect().contains(t_pos);

        updateDragSelectedMapCells(t_context);

        t_context.sfx.play("tick-on-1");
    }

    void StateEditor::stopDragging(const Context & t_context, const sf::Vector2f & t_pos)
    {
        const MapPos_t newMapPos = t_context.maps.current().screenPosToMapPos(t_context, t_pos);

        if (t_context.maps.current().isPosValid(newMapPos))
        {
            m_editPos = newMapPos;
            placeEditCursor(t_context);
            t_context.sfx.play("tick-off-1");
        }

        m_isDragging = false;

        if (t_context.layout.mapRect().contains(t_pos))
        {
            updateDragRect();
        }
        else
        {
            m_dragRectangle.setPosition({ 0.0f, 0.0f });
            m_dragRectangle.setSize({ 0.0f, 0.0f });
        }
    }

    void StateEditor::updateDragging(const Context & t_context, const sf::Vector2f & t_pos)
    {
        m_dragPosStop = t_pos;
        updateDragRect();
        updateDragSelectedMapCells(t_context);
    }

    void StateEditor::updateDragRect()
    {
        m_dragRectangle.setPosition({ util::min(m_dragPosStart.x, m_dragPosStop.x),
                                      util::min(m_dragPosStart.y, m_dragPosStop.y) });

        m_dragRectangle.setSize(sf::Vector2f{ util::abs(m_dragPosStart.x - m_dragPosStop.x),
                                              util::abs(m_dragPosStart.y - m_dragPosStop.y) });
    }

    void StateEditor::updateDragSelectedMapCells(const Context & t_context)
    {
        m_dragSelectedEntrys.clear();

        const sf::FloatRect mapRect = t_context.layout.mapRect();
        const sf::Vector2i mapSize  = t_context.layout.cellCount();

        sf::Vector2f screenPos = mapRect.position;
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const sf::FloatRect screenRect{ screenPos, t_context.layout.cellSize() };

                const sf::FloatRect dragRect{ util::position(m_dragRectangle),
                                              util::size(m_dragRectangle) };

                if (screenRect.findIntersection(dragRect))
                {
                    const MapEntry_t entry{ { x, y }, screenRect };
                    m_dragSelectedEntrys.push_back(entry);
                }

                screenPos.x += t_context.layout.cellSize().x;
            }

            screenPos.x = mapRect.position.x;
            screenPos.y += t_context.layout.cellSize().y;
        }
    }

} // namespace castlecrawl
