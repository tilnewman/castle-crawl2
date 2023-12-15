#ifndef CONTEXT_HPP_INCLUDED
#define CONTEXT_HPP_INCLUDED
//
// context.hpp
//

namespace util
{
    class Random;
    class SoundPlayer;
    class MusicPlayer;
} // namespace util

namespace castlecrawl
{
    struct GameConfig;
    class TileImages;
    class Layout;
    class Map;
    class Maps;
    class MapDisplay;
    class StateManager;
    class Player;
    class FontManager;
    class Enemies;
    class FramerateText;
    class TopPanel;

    struct Context
    {
        Context(
            const GameConfig & configParam,
            const TileImages & tileImagesParam,
            Layout & layoutParam,
            Map & mapParam,
            Maps & mapsParam,
            MapDisplay & mapDisplayParam,
            StateManager & stateManagerParam,
            Player & playerParam,
            const util::Random & randomParam,
            util::SoundPlayer & sfxParam,
            util::MusicPlayer & musicParam,
            FontManager & fontManagerParam,
            Enemies & enemiesParam,
            FramerateText & framerateTextParam,
            TopPanel & topPanelParam)
            : config(configParam)
            , tile_images(tileImagesParam)
            , layout(layoutParam)
            , map(mapParam)
            , maps(mapsParam)
            , map_display(mapDisplayParam)
            , state(stateManagerParam)
            , player(playerParam)
            , random(randomParam)
            , sfx(sfxParam)
            , music(musicParam)
            , fonts(fontManagerParam)
            , enemies(enemiesParam)
            , framerate(framerateTextParam)
            , top_panel(topPanelParam)
        {}

        const GameConfig & config;
        const TileImages & tile_images;
        Layout & layout;
        Map & map;
        const Maps & maps;
        MapDisplay & map_display;
        StateManager & state;
        Player & player;
        const util::Random & random;
        util::SoundPlayer & sfx;
        util::MusicPlayer & music;
        FontManager & fonts;
        Enemies & enemies;
        FramerateText & framerate;
        TopPanel & top_panel;
    };

} // namespace castlecrawl

#endif // CONTEXT_HPP_INCLUDED
