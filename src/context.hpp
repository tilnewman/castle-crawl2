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
    class SplatImages;
    class Layout;
    class Maps;
    class MapDisplay;
    class StateManager;
    class Player;
    class PlayerDisplay;
    class FontManager;
    class FramerateText;
    class TopPanel;
    class MonsterManager;
    class NpcManager;
    class AnimationManager;

    namespace item
    {
        class ItemFactory;
    }

    struct Context
    {
        Context(
            const GameConfig & t_config,
            const TileImages & t_tileImages,
            const SplatImages & t_splatImages,
            Layout & t_layout,
            Maps & t_maps,
            MapDisplay & t_mapDisplay,
            StateManager & t_stateManager,
            Player & t_player,
            PlayerDisplay & t_playerDisplay,
            const util::Random & t_random,
            util::SoundPlayer & t_sfx,
            util::MusicPlayer & t_music,
            FontManager & t_fontManager,
            FramerateText & t_framerateText,
            TopPanel & t_topPanel,
            item::ItemFactory & t_itemFactory,
            MonsterManager & t_monsterManager,
            NpcManager & t_npcManager,
            AnimationManager & t_animationManager)
            : config(t_config)
            , tile_images(t_tileImages)
            , splat_images(t_splatImages)
            , layout(t_layout)
            , maps(t_maps)
            , map_display(t_mapDisplay)
            , state(t_stateManager)
            , player(t_player)
            , player_display(t_playerDisplay)
            , random(t_random)
            , sfx(t_sfx)
            , music(t_music)
            , fonts(t_fontManager)
            , framerate(t_framerateText)
            , top_panel(t_topPanel)
            , items(t_itemFactory)
            , monsters(t_monsterManager)
            , npcs(t_npcManager)
            , anim(t_animationManager)
        {}

        const GameConfig & config;
        const TileImages & tile_images;
        const SplatImages & splat_images;
        Layout & layout;
        Maps & maps;
        MapDisplay & map_display;
        StateManager & state;
        Player & player;
        PlayerDisplay & player_display;
        const util::Random & random;
        util::SoundPlayer & sfx;
        util::MusicPlayer & music;
        FontManager & fonts;
        FramerateText & framerate;
        TopPanel & top_panel;
        item::ItemFactory & items;
        MonsterManager & monsters;
        NpcManager & npcs;
        AnimationManager & anim;
    };

} // namespace castlecrawl

#endif // CONTEXT_HPP_INCLUDED
