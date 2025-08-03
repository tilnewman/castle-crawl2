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
    class AltarImages;
    class DoorwayImages;
    class StatueImages;
    class Layout;
    class Maps;
    class MapDisplay;
    class StateManager;
    class Player;
    class PlayerDisplay;
    class FontManager;
    class Enemies;
    class FramerateText;
    class TopPanel;
    class DustParticleManager;
    class SparkleParticleManager;
    class CampfireAnimationManager;
    class SmokeEffectManager;
    class InfernoAnimationManager;

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
            const AltarImages & t_altarImages,
            const DoorwayImages & t_doorwayImages,
            const StatueImages & t_statueImages,
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
            Enemies & t_enemies,
            FramerateText & t_framerateText,
            TopPanel & t_topPanel,
            item::ItemFactory & t_itemFactory,
            DustParticleManager & t_dustParticleManager,
            SparkleParticleManager & t_sparkleParticleManager,
            CampfireAnimationManager & t_campfireAnimationManager,
            SmokeEffectManager & t_smokeEffectManager,
            InfernoAnimationManager & t_infernoAnimationManager)
            : config(t_config)
            , tile_images(t_tileImages)
            , splat_images(t_splatImages)
            , altar_images(t_altarImages)
            , doorway_images(t_doorwayImages)
            , statue_images(t_statueImages)
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
            , enemies(t_enemies)
            , framerate(t_framerateText)
            , top_panel(t_topPanel)
            , items(t_itemFactory)
            , dust_particles(t_dustParticleManager)
            , sparkle_particles(t_sparkleParticleManager)
            , campfire_anims(t_campfireAnimationManager)
            , smoke_anims(t_smokeEffectManager)
            , inferno_anims(t_infernoAnimationManager)
        {}

        const GameConfig & config;
        const TileImages & tile_images;
        const SplatImages & splat_images;
        const AltarImages & altar_images;
        const DoorwayImages & doorway_images;
        const StatueImages & statue_images;
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
        Enemies & enemies;
        FramerateText & framerate;
        TopPanel & top_panel;
        item::ItemFactory & items;
        DustParticleManager & dust_particles;
        SparkleParticleManager & sparkle_particles;
        CampfireAnimationManager & campfire_anims;
        SmokeEffectManager & smoke_anims;
        InfernoAnimationManager & inferno_anims;
    };

} // namespace castlecrawl

#endif // CONTEXT_HPP_INCLUDED
