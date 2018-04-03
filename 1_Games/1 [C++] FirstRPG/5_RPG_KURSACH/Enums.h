#pragma once

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

//41 - PIERSING, 42 - CRUSHING, 43 - CUTTER
//44 - PIERSING + CRUSHING, 45 - PIERSING + CUTTER, 47 - CUTTER + CRUSHING
//46 - PIERSING + CRUSHING + CUTTER
enum AttackType { PIERSING, CRUSHING, CUTTER, MAGIC_GENERAL_ATC = 10, MAGIC_FIRE_ATC, MAGIC_WATER_ATC, MAGIC_EARTH_ATC, MAGIC_AIR_ATC, MAGIC_DARK_ATC, MAGIC_LIGHT_ATC };
enum DefenseType { WITHOUT_ARMOR, LIGHT, MEDIUM, HEAVY, MAGIC, GOD, DEAMON, DEF_CNT };
enum MagicResist { MAGIC_GENERAL, MAGIC_FIRE, MAGIC_WATER, MAGIC_EARTH, MAGIC_AIR, MAGIC_DARK, MAGIC_LIGHT, MAGIC_CNT };
enum RACE { HUMAN, ORC, ELF, KOBOLD };
enum SkillType { Attack, Heal, SkillTypeCnt };

enum ItemSlot {
	Head, Armor, LeftHand, RightHand, Boots, LeftRing, RightRing, Amulet, Cloak, Belt, Gloves, Shoulders, SlotsCnt
};
//            +            +                       +              +               +
enum Scene { MAIN_MENU, LOAD_MENU, CONFIG_MENU, TOWN_CHOISE, INVENTORY_CHOISE, BATTLE_SCENE };