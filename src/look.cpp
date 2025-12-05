// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// look.cpp
//
#include "look.hpp"

#include "context.hpp"
#include "game-config.hpp"
#include "maps.hpp"
#include "monster-manager.hpp"
#include "state-manager.hpp"
#include "state-text-popup.hpp"
#include "turn-keeper.hpp"

namespace castlecrawl
{

    Look::Look() {}

    void Look::look(const Context & t_context, const MapPos_t & t_pos, const bool t_willAdvanceTurn)
    {
        const char objectChar     = t_context.maps.current().cell(t_pos).object_char;
        const TileImage tileImage = charToTileImage(objectChar);

        TextPopupInfo info;
        info.map_pos           = t_pos;
        info.will_advance_turn = t_willAdvanceTurn;

        if (objectChar == tileImageToChar(TileImage::Empty))
        {
            info.message = "Just a bare ";
            info.message += toString(t_context.maps.current().floor());
            info.message += " floor.";
        }
        else if (objectChar == tileImageToChar(TileImage::Campfire))
        {
            info.message = "A campfire crackles and smokes.";
        }
        else if (objectChar == tileImageToChar(TileImage::Inferno))
        {
            info.message = "This raging inferno looks dangerous.";
        }
        else if (objectChar == tileImageToChar(TileImage::Barrel))
        {
            info.message = "A wooden barrel that looks easy to break open...";
        }
        else if (objectChar == tileImageToChar(TileImage::Sign))
        {
            // TODO
            info.message = "A wooden sign that reads: TODO";
        }
        else if (objectChar == tileImageToChar(TileImage::Chest))
        {
            info.message = "A wooden treasure chest.";
        }
        else if (objectChar == tileImageToChar(TileImage::Ice))
        {
            info.message = "Solid Ice.";
        }
        else if (objectChar == tileImageToChar(TileImage::Door))
        {
            info.message = "An unlocked wooden door.";
        }
        else if (objectChar == tileImageToChar(TileImage::DoorLocked))
        {
            // TODO mention what kind of key it needs
            info.message = "A locked wooden door.";
        }
        else if (objectChar == tileImageToChar(TileImage::Blood))
        {
            info.message = "A pool of blood.";
        }
        else if (objectChar == tileImageToChar(TileImage::Key))
        {
            info.message = "A key that you could pickup and use.";
        }
        else if (objectChar == tileImageToChar(TileImage::FountainWater))
        {
            info.message = "A lovely fountain trickles water.";
        }
        else if (objectChar == tileImageToChar(TileImage::FountainBlood))
        {
            info.message = "This fountain is pouring blood.";
        }
        else if (objectChar == tileImageToChar(TileImage::Water))
        {
            info.message = "A pool of water.";
        }
        else if (objectChar == tileImageToChar(TileImage::Slime))
        {
            info.message = "A disgusting pool of green ooze.";
        }
        else if (objectChar == tileImageToChar(TileImage::Rock))
        {
            info.message = "A plain rock wall.";
        }
        else if (objectChar == tileImageToChar(TileImage::RockWeak))
        {
            info.message = "A rock wall that looks easy to break...";
        }
        else if (objectChar == tileImageToChar(TileImage::Stair_Up))
        {
            info.message = "A stairway leads up.";
        }
        else if (objectChar == tileImageToChar(TileImage::Stair_Down))
        {
            info.message = "A stairway leads down.";
        }
        else if (objectChar == tileImageToChar(TileImage::Altar))
        {
            info.message = "A stone altar awaits the correct sacrifice...";
        }
        else if (objectChar == tileImageToChar(TileImage::Bag))
        {
            info.message = "A plain leather bag with unknown contents...";
        }
        else if (objectChar == tileImageToChar(TileImage::Coffin))
        {
            info.message = "A wooden coffin.";
        }
        else if (objectChar == tileImageToChar(TileImage::StoneSpire))
        {
            info.message = "A large rock spire points up.";
        }
        else if (objectChar == tileImageToChar(TileImage::Lava))
        {
            info.message = "Lava bubbles quietly.";
        }
        else if (
            (objectChar == tileImageToChar(TileImage::Tree1)) ||
            (objectChar == tileImageToChar(TileImage::Tree2)) ||
            (objectChar == tileImageToChar(TileImage::Tree3)))
        {
            info.message = "This tree blocks your path.";
        }
        else if (objectChar == tileImageToChar(TileImage::Coins))
        {
            info.message = "A pile of coins on the ground.";
        }
        else if (
            (objectChar >= tileImageToChar(TileImage::Statue_Twins)) &&
            (objectChar <= tileImageToChar(TileImage::Statue_Tengu)))
        {
            // TODO have unique descriptions for each statue hinting at interactions
            info.message = "A stone statue.";
        }
        else if (
            (objectChar == tileImageToChar(TileImage::Wall_TopLeft)) ||
            (objectChar == tileImageToChar(TileImage::Wall_Horiz)) ||
            (objectChar == tileImageToChar(TileImage::Wall_Top)) ||
            (objectChar == tileImageToChar(TileImage::Wall_Vert)) ||
            (objectChar == tileImageToChar(TileImage::Wall_Block)))
        {
            info.message = "Just a wall.";
        }
        else if (objectChar == tileImageToChar(TileImage::Wall_BlockWeak))
        {
            info.message = "A wooden wall that looks easy to break...";
        }
        else if (
            (objectChar >= tileImageToChar(TileImage::Doorway_Wood)) &&
            (objectChar <= tileImageToChar(TileImage::Doorway_OrientalRed)))
        {
            // TODO have unique descriptions for each door hinting at interactions
            info.message = "A doorawy.";
        }
        else if (
            (objectChar >= tileImageToChar(TileImage::Altar_Statue)) &&
            (objectChar <= tileImageToChar(TileImage::Altar_King)))
        {
            // TODO have unique descriptions for each altar hinting at interactions
            info.message = "A proud stone altar keeps it's silent repose.";
        }
        else if (
            (objectChar == tileImageToChar(TileImage::Pillar_CrumbleLeft)) ||
            (objectChar == tileImageToChar(TileImage::Pillar_Rubble)) ||
            (objectChar == tileImageToChar(TileImage::Pillar_Complete)) ||
            (objectChar == tileImageToChar(TileImage::Pillar_Half)) ||
            (objectChar == tileImageToChar(TileImage::Pillar_Quarter)) ||
            (objectChar == tileImageToChar(TileImage::Pillar_CrumbleRight)))
        {
            info.message = "A crumbling stone column.";
        }
        else if (
            (objectChar == tileImageToChar(TileImage::Block_Emboss1)) ||
            (objectChar == tileImageToChar(TileImage::Block_Emboss2)) ||
            (objectChar == tileImageToChar(TileImage::Block_Emboss3)) ||
            (objectChar == tileImageToChar(TileImage::Block_Emboss4)))
        {
            info.message = "A rock wall with detailed carvings.";
        }
        else if (isTileImageMonster(tileImage))
        {
            // TODO add some stats (monster info) to the message
            // const MonsterStats monsterStats{ t_context.monsters.stats(t_pos) };
            info.message = toString(tileImage);
        }
        else if (isTileImageNpc(tileImage))
        {
            // TODO add some extra info on NPCs?  Maybe descriptions of what they look like?
            info.message = toString(tileImage);
        }
        else
        {
            // should never get here, but not worth throwing an exception
            info.message = "Look Error: ";
            info.message += toString(tileImage);
        }

        StateTextPopup::setInfo(info);
        t_context.state.setChangePending(State::TextPopup);
    }

} // namespace castlecrawl
