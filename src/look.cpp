// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// look.cpp
//
#include "look.hpp"

#include "context.hpp"
#include "maps.hpp"
#include "state-look-event.hpp"
#include "state-manager.hpp"
#include "state-text-popup.hpp"
#include "tile-image-enum.hpp"

namespace castlecrawl
{

    Look::Look() {}

    void Look::look(const Context & t_context, const MapPos_t & t_pos, const bool t_willAdvanceTurn)
    {
        LookEvent lookEvent;
        for (const LookEvent & next : t_context.maps.current().lookEvents())
        {
            if (t_pos == next.map_pos)
            {
                lookEvent = next;
                break;
            }
        }

        if (!lookEvent.empty() && !lookEvent.has_happened)
        {
            StateLookEvent::setEvent(lookEvent);
            t_context.state.setChangePending(State::LookEvent);
        }
        else
        {
            TextPopupInfo info;
            info.map_pos           = t_pos;
            info.will_advance_turn = t_willAdvanceTurn;
            info.message           = popupMapCharMessage(t_context, t_pos);

            StateTextPopup::setInfo(info);
            t_context.state.setChangePending(State::TextPopup);
        }
    }

    const std::string
        Look::popupMapCharMessage(const Context & t_context, const MapPos_t & t_pos) const
    {
        const char objectChar     = t_context.maps.current().cell(t_pos).object_char;
        const TileImage tileImage = charToTileImage(objectChar);

        std::string message;

        if (objectChar == tileImageToChar(TileImage::Empty))
        {
            message = "Just a bare ";
            message += toString(t_context.maps.current().floor());
            message += " floor.";
        }
        else if (objectChar == tileImageToChar(TileImage::Campfire))
        {
            message = "A campfire crackles and smokes.";
        }
        else if (objectChar == tileImageToChar(TileImage::Inferno))
        {
            message = "This raging inferno looks dangerous.";
        }
        else if (objectChar == tileImageToChar(TileImage::Barrel))
        {
            message = "A wooden barrel that looks easy to break open...";
        }
        else if (objectChar == tileImageToChar(TileImage::Sign))
        {
            // TODO
            message = "A wooden sign that reads: TODO";
        }
        else if (objectChar == tileImageToChar(TileImage::Chest))
        {
            message = "A wooden treasure chest.";
        }
        else if (objectChar == tileImageToChar(TileImage::Ice))
        {
            message = "Solid Ice.";
        }
        else if (objectChar == tileImageToChar(TileImage::Door))
        {
            message = "An unlocked wooden door.";
        }
        else if (objectChar == tileImageToChar(TileImage::DoorLocked))
        {
            message = "A locked wooden door";

            const DoorLockOpt_t doorLockOpt = t_context.maps.current().doorLock(t_pos);
            if (doorLockOpt.has_value())
            {
                message += " that needs a ";
                message += doorLockOpt->unlocking_item_name;
            }

            message += '.';
        }
        else if (objectChar == tileImageToChar(TileImage::Blood))
        {
            message = "A pool of blood.";
        }
        else if (objectChar == tileImageToChar(TileImage::Key))
        {
            message = "A key that you could pickup and use.";
        }
        else if (objectChar == tileImageToChar(TileImage::FountainWater))
        {
            message = "A lovely fountain trickles water.";
        }
        else if (objectChar == tileImageToChar(TileImage::FountainBlood))
        {
            message = "This fountain is pouring blood.";
        }
        else if (objectChar == tileImageToChar(TileImage::Water))
        {
            message = "A pool of water.";
        }
        else if (objectChar == tileImageToChar(TileImage::Slime))
        {
            message = "A disgusting pool of green ooze.";
        }
        else if (objectChar == tileImageToChar(TileImage::Rock))
        {
            message = "A plain rock wall.";
        }
        else if (objectChar == tileImageToChar(TileImage::RockWeak))
        {
            message = "A rock wall that looks easy to break...";
        }
        else if (objectChar == tileImageToChar(TileImage::Stair_Up))
        {
            message = "A stairway leads up.";
        }
        else if (objectChar == tileImageToChar(TileImage::Stair_Down))
        {
            message = "A stairway leads down.";
        }
        else if (objectChar == tileImageToChar(TileImage::Altar))
        {
            message = "A stone altar awaits the correct sacrifice...";
        }
        else if (objectChar == tileImageToChar(TileImage::Bag))
        {
            message = "A plain leather bag with unknown contents...";
        }
        else if (objectChar == tileImageToChar(TileImage::Coffin))
        {
            message = "A wooden coffin that looks easy to break open...";
        }
        else if (objectChar == tileImageToChar(TileImage::StoneSpire))
        {
            message = "A large rock spire points up.";
        }
        else if (objectChar == tileImageToChar(TileImage::Lava))
        {
            message = "Lava bubbles quietly.";
        }
        else if (
            (objectChar == tileImageToChar(TileImage::Tree1)) ||
            (objectChar == tileImageToChar(TileImage::Tree2)) ||
            (objectChar == tileImageToChar(TileImage::Tree3)))
        {
            message = "This tree blocks your path.";
        }
        else if (objectChar == tileImageToChar(TileImage::Coins))
        {
            message = "A pile of coins on the ground.";
        }
        else if (objectChar == tileImageToChar(TileImage::Well))
        {
            message = "Sounds echo deep down this empty stone well.";
        }
        else if (
            (objectChar >= tileImageToChar(TileImage::Statue_Twins)) &&
            (objectChar <= tileImageToChar(TileImage::Statue_Tengu)))
        {
            // TODO have unique descriptions for each statue hinting at interactions
            message = "A stone statue.";
        }
        else if (
            (objectChar == tileImageToChar(TileImage::Wall_TopLeft)) ||
            (objectChar == tileImageToChar(TileImage::Wall_Horiz)) ||
            (objectChar == tileImageToChar(TileImage::Wall_Top)) ||
            (objectChar == tileImageToChar(TileImage::Wall_Vert)) ||
            (objectChar == tileImageToChar(TileImage::Wall_Block)))
        {
            message = "Just a wall.";
        }
        else if (objectChar == tileImageToChar(TileImage::Wall_BlockWeak))
        {
            message = "A wooden wall that looks easy to break...";
        }
        else if (
            (objectChar >= tileImageToChar(TileImage::Doorway_Wood)) &&
            (objectChar <= tileImageToChar(TileImage::Doorway_OrientalRed)))
        {
            // TODO have unique descriptions for each door hinting at interactions
            message = "A doorawy.";
        }
        else if (
            (objectChar >= tileImageToChar(TileImage::Altar_Statue)) &&
            (objectChar <= tileImageToChar(TileImage::Altar_King)))
        {
            // TODO have unique descriptions for each altar hinting at interactions
            message = "A proud stone altar keeps it's silent repose.";
        }
        else if (
            (objectChar == tileImageToChar(TileImage::Pillar_CrumbleLeft)) ||
            (objectChar == tileImageToChar(TileImage::Pillar_Rubble)) ||
            (objectChar == tileImageToChar(TileImage::Pillar_Complete)) ||
            (objectChar == tileImageToChar(TileImage::Pillar_Half)) ||
            (objectChar == tileImageToChar(TileImage::Pillar_Quarter)) ||
            (objectChar == tileImageToChar(TileImage::Pillar_CrumbleRight)))
        {
            message = "A crumbling stone column.";
        }
        else if (
            (objectChar == tileImageToChar(TileImage::Block_Emboss1)) ||
            (objectChar == tileImageToChar(TileImage::Block_Emboss2)) ||
            (objectChar == tileImageToChar(TileImage::Block_Emboss3)) ||
            (objectChar == tileImageToChar(TileImage::Block_Emboss4)))
        {
            message = "A rock wall with detailed carvings.";
        }
        else if (isTileImageMonster(tileImage))
        {
            message = "A ";
            message += toString(tileImage);
            message += " is trying to kill you!";
        }
        else if (isTileImageNpc(tileImage))
        {
            // TODO add some extra info on NPCs?  Maybe descriptions of what they look like?
            message = "A ";
            message += toString(tileImage);
            message += " stands before you.";
        }
        else
        {
            // should never get here, but not worth throwing an exception
            message = "Look Error: ";
            message += toString(tileImage);
        }

        return message;
    }

} // namespace castlecrawl
