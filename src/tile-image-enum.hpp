#ifndef TILEIMAGEENUM_HPP_INCLUDED
#define TILEIMAGEENUM_HPP_INCLUDED
//
// tile-image-enum.hpp
//
#include <cstddef>

#include <SFML/Graphics/Rect.hpp>

namespace castlecrawl
{

    // used to index so keep unsigned
    enum class TileImage : std::size_t
    {
        Empty = 0,
        Campfire,
        Inferno,
        Rock,
        RockWeak,
        Blood,
        Lava,
        Water,
        Slime,
        Stair_Up,
        Stair_Down,
        Avatar,
        Barrel,
        Door,
        DoorLocked,
        Chest,
        Coffin,
        Bag,
        Altar,
        StoneSpire,
        Key,
        HerbWeak,
        HerbNormal,
        HerbStrong,
        Wall_TopLeft,
        Wall_Horiz,
        Wall_Top,
        Wall_Vert,
        Wall_Shadow,
        Wall_Block,
        Wall_BlockWeak,
        Floor_Wood1,
        Floor_Wood2,
        Floor_Wood3,
        Floor_Wood4,
        Floor_Wood5,
        Floor_Wood6,
        Floor_Stone1,
        Floor_Stone2,
        Floor_Stone3,
        Floor_Stone4,
        Floor_Stone5,
        Floor_Stone6,
        Floor_Dirt1,
        Floor_Dirt2,
        Floor_Dirt3,
        Floor_Dirt4,
        Floor_Dirt5,
        LiquidCor_TopLeft,
        LiquidCor_TopRight,
        LiquidCor_BotLeft,
        LiquidCor_BotRight,
        LiquidRim_TopLeft,
        LiquidRim_Top,
        LiquidRim_TopRight,
        LiquidRim_Left,
        LiquidRim_Right,
        LiquidRim_BotLeft,
        LiquidRim_Bot,
        LiquidRim_BotRight
    };

    inline constexpr bool isDrawnByMapDisplay(const char ch) noexcept 
    {
        return ((ch != 'a') && (ch != 'A') && (ch != ' '));
    }

    inline constexpr TileImage charToTileImage(const char ch) noexcept
    {
        // clang-format off
        switch (ch)
        {
            case 'a':    { return TileImage::Campfire;           }
            case 'A':    { return TileImage::Inferno;            }
            case 'r':    { return TileImage::Rock;               }
            case 'R':    { return TileImage::RockWeak;           }
            case 'e':    { return TileImage::Blood;              }
            case 'l':    { return TileImage::Lava;               }
            case 'w':    { return TileImage::Water;              }
            case 'g':    { return TileImage::Slime;              }
            case 'S':    { return TileImage::Stair_Up;           }
            case 's':    { return TileImage::Stair_Down;         }
            case 'b':    { return TileImage::Barrel;             }
            case 'd':    { return TileImage::Door;               }
            case 'D':    { return TileImage::DoorLocked;         }
            case 'c':    { return TileImage::Chest;              }
            case 'k':    { return TileImage::Coffin;             }
            case '!':    { return TileImage::Bag;                }
            case '@':    { return TileImage::Altar;              }
            case '#':    { return TileImage::StoneSpire;         }
            case '$':    { return TileImage::Key;                }
            case '%':    { return TileImage::HerbWeak;           }
            case '^':    { return TileImage::HerbNormal;         }
            case '&':    { return TileImage::HerbStrong;         }
            case 'C':    { return TileImage::Wall_TopLeft;       }
            case '-':    { return TileImage::Wall_Horiz;         }
            case 'T':    { return TileImage::Wall_Top;           }
            case '|':    { return TileImage::Wall_Vert;          }
            case 'B':    { return TileImage::Wall_Block;         }
            case 'q':    { return TileImage::Wall_BlockWeak;     }
            case 'p':    { return TileImage::Avatar;             }
            case '\x0':  { return TileImage::Floor_Wood1;        }
            case '\x1':  { return TileImage::Floor_Wood2;        }
            case '\x2':  { return TileImage::Floor_Wood3;        }
            case '\x3':  { return TileImage::Floor_Wood4;        }
            case '\x4':  { return TileImage::Floor_Wood5;        }
            case '\x5':  { return TileImage::Floor_Wood6;        }
            case '\x6':  { return TileImage::Floor_Stone1;       }
            case '\x7':  { return TileImage::Floor_Stone2;       }
            case '\x8':  { return TileImage::Floor_Stone3;       }
            case '\x9':  { return TileImage::Floor_Stone4;       }
            case '\xA':  { return TileImage::Floor_Stone5;       }
            case '\xB':  { return TileImage::Floor_Stone6;       }
            case '\xC':  { return TileImage::Floor_Dirt1;        }
            case '\xD':  { return TileImage::Floor_Dirt2;        }
            case '\xE':  { return TileImage::Floor_Dirt3;        }
            case '\xF':  { return TileImage::Floor_Dirt4;        }
            case '\x10': { return TileImage::Floor_Dirt5;        }
            case '\x80': { return TileImage::LiquidCor_TopLeft;  }
            case '\x81': { return TileImage::LiquidCor_TopRight; }
            case '\x82': { return TileImage::LiquidCor_BotLeft;  }
            case '\x83': { return TileImage::LiquidCor_BotRight; }
            case '\x90': { return TileImage::LiquidRim_TopLeft;  }
            case '\x91': { return TileImage::LiquidRim_Top;      }
            case '\x92': { return TileImage::LiquidRim_TopRight; }
            case '\x93': { return TileImage::LiquidRim_Left;     }
            case '\x94': { return TileImage::LiquidRim_Right;    }
            case '\x95': { return TileImage::LiquidRim_BotLeft;  }
            case '\x96': { return TileImage::LiquidRim_Bot;      }
            case '\x97': { return TileImage::LiquidRim_BotRight; }
            case '\x98': { return TileImage::Wall_Shadow;        }
            case ' ':    
            default:     { return TileImage::Empty;              }
        }
        // clang-format on
    }

    inline const sf::IntRect tileImageToRect(const TileImage tileImage)
    {
        // clang-format off
        switch (tileImage)
        {
            case TileImage::Campfire:           { return sf::IntRect( { 64,224},{32,32}); }
            case TileImage::Rock:               { return sf::IntRect( { 96, 64},{32,32}); }
            case TileImage::RockWeak:           { return sf::IntRect( { 96, 96},{32,32}); }
            case TileImage::Blood:              { return sf::IntRect( { 96,224},{32,32}); }
            case TileImage::Lava:               { return sf::IntRect( { 32,192},{32,32}); }
            case TileImage::Water:              { return sf::IntRect( { 64,192},{32,32}); }
            case TileImage::Slime:              { return sf::IntRect( {  0,192},{32,32}); }
            case TileImage::Stair_Up:           { return sf::IntRect( {128,  0},{32,32}); }
            case TileImage::Stair_Down:         { return sf::IntRect( {128, 32},{32,32}); }
            case TileImage::Barrel:             { return sf::IntRect( { 96,  0},{32,32}); }
            case TileImage::Door:               { return sf::IntRect( {  0,224},{32,32}); }
            case TileImage::DoorLocked:         { return sf::IntRect( { 32,224},{32,32}); }
            case TileImage::Chest:              { return sf::IntRect( {128, 64},{32,32}); }
            case TileImage::Coffin:             { return sf::IntRect( {160, 64},{32,32}); }
            case TileImage::Bag:                { return sf::IntRect( {224,  0},{32,32}); }
            case TileImage::Altar:              { return sf::IntRect( {128, 96},{32,32}); }
            case TileImage::StoneSpire:         { return sf::IntRect( {160, 96},{32,32}); }
            case TileImage::Key:                { return sf::IntRect( {192,128},{32,32}); }
            case TileImage::HerbWeak:           { return sf::IntRect( {224,128},{32,32}); }
            case TileImage::HerbNormal:         { return sf::IntRect( {192,160},{32,32}); }
            case TileImage::HerbStrong:         { return sf::IntRect( {224,160},{32,32}); }
            case TileImage::Wall_TopLeft:       { return sf::IntRect( {  0,  0},{32,32}); }
            case TileImage::Wall_Horiz:         { return sf::IntRect( { 32,  0},{32,32}); }
            case TileImage::Wall_Top:           { return sf::IntRect( { 64,  0},{32,32}); }
            case TileImage::Wall_Vert:          { return sf::IntRect( {  0, 32},{32,32}); }
            case TileImage::Wall_Block:         { return sf::IntRect( { 64, 32},{32,32}); }
            case TileImage::Wall_BlockWeak:     { return sf::IntRect( { 96, 32},{32,32}); }
            case TileImage::Avatar:             { return sf::IntRect( {224,224},{32,32}); }
            case TileImage::Floor_Wood1:        { return sf::IntRect( {  0, 64},{32,32}); }
            case TileImage::Floor_Wood2:        { return sf::IntRect( { 32, 64},{32,32}); }
            case TileImage::Floor_Wood3:        { return sf::IntRect( { 64, 64},{32,32}); }
            case TileImage::Floor_Wood4:        { return sf::IntRect( {  0, 96},{32,32}); }
            case TileImage::Floor_Wood5:        { return sf::IntRect( { 32, 96},{32,32}); }
            case TileImage::Floor_Wood6:        { return sf::IntRect( { 64, 96},{32,32}); }
            case TileImage::Floor_Stone1:       { return sf::IntRect( {  0,128},{32,32}); }
            case TileImage::Floor_Stone2:       { return sf::IntRect( { 32,128},{32,32}); }
            case TileImage::Floor_Stone3:       { return sf::IntRect( { 64,128},{32,32}); }
            case TileImage::Floor_Stone4:       { return sf::IntRect( {  0,160},{32,32}); }
            case TileImage::Floor_Stone5:       { return sf::IntRect( { 32,160},{32,32}); }
            case TileImage::Floor_Stone6:       { return sf::IntRect( { 64,160},{32,32}); }
            case TileImage::Floor_Dirt1:        { return sf::IntRect( {160,  0},{32,32}); }
            case TileImage::Floor_Dirt2:        { return sf::IntRect( {192,  0},{32,32}); }
            case TileImage::Floor_Dirt3:        { return sf::IntRect( {160, 32},{32,32}); }
            case TileImage::Floor_Dirt4:        { return sf::IntRect( {192, 32},{32,32}); }
            case TileImage::Floor_Dirt5:        { return sf::IntRect( {224, 32},{32,32}); }
            case TileImage::LiquidCor_TopLeft:  { return sf::IntRect( {192, 64},{32,32}); }
            case TileImage::LiquidCor_TopRight: { return sf::IntRect( {224, 64},{32,32}); }
            case TileImage::LiquidCor_BotLeft:  { return sf::IntRect( {192, 96},{32,32}); }
            case TileImage::LiquidCor_BotRight: { return sf::IntRect( {224, 96},{32,32}); }
            case TileImage::LiquidRim_TopLeft:  { return sf::IntRect( { 96,128},{32,32}); }
            case TileImage::LiquidRim_Top:      { return sf::IntRect( {128,128},{32,32}); }
            case TileImage::LiquidRim_TopRight: { return sf::IntRect( {160,128},{32,32}); }
            case TileImage::LiquidRim_Left:     { return sf::IntRect( { 96,160},{32,32}); }
            case TileImage::LiquidRim_Right:    { return sf::IntRect( {160,160},{32,32}); }
            case TileImage::LiquidRim_BotLeft:  { return sf::IntRect( { 96,192},{32,32}); }
            case TileImage::LiquidRim_Bot:      { return sf::IntRect( {128,192},{32,32}); }
            case TileImage::LiquidRim_BotRight: { return sf::IntRect( {160,192},{32,32}); }
            case TileImage::Wall_Shadow:        { return sf::IntRect( { 32, 32},{32,32}); }
            case TileImage::Empty:
            case TileImage::Inferno:
            default:                            { return sf::IntRect( {128,160},{32,32}); }
        }
        // clang-format on
    }

} // namespace castlecrawl

#endif // CONTEXT_HPP_INCLUDED
