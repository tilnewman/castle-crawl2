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
#include "map.hpp"
#include "sound-player.hpp"
#include "state-manager.hpp"
#include "util.hpp"

#include <fstream>

namespace castlecrawl2
{

    StateEditor::StateEditor()
        : m_mapChars()
        , m_editPos(0, 0)
        , m_floor(Floor::Stone)
        , m_editRectangle()
        , m_borderRectangle()
        , m_keyText()
        , m_fadeText()
        , m_mouseover()
        , m_isDragging(false)
        , m_dragPosStart(0.0f, 0.0f)
        , m_dragPosStop(0.0f, 0.0f)
        , m_dragRectangle()
        , m_dragSelectedEntrys()
    {}

    void StateEditor::onEnter(const Context & context)
    {
        m_mapChars = std::vector<std::string>(
            static_cast<std::size_t>(context.config.map_size_max.y),
            std::string(static_cast<std::size_t>(context.config.map_size_max.x), '.'));

        resetMap(context);

        m_editRectangle.setFillColor(sf::Color(0, 255, 255, 64));
        m_editRectangle.setOutlineColor(sf::Color(0, 255, 255));
        m_editRectangle.setOutlineThickness(1.0f);
        m_editRectangle.setSize(context.layout.cellSize());
        m_editRectangle.setPosition(util::position(context.layout.mapRect()));

        m_borderRectangle.setFillColor(sf::Color::Transparent);
        m_borderRectangle.setOutlineColor(sf::Color(255, 255, 255, 64));
        m_borderRectangle.setOutlineThickness(1.0f);
        m_borderRectangle.setPosition(util::position(context.layout.mapRect()));
        m_borderRectangle.setSize(util::size(context.layout.mapRect()));

        m_dragRectangle.setFillColor(sf::Color(0, 255, 255, 64));

        m_keyText  = context.fonts.makeText(FontSize::Small, "", sf::Color::White);
        m_fadeText = context.fonts.makeText(FontSize::Large, "", sf::Color::Transparent);
    }

    void StateEditor::update(const Context & context, const float frameTimeSec)
    {
        updateHelpText(context);
        updateFadeText();
        m_mouseover.update(context, frameTimeSec);
    }

    void StateEditor::draw(
        const Context & context, sf::RenderTarget & target, sf::RenderStates states) const
    {
        target.clear(context.config.background_color);
        context.map_display.draw(context, target, states);

        if (!m_keyText.getString().isEmpty())
        {
            target.draw(m_keyText, states);
        }

        target.draw(m_borderRectangle, states);
        target.draw(m_editRectangle, states);
        target.draw(m_fadeText, states);

        if (m_isDragging)
        {
            target.draw(m_dragRectangle);
        }

        for (const MapEntry_t & entry : m_dragSelectedEntrys)
        {
            sf::RectangleShape rectangle;
            rectangle.setFillColor(sf::Color(0, 255, 255, 64));
            rectangle.setPosition(util::position(entry.rect));
            rectangle.setSize(util::size(entry.rect));

            target.draw(rectangle);
        }

        m_mouseover.draw(context, target, states);
    }

    void StateEditor::handleEvent(const Context & context, const sf::Event & event)
    {
        if (sf::Event::MouseButtonPressed == event.type)
        {
            startDragging(
                context,
                { static_cast<float>(event.mouseButton.x),
                  static_cast<float>(event.mouseButton.y) });

            return;
        }

        if (sf::Event::MouseButtonReleased == event.type)
        {
            stopDragging(
                context,
                { static_cast<float>(event.mouseButton.x),
                  static_cast<float>(event.mouseButton.y) });

            return;
        }

        if (sf::Event::MouseMoved == event.type)
        {
            m_mouseover.handleMouseMovedEvent({ event.mouseMove.x, event.mouseMove.y });

            if (m_isDragging)
            {
                updateDragging(
                    context,
                    { static_cast<float>(event.mouseMove.x),
                      static_cast<float>(event.mouseMove.y) });
            }

            return;
        }

        if ((event.type == sf::Event::MouseButtonPressed) &&
            (event.mouseButton.button == sf::Mouse::Button::Left))
        {
            const sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

            const MapPos_t newMapPos =
                context.map.screenPosToMapPos(context, sf::Vector2f{ mousePos });

            if ((newMapPos.x >= 0) && (newMapPos.y >= 0))
            {
                m_editPos = newMapPos;
                placeEditCursor(context);
                context.sfx.play("tick-off-1");
            }

            return;
        }

        // all events are key released events
        if (event.type != sf::Event::KeyReleased)
        {
            return;
        }

        if (event.key.code == sf::Keyboard::Escape)
        {
            context.state.change(context, State::Quit);
        }
        else if (
            event.key.code == sf::Keyboard::S &&
            (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)))
        {
            fadeText(context, "Saving");
            save();
        }
        else if (event.key.code == sf::Keyboard::F)
        {
            if (m_floor == Floor::Dirt)
            {
                m_floor = Floor::Stone;
                fadeText(context, "Stone Floor");
            }
            else if (m_floor == Floor::Stone)
            {
                m_floor = Floor::Wood;
                fadeText(context, "Wood Floor");
            }
            else if (m_floor == Floor::Wood)
            {
                m_floor = Floor::Dirt;
                fadeText(context, "Dirt Floor");
            }

            resetMap(context);
            context.sfx.play("tick-off-2");
        }
        else if (event.key.code == sf::Keyboard::Up)
        {
            if (m_editPos.y > 0)
            {
                --m_editPos.y;
                placeEditCursor(context);
                context.sfx.play("tick-off-1");
            }
            else
            {
                context.sfx.play("tap-wood-low");
            }
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            if (m_editPos.y < (static_cast<int>(m_mapChars.size()) - 1))
            {
                ++m_editPos.y;
                placeEditCursor(context);
                context.sfx.play("tick-off-1");
            }
            else
            {
                context.sfx.play("tap-wood-low");
            }
        }
        else if (event.key.code == sf::Keyboard::Left)
        {
            if (m_editPos.x > 0)
            {
                --m_editPos.x;
                placeEditCursor(context);
                context.sfx.play("tick-off-1");
            }
            else
            {
                context.sfx.play("tap-wood-low");
            }
        }
        else if (event.key.code == sf::Keyboard::Right)
        {
            if (m_editPos.x < (static_cast<int>(m_mapChars.front().size()) - 1))
            {
                ++m_editPos.x;
                placeEditCursor(context);
                context.sfx.play("tick-off-1");
            }
            else
            {
                context.sfx.play("tap-wood-low");
            }
        }
        // clang-format off
        else if (event.key.code == sf::Keyboard::Space)     { editMap(context, ' ', ' '); }
        else if (event.key.code == sf::Keyboard::Period)    { editMap(context, '.', '.'); }
        else if (event.key.code == sf::Keyboard::D)         { editMap(context, 'D', 'd'); }
        else if (event.key.code == sf::Keyboard::S)         { editMap(context, 'S', 's'); }
        else if (event.key.code == sf::Keyboard::R)         { editMap(context, 'r', 'r'); }
        else if (event.key.code == sf::Keyboard::L)         { editMap(context, 'l', 'l'); }
        else if (event.key.code == sf::Keyboard::W)         { editMap(context, 'w', 'w'); }
        else if (event.key.code == sf::Keyboard::B)         { editMap(context, 'b', 'b'); }
        else if (event.key.code == sf::Keyboard::C)         { editMap(context, 'c', 'c'); }
        else if (event.key.code == sf::Keyboard::K)         { editMap(context, 'k', 'k'); }
        else if (event.key.code == sf::Keyboard::Num0)      { editMap(context, '0', '0'); }
        else if (event.key.code == sf::Keyboard::Num1)      { editMap(context, '1', '1'); }
        else if (event.key.code == sf::Keyboard::Num2)      { editMap(context, '2', '2'); }
        else if (event.key.code == sf::Keyboard::Num3)      { editMap(context, '3', '3'); }
        else if (event.key.code == sf::Keyboard::Num4)      { editMap(context, '4', '4'); }
        else if (event.key.code == sf::Keyboard::Num5)      { editMap(context, '5', '5'); }
        else if (event.key.code == sf::Keyboard::Num6)      { editMap(context, '6', '6'); }
        else if (event.key.code == sf::Keyboard::Num7)      { editMap(context, '7', '7'); }
        else if (event.key.code == sf::Keyboard::Num8)      { editMap(context, '8', '8'); }
        else if (event.key.code == sf::Keyboard::Num9)      { editMap(context, '9', '9'); }
        else if (event.key.code == sf::Keyboard::Semicolon) { editMap(context, ';', ':'); }
        else if (event.key.code == sf::Keyboard::LBracket)  { editMap(context, '[', '['); }
        else if (event.key.code == sf::Keyboard::RBracket)  { editMap(context, ']', ']'); }
        // clang-format on
    }

    void StateEditor::updateHelpText(const Context & context)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Slash))
        {
            const std::string keyText(
                "Esc-Quit\nCNTRL-s-Save\nSpace-Bare Floor\nPeriod-Erase\n"
                "f-Change-Flooring\nr-Rock\nl-Lava\nw-Water\nc-Chest\nk-Coffin\n"
                "S-Stairs Up\ns-Stair Down\nD-Door Locked\nd-Door Unlocked\n"
                "0-Snake\n1-SnakeBag\n2-Spider\n3-Spiderweb\n4-Goblin\n5-GoblinBarrel\n"
                "6-Bat\n7-BatMask\n8-Skeleton\n9-SkeletonGrave\n:-Demon\n;-DemonDoor\n"
                "[-Dragon\n]-DragonInferno");

            m_keyText.setString(keyText);

            m_keyText.setPosition(
                ((context.layout.topRect().width * 0.5f) -
                 (m_keyText.getGlobalBounds().width * 0.5f)),
                (context.layout.topRect().height + 100.0f));
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

    void StateEditor::resetMap(const Context & context)
    {
        Map startingMap(MapName::Level_1_Cell, context, m_floor, m_mapChars, MapTransitions_t{});

        context.map = startingMap;
        context.map_display.load(context);
    }

    void StateEditor::placeEditCursor(const Context & context)
    {
        m_editRectangle.setPosition(context.map.mapPosToScreenPos(context, m_editPos));
    }

    void StateEditor::setMapChar(const char ch)
    {
        if (m_dragSelectedEntrys.empty())
        {
            m_mapChars.at(static_cast<std::size_t>(m_editPos.y))
                .at(static_cast<std::size_t>(m_editPos.x)) = ch;
        }
        else
        {
            for (const MapEntry_t & entry : m_dragSelectedEntrys)
            {
                m_mapChars.at(static_cast<std::size_t>(entry.pos.y))
                    .at(static_cast<std::size_t>(entry.pos.x)) = ch;
            }
        }
    }

    void StateEditor::editMap(const Context & context, const char upper, const char lower)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
        {
            setMapChar(upper);
            fadeText(context, mapCharToName(upper));
        }
        else
        {
            setMapChar(lower);
            fadeText(context, mapCharToName(lower));
        }

        resetMap(context);
        context.sfx.play("tick-on-1");
    }

    void StateEditor::fadeText(const Context & context, const std::string & text)
    {
        m_fadeText.setString(text);
        m_fadeText.setFillColor(sf::Color::White);

        m_fadeText.setPosition(
            ((context.layout.topRect().width * 0.5f) - (m_fadeText.getGlobalBounds().width * 0.5f)),
            0.0f);
    }

    void StateEditor::save() const
    {
        std::ofstream fStream("map.txt", std::ios::trunc);

        // clang-format off
        switch (m_floor)
        {
            case Floor::Dirt:   { fStream << "Dirt" << std::endl; break; }
            case Floor::Stone:  { fStream << "Stone" << std::endl; break; }
            case Floor::Wood:   { fStream << "Wood" << std::endl; break; }
            default:            { fStream << "(floor type error)" << std::endl; break; }
        }
        // clang-format on

        for (const std::string & rowStr : m_mapChars)
        {
            fStream << '\"' << rowStr << '\"' << std::endl;
        }
    }

    const std::string StateEditor::mapCharToName(const char ch) noexcept
    {
        // clang-format off
        switch (ch)
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
            case 'b': { return "Barrel"; }
            case 'c': { return "Chest"; }
            case 'k': { return "Coffin"; }
            case '0': { return "Snake"; }
            case '1': { return "SnakeBag"; }
            case '2': { return "Spider"; }
            case '3': { return "Spiderweb"; }
            case '4': { return "Goblin"; }
            case '5': { return "GoblinBarrel"; }
            case '6': { return "Bat"; }
            case '7': { return "BatMask"; }
            case '8': { return "Skeleton"; }
            case '9': { return "SkeletonGrave"; }
            case ':': { return "Demon"; }
            case ';': { return "DemonDoor"; }
            case '[': { return "Dragon"; }
            case ']': { return "DragonInferno"; }
            default:  { return ""; }
        }
        // clang-format on
    }

    void StateEditor::startDragging(const Context & context, const sf::Vector2f & pos)
    {
        m_dragPosStart = pos;
        m_dragPosStop  = pos;

        updateDragRect();

        m_isDragging = context.layout.mapRect().contains(pos);

        updateDragSelectedMapCells(context);

        context.sfx.play("tick-on-1");
    }

    void StateEditor::stopDragging(const Context & context, const sf::Vector2f & pos)
    {
        const MapPos_t newMapPos = context.map.screenPosToMapPos(context, pos);

        if (context.map.isPosValid(newMapPos))
        {
            m_editPos = newMapPos;
            placeEditCursor(context);
            context.sfx.play("tick-off-1");
        }

        m_isDragging = false;

        if (context.layout.mapRect().contains(pos))
        {
            updateDragRect();
        }
        else
        {
            m_dragRectangle.setPosition({ 0.0f, 0.0f });
            m_dragRectangle.setSize({ 0.0f, 0.0f });
        }
    }

    void StateEditor::updateDragging(const Context & context, const sf::Vector2f & pos)
    {
        m_dragPosStop = pos;
        updateDragRect();
        updateDragSelectedMapCells(context);
    }

    void StateEditor::updateDragRect()
    {
        m_dragRectangle.setPosition(
            util::min(m_dragPosStart.x, m_dragPosStop.x),
            util::min(m_dragPosStart.y, m_dragPosStop.y));

        m_dragRectangle.setSize(sf::Vector2f{ util::abs(m_dragPosStart.x - m_dragPosStop.x),
                                              util::abs(m_dragPosStart.y - m_dragPosStop.y) });
    }

    void StateEditor::updateDragSelectedMapCells(const Context & context)
    {
        m_dragSelectedEntrys.clear();

        const sf::FloatRect mapRect = context.layout.mapRect();
        const sf::Vector2i mapSize  = context.layout.cellCount();

        sf::Vector2f screenPos = util::position(mapRect);
        for (int y(0); y < mapSize.y; ++y)
        {
            for (int x(0); x < mapSize.x; ++x)
            {
                const sf::FloatRect screenRect{ screenPos, context.layout.cellSize() };

                const sf::FloatRect dragRect{ util::position(m_dragRectangle),
                                              util::size(m_dragRectangle) };

                if (screenRect.intersects(dragRect))
                {
                    const MapEntry_t entry{ { x, y }, screenRect };
                    m_dragSelectedEntrys.push_back(entry);
                }

                screenPos.x += context.layout.cellSize().x;
            }

            screenPos.x = mapRect.left;
            screenPos.y += context.layout.cellSize().y;
        }
    }

} // namespace castlecrawl2
