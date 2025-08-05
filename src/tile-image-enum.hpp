#ifndef TILEIMAGEENUM_HPP_INCLUDED
#define TILEIMAGEENUM_HPP_INCLUDED
//
// tile-image-enum.hpp
//
#include <cstddef>
#include <string_view>

#include <SFML/Graphics/Rect.hpp>

namespace castlecrawl
{

    // used to index so keep unsigned
    enum class TileImage : std::size_t
    {
        Empty = 0,
        Sign,
        FountainWater,
        FountainBlood,
        Campfire,
        Inferno,
        Rock,
        RockWeak,
        Ice,
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
        Tree1,
        Tree2,
        Tree3,

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
        LiquidRim_BotRight,

        Pillar_CrumbleLeft,
        Pillar_Rubble,
        Pillar_Complete,
        Pillar_Half,
        Pillar_Quarter,
        Pillar_CrumbleRight,

        Block_Emboss1,
        Block_Emboss2,
        Block_Emboss3,
        Block_Emboss4,

        Altar_Statue,
        Altar_Challace,
        Altar_Skull,
        Altar_Throne,
        Altar_Blood,
        Altar_Body,
        Altar_Demonic,
        Altar_Hand,
        Altar_King,

        Statue_Twins,
        Statue_Mermaid,
        Statue_Demonic,
        Statue_Wraith,
        Statue_Sword,
        Statue_Thresher,
        Statue_Orb,
        Statue_Naga,
        Statue_Imp,
        Statue_Hydra,
        Statue_Elephant,
        Statue_Dwarf,
        Statue_Dragon,
        Statue_Flamberg,
        Statue_Centaur,
        Statue_Cat,
        Statue_Angel,
        Statue_Monster,
        Statue_Princess,
        Statue_Tengu,

        Doorway_Wood,
        Doorway_WoodRune,
        Doorway_SatanicGray,
        Doorway_SatanicRed,
        Doorway_RuneOpen,
        Doorway_RuneGray,
        Doorway_RuneBlue,
        Doorway_RuneSkull,
        Doorway_MirrorLit,
        Doorway_Mirror,
        Doorway_SantaicLava,
        Doorway_Candle,
        Doorway_Ghost,
        Doorway_Snake,
        Doorway_Oriental,
        Doorway_OrientalRed,

        // monsters
        BeholderSpawn,
        SkullSlime,
        BoneDragon,
        SwampThing,
        RabidRodent,
        Bat,
        DragonWarlord,
        AquaSlime,

        SlimeBeholder,
        Cyclops,
        FleshCreeper,
        Wailing,
        CoillingViper,
        IceKnight,
        Beholder,
        RottingChomper,

        SkitterMite,
        BloodCreeper,
        WindHowler,
        GreenSnake,
        BloatedCreeper,
        MudDemon,
        Serpent,
        WalkingBeholder,

        InvisibleMan,
        Kracklin,
        Kobold,
        FireGiant,
        BeholderMite,
        RacerSnake,
        DessertSnake,
        TwoHeadedOgre,

        MothDragon,
        Catterhorror,
        CaveSpider,
        VineShambler,
        SpikeCreeper,
        SlimeShambler,
        Spider,
        SpellWalker,

        GreenWight,
        SoulEater,
        BoneHound,
        ArcaneBeholder,
        Siren,
        Specter,
        BoneHydra,
        ShadowFiend,

        StripedSnake,
        Scorpion,
        Firebrand,
        RustDevil,
        Revenant,
        WidowSpider,
        RedDemon,
        QuicksilverDragon,

        Dragon,
        Antlion,
        Quasit,
        KoboldBrute,
        SpiderHorror,
        OrangeDemon,
        Ooze,
        OctoCrawler,

        Wollynaut,
        BogSlave,
        MutantBeast,
        MoonTroll,
        ManaViper,
        Lorocyproca,
        FleshChomper,
        Juggernaut,

        ElephantDemon,
        RedJelly,
        IronGiant,
        Hippogriff,
        HellWing,
        Hellion,
        HellHound,
        GuardianCobra,

        GoldScorpion,
        GreenBullber,
        GoldenDragon,
        GiantLeech,
        GiantAmoeba,
        OrangeClamber,
        FrostGiant,
        AntCreeper,

        SunWeaver,
        SkiteWing,
        FireElemental,
        RustCrab,
        FireBat,
        WanderingEye,
        TwoHeadedGiant,
        BruteWitch,

        Draconian,
        WailingSlime,
        Madman,
        Fungosite,

        // npc
        Gnome,
        Faun,
        Elfman,
        Dwarf,

        Wiglaf,
        Human,
        RedKnight,
        Elf,
        ElfWarrior,
        GreenElf,
        GreenElfMage,
        BlueClown,

        BlueKnight,
        Spartan,
        Satyr,
        GoldKnight,
        DeepCaster,
        OldMan,
        GoldClown,
        Hag,

        CyanKnight,
        Elfnee,
        Javelinee,
        SkullSpeaker,
        FolkMage,
        Maud,
        GreenRanger,
        BookSpeaker
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
            case 'a':    { return TileImage::Campfire;              }
            case 'A':    { return TileImage::Inferno;               }
            case 'b':    { return TileImage::Barrel;                }
            case 'B':    { return TileImage::Sign;                  }
            case 'c':    { return TileImage::Chest;                 }
            case 'C':    { return TileImage::Ice;                   }
            case 'd':    { return TileImage::Door;                  }
            case 'D':    { return TileImage::DoorLocked;            }
            case 'e':    { return TileImage::Blood;                 }
            case 'E':    { return TileImage::Key;                   }
            case 'f':    { return TileImage::FountainWater;         }
            case 'F':    { return TileImage::FountainBlood;         }
            case 'g':    { return TileImage::Water;                 }
            case 'G':    { return TileImage::Slime;                 }
            case 'h':    { return TileImage::Rock;                  }
            case 'H':    { return TileImage::RockWeak;              }
            case 'i':    { return TileImage::Stair_Up;              }
            case 'I':    { return TileImage::Stair_Down;            }
            case 'j':    { return TileImage::Altar;                 }
            case 'J':    { return TileImage::Bag;                   }
            case 'k':    { return TileImage::Coffin;                }
            case 'K':    { return TileImage::StoneSpire;            }
            case 'l':    { return TileImage::Lava;                  }
            case 'L':    { return TileImage::Tree1;                 }
            case 'm':    { return TileImage::Tree2;                 }
            case 'M':    { return TileImage::Tree3;                 }

            case 'n':    { return TileImage::Statue_Twins;          }
            case 'N':    { return TileImage::Statue_Mermaid;        }
            case 'o':    { return TileImage::Statue_Demonic;        }
            case 'O':    { return TileImage::Statue_Wraith;         }
            case 'p':    { return TileImage::Statue_Sword;          }
            case 'P':    { return TileImage::Statue_Thresher;       }
            case 'q':    { return TileImage::Statue_Orb;            }
            case 'Q':    { return TileImage::Statue_Naga;           }
            case 'r':    { return TileImage::Statue_Imp;            }
            case 'R':    { return TileImage::Statue_Hydra;          }
            case 's':    { return TileImage::Statue_Elephant;       }
            case 'S':    { return TileImage::Statue_Dwarf;          }
            case 't':    { return TileImage::Statue_Dragon;         }
            case 'T':    { return TileImage::Statue_Flamberg;       }
            case 'u':    { return TileImage::Statue_Centaur;        }
            case 'U':    { return TileImage::Statue_Cat;            }
            case 'v':    { return TileImage::Statue_Angel;          }
            case 'V':    { return TileImage::Statue_Monster;        }
            case 'w':    { return TileImage::Statue_Princess;       }
            case 'W':    { return TileImage::Statue_Tengu;          }

            case 'x':    { return TileImage::Wall_TopLeft;          }
            case 'X':    { return TileImage::Wall_Horiz;            }
            case 'y':    { return TileImage::Wall_Top;              }
            case 'Y':    { return TileImage::Wall_Vert;             }
            case 'z':    { return TileImage::Wall_Block;            }
            case 'Z':    { return TileImage::Wall_BlockWeak;        }
            
            case '!':    { return TileImage::Doorway_Wood;          }
            case '"':    { return TileImage::Doorway_WoodRune;      }
            case '#':    { return TileImage::Doorway_SatanicGray;   }
            case '$':    { return TileImage::Doorway_SatanicRed;    }
            case '%':    { return TileImage::Doorway_RuneOpen;      }
            case '&':    { return TileImage::Doorway_RuneGray;      }
            case '|':    { return TileImage::Doorway_RuneBlue;      }
            case '(':    { return TileImage::Doorway_RuneSkull;     }
            case ')':    { return TileImage::Doorway_MirrorLit;     }
            case '*':    { return TileImage::Doorway_Mirror;        }
            case '+':    { return TileImage::Doorway_SantaicLava;   }
            case ',':    { return TileImage::Doorway_Candle;        }
            case '-':    { return TileImage::Doorway_Ghost;         }
            case '^':    { return TileImage::Doorway_Snake;         }
            case '/':    { return TileImage::Doorway_Oriental;      }
            case '0':    { return TileImage::Doorway_OrientalRed;   }

            case '1':    { return TileImage::Altar_Statue;          }
            case '2':    { return TileImage::Altar_Challace;        }
            case '3':    { return TileImage::Altar_Skull;           }
            case '4':    { return TileImage::Altar_Throne;          }
            case '5':    { return TileImage::Altar_Blood;           }
            case '6':    { return TileImage::Altar_Body;            }
            case '7':    { return TileImage::Altar_Demonic;         }
            case '8':    { return TileImage::Altar_Hand;            }
            case '9':    { return TileImage::Altar_King;            }

            case ':':    { return TileImage::Pillar_CrumbleLeft;    }
            case ';':    { return TileImage::Pillar_Rubble;         }
            case '<':    { return TileImage::Pillar_Complete;       }
            case '=':    { return TileImage::Pillar_Half;           }
            case '>':    { return TileImage::Pillar_Quarter;        }
            case '?':    { return TileImage::Pillar_CrumbleRight;   }

            case '@':    { return TileImage::Block_Emboss1;         }
            case '[':    { return TileImage::Block_Emboss2;         }
            case '_':    { return TileImage::Block_Emboss3;         }
            case ']':    { return TileImage::Block_Emboss4;         }

            //case '\\':
            //case '`':
            //case '{':
            //case '\'':
            //case '}';
            //case '~':
            //
            //case '\x1F':
            //case '\x7F':
                    
            case '\x1D': { return TileImage::Wall_Shadow;           }
            case '\x1E': { return TileImage::Avatar;                }

            case '\x00': { return TileImage::Floor_Wood1;           }
            case '\x01': { return TileImage::Floor_Wood2;           }
            case '\x02': { return TileImage::Floor_Wood3;           }
            case '\x03': { return TileImage::Floor_Wood4;           }
            case '\x04': { return TileImage::Floor_Wood5;           }
            case '\x05': { return TileImage::Floor_Wood6;           }
            case '\x06': { return TileImage::Floor_Stone1;          }
            case '\x07': { return TileImage::Floor_Stone2;          }
            case '\x08': { return TileImage::Floor_Stone3;          }
            case '\x09': { return TileImage::Floor_Stone4;          }
            case '\x0A': { return TileImage::Floor_Stone5;          }
            case '\x0B': { return TileImage::Floor_Stone6;          }
            case '\x0C': { return TileImage::Floor_Dirt1;           }
            case '\x0D': { return TileImage::Floor_Dirt2;           }
            case '\x0E': { return TileImage::Floor_Dirt3;           }
            case '\x0F': { return TileImage::Floor_Dirt4;           }
            case '\x10': { return TileImage::Floor_Dirt5;           }

            case '\x11': { return TileImage::LiquidCor_TopLeft;     }
            case '\x12': { return TileImage::LiquidCor_TopRight;    }
            case '\x13': { return TileImage::LiquidCor_BotLeft;     }
            case '\x14': { return TileImage::LiquidCor_BotRight;    }
            case '\x15': { return TileImage::LiquidRim_TopLeft;     }
            case '\x16': { return TileImage::LiquidRim_Top;         }
            case '\x17': { return TileImage::LiquidRim_TopRight;    }
            case '\x18': { return TileImage::LiquidRim_Left;        }
            case '\x19': { return TileImage::LiquidRim_Right;       }
            case '\x1A': { return TileImage::LiquidRim_BotLeft;     }
            case '\x1B': { return TileImage::LiquidRim_Bot;         }
            case '\x1C': { return TileImage::LiquidRim_BotRight;    }

            // monsters
            case '\x80': { return TileImage::BeholderSpawn;         }
            case '\x81': { return TileImage::SkullSlime;            }
            case '\x82': { return TileImage::BoneDragon;            }
            case '\x83': { return TileImage::SwampThing;            }
            case '\x84': { return TileImage::RabidRodent;           }
            case '\x85': { return TileImage::Bat;                   }
            case '\x86': { return TileImage::DragonWarlord;         }
            case '\x87': { return TileImage::AquaSlime;             }

            case '\x88': { return TileImage::SlimeBeholder;         }
            case '\x89': { return TileImage::Cyclops;               }
            case '\x8A': { return TileImage::FleshCreeper;          }
            case '\x8B': { return TileImage::Wailing;               }
            case '\x8C': { return TileImage::CoillingViper;         }
            case '\x8D': { return TileImage::IceKnight;             }
            case '\x8E': { return TileImage::Beholder;              }
            case '\x8F': { return TileImage::RottingChomper;        }

            case '\x90': { return TileImage::SkitterMite;           }
            case '\x91': { return TileImage::BloodCreeper;          }
            case '\x92': { return TileImage::WindHowler;            }
            case '\x93': { return TileImage::GreenSnake;            }
            case '\x94': { return TileImage::BloatedCreeper;        }
            case '\x95': { return TileImage::MudDemon;              }
            case '\x96': { return TileImage::Serpent;               }
            case '\x97': { return TileImage::WalkingBeholder;       }

            case '\x98': { return TileImage::InvisibleMan;          }
            case '\x99': { return TileImage::Kracklin;              }
            case '\x9A': { return TileImage::Kobold;                }
            case '\x9B': { return TileImage::FireGiant;             }
            case '\x9C': { return TileImage::BeholderMite;          }
            case '\x9D': { return TileImage::RacerSnake;            }
            case '\x9E': { return TileImage::DessertSnake;          }
            case '\x9F': { return TileImage::TwoHeadedOgre;         }
                        
            case '\xA0': { return TileImage::MothDragon;            }
            case '\xA1': { return TileImage::Catterhorror;          }
            case '\xA2': { return TileImage::CaveSpider;            }
            case '\xA3': { return TileImage::VineShambler;          }
            case '\xA4': { return TileImage::SpikeCreeper;          }
            case '\xA5': { return TileImage::SlimeShambler;         }
            case '\xA6': { return TileImage::Spider;                }
            case '\xA7': { return TileImage::SpellWalker;           }
                     
            case '\xA8': { return TileImage::GreenWight;            }
            case '\xA9': { return TileImage::SoulEater;             }
            case '\xAA': { return TileImage::BoneHound;             }
            case '\xAB': { return TileImage::ArcaneBeholder;        }
            case '\xAC': { return TileImage::Siren;                 }
            case '\xAD': { return TileImage::Specter;               }
            case '\xAE': { return TileImage::BoneHydra;             }
            case '\xAF': { return TileImage::ShadowFiend;           }
                     
            case '\xB0': { return TileImage::StripedSnake;          }
            case '\xB1': { return TileImage::Scorpion;              }
            case '\xB2': { return TileImage::Firebrand;             }
            case '\xB3': { return TileImage::RustDevil;             }
            case '\xB4': { return TileImage::Revenant;              }
            case '\xB5': { return TileImage::WidowSpider;           }
            case '\xB6': { return TileImage::RedDemon;              }
            case '\xB7': { return TileImage::QuicksilverDragon;     }
                     
            case '\xB8': { return TileImage::Dragon;                }
            case '\xB9': { return TileImage::Antlion;               }
            case '\xBA': { return TileImage::Quasit;                }
            case '\xBB': { return TileImage::KoboldBrute;           }
            case '\xBC': { return TileImage::SpiderHorror;          }
            case '\xBD': { return TileImage::OrangeDemon;           }
            case '\xBE': { return TileImage::Ooze;                  }
            case '\xBF': { return TileImage::OctoCrawler;           }
                     
            case '\xC0': { return TileImage::Wollynaut;             }
            case '\xC1': { return TileImage::BogSlave;              }
            case '\xC2': { return TileImage::MutantBeast;           }
            case '\xC3': { return TileImage::MoonTroll;             }
            case '\xC4': { return TileImage::ManaViper;             }
            case '\xC5': { return TileImage::Lorocyproca;           }
            case '\xC6': { return TileImage::FleshChomper;          }
            case '\xC7': { return TileImage::Juggernaut;            }
                     
            case '\xC8': { return TileImage::ElephantDemon;         }
            case '\xC9': { return TileImage::RedJelly;              }
            case '\xCA': { return TileImage::IronGiant;             }
            case '\xCB': { return TileImage::Hippogriff;            }
            case '\xCC': { return TileImage::HellWing;              }
            case '\xCD': { return TileImage::Hellion;               }
            case '\xCE': { return TileImage::HellHound;             }
            case '\xCF': { return TileImage::GuardianCobra;         }
                     
            case '\xD0': { return TileImage::GoldScorpion;          }
            case '\xD1': { return TileImage::GreenBullber;          }
            case '\xD2': { return TileImage::GoldenDragon;          }
            case '\xD3': { return TileImage::GiantLeech;            }
            case '\xD4': { return TileImage::GiantAmoeba;           }
            case '\xD5': { return TileImage::OrangeClamber;         }
            case '\xD6': { return TileImage::FrostGiant;            }
            case '\xD7': { return TileImage::AntCreeper;            }
                     
            case '\xD8': { return TileImage::SunWeaver;             }
            case '\xD9': { return TileImage::SkiteWing;             }
            case '\xDA': { return TileImage::FireElemental;         }
            case '\xDB': { return TileImage::RustCrab;              }
            case '\xDC': { return TileImage::FireBat;               }
            case '\xDD': { return TileImage::WanderingEye;          }
            case '\xDE': { return TileImage::TwoHeadedGiant;        }
            case '\xDF': { return TileImage::BruteWitch;            }
                     
            case '\xE0': { return TileImage::Draconian;             }
            case '\xE1': { return TileImage::WailingSlime;          }
            case '\xE2': { return TileImage::Madman;                }
            case '\xE3': { return TileImage::Fungosite;             }
                        
            // npc          
            case '\xE4': { return TileImage::Gnome;                 }
            case '\xE5': { return TileImage::Faun;                  }
            case '\xE6': { return TileImage::Elfman;                }
            case '\xE7': { return TileImage::Dwarf;                 }
                     
            case '\xE8': { return TileImage::Wiglaf;                }
            case '\xE9': { return TileImage::Human;                 }
            case '\xEA': { return TileImage::RedKnight;             }
            case '\xEB': { return TileImage::Elf;                   }
            case '\xEC': { return TileImage::ElfWarrior;            }
            case '\xED': { return TileImage::GreenElf;              }
            case '\xEE': { return TileImage::GreenElfMage;          }
            case '\xEF': { return TileImage::BlueClown;             }
                     
            case '\xF0': { return TileImage::BlueKnight;            }
            case '\xF1': { return TileImage::Spartan;               }
            case '\xF2': { return TileImage::Satyr;                 }
            case '\xF3': { return TileImage::GoldKnight;            }
            case '\xF4': { return TileImage::DeepCaster;            }
            case '\xF5': { return TileImage::OldMan;                }
            case '\xF6': { return TileImage::GoldClown;             }
            case '\xF7': { return TileImage::Hag;                   }
                     
            case '\xF8': { return TileImage::CyanKnight;            }
            case '\xF9': { return TileImage::Elfnee;                }
            case '\xFA': { return TileImage::Javelinee;             }
            case '\xFB': { return TileImage::SkullSpeaker;          }
            case '\xFC': { return TileImage::FolkMage;              }
            case '\xFD': { return TileImage::Maud;                  }
            case '\xFE': { return TileImage::GreenRanger;           }
            case '\xFF': { return TileImage::BookSpeaker;           }

            case ' ':
            default:     { return TileImage::Empty;                 }
        }
        // clang-format on
    }

    inline constexpr char tileImageToChar(const TileImage t_image) noexcept
    {
        // clang-format off
        switch (t_image)
        {
            case TileImage::Campfire:            { return 'a'; }
            case TileImage::Inferno:             { return 'A'; }
            case TileImage::Barrel:              { return 'b'; }
            case TileImage::Sign:                { return 'B'; }
            case TileImage::Chest:               { return 'c'; }
            case TileImage::Ice:                 { return 'C'; }
            case TileImage::Door:                { return 'd'; }
            case TileImage::DoorLocked:          { return 'D'; }
            case TileImage::Blood:               { return 'e'; }
            case TileImage::Key:                 { return 'E'; }
            case TileImage::FountainWater:       { return 'f'; }
            case TileImage::FountainBlood:       { return 'F'; }
            case TileImage::Water:               { return 'g'; }
            case TileImage::Slime:               { return 'G'; }
            case TileImage::Rock:                { return 'h'; }
            case TileImage::RockWeak:            { return 'H'; }
            case TileImage::Stair_Up:            { return 'i'; }
            case TileImage::Stair_Down:          { return 'I'; }
            case TileImage::Altar:               { return 'j'; }
            case TileImage::Bag:                 { return 'J'; }
            case TileImage::Coffin:              { return 'k'; }
            case TileImage::StoneSpire:          { return 'K'; }
            case TileImage::Lava:                { return 'l'; }
            case TileImage::Tree1:               { return 'L'; }
            case TileImage::Tree2:               { return 'm'; }
            case TileImage::Tree3:               { return 'M'; }

            case TileImage::Statue_Twins:        { return 'n'; }
            case TileImage::Statue_Mermaid:      { return 'N'; }
            case TileImage::Statue_Demonic:      { return 'o'; }
            case TileImage::Statue_Wraith:       { return 'O'; }
            case TileImage::Statue_Sword:        { return 'p'; }
            case TileImage::Statue_Thresher:     { return 'P'; }
            case TileImage::Statue_Orb:          { return 'q'; }
            case TileImage::Statue_Naga:         { return 'Q'; }
            case TileImage::Statue_Imp:          { return 'r'; }
            case TileImage::Statue_Hydra:        { return 'R'; }
            case TileImage::Statue_Elephant:     { return 's'; }
            case TileImage::Statue_Dwarf:        { return 'S'; }
            case TileImage::Statue_Dragon:       { return 't'; }
            case TileImage::Statue_Flamberg:     { return 'T'; }
            case TileImage::Statue_Centaur:      { return 'u'; }
            case TileImage::Statue_Cat:          { return 'U'; }
            case TileImage::Statue_Angel:        { return 'v'; }
            case TileImage::Statue_Monster:      { return 'V'; }
            case TileImage::Statue_Princess:     { return 'w'; }
            case TileImage::Statue_Tengu:        { return 'W'; }

            case TileImage::Wall_TopLeft:        { return 'x'; }
            case TileImage::Wall_Horiz:          { return 'X'; }
            case TileImage::Wall_Top:            { return 'y'; }
            case TileImage::Wall_Vert:           { return 'Y'; }
            case TileImage::Wall_Block:          { return 'z'; }
            case TileImage::Wall_BlockWeak:      { return 'Z'; }

            case TileImage::Doorway_Wood:        { return '!'; }
            case TileImage::Doorway_WoodRune:    { return '"'; }
            case TileImage::Doorway_SatanicGray: { return '#'; }
            case TileImage::Doorway_SatanicRed:  { return '$'; }
            case TileImage::Doorway_RuneOpen:    { return '%'; }
            case TileImage::Doorway_RuneGray:    { return '&'; }
            case TileImage::Doorway_RuneBlue:    { return '|'; }
            case TileImage::Doorway_RuneSkull:   { return '('; }
            case TileImage::Doorway_MirrorLit:   { return ')'; }
            case TileImage::Doorway_Mirror:      { return '*'; }
            case TileImage::Doorway_SantaicLava: { return '+'; }
            case TileImage::Doorway_Candle:      { return ','; }
            case TileImage::Doorway_Ghost:       { return '-'; }
            case TileImage::Doorway_Snake:       { return '^'; }
            case TileImage::Doorway_Oriental:    { return '/'; }
            case TileImage::Doorway_OrientalRed: { return '0'; }

            case TileImage::Altar_Statue:        { return '1'; }
            case TileImage::Altar_Challace:      { return '2'; }
            case TileImage::Altar_Skull:         { return '3'; }
            case TileImage::Altar_Throne:        { return '4'; }
            case TileImage::Altar_Blood:         { return '5'; }
            case TileImage::Altar_Body:          { return '6'; }
            case TileImage::Altar_Demonic:       { return '7'; }
            case TileImage::Altar_Hand:          { return '8'; }
            case TileImage::Altar_King:          { return '9'; }

            case TileImage::Pillar_CrumbleLeft:  { return ':'; }
            case TileImage::Pillar_Rubble:       { return ';'; }
            case TileImage::Pillar_Complete:     { return '<'; }
            case TileImage::Pillar_Half:         { return '='; }
            case TileImage::Pillar_Quarter:      { return '>'; }
            case TileImage::Pillar_CrumbleRight: { return '?'; }

            case TileImage::Block_Emboss1:       { return '@'; }
            case TileImage::Block_Emboss2:       { return '['; }
            case TileImage::Block_Emboss3:       { return '_'; }
            case TileImage::Block_Emboss4:       { return ']'; }

            case TileImage::Wall_Shadow:         { return '\x1D'; }
            case TileImage::Avatar:              { return '\x1E'; }

            case TileImage::Floor_Wood1:         { return '\x00'; }
            case TileImage::Floor_Wood2:         { return '\x01'; }
            case TileImage::Floor_Wood3:         { return '\x02'; }
            case TileImage::Floor_Wood4:         { return '\x03'; }
            case TileImage::Floor_Wood5:         { return '\x04'; }
            case TileImage::Floor_Wood6:         { return '\x05'; }
            case TileImage::Floor_Stone1:        { return '\x06'; }
            case TileImage::Floor_Stone2:        { return '\x07'; }
            case TileImage::Floor_Stone3:        { return '\x08'; }
            case TileImage::Floor_Stone4:        { return '\x09'; }
            case TileImage::Floor_Stone5:        { return '\x0A'; }
            case TileImage::Floor_Stone6:        { return '\x0B'; }
            case TileImage::Floor_Dirt1:         { return '\x0C'; }
            case TileImage::Floor_Dirt2:         { return '\x0D'; }
            case TileImage::Floor_Dirt3:         { return '\x0E'; }
            case TileImage::Floor_Dirt4:         { return '\x0F'; }
            case TileImage::Floor_Dirt5:         { return '\x10'; }

            case TileImage::LiquidCor_TopLeft:   { return '\x11'; }
            case TileImage::LiquidCor_TopRight:  { return '\x12'; }
            case TileImage::LiquidCor_BotLeft:   { return '\x13'; }
            case TileImage::LiquidCor_BotRight:  { return '\x14'; }
            case TileImage::LiquidRim_TopLeft:   { return '\x15'; }
            case TileImage::LiquidRim_Top:       { return '\x16'; }
            case TileImage::LiquidRim_TopRight:  { return '\x17'; }
            case TileImage::LiquidRim_Left:      { return '\x18'; }
            case TileImage::LiquidRim_Right:     { return '\x19'; }
            case TileImage::LiquidRim_BotLeft:   { return '\x1A'; }
            case TileImage::LiquidRim_Bot:       { return '\x1B'; }
            case TileImage::LiquidRim_BotRight:  { return '\x1C'; }

            // monsters
            case TileImage::BeholderSpawn:       { return '\x80'; }
            case TileImage::SkullSlime:          { return '\x81'; }
            case TileImage::BoneDragon:          { return '\x82'; }
            case TileImage::SwampThing:          { return '\x83'; }
            case TileImage::RabidRodent:         { return '\x84'; }
            case TileImage::Bat:                 { return '\x85'; }
            case TileImage::DragonWarlord:       { return '\x86'; }
            case TileImage::AquaSlime:           { return '\x87'; }

            case TileImage::SlimeBeholder:       { return '\x88'; }
            case TileImage::Cyclops:             { return '\x89'; }
            case TileImage::FleshCreeper:        { return '\x8A'; }
            case TileImage::Wailing:             { return '\x8B'; }
            case TileImage::CoillingViper:       { return '\x8C'; }
            case TileImage::IceKnight:           { return '\x8D'; }
            case TileImage::Beholder:            { return '\x8E'; }
            case TileImage::RottingChomper:      { return '\x8F'; }

            case TileImage::SkitterMite:         { return '\x90'; }
            case TileImage::BloodCreeper:        { return '\x91'; }
            case TileImage::WindHowler:          { return '\x92'; }
            case TileImage::GreenSnake:          { return '\x93'; }
            case TileImage::BloatedCreeper:      { return '\x94'; }
            case TileImage::MudDemon:            { return '\x95'; }
            case TileImage::Serpent:             { return '\x96'; }
            case TileImage::WalkingBeholder:     { return '\x97'; }

            case TileImage::InvisibleMan:        { return '\x98'; }
            case TileImage::Kracklin:            { return '\x99'; }
            case TileImage::Kobold:              { return '\x9A'; }
            case TileImage::FireGiant:           { return '\x9B'; }
            case TileImage::BeholderMite:        { return '\x9C'; }
            case TileImage::RacerSnake:          { return '\x9D'; }
            case TileImage::DessertSnake:        { return '\x9E'; }
            case TileImage::TwoHeadedOgre:       { return '\x9F'; }
    ;
            case TileImage::MothDragon:          { return '\xA0'; }
            case TileImage::Catterhorror:        { return '\xA1'; }
            case TileImage::CaveSpider:          { return '\xA2'; }
            case TileImage::VineShambler:        { return '\xA3'; }
            case TileImage::SpikeCreeper:        { return '\xA4'; }
            case TileImage::SlimeShambler:       { return '\xA5'; }
            case TileImage::Spider:              { return '\xA6'; }
            case TileImage::SpellWalker:         { return '\xA7'; }

            case TileImage::GreenWight:          { return '\xA8'; }
            case TileImage::SoulEater:           { return '\xA9'; }
            case TileImage::BoneHound:           { return '\xAA'; }
            case TileImage::ArcaneBeholder:      { return '\xAB'; }
            case TileImage::Siren:               { return '\xAC'; }
            case TileImage::Specter:             { return '\xAD'; }
            case TileImage::BoneHydra:           { return '\xAE'; }
            case TileImage::ShadowFiend:         { return '\xAF'; }
                     
            case TileImage::StripedSnake:        { return '\xB0'; }
            case TileImage::Scorpion:            { return '\xB1'; }
            case TileImage::Firebrand:           { return '\xB2'; }
            case TileImage::RustDevil:           { return '\xB3'; }
            case TileImage::Revenant:            { return '\xB4'; }
            case TileImage::WidowSpider:         { return '\xB5'; }
            case TileImage::RedDemon:            { return '\xB6'; }
            case TileImage::QuicksilverDragon:   { return '\xB7'; }

            case TileImage::Dragon:              { return '\xB8'; }
            case TileImage::Antlion:             { return '\xB9'; }
            case TileImage::Quasit:              { return '\xBA'; }
            case TileImage::KoboldBrute:         { return '\xBB'; }
            case TileImage::SpiderHorror:        { return '\xBC'; }
            case TileImage::OrangeDemon:         { return '\xBD'; }
            case TileImage::Ooze:                { return '\xBE'; }
            case TileImage::OctoCrawler:         { return '\xBF'; }

            case TileImage::Wollynaut:           { return '\xC0'; }
            case TileImage::BogSlave:            { return '\xC1'; }
            case TileImage::MutantBeast:         { return '\xC2'; }
            case TileImage::MoonTroll:           { return '\xC3'; }
            case TileImage::ManaViper:           { return '\xC4'; }
            case TileImage::Lorocyproca:         { return '\xC5'; }
            case TileImage::FleshChomper:        { return '\xC6'; }
            case TileImage::Juggernaut:          { return '\xC7'; }

            case TileImage::ElephantDemon:       { return '\xC8'; }
            case TileImage::RedJelly:            { return '\xC9'; }
            case TileImage::IronGiant:           { return '\xCA'; }
            case TileImage::Hippogriff:          { return '\xCB'; }
            case TileImage::HellWing:            { return '\xCC'; }
            case TileImage::Hellion:             { return '\xCD'; }
            case TileImage::HellHound:           { return '\xCE'; }
            case TileImage::GuardianCobra:       { return '\xCF'; }

            case TileImage::GoldScorpion:        { return '\xD0'; }
            case TileImage::GreenBullber:        { return '\xD1'; }
            case TileImage::GoldenDragon:        { return '\xD2'; }
            case TileImage::GiantLeech:          { return '\xD3'; }
            case TileImage::GiantAmoeba:         { return '\xD4'; }
            case TileImage::OrangeClamber:       { return '\xD5'; }
            case TileImage::FrostGiant:          { return '\xD6'; }
            case TileImage::AntCreeper:          { return '\xD7'; }

            case TileImage::SunWeaver:           { return '\xD8'; }
            case TileImage::SkiteWing:           { return '\xD9'; }
            case TileImage::FireElemental:       { return '\xDA'; }
            case TileImage::RustCrab:            { return '\xDB'; }
            case TileImage::FireBat:             { return '\xDC'; }
            case TileImage::WanderingEye:        { return '\xDD'; }
            case TileImage::TwoHeadedGiant:      { return '\xDE'; }
            case TileImage::BruteWitch:          { return '\xDF'; }
                     
            case TileImage::Draconian:           { return '\xE0'; }
            case TileImage::WailingSlime:        { return '\xE1'; }
            case TileImage::Madman:              { return '\xE2'; }
            case TileImage::Fungosite:           { return '\xE3'; }
                        
            // npc
            case TileImage::Gnome:               { return '\xE4'; }
            case TileImage::Faun:                { return '\xE5'; }
            case TileImage::Elfman:              { return '\xE6'; }
            case TileImage::Dwarf:               { return '\xE7'; }

            case TileImage::Wiglaf:              { return '\xE8'; }
            case TileImage::Human:               { return '\xE9'; }
            case TileImage::RedKnight:           { return '\xEA'; }
            case TileImage::Elf:                 { return '\xEB'; }
            case TileImage::ElfWarrior:          { return '\xEC'; }
            case TileImage::GreenElf:            { return '\xED'; }
            case TileImage::GreenElfMage:        { return '\xEE'; }
            case TileImage::BlueClown:           { return '\xEF'; }

            case TileImage::BlueKnight:          { return '\xF0'; }
            case TileImage::Spartan:             { return '\xF1'; }
            case TileImage::Satyr:               { return '\xF2'; }
            case TileImage::GoldKnight:          { return '\xF3'; }
            case TileImage::DeepCaster:          { return '\xF4'; }
            case TileImage::OldMan:              { return '\xF5'; }
            case TileImage::GoldClown:           { return '\xF6'; }
            case TileImage::Hag:                 { return '\xF7'; }

            case TileImage::CyanKnight:          { return '\xF8'; }
            case TileImage::Elfnee:              { return '\xF9'; }
            case TileImage::Javelinee:           { return '\xFA'; }
            case TileImage::SkullSpeaker:        { return '\xFB'; }
            case TileImage::FolkMage:            { return '\xFC'; }
            case TileImage::Maud:                { return '\xFD'; }
            case TileImage::GreenRanger:         { return '\xFE'; }
            case TileImage::BookSpeaker:         { return '\xFF'; }

            case TileImage::Empty:
            default:                             { return ' '; }
        }
        // clang-format on
    }

    inline constexpr bool isTileImageMonster(const TileImage t_image) noexcept
    {
        // clang-format off
        switch (t_image)
        {
            // monsters
            case TileImage::BeholderSpawn:       
            case TileImage::SkullSlime:          
            case TileImage::BoneDragon:          
            case TileImage::SwampThing:          
            case TileImage::RabidRodent:         
            case TileImage::Bat:                 
            case TileImage::DragonWarlord:       
            case TileImage::AquaSlime:           

            case TileImage::SlimeBeholder:       
            case TileImage::Cyclops:             
            case TileImage::FleshCreeper:        
            case TileImage::Wailing:             
            case TileImage::CoillingViper:       
            case TileImage::IceKnight:           
            case TileImage::Beholder:            
            case TileImage::RottingChomper:      

            case TileImage::SkitterMite:         
            case TileImage::BloodCreeper:        
            case TileImage::WindHowler:          
            case TileImage::GreenSnake:          
            case TileImage::BloatedCreeper:      
            case TileImage::MudDemon:            
            case TileImage::Serpent:             
            case TileImage::WalkingBeholder:     

            case TileImage::InvisibleMan:        
            case TileImage::Kracklin:            
            case TileImage::Kobold:              
            case TileImage::FireGiant:           
            case TileImage::BeholderMite:        
            case TileImage::RacerSnake:          
            case TileImage::DessertSnake:        
            case TileImage::TwoHeadedOgre:       
    ;
            case TileImage::MothDragon:          
            case TileImage::Catterhorror:        
            case TileImage::CaveSpider:          
            case TileImage::VineShambler:        
            case TileImage::SpikeCreeper:        
            case TileImage::SlimeShambler:       
            case TileImage::Spider:              
            case TileImage::SpellWalker:         

            case TileImage::GreenWight:          
            case TileImage::SoulEater:           
            case TileImage::BoneHound:           
            case TileImage::ArcaneBeholder:      
            case TileImage::Siren:               
            case TileImage::Specter:             
            case TileImage::BoneHydra:           
            case TileImage::ShadowFiend:         
                     
            case TileImage::StripedSnake:        
            case TileImage::Scorpion:            
            case TileImage::Firebrand:           
            case TileImage::RustDevil:           
            case TileImage::Revenant:            
            case TileImage::WidowSpider:         
            case TileImage::RedDemon:            
            case TileImage::QuicksilverDragon:   

            case TileImage::Dragon:              
            case TileImage::Antlion:             
            case TileImage::Quasit:              
            case TileImage::KoboldBrute:         
            case TileImage::SpiderHorror:        
            case TileImage::OrangeDemon:         
            case TileImage::Ooze:                
            case TileImage::OctoCrawler:         

            case TileImage::Wollynaut:           
            case TileImage::BogSlave:            
            case TileImage::MutantBeast:         
            case TileImage::MoonTroll:           
            case TileImage::ManaViper:           
            case TileImage::Lorocyproca:         
            case TileImage::FleshChomper:        
            case TileImage::Juggernaut:          

            case TileImage::ElephantDemon:       
            case TileImage::RedJelly:            
            case TileImage::IronGiant:           
            case TileImage::Hippogriff:          
            case TileImage::HellWing:            
            case TileImage::Hellion:             
            case TileImage::HellHound:           
            case TileImage::GuardianCobra:       

            case TileImage::GoldScorpion:        
            case TileImage::GreenBullber:        
            case TileImage::GoldenDragon:        
            case TileImage::GiantLeech:          
            case TileImage::GiantAmoeba:         
            case TileImage::OrangeClamber:       
            case TileImage::FrostGiant:          
            case TileImage::AntCreeper:          

            case TileImage::SunWeaver:           
            case TileImage::SkiteWing:           
            case TileImage::FireElemental:       
            case TileImage::RustCrab:            
            case TileImage::FireBat:             
            case TileImage::WanderingEye:        
            case TileImage::TwoHeadedGiant:      
            case TileImage::BruteWitch:          
                     
            case TileImage::Draconian:           
            case TileImage::WailingSlime:        
            case TileImage::Madman:              
            case TileImage::Fungosite:           { return true; }
                        
            // npc
            case TileImage::Gnome:               
            case TileImage::Faun:                
            case TileImage::Elfman:              
            case TileImage::Dwarf:               

            case TileImage::Wiglaf:              
            case TileImage::Human:               
            case TileImage::RedKnight:           
            case TileImage::Elf:                 
            case TileImage::ElfWarrior:          
            case TileImage::GreenElf:            
            case TileImage::GreenElfMage:        
            case TileImage::BlueClown:           

            case TileImage::BlueKnight:          
            case TileImage::Spartan:             
            case TileImage::Satyr:               
            case TileImage::GoldKnight:          
            case TileImage::DeepCaster:          
            case TileImage::OldMan:              
            case TileImage::GoldClown:           
            case TileImage::Hag:                 

            case TileImage::CyanKnight:          
            case TileImage::Elfnee:              
            case TileImage::Javelinee:           
            case TileImage::SkullSpeaker:        
            case TileImage::FolkMage:            
            case TileImage::Maud:                
            case TileImage::GreenRanger:         
            case TileImage::BookSpeaker:       

            case TileImage::Campfire:            
            case TileImage::Inferno:             
            case TileImage::Barrel:              
            case TileImage::Sign:                
            case TileImage::Chest:               
            case TileImage::Ice:                 
            case TileImage::Door:                
            case TileImage::DoorLocked:          
            case TileImage::Blood:               
            case TileImage::Key:                 
            case TileImage::FountainWater:       
            case TileImage::FountainBlood:       
            case TileImage::Water:               
            case TileImage::Slime:               
            case TileImage::Rock:                
            case TileImage::RockWeak:            
            case TileImage::Stair_Up:            
            case TileImage::Stair_Down:          
            case TileImage::Altar:               
            case TileImage::Bag:                 
            case TileImage::Coffin:              
            case TileImage::StoneSpire:          
            case TileImage::Lava:                
            case TileImage::Tree1:               
            case TileImage::Tree2:               
            case TileImage::Tree3:               

            case TileImage::Statue_Twins:        
            case TileImage::Statue_Mermaid:      
            case TileImage::Statue_Demonic:      
            case TileImage::Statue_Wraith:       
            case TileImage::Statue_Sword:        
            case TileImage::Statue_Thresher:     
            case TileImage::Statue_Orb:          
            case TileImage::Statue_Naga:         
            case TileImage::Statue_Imp:          
            case TileImage::Statue_Hydra:        
            case TileImage::Statue_Elephant:     
            case TileImage::Statue_Dwarf:        
            case TileImage::Statue_Dragon:       
            case TileImage::Statue_Flamberg:     
            case TileImage::Statue_Centaur:      
            case TileImage::Statue_Cat:          
            case TileImage::Statue_Angel:        
            case TileImage::Statue_Monster:      
            case TileImage::Statue_Princess:     
            case TileImage::Statue_Tengu:        

            case TileImage::Wall_TopLeft:        
            case TileImage::Wall_Horiz:          
            case TileImage::Wall_Top:            
            case TileImage::Wall_Vert:           
            case TileImage::Wall_Block:          
            case TileImage::Wall_BlockWeak:      

            case TileImage::Doorway_Wood:        
            case TileImage::Doorway_WoodRune:    
            case TileImage::Doorway_SatanicGray: 
            case TileImage::Doorway_SatanicRed:  
            case TileImage::Doorway_RuneOpen:    
            case TileImage::Doorway_RuneGray:    
            case TileImage::Doorway_RuneBlue:    
            case TileImage::Doorway_RuneSkull:   
            case TileImage::Doorway_MirrorLit:   
            case TileImage::Doorway_Mirror:      
            case TileImage::Doorway_SantaicLava: 
            case TileImage::Doorway_Candle:      
            case TileImage::Doorway_Ghost:       
            case TileImage::Doorway_Snake:       
            case TileImage::Doorway_Oriental:    
            case TileImage::Doorway_OrientalRed: 

            case TileImage::Altar_Statue:        
            case TileImage::Altar_Challace:      
            case TileImage::Altar_Skull:         
            case TileImage::Altar_Throne:        
            case TileImage::Altar_Blood:         
            case TileImage::Altar_Body:          
            case TileImage::Altar_Demonic:       
            case TileImage::Altar_Hand:          
            case TileImage::Altar_King:          

            case TileImage::Pillar_CrumbleLeft:  
            case TileImage::Pillar_Rubble:       
            case TileImage::Pillar_Complete:     
            case TileImage::Pillar_Half:         
            case TileImage::Pillar_Quarter:      
            case TileImage::Pillar_CrumbleRight: 

            case TileImage::Block_Emboss1:       
            case TileImage::Block_Emboss2:       
            case TileImage::Block_Emboss3:       
            case TileImage::Block_Emboss4:       

            case TileImage::Wall_Shadow:         
            case TileImage::Avatar:              

            case TileImage::Floor_Wood1:         
            case TileImage::Floor_Wood2:         
            case TileImage::Floor_Wood3:         
            case TileImage::Floor_Wood4:         
            case TileImage::Floor_Wood5:         
            case TileImage::Floor_Wood6:         
            case TileImage::Floor_Stone1:        
            case TileImage::Floor_Stone2:        
            case TileImage::Floor_Stone3:        
            case TileImage::Floor_Stone4:        
            case TileImage::Floor_Stone5:        
            case TileImage::Floor_Stone6:        
            case TileImage::Floor_Dirt1:         
            case TileImage::Floor_Dirt2:         
            case TileImage::Floor_Dirt3:         
            case TileImage::Floor_Dirt4:         
            case TileImage::Floor_Dirt5:         

            case TileImage::LiquidCor_TopLeft:   
            case TileImage::LiquidCor_TopRight:  
            case TileImage::LiquidCor_BotLeft:   
            case TileImage::LiquidCor_BotRight:  
            case TileImage::LiquidRim_TopLeft:   
            case TileImage::LiquidRim_Top:       
            case TileImage::LiquidRim_TopRight:  
            case TileImage::LiquidRim_Left:      
            case TileImage::LiquidRim_Right:     
            case TileImage::LiquidRim_BotLeft:   
            case TileImage::LiquidRim_Bot:       
            case TileImage::LiquidRim_BotRight:  

            case TileImage::Empty:
            default:                             { return false; }
        }
        // clang-format on
    }

    inline constexpr bool isTileImageNPC(const TileImage t_image) noexcept
    {
        // clang-format off
        switch (t_image)
        {
            // monsters
            case TileImage::BeholderSpawn:       
            case TileImage::SkullSlime:          
            case TileImage::BoneDragon:          
            case TileImage::SwampThing:          
            case TileImage::RabidRodent:         
            case TileImage::Bat:                 
            case TileImage::DragonWarlord:       
            case TileImage::AquaSlime:           

            case TileImage::SlimeBeholder:       
            case TileImage::Cyclops:             
            case TileImage::FleshCreeper:        
            case TileImage::Wailing:             
            case TileImage::CoillingViper:       
            case TileImage::IceKnight:           
            case TileImage::Beholder:            
            case TileImage::RottingChomper:      

            case TileImage::SkitterMite:         
            case TileImage::BloodCreeper:        
            case TileImage::WindHowler:          
            case TileImage::GreenSnake:          
            case TileImage::BloatedCreeper:      
            case TileImage::MudDemon:            
            case TileImage::Serpent:             
            case TileImage::WalkingBeholder:     

            case TileImage::InvisibleMan:        
            case TileImage::Kracklin:            
            case TileImage::Kobold:              
            case TileImage::FireGiant:           
            case TileImage::BeholderMite:        
            case TileImage::RacerSnake:          
            case TileImage::DessertSnake:        
            case TileImage::TwoHeadedOgre:       
    ;
            case TileImage::MothDragon:          
            case TileImage::Catterhorror:        
            case TileImage::CaveSpider:          
            case TileImage::VineShambler:        
            case TileImage::SpikeCreeper:        
            case TileImage::SlimeShambler:       
            case TileImage::Spider:              
            case TileImage::SpellWalker:         

            case TileImage::GreenWight:          
            case TileImage::SoulEater:           
            case TileImage::BoneHound:           
            case TileImage::ArcaneBeholder:      
            case TileImage::Siren:               
            case TileImage::Specter:             
            case TileImage::BoneHydra:           
            case TileImage::ShadowFiend:         
                     
            case TileImage::StripedSnake:        
            case TileImage::Scorpion:            
            case TileImage::Firebrand:           
            case TileImage::RustDevil:           
            case TileImage::Revenant:            
            case TileImage::WidowSpider:         
            case TileImage::RedDemon:            
            case TileImage::QuicksilverDragon:   

            case TileImage::Dragon:              
            case TileImage::Antlion:             
            case TileImage::Quasit:              
            case TileImage::KoboldBrute:         
            case TileImage::SpiderHorror:        
            case TileImage::OrangeDemon:         
            case TileImage::Ooze:                
            case TileImage::OctoCrawler:         

            case TileImage::Wollynaut:           
            case TileImage::BogSlave:            
            case TileImage::MutantBeast:         
            case TileImage::MoonTroll:           
            case TileImage::ManaViper:           
            case TileImage::Lorocyproca:         
            case TileImage::FleshChomper:        
            case TileImage::Juggernaut:          

            case TileImage::ElephantDemon:       
            case TileImage::RedJelly:            
            case TileImage::IronGiant:           
            case TileImage::Hippogriff:          
            case TileImage::HellWing:            
            case TileImage::Hellion:             
            case TileImage::HellHound:           
            case TileImage::GuardianCobra:       

            case TileImage::GoldScorpion:        
            case TileImage::GreenBullber:        
            case TileImage::GoldenDragon:        
            case TileImage::GiantLeech:          
            case TileImage::GiantAmoeba:         
            case TileImage::OrangeClamber:       
            case TileImage::FrostGiant:          
            case TileImage::AntCreeper:          

            case TileImage::SunWeaver:           
            case TileImage::SkiteWing:           
            case TileImage::FireElemental:       
            case TileImage::RustCrab:            
            case TileImage::FireBat:             
            case TileImage::WanderingEye:        
            case TileImage::TwoHeadedGiant:      
            case TileImage::BruteWitch:          
                     
            case TileImage::Draconian:           
            case TileImage::WailingSlime:        
            case TileImage::Madman:              
            case TileImage::Fungosite:           { return false; }
                        
            // npc
            case TileImage::Gnome:               
            case TileImage::Faun:                
            case TileImage::Elfman:              
            case TileImage::Dwarf:               

            case TileImage::Wiglaf:              
            case TileImage::Human:               
            case TileImage::RedKnight:           
            case TileImage::Elf:                 
            case TileImage::ElfWarrior:          
            case TileImage::GreenElf:            
            case TileImage::GreenElfMage:        
            case TileImage::BlueClown:           

            case TileImage::BlueKnight:          
            case TileImage::Spartan:             
            case TileImage::Satyr:               
            case TileImage::GoldKnight:          
            case TileImage::DeepCaster:          
            case TileImage::OldMan:              
            case TileImage::GoldClown:           
            case TileImage::Hag:                 

            case TileImage::CyanKnight:          
            case TileImage::Elfnee:              
            case TileImage::Javelinee:           
            case TileImage::SkullSpeaker:        
            case TileImage::FolkMage:            
            case TileImage::Maud:                
            case TileImage::GreenRanger:         
            case TileImage::BookSpeaker:        { return true; }

            case TileImage::Campfire:            
            case TileImage::Inferno:             
            case TileImage::Barrel:              
            case TileImage::Sign:                
            case TileImage::Chest:               
            case TileImage::Ice:                 
            case TileImage::Door:                
            case TileImage::DoorLocked:          
            case TileImage::Blood:               
            case TileImage::Key:                 
            case TileImage::FountainWater:       
            case TileImage::FountainBlood:       
            case TileImage::Water:               
            case TileImage::Slime:               
            case TileImage::Rock:                
            case TileImage::RockWeak:            
            case TileImage::Stair_Up:            
            case TileImage::Stair_Down:          
            case TileImage::Altar:               
            case TileImage::Bag:                 
            case TileImage::Coffin:              
            case TileImage::StoneSpire:          
            case TileImage::Lava:                
            case TileImage::Tree1:               
            case TileImage::Tree2:               
            case TileImage::Tree3:               

            case TileImage::Statue_Twins:        
            case TileImage::Statue_Mermaid:      
            case TileImage::Statue_Demonic:      
            case TileImage::Statue_Wraith:       
            case TileImage::Statue_Sword:        
            case TileImage::Statue_Thresher:     
            case TileImage::Statue_Orb:          
            case TileImage::Statue_Naga:         
            case TileImage::Statue_Imp:          
            case TileImage::Statue_Hydra:        
            case TileImage::Statue_Elephant:     
            case TileImage::Statue_Dwarf:        
            case TileImage::Statue_Dragon:       
            case TileImage::Statue_Flamberg:     
            case TileImage::Statue_Centaur:      
            case TileImage::Statue_Cat:          
            case TileImage::Statue_Angel:        
            case TileImage::Statue_Monster:      
            case TileImage::Statue_Princess:     
            case TileImage::Statue_Tengu:        

            case TileImage::Wall_TopLeft:        
            case TileImage::Wall_Horiz:          
            case TileImage::Wall_Top:            
            case TileImage::Wall_Vert:           
            case TileImage::Wall_Block:          
            case TileImage::Wall_BlockWeak:      

            case TileImage::Doorway_Wood:        
            case TileImage::Doorway_WoodRune:    
            case TileImage::Doorway_SatanicGray: 
            case TileImage::Doorway_SatanicRed:  
            case TileImage::Doorway_RuneOpen:    
            case TileImage::Doorway_RuneGray:    
            case TileImage::Doorway_RuneBlue:    
            case TileImage::Doorway_RuneSkull:   
            case TileImage::Doorway_MirrorLit:   
            case TileImage::Doorway_Mirror:      
            case TileImage::Doorway_SantaicLava: 
            case TileImage::Doorway_Candle:      
            case TileImage::Doorway_Ghost:       
            case TileImage::Doorway_Snake:       
            case TileImage::Doorway_Oriental:    
            case TileImage::Doorway_OrientalRed: 

            case TileImage::Altar_Statue:        
            case TileImage::Altar_Challace:      
            case TileImage::Altar_Skull:         
            case TileImage::Altar_Throne:        
            case TileImage::Altar_Blood:         
            case TileImage::Altar_Body:          
            case TileImage::Altar_Demonic:       
            case TileImage::Altar_Hand:          
            case TileImage::Altar_King:          

            case TileImage::Pillar_CrumbleLeft:  
            case TileImage::Pillar_Rubble:       
            case TileImage::Pillar_Complete:     
            case TileImage::Pillar_Half:         
            case TileImage::Pillar_Quarter:      
            case TileImage::Pillar_CrumbleRight: 

            case TileImage::Block_Emboss1:       
            case TileImage::Block_Emboss2:       
            case TileImage::Block_Emboss3:       
            case TileImage::Block_Emboss4:       

            case TileImage::Wall_Shadow:         
            case TileImage::Avatar:              

            case TileImage::Floor_Wood1:         
            case TileImage::Floor_Wood2:         
            case TileImage::Floor_Wood3:         
            case TileImage::Floor_Wood4:         
            case TileImage::Floor_Wood5:         
            case TileImage::Floor_Wood6:         
            case TileImage::Floor_Stone1:        
            case TileImage::Floor_Stone2:        
            case TileImage::Floor_Stone3:        
            case TileImage::Floor_Stone4:        
            case TileImage::Floor_Stone5:        
            case TileImage::Floor_Stone6:        
            case TileImage::Floor_Dirt1:         
            case TileImage::Floor_Dirt2:         
            case TileImage::Floor_Dirt3:         
            case TileImage::Floor_Dirt4:         
            case TileImage::Floor_Dirt5:         

            case TileImage::LiquidCor_TopLeft:   
            case TileImage::LiquidCor_TopRight:  
            case TileImage::LiquidCor_BotLeft:   
            case TileImage::LiquidCor_BotRight:  
            case TileImage::LiquidRim_TopLeft:   
            case TileImage::LiquidRim_Top:       
            case TileImage::LiquidRim_TopRight:  
            case TileImage::LiquidRim_Left:      
            case TileImage::LiquidRim_Right:     
            case TileImage::LiquidRim_BotLeft:   
            case TileImage::LiquidRim_Bot:       
            case TileImage::LiquidRim_BotRight:  

            case TileImage::Empty:
            default:                             { return false; }
        }
        // clang-format on
    }

    inline const sf::IntRect tileImageToRect(const TileImage tileImage)
    {
        // clang-format off
        switch (tileImage)
        {
            case TileImage::Sign:               { return sf::IntRect( {224,128},{32,32}); }
            case TileImage::FountainWater:      { return sf::IntRect( {192,192},{32,32}); }
            case TileImage::FountainBlood:      { return sf::IntRect( {224,192},{32,32}); }
            case TileImage::Rock:               { return sf::IntRect( { 96, 64},{32,32}); }
            case TileImage::RockWeak:           { return sf::IntRect( { 96, 96},{32,32}); }
            case TileImage::Ice:                { return sf::IntRect( { 64,224},{32,32}); }
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
            case TileImage::Tree1:              { return sf::IntRect( {128,224},{32,32}); }
            case TileImage::Tree2:              { return sf::IntRect( {160,224},{32,32}); }
            case TileImage::Tree3:              { return sf::IntRect( {192,224},{32,32}); }
            case TileImage::Wall_Shadow:        { return sf::IntRect( { 32, 32},{32,32}); }
            case TileImage::Avatar:             { return sf::IntRect( {224,224},{32,32}); }
            
            case TileImage::Wall_TopLeft:       { return sf::IntRect( {  0,  0},{32,32}); }
            case TileImage::Wall_Horiz:         { return sf::IntRect( { 32,  0},{32,32}); }
            case TileImage::Wall_Top:           { return sf::IntRect( { 64,  0},{32,32}); }
            case TileImage::Wall_Vert:          { return sf::IntRect( {  0, 32},{32,32}); }
            case TileImage::Wall_Block:         { return sf::IntRect( { 64, 32},{32,32}); }
            case TileImage::Wall_BlockWeak:     { return sf::IntRect( { 96, 32},{32,32}); }
            
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
            
            case TileImage::Pillar_CrumbleLeft: { return sf::IntRect( {  0,480},{32,32}); }
            case TileImage::Pillar_Rubble:      { return sf::IntRect( { 32,480},{32,32}); }
            case TileImage::Pillar_Complete:    { return sf::IntRect( { 64,480},{32,32}); }
            case TileImage::Pillar_Half:        { return sf::IntRect( { 96,480},{32,32}); }
            case TileImage::Pillar_Quarter:     { return sf::IntRect( {128,480},{32,32}); }
            case TileImage::Pillar_CrumbleRight:{ return sf::IntRect( {160,480},{32,32}); }

            case TileImage::Block_Emboss1:      { return sf::IntRect( {128,416},{32,32}); }
            case TileImage::Block_Emboss2:      { return sf::IntRect( {160,416},{32,32}); }
            case TileImage::Block_Emboss3:      { return sf::IntRect( {192,416},{32,32}); }
            case TileImage::Block_Emboss4:      { return sf::IntRect( {224,416},{32,32}); }

            case TileImage::Altar_Statue:       { return sf::IntRect( {  0,384},{32,32}); }
            case TileImage::Altar_Challace:     { return sf::IntRect( { 32,384},{32,32}); }
            case TileImage::Altar_Skull:        { return sf::IntRect( { 64,384},{32,32}); }
            case TileImage::Altar_Throne:       { return sf::IntRect( {  0,416},{32,32}); }
            case TileImage::Altar_Blood:        { return sf::IntRect( { 32,416},{32,32}); }
            case TileImage::Altar_Body:         { return sf::IntRect( { 64,416},{32,32}); }
            case TileImage::Altar_Demonic:      { return sf::IntRect( {  0,448},{32,32}); }
            case TileImage::Altar_Hand:         { return sf::IntRect( { 32,448},{32,32}); }
            case TileImage::Altar_King:         { return sf::IntRect( { 64,448},{32,32}); }

            case TileImage::Statue_Twins:       { return sf::IntRect( {128,256},{32,32}); }
            case TileImage::Statue_Mermaid:     { return sf::IntRect( {160,256},{32,32}); }
            case TileImage::Statue_Demonic:     { return sf::IntRect( {192,256},{32,32}); }
            case TileImage::Statue_Wraith:      { return sf::IntRect( {224,256},{32,32}); }
            case TileImage::Statue_Sword:       { return sf::IntRect( {128,288},{32,32}); }
            case TileImage::Statue_Thresher:    { return sf::IntRect( {160,288},{32,32}); }
            case TileImage::Statue_Orb:         { return sf::IntRect( {192,288},{32,32}); }
            case TileImage::Statue_Naga:        { return sf::IntRect( {224,288},{32,32}); }
            case TileImage::Statue_Imp:         { return sf::IntRect( {128,320},{32,32}); }
            case TileImage::Statue_Hydra:       { return sf::IntRect( {160,320},{32,32}); }
            case TileImage::Statue_Elephant:    { return sf::IntRect( {192,320},{32,32}); }
            case TileImage::Statue_Dwarf:       { return sf::IntRect( {224,320},{32,32}); }
            case TileImage::Statue_Dragon:      { return sf::IntRect( {128,352},{32,32}); }
            case TileImage::Statue_Flamberg:    { return sf::IntRect( {160,352},{32,32}); }
            case TileImage::Statue_Centaur:     { return sf::IntRect( {192,352},{32,32}); }
            case TileImage::Statue_Cat:         { return sf::IntRect( {224,352},{32,32}); }
            case TileImage::Statue_Angel:       { return sf::IntRect( {128,384},{32,32}); }
            case TileImage::Statue_Monster:     { return sf::IntRect( {160,384},{32,32}); }
            case TileImage::Statue_Princess:    { return sf::IntRect( {192,384},{32,32}); }
            case TileImage::Statue_Tengu:       { return sf::IntRect( {224,384},{32,32}); }

            case TileImage::Doorway_Wood:       { return sf::IntRect( {  0,256},{32,32}); }
            case TileImage::Doorway_WoodRune:   { return sf::IntRect( { 32,256},{32,32}); }
            case TileImage::Doorway_SatanicGray:{ return sf::IntRect( { 64,256},{32,32}); }
            case TileImage::Doorway_SatanicRed: { return sf::IntRect( { 96,256},{32,32}); }
            case TileImage::Doorway_RuneOpen:   { return sf::IntRect( {  0,288},{32,32}); }
            case TileImage::Doorway_RuneGray:   { return sf::IntRect( { 32,288},{32,32}); }
            case TileImage::Doorway_RuneBlue:   { return sf::IntRect( { 64,288},{32,32}); }
            case TileImage::Doorway_RuneSkull:  { return sf::IntRect( { 96,288},{32,32}); }
            case TileImage::Doorway_MirrorLit:  { return sf::IntRect( {  0,320},{32,32}); }
            case TileImage::Doorway_Mirror:     { return sf::IntRect( { 32,320},{32,32}); }
            case TileImage::Doorway_SantaicLava:{ return sf::IntRect( { 64,320},{32,32}); }
            case TileImage::Doorway_Candle:     { return sf::IntRect( { 96,320},{32,32}); }
            case TileImage::Doorway_Ghost:      { return sf::IntRect( {  0,352},{32,32}); }
            case TileImage::Doorway_Snake:      { return sf::IntRect( { 32,352},{32,32}); }
            case TileImage::Doorway_Oriental:   { return sf::IntRect( { 64,352},{32,32}); }
            case TileImage::Doorway_OrientalRed:{ return sf::IntRect( { 96,352},{32,32}); }

            // monsters
            case TileImage::BeholderSpawn:      { return sf::IntRect( {256,  0},{32,32}); }
            case TileImage::SkullSlime:         { return sf::IntRect( {288,  0},{32,32}); }
            case TileImage::BoneDragon:         { return sf::IntRect( {320,  0},{32,32}); }
            case TileImage::SwampThing:         { return sf::IntRect( {352,  0},{32,32}); }
            case TileImage::RabidRodent:        { return sf::IntRect( {384,  0},{32,32}); }
            case TileImage::Bat:                { return sf::IntRect( {416,  0},{32,32}); }
            case TileImage::DragonWarlord:      { return sf::IntRect( {448,  0},{32,32}); }
            case TileImage::AquaSlime:          { return sf::IntRect( {480,  0},{32,32}); }

            case TileImage::SlimeBeholder:      { return sf::IntRect( {256, 32},{32,32}); }
            case TileImage::Cyclops:            { return sf::IntRect( {288, 32},{32,32}); }
            case TileImage::FleshCreeper:       { return sf::IntRect( {320, 32},{32,32}); }
            case TileImage::Wailing:            { return sf::IntRect( {352, 32},{32,32}); }
            case TileImage::CoillingViper:      { return sf::IntRect( {384, 32},{32,32}); }
            case TileImage::IceKnight:          { return sf::IntRect( {416, 32},{32,32}); }
            case TileImage::Beholder:           { return sf::IntRect( {448, 32},{32,32}); }
            case TileImage::RottingChomper:     { return sf::IntRect( {480, 32},{32,32}); }

            case TileImage::SkitterMite:        { return sf::IntRect( {256, 64},{32,32}); }
            case TileImage::BloodCreeper:       { return sf::IntRect( {288, 64},{32,32}); }
            case TileImage::WindHowler:         { return sf::IntRect( {320, 64},{32,32}); }
            case TileImage::GreenSnake:         { return sf::IntRect( {352, 64},{32,32}); }
            case TileImage::BloatedCreeper:     { return sf::IntRect( {384, 64},{32,32}); }
            case TileImage::MudDemon:           { return sf::IntRect( {416, 64},{32,32}); }
            case TileImage::Serpent:            { return sf::IntRect( {448, 64},{32,32}); }
            case TileImage::WalkingBeholder:    { return sf::IntRect( {480, 64},{32,32}); }

            case TileImage::InvisibleMan:       { return sf::IntRect( {256, 96},{32,32}); }
            case TileImage::Kracklin:           { return sf::IntRect( {288, 96},{32,32}); }
            case TileImage::Kobold:             { return sf::IntRect( {320, 96},{32,32}); }
            case TileImage::FireGiant:          { return sf::IntRect( {352, 96},{32,32}); }
            case TileImage::BeholderMite:       { return sf::IntRect( {384, 96},{32,32}); }
            case TileImage::RacerSnake:         { return sf::IntRect( {416, 96},{32,32}); }
            case TileImage::DessertSnake:       { return sf::IntRect( {448, 96},{32,32}); }
            case TileImage::TwoHeadedOgre:      { return sf::IntRect( {480, 96},{32,32}); }

            case TileImage::MothDragon:         { return sf::IntRect( {256,128},{32,32}); }
            case TileImage::Catterhorror:       { return sf::IntRect( {288,128},{32,32}); }
            case TileImage::CaveSpider:         { return sf::IntRect( {320,128},{32,32}); }
            case TileImage::VineShambler:       { return sf::IntRect( {352,128},{32,32}); }
            case TileImage::SpikeCreeper:       { return sf::IntRect( {384,128},{32,32}); }
            case TileImage::SlimeShambler:      { return sf::IntRect( {416,128},{32,32}); }
            case TileImage::Spider:             { return sf::IntRect( {448,128},{32,32}); }
            case TileImage::SpellWalker:        { return sf::IntRect( {480,128},{32,32}); }

            case TileImage::GreenWight:         { return sf::IntRect( {256,160},{32,32}); }
            case TileImage::SoulEater:          { return sf::IntRect( {288,160},{32,32}); }
            case TileImage::BoneHound:          { return sf::IntRect( {320,160},{32,32}); }
            case TileImage::ArcaneBeholder:     { return sf::IntRect( {352,160},{32,32}); }
            case TileImage::Siren:              { return sf::IntRect( {384,160},{32,32}); }
            case TileImage::Specter:            { return sf::IntRect( {416,160},{32,32}); }
            case TileImage::BoneHydra:          { return sf::IntRect( {448,160},{32,32}); }
            case TileImage::ShadowFiend:        { return sf::IntRect( {480,160},{32,32}); }

            case TileImage::StripedSnake:       { return sf::IntRect( {256,192},{32,32}); }
            case TileImage::Scorpion:           { return sf::IntRect( {288,192},{32,32}); }
            case TileImage::Firebrand:          { return sf::IntRect( {320,192},{32,32}); }
            case TileImage::RustDevil:          { return sf::IntRect( {352,192},{32,32}); }
            case TileImage::Revenant:           { return sf::IntRect( {384,192},{32,32}); }
            case TileImage::WidowSpider:        { return sf::IntRect( {416,192},{32,32}); }
            case TileImage::RedDemon:           { return sf::IntRect( {448,192},{32,32}); }
            case TileImage::QuicksilverDragon:  { return sf::IntRect( {480,192},{32,32}); }

            case TileImage::Dragon:             { return sf::IntRect( {256,224},{32,32}); }
            case TileImage::Antlion:            { return sf::IntRect( {288,224},{32,32}); }
            case TileImage::Quasit:             { return sf::IntRect( {320,224},{32,32}); }
            case TileImage::KoboldBrute:        { return sf::IntRect( {352,224},{32,32}); }
            case TileImage::SpiderHorror:       { return sf::IntRect( {384,224},{32,32}); }
            case TileImage::OrangeDemon:        { return sf::IntRect( {416,224},{32,32}); }
            case TileImage::Ooze:               { return sf::IntRect( {448,224},{32,32}); }
            case TileImage::OctoCrawler:        { return sf::IntRect( {480,224},{32,32}); }

            case TileImage::Wollynaut:          { return sf::IntRect( {256,256},{32,32}); }
            case TileImage::BogSlave:           { return sf::IntRect( {288,256},{32,32}); }
            case TileImage::MutantBeast:        { return sf::IntRect( {320,256},{32,32}); }
            case TileImage::MoonTroll:          { return sf::IntRect( {352,256},{32,32}); }
            case TileImage::ManaViper:          { return sf::IntRect( {384,256},{32,32}); }
            case TileImage::Lorocyproca:        { return sf::IntRect( {416,256},{32,32}); }
            case TileImage::FleshChomper:       { return sf::IntRect( {448,256},{32,32}); }
            case TileImage::Juggernaut:         { return sf::IntRect( {480,256},{32,32}); }

            case TileImage::ElephantDemon:      { return sf::IntRect( {256,288},{32,32}); }
            case TileImage::RedJelly:           { return sf::IntRect( {288,288},{32,32}); }
            case TileImage::IronGiant:          { return sf::IntRect( {320,288},{32,32}); }
            case TileImage::Hippogriff:         { return sf::IntRect( {352,288},{32,32}); }
            case TileImage::HellWing:           { return sf::IntRect( {384,288},{32,32}); }
            case TileImage::Hellion:            { return sf::IntRect( {416,288},{32,32}); }
            case TileImage::HellHound:          { return sf::IntRect( {448,288},{32,32}); }
            case TileImage::GuardianCobra:      { return sf::IntRect( {480,288},{32,32}); }

            case TileImage::GoldScorpion:       { return sf::IntRect( {256,320},{32,32}); }
            case TileImage::GreenBullber:       { return sf::IntRect( {288,320},{32,32}); }
            case TileImage::GoldenDragon:       { return sf::IntRect( {320,320},{32,32}); }
            case TileImage::GiantLeech:         { return sf::IntRect( {352,320},{32,32}); }
            case TileImage::GiantAmoeba:        { return sf::IntRect( {384,320},{32,32}); }
            case TileImage::OrangeClamber:      { return sf::IntRect( {416,320},{32,32}); }
            case TileImage::FrostGiant:         { return sf::IntRect( {448,320},{32,32}); }
            case TileImage::AntCreeper:         { return sf::IntRect( {480,320},{32,32}); }

            case TileImage::SunWeaver:          { return sf::IntRect( {256,352},{32,32}); }
            case TileImage::SkiteWing:          { return sf::IntRect( {288,352},{32,32}); }
            case TileImage::FireElemental:      { return sf::IntRect( {320,352},{32,32}); }
            case TileImage::RustCrab:           { return sf::IntRect( {352,352},{32,32}); }
            case TileImage::FireBat:            { return sf::IntRect( {384,352},{32,32}); }
            case TileImage::WanderingEye:       { return sf::IntRect( {416,352},{32,32}); }
            case TileImage::TwoHeadedGiant:     { return sf::IntRect( {448,352},{32,32}); }
            case TileImage::BruteWitch:         { return sf::IntRect( {480,352},{32,32}); }

            case TileImage::Draconian:          { return sf::IntRect( {256,384},{32,32}); }
            case TileImage::WailingSlime:       { return sf::IntRect( {288,384},{32,32}); }
            case TileImage::Madman:             { return sf::IntRect( {320,384},{32,32}); }
            case TileImage::Fungosite:          { return sf::IntRect( {352,384},{32,32}); }

            // npc
            case TileImage::Gnome:              { return sf::IntRect( {384,384},{32,32}); }
            case TileImage::Faun:               { return sf::IntRect( {416,384},{32,32}); }
            case TileImage::Elfman:             { return sf::IntRect( {448,384},{32,32}); }
            case TileImage::Dwarf:              { return sf::IntRect( {480,384},{32,32}); }

            case TileImage::Wiglaf:             { return sf::IntRect( {256,416},{32,32}); }
            case TileImage::Human:              { return sf::IntRect( {288,416},{32,32}); }
            case TileImage::RedKnight:          { return sf::IntRect( {320,416},{32,32}); }
            case TileImage::Elf:                { return sf::IntRect( {352,416},{32,32}); }
            case TileImage::ElfWarrior:         { return sf::IntRect( {384,416},{32,32}); }
            case TileImage::GreenElf:           { return sf::IntRect( {416,416},{32,32}); }
            case TileImage::GreenElfMage:       { return sf::IntRect( {448,416},{32,32}); }
            case TileImage::BlueClown:          { return sf::IntRect( {480,416},{32,32}); }

            case TileImage::BlueKnight:         { return sf::IntRect( {256,448},{32,32}); }
            case TileImage::Spartan:            { return sf::IntRect( {288,448},{32,32}); }
            case TileImage::Satyr:              { return sf::IntRect( {320,448},{32,32}); }
            case TileImage::GoldKnight:         { return sf::IntRect( {352,448},{32,32}); }
            case TileImage::DeepCaster:         { return sf::IntRect( {384,448},{32,32}); }
            case TileImage::OldMan:             { return sf::IntRect( {416,448},{32,32}); }
            case TileImage::GoldClown:          { return sf::IntRect( {448,448},{32,32}); }
            case TileImage::Hag:                { return sf::IntRect( {480,448},{32,32}); }

            case TileImage::CyanKnight:         { return sf::IntRect( {256,480},{32,32}); }
            case TileImage::Elfnee:             { return sf::IntRect( {288,480},{32,32}); }
            case TileImage::Javelinee:          { return sf::IntRect( {320,480},{32,32}); }
            case TileImage::SkullSpeaker:       { return sf::IntRect( {352,480},{32,32}); }
            case TileImage::FolkMage:           { return sf::IntRect( {384,480},{32,32}); }
            case TileImage::Maud:               { return sf::IntRect( {416,480},{32,32}); }
            case TileImage::GreenRanger:        { return sf::IntRect( {448,480},{32,32}); }
            case TileImage::BookSpeaker:        { return sf::IntRect( {480,480},{32,32}); }

            case TileImage::Empty:
            case TileImage::Inferno:
            case TileImage::Campfire:
            default:                            { return sf::IntRect( {128,160},{32,32}); }
        }
        // clang-format on
    }

    constexpr inline const std::string_view tileImageToName(const TileImage tileImage)
    {
        // clang-format off
        switch (tileImage)
        {
            case TileImage::Sign:               { return "Sign"; }
            case TileImage::FountainWater:      { return "Water Fountain"; }
            case TileImage::FountainBlood:      { return "Blood Fountain"; }
            case TileImage::Rock:               { return "Rock"; }
            case TileImage::RockWeak:           { return "Breakable Rock"; }
            case TileImage::Ice:                { return "Ice"; }
            case TileImage::Blood:              { return "Blood"; }
            case TileImage::Lava:               { return "Lava"; }
            case TileImage::Water:              { return "Water"; }
            case TileImage::Slime:              { return "Slime"; }
            case TileImage::Stair_Up:           { return "Stairs Up"; }
            case TileImage::Stair_Down:         { return "Stairs Down"; }
            case TileImage::Barrel:             { return "Barrel"; }
            case TileImage::Door:               { return "Door"; }
            case TileImage::DoorLocked:         { return "Locked Door"; }
            case TileImage::Chest:              { return "Chest"; }
            case TileImage::Coffin:             { return "Coffin"; }
            case TileImage::Bag:                { return "Bag"; }
            case TileImage::Altar:              { return "Altar"; }
            case TileImage::StoneSpire:         { return "Stone Spire"; }
            case TileImage::Key:                { return "Key"; }
            case TileImage::Tree1:              { return "Tree"; }
            case TileImage::Tree2:              { return "Tree"; }
            case TileImage::Tree3:              { return "Tree"; }
            case TileImage::Wall_Shadow:        { return "Wall_Shadow"; }
            case TileImage::Avatar:             { return "You"; }
            
            case TileImage::Wall_TopLeft:       { return "Wall_TopLeft"; }
            case TileImage::Wall_Horiz:         { return "Wall_Horiz"; }
            case TileImage::Wall_Top:           { return "Wall_Top"; }
            case TileImage::Wall_Vert:          { return "Wall_Vert"; }
            case TileImage::Wall_Block:         { return "Wall_Block"; }
            case TileImage::Wall_BlockWeak:     { return "Wall_BlockWeak"; }
            
            case TileImage::Floor_Wood1:        { return "Floor_Wood1"; }
            case TileImage::Floor_Wood2:        { return "Floor_Wood2"; }
            case TileImage::Floor_Wood3:        { return "Floor_Wood3"; }
            case TileImage::Floor_Wood4:        { return "Floor_Wood4"; }
            case TileImage::Floor_Wood5:        { return "Floor_Wood5"; }
            case TileImage::Floor_Wood6:        { return "Floor_Wood6"; }
            case TileImage::Floor_Stone1:       { return "Floor_Stone1"; }
            case TileImage::Floor_Stone2:       { return "Floor_Stone2"; }
            case TileImage::Floor_Stone3:       { return "Floor_Stone3"; }
            case TileImage::Floor_Stone4:       { return "Floor_Stone4"; }
            case TileImage::Floor_Stone5:       { return "Floor_Stone5"; }
            case TileImage::Floor_Stone6:       { return "Floor_Stone6"; }
            case TileImage::Floor_Dirt1:        { return "Floor_Dirt1"; }
            case TileImage::Floor_Dirt2:        { return "Floor_Dirt2"; }
            case TileImage::Floor_Dirt3:        { return "Floor_Dirt3"; }
            case TileImage::Floor_Dirt4:        { return "Floor_Dirt4"; }
            case TileImage::Floor_Dirt5:        { return "Floor_Dirt5"; }
            
            case TileImage::LiquidCor_TopLeft:  { return "LiquidCor_TopLeft"; }
            case TileImage::LiquidCor_TopRight: { return "LiquidCor_TopRight"; }
            case TileImage::LiquidCor_BotLeft:  { return "LiquidCor_BotLeft"; }
            case TileImage::LiquidCor_BotRight: { return "LiquidCor_BotRight"; }
            case TileImage::LiquidRim_TopLeft:  { return "LiquidRim_TopLeft"; }
            case TileImage::LiquidRim_Top:      { return "LiquidRim_Top"; }
            case TileImage::LiquidRim_TopRight: { return "LiquidRim_TopRight"; }
            case TileImage::LiquidRim_Left:     { return "LiquidRim_Left"; }
            case TileImage::LiquidRim_Right:    { return "LiquidRim_Right"; }
            case TileImage::LiquidRim_BotLeft:  { return "LiquidRim_BotLeft"; }
            case TileImage::LiquidRim_Bot:      { return "LiquidRim_Bot"; }
            case TileImage::LiquidRim_BotRight: { return "LiquidRim_BotRight"; }
            
            case TileImage::Pillar_CrumbleLeft: { return "Pillar_CrumbleLeft"; }
            case TileImage::Pillar_Rubble:      { return "Pillar_Rubble"; }
            case TileImage::Pillar_Complete:    { return "Pillar_Complete"; }
            case TileImage::Pillar_Half:        { return "Pillar_Half"; }
            case TileImage::Pillar_Quarter:     { return "Pillar_Quarter"; }
            case TileImage::Pillar_CrumbleRight:{ return "Pillar_CrumbleRight"; }

            case TileImage::Block_Emboss1:      { return "Block_Emboss1"; }
            case TileImage::Block_Emboss2:      { return "Block_Emboss2"; }
            case TileImage::Block_Emboss3:      { return "Block_Emboss3"; }
            case TileImage::Block_Emboss4:      { return "Block_Emboss4"; }

            case TileImage::Altar_Statue:       { return "Altar_Statue"; }
            case TileImage::Altar_Challace:     { return "Altar_Challace"; }
            case TileImage::Altar_Skull:        { return "Altar_Skull"; }
            case TileImage::Altar_Throne:       { return "Altar_Throne"; }
            case TileImage::Altar_Blood:        { return "Altar_Blood"; }
            case TileImage::Altar_Body:         { return "Altar_Body"; }
            case TileImage::Altar_Demonic:      { return "Altar_Demonic"; }
            case TileImage::Altar_Hand:         { return "Altar_Hand"; }
            case TileImage::Altar_King:         { return "Altar_King"; }

            case TileImage::Statue_Twins:       { return "Statue_Twins"; }
            case TileImage::Statue_Mermaid:     { return "Statue_Mermaid"; }
            case TileImage::Statue_Demonic:     { return "Statue_Demonic"; }
            case TileImage::Statue_Wraith:      { return "Statue_Wraith"; }
            case TileImage::Statue_Sword:       { return "Statue_Sword"; }
            case TileImage::Statue_Thresher:    { return "Statue_Thresher"; }
            case TileImage::Statue_Orb:         { return "Statue_Orb"; }
            case TileImage::Statue_Naga:        { return "Statue_Naga"; }
            case TileImage::Statue_Imp:         { return "Statue_Imp"; }
            case TileImage::Statue_Hydra:       { return "Statue_Hydra"; }
            case TileImage::Statue_Elephant:    { return "Statue_Elephant"; }
            case TileImage::Statue_Dwarf:       { return "Statue_Dwarf"; }
            case TileImage::Statue_Dragon:      { return "Statue_Dragon"; }
            case TileImage::Statue_Flamberg:    { return "Statue_Flamberg"; }
            case TileImage::Statue_Centaur:     { return "Statue_Centaur"; }
            case TileImage::Statue_Cat:         { return "Statue_Cat"; }
            case TileImage::Statue_Angel:       { return "Statue_Angel"; }
            case TileImage::Statue_Monster:     { return "Statue_Monster"; }
            case TileImage::Statue_Princess:    { return "Statue_Princess"; }
            case TileImage::Statue_Tengu:       { return "Statue_Tengu"; }

            case TileImage::Doorway_Wood:       { return "Doorway_Wood"; }
            case TileImage::Doorway_WoodRune:   { return "Doorway_WoodRune"; }
            case TileImage::Doorway_SatanicGray:{ return "Doorway_SatanicGray"; }
            case TileImage::Doorway_SatanicRed: { return "Doorway_SatanicRed"; }
            case TileImage::Doorway_RuneOpen:   { return "Doorway_RuneOpen"; }
            case TileImage::Doorway_RuneGray:   { return "Doorway_RuneGray"; }
            case TileImage::Doorway_RuneBlue:   { return "Doorway_RuneBlue"; }
            case TileImage::Doorway_RuneSkull:  { return "Doorway_RuneSkull"; }
            case TileImage::Doorway_MirrorLit:  { return "Doorway_MirrorLit"; }
            case TileImage::Doorway_Mirror:     { return "Doorway_Mirror"; }
            case TileImage::Doorway_SantaicLava:{ return "Doorway_SantaicLava"; }
            case TileImage::Doorway_Candle:     { return "Doorway_Candle"; }
            case TileImage::Doorway_Ghost:      { return "Doorway_Ghost"; }
            case TileImage::Doorway_Snake:      { return "Doorway_Snake"; }
            case TileImage::Doorway_Oriental:   { return "Doorway_Oriental"; }
            case TileImage::Doorway_OrientalRed:{ return "Doorway_OrientalRed"; }

            // monsters
            case TileImage::BeholderSpawn:      { return "Beholder Spawn"; }
            case TileImage::SkullSlime:         { return "Skull Slime"; }
            case TileImage::BoneDragon:         { return "Bone Dragon"; }
            case TileImage::SwampThing:         { return "Swamp Thing"; }
            case TileImage::RabidRodent:        { return "Rabid Rodent"; }
            case TileImage::Bat:                { return "Bat"; }
            case TileImage::DragonWarlord:      { return "Dragon Warlord"; }
            case TileImage::AquaSlime:          { return "Aqua Slime"; }

            case TileImage::SlimeBeholder:      { return "Slime Beholder"; }
            case TileImage::Cyclops:            { return "Cyclops"; }
            case TileImage::FleshCreeper:       { return "Flesh Creeper"; }
            case TileImage::Wailing:            { return "Wailing"; }
            case TileImage::CoillingViper:      { return "Coilling Viper"; }
            case TileImage::IceKnight:          { return "Ice Knight"; }
            case TileImage::Beholder:           { return "Beholder"; }
            case TileImage::RottingChomper:     { return "Rotting Chomper"; }

            case TileImage::SkitterMite:        { return "Skitter Mite"; }
            case TileImage::BloodCreeper:       { return "Blood Creeper"; }
            case TileImage::WindHowler:         { return "Wind Howler"; }
            case TileImage::GreenSnake:         { return "Green Snake"; }
            case TileImage::BloatedCreeper:     { return "Bloated Creeper"; }
            case TileImage::MudDemon:           { return "Mud Demon"; }
            case TileImage::Serpent:            { return "Serpent"; }
            case TileImage::WalkingBeholder:    { return "Walking Beholder"; }
             
            case TileImage::InvisibleMan:       { return "Invisible Man"; }
            case TileImage::Kracklin:           { return "Kracklin"; }
            case TileImage::Kobold:             { return "Kobold"; }
            case TileImage::FireGiant:          { return "Fire Giant"; }
            case TileImage::BeholderMite:       { return "Beholder Mite"; }
            case TileImage::RacerSnake:         { return "Racer Snake"; }
            case TileImage::DessertSnake:       { return "Dessert Snake"; }
            case TileImage::TwoHeadedOgre:      { return "Two-Headed Ogre"; }
                  
            case TileImage::MothDragon:         { return "Moth Dragon"; }
            case TileImage::Catterhorror:       { return "Catterhorror"; }
            case TileImage::CaveSpider:         { return "Cave Spider"; }
            case TileImage::VineShambler:       { return "Vine Shambler"; }
            case TileImage::SpikeCreeper:       { return "Spike Creeper"; }
            case TileImage::SlimeShambler:      { return "Slime Shambler"; }
            case TileImage::Spider:             { return "Spider"; }
            case TileImage::SpellWalker:        { return "Spell Walker"; }
                                          
            case TileImage::GreenWight:         { return "Green Wight"; }
            case TileImage::SoulEater:          { return "Soul Eater"; }
            case TileImage::BoneHound:          { return "Bone Hound"; }
            case TileImage::ArcaneBeholder:     { return "Arcane Beholder"; }
            case TileImage::Siren:              { return "Siren"; }
            case TileImage::Specter:            { return "Specter"; }
            case TileImage::BoneHydra:          { return "Bone Hydra"; }
            case TileImage::ShadowFiend:        { return "Shadow Fiend"; }

            case TileImage::StripedSnake:       { return "Striped Snake"; }
            case TileImage::Scorpion:           { return "Scorpion"; }
            case TileImage::Firebrand:          { return "Firebrand"; }
            case TileImage::RustDevil:          { return "Rust Devil"; }
            case TileImage::Revenant:           { return "Revenant"; }
            case TileImage::WidowSpider:        { return "Widow Spider"; }
            case TileImage::RedDemon:           { return "Red Demon"; }
            case TileImage::QuicksilverDragon:  { return "Quicksilver Dragon"; }
                                        
            case TileImage::Dragon:             { return "Dragon"; }
            case TileImage::Antlion:            { return "Antlion"; }
            case TileImage::Quasit:             { return "Quasit"; }
            case TileImage::KoboldBrute:        { return "Kobold Brute"; }
            case TileImage::SpiderHorror:       { return "Spider Horror"; }
            case TileImage::OrangeDemon:        { return "Orange Demon"; }
            case TileImage::Ooze:               { return "Ooze"; }
            case TileImage::OctoCrawler:        { return "Octo Crawler"; }
                                           
            case TileImage::Wollynaut:          { return "Wollynaut"; }
            case TileImage::BogSlave:           { return "Bog Slave"; }
            case TileImage::MutantBeast:        { return "Mutant Beast"; }
            case TileImage::MoonTroll:          { return "Moon Troll"; }
            case TileImage::ManaViper:          { return "Mana Viper"; }
            case TileImage::Lorocyproca:        { return "Lorocyproca"; }
            case TileImage::FleshChomper:       { return "Flesh Chomper"; }
            case TileImage::Juggernaut:         { return "Juggernaut"; }
                                         
            case TileImage::ElephantDemon:      { return "Elephant Demon"; }
            case TileImage::RedJelly:           { return "Red Jelly"; }
            case TileImage::IronGiant:          { return "Iron Giant"; }
            case TileImage::Hippogriff:         { return "Hippogriff"; }
            case TileImage::HellWing:           { return "Hell Wing"; }
            case TileImage::Hellion:            { return "Hellion"; }
            case TileImage::HellHound:          { return "Hell Hound"; }
            case TileImage::GuardianCobra:      { return "Guardian Cobra"; }
                                        
            case TileImage::GoldScorpion:       { return "Gold Scorpion"; }
            case TileImage::GreenBullber:       { return "Green Bullber"; }
            case TileImage::GoldenDragon:       { return "Golden Dragon"; }
            case TileImage::GiantLeech:         { return "Giant Leech"; }
            case TileImage::GiantAmoeba:        { return "Giant Amoeba"; }
            case TileImage::OrangeClamber:      { return "Orange Clamber"; }
            case TileImage::FrostGiant:         { return "Frost Giant"; }
            case TileImage::AntCreeper:         { return "Ant Creeper"; }

            case TileImage::SunWeaver:          { return "Sun Weaver"; }
            case TileImage::SkiteWing:          { return "Skite Wing"; }
            case TileImage::FireElemental:      { return "Fire Elemental"; }
            case TileImage::RustCrab:           { return "Rust Crab"; }
            case TileImage::FireBat:            { return "Fire Bat"; }
            case TileImage::WanderingEye:       { return "Wandering Eye"; }
            case TileImage::TwoHeadedGiant:     { return "TwoHeaded Giant"; }
            case TileImage::BruteWitch:         { return "Brute Witch"; }

            case TileImage::Draconian:          { return "Draconian"; }
            case TileImage::WailingSlime:       { return "Wailing Slime"; }
            case TileImage::Madman:             { return "Madman"; }
            case TileImage::Fungosite:          { return "Fungosite"; }

            // npc
            case TileImage::Gnome:              { return "Gnome"; }
            case TileImage::Faun:               { return "Faun"; }
            case TileImage::Elfman:             { return "Elfman"; }
            case TileImage::Dwarf:              { return "Dwarf"; }
            
            case TileImage::Wiglaf:             { return "Wiglaf"; }
            case TileImage::Human:              { return "Human"; }
            case TileImage::RedKnight:          { return "Red Knight"; }
            case TileImage::Elf:                { return "Elf"; }
            case TileImage::ElfWarrior:         { return "Elf Warrior"; }
            case TileImage::GreenElf:           { return "Green Elf"; }
            case TileImage::GreenElfMage:       { return "Green Elf Mage"; }
            case TileImage::BlueClown:          { return "Blue Clown"; }
            
            case TileImage::BlueKnight:         { return "Blue Knight"; }
            case TileImage::Spartan:            { return "Spartan"; }
            case TileImage::Satyr:              { return "Satyr"; }
            case TileImage::GoldKnight:         { return "Gold Knight"; }
            case TileImage::DeepCaster:         { return "Deep Caster"; }
            case TileImage::OldMan:             { return "Old Man"; }
            case TileImage::GoldClown:          { return "Gold Clown"; }
            case TileImage::Hag:                { return "Hag"; }
            
            case TileImage::CyanKnight:         { return "Cyan Knight"; }
            case TileImage::Elfnee:             { return "Elfnee"; }
            case TileImage::Javelinee:          { return "Javelinee"; }
            case TileImage::SkullSpeaker:       { return "Skull Speaker"; }
            case TileImage::FolkMage:           { return "Folk Mage"; }
            case TileImage::Maud:               { return "Maud"; }
            case TileImage::GreenRanger:        { return "Green Ranger"; }
            case TileImage::BookSpeaker:        { return "Book Speaker"; }

            case TileImage::Inferno:            { return "Inferno"; }
            case TileImage::Campfire:           { return "Campfire"; }

            case TileImage::Empty:
            default:                            { return ""; }
        }
        // clang-format on
    }

} // namespace castlecrawl

#endif // CONTEXT_HPP_INCLUDED
