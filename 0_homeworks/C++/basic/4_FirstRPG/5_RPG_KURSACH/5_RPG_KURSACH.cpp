#pragma comment(lib, "winmm.lib")
#include "stdafx.h"
#include "Enums.h"

#define grey SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightGray))
#define blue SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightCyan))
#define red SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | LightRed))
#define yellow SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow))
#define usi unsigned short int

template <typename T>
void ArrPushBack(T *&arr, usi &size) {
	T *tmp = new T[size + 1];

	for (usi i = 0; i < size; i++)
		tmp[i] = arr[i];
	arr = tmp;
	++size;
}
template <typename T>
void ArrDeleteByIndex(T *&arr, usi &size, usi index) {
	usi j = 0;
	T *tmpArr = new T[j];

	for (int i = 0; i < size; i++) {
		if (i != index) {
			ArrPushBack(tmpArr, j);
			tmpArr[j - 1] = arr[i];
		}
	}
	arr = tmpArr;
	size = j;
}

struct LOG_STRC {
	ofstream fout;
	LOG_STRC(char * argv[]) {
		const char PRJ_NAME[] = "5_RPG_KURSACH.exe";
		char *BD_NAME = "log.txt";
		char PATH[_MAX_PATH];   //260
		strcpy(PATH, argv[0]);
		char *p = strstr(PATH, PRJ_NAME);
		strcpy(p, BD_NAME);
		fout.open(PATH, ios_base::app);
		if (!fout.is_open()) {
			cout << "Cant open " << BD_NAME << endl;
			system("pause");
			return;
		}
	}
	~LOG_STRC() {
		fout.close();
	}
	void print(char *str) {
		fout << str << endl;
	}
	void print(int str) {
		fout << str << endl;
	}
};
struct items_s {
	char name[50];
	char description[200];

	int price;
	int slot;

	int posInBD;

	//based on strength
	int meleeDMGMin, meleeDMGMax, meleeBlock;
	//based on agility
	int hitChance;
	int rangeDMGMin, rangeDMGMax, rangeAvoid;
	//based on intelligence
	int magicGMG;
	int magicResist[MAGIC_CNT];
	//based on endurance
	short int HPMax, HPHeal;
	//based on luck
	int luckMod;

	//20 не броня
	int armorType, armorNum;

	void PrintInfoForShop(char * argv[], int f_Slot) {
		const char PRJ_NAME[] = "5_RPG_KURSACH.exe";
		char *BD_NAME = "items\\items.txt";
		char PATH[_MAX_PATH];   //260
		strcpy(PATH, argv[0]);
		char *p = strstr(PATH, PRJ_NAME);

		ifstream fin;
		strcpy(p, BD_NAME);
		fin.open(PATH);
		if (!fin.is_open()) {
			cout << "Cant open " << BD_NAME << endl;
			system("pause");
		}

		fin.seekg(0);
		for (usi i = 0; fin.peek() != EOF; i++) {
			int CurrSkillPos = -1;
			char ch1 = fin.get();
			if (ch1 == ':') {
				char ch2 = fin.get();
				if (ch2 == ':') {
					char ch3 = fin.get();
					if (ch3 == ':') {
						char chPos[32] = { '\0' };
						usi i = 0;
						fin.getline(chPos, 9);

						CurrSkillPos = atoi(chPos);
						fin.getline(name, 50);
						fin.getline(description, 200);
						fin >> price;
						fin >> slot;
					}
				}
			}
			if (CurrSkillPos != -1) {
				if (f_Slot == slot) {
					cout << "Item ID: " << CurrSkillPos << endl;
					cout << name << endl;
					if(description[0] != ' ')
					cout << description << endl;
					cout << "Price: " << price << " g" << endl;
					/*cout << "Slot: ";
					if (slot == Head) {
						cout << "Head" << endl;
					}
					else if (slot == Armor) {
						cout << "Armor" << endl;
					}
					else if (slot == LeftHand) {
						cout << "Left Hand" << endl;
					}
					else if (slot == RightHand) {
						cout << "Right Hand" << endl;
					}
					else if (slot == Boots) {
						cout << "Boots" << endl;
					}
					else if (slot == LeftRing) {
						cout << "Ring" << endl;
					}
					else if (slot == RightRing) {
						cout << "Ring" << endl;
					}
					else if (slot == Amulet) {
						cout << "Amulet" << endl;
					}
					else if (slot == Cloak) {
						cout << "Cloak" << endl;
					}
					else if (slot == Belt) {
						cout << "Belt" << endl;
					}
					else if (slot == Gloves) {
						cout << "Gloves" << endl;
					}
					else if (slot == Shoulders) {
						cout << "Shoulders" << endl;
					}*/
					cout << endl;
				}
			}
		}

		fin.close();
	}
	items_s ReadItemFromTXT(char * argv[], int pos) {
		posInBD = -1;
		const char PRJ_NAME[] = "5_RPG_KURSACH.exe";
		char *BD_NAME = "items\\items.txt";
		char PATH[_MAX_PATH];   //260
		strcpy(PATH, argv[0]);
		char *p = strstr(PATH, PRJ_NAME);

		ifstream fin;
		strcpy(p, BD_NAME);
		fin.open(PATH);
		if (!fin.is_open()) {
			cout << "Cant open " << BD_NAME << endl;
			system("pause");
		}

		fin.seekg(0);
		for (usi i = 0; fin.peek() != EOF; i++) {
			char ch1 = fin.get();

			if (ch1 == ':') {
				char ch2 = fin.get();
				if (ch2 == ':') {
					char ch3 = fin.get();
					if (ch3 == ':') {
						char chPos[32] = { '\0' };
						usi i = 0;
						fin.getline(chPos, 9);

						int CurrSkillPos = -1;
						CurrSkillPos = atoi(chPos);
						if (CurrSkillPos == pos) {
							fin.getline(name, 50);
							fin.getline(description, 200);

							fin >> price;
							fin >> slot;

							fin >> meleeDMGMin >> meleeDMGMax >> meleeBlock;
							fin >> hitChance;
							fin >> rangeDMGMin >> rangeDMGMax >> rangeAvoid;
							fin >> magicGMG;
							fin >> magicResist[MAGIC_GENERAL] >> magicResist[MAGIC_FIRE] >> magicResist[MAGIC_WATER] >> magicResist[MAGIC_EARTH] >> magicResist[MAGIC_AIR] >> magicResist[MAGIC_DARK] >> magicResist[MAGIC_LIGHT];
							fin >> HPMax >> HPHeal;
							fin >> luckMod;
							fin >> armorType >> armorNum;
							posInBD = pos;
						}
					}
				}
			}
		}

		fin.close();
		//Це вообще законно?!
		return *this;
	}
	void PrintInfo() {
		cout << name << endl;
		cout << description << endl;
		cout << "Price: " << price << " g" << endl;
		cout << "Slot: ";

		if (slot == Head) {
			cout << "Head" << endl;
		}
		else if (slot == Armor) {
			cout << "Armor" << endl;
		}
		else if (slot == LeftHand) {
			cout << "Left Hand" << endl;
		}
		else if (slot == RightHand) {
			cout << "Right Hand" << endl;
		}
		else if (slot == Boots) {
			cout << "Boots" << endl;
		}
		else if (slot == LeftRing) {
			cout << "Ring" << endl;
		}
		else if (slot == RightRing) {
			cout << "Ring" << endl;
		}
		else if (slot == Amulet) {
			cout << "Amulet" << endl;
		}
		else if (slot == Cloak) {
			cout << "Cloak" << endl;
		}
		else if (slot == Belt) {
			cout << "Belt" << endl;
		}
		else if (slot == Gloves) {
			cout << "Gloves" << endl;
		}
		else if (slot == Shoulders) {
			cout << "Shoulders" << endl;
		}

		if (armorNum != 0)
			cout << "Armor: ";
		if (armorType == WITHOUT_ARMOR)
			cout << "without armor ";
		else if (armorType == LIGHT)
			cout << "light ";
		else if (armorType == MEDIUM)
			cout << "medium ";
		else if (armorType == HEAVY)
			cout << "heavy ";
		else if (armorType == MAGIC)
			cout << "magic ";
		if (armorNum != 0)
			cout << armorNum << endl << endl;

		if (armorType >= 41 && armorType <= 47)
			cout << "Attack type: ";
		if (armorType == 41)
			cout << "PIERSING";
		else if (armorType == 42)
			cout << "CRUSHING ";
		else if (armorType == 43)
			cout << "CUTTER ";
		else if (armorType == 44)
			cout << "PIERSING + CRUSHING ";
		else if (armorType == 45)
			cout << "PIERSING + CUTTER ";
		else if (armorType == 46)
			cout << "PIERSING + CRUSHING + CUTTER ";
		else if (armorType == 47)
			cout << "CUTTER + CRUSHING ";
		cout << endl;

		//cout << "STR: " << strength << endl;
		if (meleeDMGMin != 0 || meleeDMGMax != 0)
			cout << "\tMelee DMG: " << meleeDMGMin << " - " << meleeDMGMax << endl;
		if (meleeBlock != 0)
			cout << "\tMelee block: " << meleeBlock << "%" << endl;

		//cout << "AGI: " << agility << endl;
		if (rangeDMGMin != 0 && rangeDMGMax != 0)
			cout << "\tRange DMG: " << rangeDMGMin << " - " << rangeDMGMax << endl;
		if (hitChance != 0)
			cout << "\tHit chance: " << hitChance << "%" << endl;
		if (rangeAvoid != 0)
			cout << "\tAvoid chance: " << rangeAvoid << "%" << endl;

		//cout << "INT: " << intelligence << endl;
		if (magicGMG != 0)
			cout << "\tMagic DMG: " << magicGMG << endl;
		if (magicResist[MAGIC_GENERAL] != 0)
			cout << "\tMagic resistent: " << magicResist[MAGIC_GENERAL] << "%" << endl;

		//cout << "END: " << endurance << endl;
		if (HPMax != 0)
			cout << "\tMax HP: " << HPMax << endl;
		if (HPHeal != 0)
			cout << "\tHeal: " << HPHeal << endl;

		//cout << "Luck: " << luck << endl;
		if (luckMod != 0)
			cout << "\tLuck mod: " << luckMod << endl;


		usi magicResistentCounter = 0;
		for (usi i = 1; i < MAGIC_CNT; i++) {
			if (magicResist[i] != 0)
				magicResistentCounter++;
		}

		if (magicResistentCounter != 0)
			cout << endl << "Special magic resistent: " << endl;
		if (magicResist[MAGIC_FIRE] != 0)
			cout << "\t Fire: " << magicResist[MAGIC_FIRE] << "%" << endl;
		if (magicResist[MAGIC_WATER] != 0)
			cout << "\t Water: " << magicResist[MAGIC_WATER] << "%" << endl;
		if (magicResist[MAGIC_EARTH] != 0)
			cout << "\t Earth: " << magicResist[MAGIC_EARTH] << "%" << endl;
		if (magicResist[MAGIC_AIR] != 0)
			cout << "\t Air: " << magicResist[MAGIC_AIR] << "%" << endl;
		if (magicResist[MAGIC_DARK] != 0)
			cout << "\t Dark: " << magicResist[MAGIC_DARK] << "%" << endl;
		if (magicResist[MAGIC_LIGHT] != 0)
			cout << "\t Light: " << magicResist[MAGIC_LIGHT] << "%" << endl << endl;
	}
};

struct HealSkill {
	int BaseHeal;
};
struct DMGSkill {
	int BaseDMG;
	int attackType;
	bool isRange : 1;
	bool isMagic : 1;
};
union skill {
	char name[50];
	char description[100];
	int skillType;
	HealSkill hSkill;
	DMGSkill dSkill;

	skill* ReadSkillFromTXT(char * argv[], usi pos) {
		ifstream fin;
		if (skillType == Attack) {
			const char PRJ_NAME[] = "5_RPG_KURSACH.exe";
			char *BD_NAME = "Skills_DMG.txt";
			char PATH[_MAX_PATH];   //260
			strcpy(PATH, argv[0]);
			char *p = strstr(PATH, PRJ_NAME);

			strcpy(p, BD_NAME);
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << BD_NAME << endl;
				system("pause");
				return NULL;
			}
		}
		else if (skillType == Heal) {
			const char PRJ_NAME[] = "5_RPG_KURSACH.exe";
			char *BD_NAME = "Skills_HEAL.txt";
			char PATH[_MAX_PATH];   //260
			strcpy(PATH, argv[0]);
			char *p = strstr(PATH, PRJ_NAME);

			strcpy(p, BD_NAME);
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << BD_NAME << endl;
				system("pause");
				return NULL;
			}
		}

		/*fin.seekg(0);
		for (usi i = 0; fin.peek() != EOF; i++) {
		fin.get();
		}*/

		fin.getline(name, 50);
		fin.getline(description, 100);

		if (skillType == Attack) {
			bool tmp;
			fin >> tmp;
			dSkill.isRange = tmp;
			fin >> tmp;
			dSkill.isMagic = tmp;
			fin >> dSkill.attackType;
			fin >> dSkill.BaseDMG;
		}
		else if (skillType == Heal) {
			fin >> hSkill.BaseHeal;
		}

		fin.close();
		//Це вообще законно?!
		return this;
	}
	void PrintInfo() {
		cout << name << endl;
		cout << description << endl;
		enum AttackType { PIERSING, CRUSHING, CUTTER, MAGIC_GENERAL_ATC = 10, MAGIC_FIRE_ATC, MAGIC_WATER_ATC, MAGIC_EARTH_ATC, MAGIC_AIR_ATC, MAGIC_DARK_ATC, MAGIC_LIGHT_ATC };
		if (skillType == Attack) {
			cout << dSkill.isRange;
			cout << dSkill.isMagic;
			cout << dSkill.attackType;
			cout << dSkill.BaseDMG;
		}
		else if (skillType == Heal) {
			cout << "Heal Skill: ";
			cout << name << endl;
			cout << "\t" << description;
			cout << "Heal Mod";
			cout << hSkill.BaseHeal;
		}
	}

};

struct Mob {
	char name[32];
	usi race;
	//main characters
	usi strength, agility, intelligence, endurance, luck;
	//based on strength
	usi meleeDMGMin, meleeDMGMax, meleeBlock;
	//based on agility
	usi hitChance;
	usi rangeDMGMin, rangeDMGMax, rangeAvoid;
	//based on intelligence
	usi magicGMG;
	usi magicResist[MAGIC_CNT];
	//based on endurance
	short int HPMax, HPCurrent, HPHeal;
	//based on luck
	usi luckMod;
	//Level and XP
	unsigned int XPToNextLVL, currentXP;
	usi LVL;
	//Armor
	int armorType, armorNum, armorPersent;
	//Weapon
	AttackType weaponStdAtack;

	//В цих каунтерах зберiгається кiлькiсть скiлiв i предметiв.
	usi equipedItemsCNT, skillsCNT, inventoryCNT;
	//В цих масивах зберiгається позицiя скiла i предмета у файлi.
	items_s equipedItems[SlotsCnt];
	skill *skills;
	items_s *inventory;
	unsigned int money;
	int arenaCnt;

	LOG_STRC *log;
	void LOG_STRC_Getptr(LOG_STRC *log) {
		this->log = log;
	}
	int DoDMGStandart(bool isRange, bool isMagic, AttackType attackType, double minDMGMultiple, double maxDMGMultiple, double hitChanseMultiple, Mob &attacker) {
		//20 не броня, 41 - 46 - типи атаки. 
		//41 - PIERSING, 42 - CRUSHING, 43 - CUTTER
		//44 - PIERSING + CRUSHING, 45 - PIERSING + CUTTER, 47 - CUTTER + CRUSHING
		//46 - PIERSING + CRUSHING + CUTTER
		enum AttackType { PIERSING, CRUSHING, CUTTER, MAGIC_GENERAL_ATC = 10, MAGIC_FIRE_ATC, MAGIC_WATER_ATC, MAGIC_EARTH_ATC, MAGIC_AIR_ATC, MAGIC_DARK_ATC, MAGIC_LIGHT_ATC };
		enum DefenseType { WITHOUT_ARMOR, LIGHT, MEDIUM, HEAVY, MAGIC, GOD, DEAMON, DEF_CNT };
		enum MagicResist { MAGIC_GENERAL, MAGIC_FIRE, MAGIC_WATER, MAGIC_EARTH, MAGIC_AIR, MAGIC_DARK, MAGIC_LIGHT, MAGIC_CNT };
		if (attacker.hitChance * hitChanseMultiple >= rand() % 100 + 1) {
			if (isRange == 1) {

			}
			else if (isMagic == 1) {

			}
			else {
				//Физический, касание
				if (attackType == PIERSING) {
					if (
						PIERSING == attacker.weaponStdAtack ||
						41 == attacker.weaponStdAtack ||
						44 == attacker.weaponStdAtack ||
						45 == attacker.weaponStdAtack ||
						46 == attacker.weaponStdAtack
						) {
						int expectedDMG = (rand() % (int)((maxDMGMultiple * attacker.meleeDMGMax) - (minDMGMultiple * meleeDMGMin) + 1) + (minDMGMultiple* meleeDMGMin));
						cout << attacker.name << " наносить " << expectedDMG << " урона" << endl;
						return expectedDMG;
					}
					else {
						cout << attacker.name << " Використовує скiл, який не пiдходить для його зброї!" << endl;
						char str[100];
						strcpy(str, attacker.name);
						strcat(str, " Використовує скiл, який не пiдходить для його зброї!");
						attacker.log->print(str);
						return 0;
					}
				}
				else if (attackType == CRUSHING) {
					if (
						CRUSHING == attacker.weaponStdAtack ||
						42 == attacker.weaponStdAtack ||
						44 == attacker.weaponStdAtack ||
						47 == attacker.weaponStdAtack ||
						46 == attacker.weaponStdAtack
						) {
						int expectedDMG = (rand() % (int)((maxDMGMultiple * attacker.meleeDMGMax) - (minDMGMultiple * meleeDMGMin) + 1) + (minDMGMultiple* meleeDMGMin));
						cout << attacker.name << " наносить " << expectedDMG << " урона" << endl;
						return expectedDMG;
					}
					else {
						cout << attacker.name << " Використовує скiл, який не пiдходить для його зброї!" << endl;
						char str[100];
						strcpy(str, attacker.name);
						strcat(str, " Використовує скiл, який не пiдходить для його зброї!");
						attacker.log->print(str);
						return 0;
					}
				}
				else if (attackType == CUTTER) {
					if (
						CUTTER == attacker.weaponStdAtack ||
						45 == attacker.weaponStdAtack ||
						46 == attacker.weaponStdAtack ||
						47 == attacker.weaponStdAtack ||
						43 == attacker.weaponStdAtack
						) {
						int expectedDMG = (rand() % (int)((maxDMGMultiple * attacker.meleeDMGMax) - (minDMGMultiple * meleeDMGMin) + 1) + (minDMGMultiple* meleeDMGMin));
						cout << attacker.name << " наносить " << expectedDMG << " урона" << endl;
						return expectedDMG;
					}
					else {
						cout << attacker.name << " Використовує скiл, який не пiдходить для його зброї!" << endl;
						char str[100];
						strcpy(str, attacker.name);
						strcat(str, " Використовує скiл, який не пiдходить для його зброї!");
						attacker.log->print(str);
						return 0;
					}
				}
			}
		}
		else {
			cout << attacker.name << " промахується!" << endl;
			char str[100];
			strcpy(str, attacker.name);
			strcat(str, " промахується!");
			attacker.log->print(str);
			return 0;
		}
	}
	void GetDMGStandart(bool isRange, bool isMagic, AttackType attackType, int DMG, Mob &defender) {
		if (isRange == 1) {

		}
		else if (isMagic == 1) {

		}
		else {
			//Физический, касание
			if (attackType == PIERSING) {
				int expectedDMG;
				if (defender.armorPersent > 0)
					expectedDMG = DMG / 100 * defender.armorPersent;
				else
					expectedDMG = DMG;

				if (defender.armorType == WITHOUT_ARMOR) {
					cout << defender.name << " отримав " << expectedDMG * 1.2 << " урона.";
					defender.HPCurrent -= expectedDMG * 1.2;
				}
				else if (defender.armorType == LIGHT) {
					cout << defender.name << " отримав " << expectedDMG * 1.2 << " урона.";
					defender.HPCurrent -= expectedDMG * 1.2;
				}
				else if (defender.armorType == MEDIUM) {
					cout << defender.name << " отримав " << expectedDMG * 0.8 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.8;
				}
				else if (defender.armorType == HEAVY) {
					cout << defender.name << " отримав " << expectedDMG << " урона.";
					defender.HPCurrent -= expectedDMG;
				}
				else if (defender.armorType == MAGIC) {
					cout << defender.name << " отримав " << expectedDMG * 0.5 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.5;
				}
				else if (defender.armorType == GOD) {
					cout << defender.name << " отримав " << expectedDMG * 0.1 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.1;
				}
				else if (defender.armorType == DEAMON) {
					cout << defender.name << " отримав " << expectedDMG * 0.666 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.666;
				}

				char str[100];
				strcpy(str, defender.name);
				strcat(str, " отримав ");
				defender.log->print(str);
				defender.log->print(expectedDMG);
				defender.log->print(" урона.");
			}
			else if (attackType == CRUSHING) {
				int expectedDMG;
				if (defender.armorPersent > 0)
					expectedDMG = DMG / 100 * defender.armorPersent;
				else
					expectedDMG = DMG;

				if (defender.armorType == WITHOUT_ARMOR) {
					cout << defender.name << " отримав " << expectedDMG * 1.2 << " урона.";
					defender.HPCurrent -= expectedDMG * 1.2;
				}
				else if (defender.armorType == LIGHT) {
					cout << defender.name << " отримав " << expectedDMG * 0.8 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.8;
				}
				else if (defender.armorType == MEDIUM) {
					cout << defender.name << " отримав " << expectedDMG * 1 << " урона.";
					defender.HPCurrent -= expectedDMG * 1;
				}
				else if (defender.armorType == HEAVY) {
					cout << defender.name << " отримав " << expectedDMG * 1.2 << " урона.";
					defender.HPCurrent -= expectedDMG * 1.2;
				}
				else if (defender.armorType == MAGIC) {
					cout << defender.name << " отримав " << expectedDMG * 0.5 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.5;
				}
				else if (defender.armorType == GOD) {
					cout << defender.name << " отримав " << expectedDMG * 0.1 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.1;
				}
				else if (defender.armorType == DEAMON) {
					cout << defender.name << " отримав " << expectedDMG * 0.666 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.666;
				}

				char str[100];
				strcpy(str, defender.name);
				strcat(str, " отримав ");
				defender.log->print(str);
				defender.log->print(expectedDMG);
				defender.log->print(" урона.");
			}
			else if (attackType == CUTTER) {
				int expectedDMG;
				if (defender.armorPersent > 0)
					expectedDMG = DMG / 100 * defender.armorPersent;
				else
					expectedDMG = DMG;

				if (defender.armorType == WITHOUT_ARMOR) {
					cout << defender.name << " отримав " << expectedDMG * 1.2 << " урона.";
					defender.HPCurrent -= expectedDMG * 1.2;
				}
				else if (defender.armorType == LIGHT) {
					cout << defender.name << " отримав " << expectedDMG * 1 << " урона.";
					defender.HPCurrent -= expectedDMG * 1;
				}
				else if (defender.armorType == MEDIUM) {
					cout << defender.name << " отримав " << expectedDMG * 1.2 << " урона.";
					defender.HPCurrent -= expectedDMG * 1.2;
				}
				else if (defender.armorType == HEAVY) {
					cout << defender.name << " отримав " << expectedDMG * 0.8 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.8;
				}
				else if (defender.armorType == MAGIC) {
					cout << defender.name << " отримав " << expectedDMG * 0.5 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.5;
				}
				else if (defender.armorType == GOD) {
					cout << defender.name << " отримав " << expectedDMG * 0.1 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.1;
				}
				else if (defender.armorType == DEAMON) {
					cout << defender.name << " отримав " << expectedDMG * 0.666 << " урона.";
					defender.HPCurrent -= expectedDMG * 0.666;
				}

				char str[100];
				strcpy(str, defender.name);
				strcat(str, " отримав ");
				defender.log->print(str);
				defender.log->print(expectedDMG);
				defender.log->print(" урона.");
			}
		}
	}
	void AddAllItemBonus() {
		for (usi i = 0; i < SlotsCnt; i++) {
			if (equipedItems[i].posInBD != -1) {
				//based on strength
				meleeDMGMin += equipedItems[i].meleeDMGMin;
				meleeDMGMax += equipedItems[i].meleeDMGMax;
				meleeBlock += equipedItems[i].meleeBlock;
				//based on agility
				hitChance += equipedItems[i].hitChance;
				rangeDMGMin += equipedItems[i].rangeDMGMin;
				rangeDMGMax += equipedItems[i].rangeDMGMax;
				rangeAvoid += equipedItems[i].rangeAvoid;
				//based on intelligence
				magicGMG += equipedItems[i].magicGMG;
				magicResist[MAGIC_CNT] += equipedItems[i].magicResist[MAGIC_CNT];
				//based on endurance
				HPMax += equipedItems[i].HPMax;
				HPHeal += equipedItems[i].HPHeal;
				//based on luck
				luckMod += equipedItems[i].luckMod;

				//20 не броня, 41 - 46 - типи атаки. 
				//41 - PIERSING, 42 - CRUSHING, 43 - CUTTER
				//44 - PIERSING + CRUSHING, 45 - PIERSING + CUTTER, 47 - CUTTER + CRUSHING
				//46 - PIERSING + CRUSHING + CUTTER
				if (equipedItems[i].armorType != 20 &&
					equipedItems[i].armorType != 41 &&
					equipedItems[i].armorType != 42 &&
					equipedItems[i].armorType != 43 &&
					equipedItems[i].armorType != 44 &&
					equipedItems[i].armorType != 45 &&
					equipedItems[i].armorType != 46 &&
					equipedItems[i].armorType != 47
					) {
					armorType = equipedItems[i].armorType;
				}
				else if (equipedItems[i].armorType == 41 ||
					equipedItems[i].armorType == 42 ||
					equipedItems[i].armorType == 43 ||
					equipedItems[i].armorType == 44 ||
					equipedItems[i].armorType == 45 ||
					equipedItems[i].armorType == 46 ||
					equipedItems[i].armorType == 47
					) {
					if (equipedItems[i].armorType == 41)
						weaponStdAtack = PIERSING;
					else if (equipedItems[i].armorType == 42)
						weaponStdAtack = CRUSHING;
					else if (equipedItems[i].armorType == 43)
						weaponStdAtack = CUTTER;
				}
				armorNum += equipedItems[i].armorNum;
			}
		}
	}
	void LVL_UP() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		short int CP = 1;
		if (XPToNextLVL <= currentXP) {
			LVL++;
			currentXP -= XPToNextLVL;
			XPToNextLVL *= 1.5;
			log->print("Новий рiвень персонажа");
			cout << "LVL пiдвищується до " << LVL << endl;
			cout << "Отримано 2 очка характеристик" << endl;
			while (CP <= 2) {
				usi chose = 10;
				cout << "Куди вкинути " << CP << " очко?" << endl;
				cout << "[1] - STR" << endl;
				cout << "[2] - AGI" << endl;
				cout << "[3] - INT" << endl;
				cout << "[4] - END" << endl;
				do {
					char tmp;
					cout << ">";
					tmp = getch();

					//cout << isalpha(tmp) << endl;
					if (tmp == '?') {
						cout << endl << "Виберiть куди вкласти новi ";
						blue;
						cout << "очки харектеристик";
						grey;
						cout << ". Всього їх доступно 2." << endl;

						blue;
						cout << "STR";
						grey;
						cout << " - Збiльшує ";
						blue;
						cout << "урон ближнього бою";
						grey;
						cout << " i ";
						blue;
						cout << "шанс блоку" << endl;
						grey;

						blue;
						cout << "AGI";
						grey;
						cout << " - Збiльшує ";
						blue;
						cout << "урон дальнього бою";
						grey;
						cout << ", ";
						blue;
						cout << "шанс попадання";
						grey;
						cout << " i ";
						blue;
						cout << "шанс ухилитися" << endl;
						grey;

						blue;
						cout << "INT";
						grey;
						cout << " - Збiльшує";
						blue;
						cout << " урон магiї";
						grey;
						cout << " i ";
						blue;
						cout << "опiр магiї" << endl;
						grey;


						blue;
						cout << "END";
						grey;
						cout << " - Збiльшує ";
						blue;
						cout << "HP";
						grey;
						cout << " i ";
						blue;
						cout << "зцiлення" << endl;
						grey;
						blue;
						cout << "LUCK";
						grey;
						cout << " - Впливає на все потроху. Збiльшити звичайним методом неможливо" << endl;
					}
					else if (isalpha(tmp) == 0)
						chose = tmp - '0';
				} while (!(chose >= 1 && chose <= 4));
				if (chose == 1)
					strength++;
				else if (chose == 2)
					agility++;
				else if (chose == 3)
					intelligence++;
				else if (chose == 4)
					endurance++;
				CP++;
				system("cls");
			}
		}
	}
	void RecalcStats() {
		armorNum = armorType = 0;

		luckMod = ceil(ceil(luck / 10.) / 2.);

		meleeDMGMin = strength / 3;
		meleeDMGMax = strength / 2;
		meleeBlock = strength / 4 + luckMod;

		hitChance = 50 + agility / 10;
		rangeDMGMin = agility / 4;
		rangeDMGMax = agility / 3;
		rangeAvoid = agility / 4 + luckMod;

		magicGMG = intelligence / 4;
		magicResist[MAGIC_GENERAL] = intelligence / 6;
		for (usi i = 1; i < MAGIC_CNT; i++)
			magicResist[i] = 0;

		HPMax = endurance * 3 + LVL * 2;
		
		HPHeal = HPMax / 4;

		const float ArmorMult = 0.06;
		armorPersent = (((armorNum)* ArmorMult) / (1 + ArmorMult * (armorNum))) * 100;
		log->print("Перерахованi стати для персонажа");
		AddAllItemBonus();
		log->print("Перерахованi стати для персонажа + шмот");
		HPCurrent = HPMax;
	}
	void PrintInfo() {
		cout << name << "  ";
		if (race == HUMAN)
			cout << "Human";
		if (race == ORC)
			cout << "Orc";
		else if (race == ELF)
			cout << "Elf";
		else if (race == KOBOLD)
			cout << "Kobold";
		cout << endl;

		cout << "LVL: " << LVL << "  " << currentXP << "/" << XPToNextLVL << "   (" << currentXP*1. / XPToNextLVL * 100 << "%)" << endl << endl;

		cout << "Armor: ";
		if (armorType == WITHOUT_ARMOR)
			cout << "without armor ";
		else if (armorType == LIGHT)
			cout << "light ";
		else if (armorType == MEDIUM)
			cout << "medium ";
		else if (armorType == HEAVY)
			cout << "heavy ";
		else if (armorType == MAGIC)
			cout << "magic ";
		cout << armorNum << " - " << armorPersent << "%" << endl << endl;

		cout << "STR: " << strength << endl;
		cout << "\tMelee DMG: " << meleeDMGMin << " - " << meleeDMGMax << endl;
		cout << "\tMelee block: " << meleeBlock << "%" << endl;

		cout << "AGI: " << agility << endl;
		cout << "\tRange DMG: " << rangeDMGMin << " - " << rangeDMGMax << endl;
		cout << "\tHit chance: " << hitChance << "%" << endl;
		cout << "\tAvoid chance: " << rangeAvoid << "%" << endl;

		cout << "INT: " << intelligence << endl;
		cout << "\tMagic DMG: " << magicGMG << endl;
		cout << "\tMagic resistent: " << magicResist[MAGIC_GENERAL] << "%" << endl;

		cout << "END: " << endurance << endl;
		cout << "\tMax HP: " << HPMax << endl;
		cout << "\tCurrent HP: " << HPCurrent << endl;
		cout << "\tHeal: " << HPHeal << endl;

		cout << "Luck: " << luck << endl;
		cout << "\tLuck mod: " << luckMod << endl;

		cout << "Special magic resistent: " << endl;
		cout << "\t Fire: " << magicResist[MAGIC_FIRE] << "%" << endl;
		cout << "\t Water: " << magicResist[MAGIC_WATER] << "%" << endl;
		cout << "\t Earth: " << magicResist[MAGIC_EARTH] << "%" << endl;
		cout << "\t Air: " << magicResist[MAGIC_AIR] << "%" << endl;
		cout << "\t Dark: " << magicResist[MAGIC_DARK] << "%" << endl;
		cout << "\t Light: " << magicResist[MAGIC_LIGHT] << "%" << endl << endl;
	}
	void FirstFillPlayer(char *name) {
		weaponStdAtack = CRUSHING;
		LVL = 1;
		currentXP = 0;
		XPToNextLVL = 1000;
		arenaCnt = 1;

		cout << "Виберiть расу:" << endl;
		cout << "[1] Людина" << endl;
		cout << "\t" << "Всi стати по 10" << endl;
		cout << "[2] Орк" << endl;
		cout << "\t" << "+ 5 до STR i END" << endl;
		cout << "\t" << "- 5 до AGI i INT" << endl;
		cout << "[3] Ельф" << endl;
		cout << "\t" << "+ 5 до AGI i INT" << endl;
		cout << "\t" << "- 5 до STR i END" << endl;
		cout << "[4] Кобольд" << endl;
		cout << "\t" << "+ 5 до AGI i END" << endl;
		cout << "\t" << "- 5 до INT i STR" << endl;
		do {
			cin >> race;
		} while (race < 1 && race > 4);
		system("cls");
		race--;
		strength = agility = intelligence = endurance = luck = 10;

		if (race == ORC) {
			strength += 5;
			endurance += 5;
			agility -= 5;
			intelligence -= 5;
		}
		else if (race == ELF) {
			agility += 5;
			intelligence += 5;
			strength -= 5;
			endurance -= 5;
		}
		else if (race == KOBOLD) {
			agility += 5;
			endurance += 5;
			strength -= 5;
			intelligence -= 5;
		}

		strcpy(this->name, name);
		armorType = WITHOUT_ARMOR;
		armorNum = 0;
		equipedItemsCNT = skillsCNT = inventoryCNT = 0;
		money = 100;
		for (usi i = 0; i < SlotsCnt; i++)
			equipedItems[i].posInBD = -1;
	}
	void SavePlayer(char * argv[], char *Slot) {
		const char PRJ_NAME[] = "5_RPG_KURSACH.exe";
		char *BD_NAME = new char[strlen(Slot) + 1];
		strcpy(BD_NAME, Slot);
		char PATH[_MAX_PATH];   //260
		strcpy(PATH, argv[0]);
		char *p = strstr(PATH, PRJ_NAME);

		ofstream fout;
		strcpy(p, BD_NAME);

		fout.open(PATH);
		if (!fout.is_open()) {
			cout << "Cant open " << BD_NAME << endl;
			system("pause");
			return;
		}

		fout << name << '\n';
		fout << race << '\n';
		fout << " " << strength << " " << agility << " " << intelligence << " " << endurance << " " << luck << " " << '\n';
		fout << " " << LVL << " " << currentXP << " " << XPToNextLVL << '\n';
		fout << arenaCnt << '\n';
		fout << " " << equipedItemsCNT << " " << skillsCNT << " " << inventoryCNT << '\n';
		fout << " " << money << '\n';

		for (usi i = 0; i < SlotsCnt; i++)
			fout << equipedItems[i].posInBD << " ";
		fout << '\n';
		for (usi i = 0; i < inventoryCNT; i++) {
			fout << inventory[i].posInBD << " ";
		}
		fout << '\n';

		delete[] BD_NAME;
		fout.close();
	}
	void LoadPlayer(char * argv[], char *Slot, int isMob = 0) {
		if (isMob == 0) {
			const char PRJ_NAME[] = "5_RPG_KURSACH.exe";
			char *BD_NAME = new char[strlen(Slot) + 1];
			if (isMob == 0)
				strcpy(BD_NAME, Slot);
			char PATH[_MAX_PATH];   //260
			strcpy(PATH, argv[0]);
			char *p = strstr(PATH, PRJ_NAME);

			ifstream fin;
			strcpy(p, BD_NAME);

			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << BD_NAME << endl;
				system("pause");
				return;
			}

			armorNum = armorType = 0;
			weaponStdAtack = CRUSHING;

			fin >> name;
			fin >> race;
			fin >> strength >> agility >> intelligence >> endurance >> luck;
			fin >> LVL >> currentXP >> XPToNextLVL;
			fin >> arenaCnt;
			fin >> equipedItemsCNT >> skillsCNT >> inventoryCNT;
			fin >> money;

			for (usi i = 0; i < SlotsCnt; i++) {
				fin >> equipedItems[i].posInBD;
				if (equipedItems[i].posInBD != -1) {
					items_s *it = new items_s;
					equipedItems[i] = it->ReadItemFromTXT(argv, equipedItems[i].posInBD);
				}
			}



			usi _TMP_inventoryCNT = 0;
			for (usi i = 0; i < inventoryCNT; i++) {
				items_s *it = new items_s;
				ArrPushBack(inventory, _TMP_inventoryCNT);
				fin >> inventory[i].posInBD;
				inventory[i] = it->ReadItemFromTXT(argv, inventory[i].posInBD);
			}
			delete[] BD_NAME;
			fin.close();
			RecalcStats();
		}
		else {
			const char PRJ_NAME[] = "5_RPG_KURSACH.exe";
			char *BD_NAME = "Mobs\\mobs.txt";
			char PATH[_MAX_PATH];   //260
			strcpy(PATH, argv[0]);
			char *p = strstr(PATH, PRJ_NAME);

			ifstream fin;
			strcpy(p, BD_NAME);
			fin.open(PATH);
			if (!fin.is_open()) {
				cout << "Cant open " << BD_NAME << endl;
				system("pause");
			}

			fin.seekg(0);
			for (usi i = 0; fin.peek() != EOF; i++) {
				char ch1 = fin.get();

				if (ch1 == ':') {
					char ch2 = fin.get();
					if (ch2 == ':') {
						char ch3 = fin.get();
						if (ch3 == ':') {
							char chPos[32] = { '\0' };
							usi i = 0;
							fin.getline(chPos, 9);

							int CurrSkillPos = -1;
							CurrSkillPos = atoi(chPos);
							if (CurrSkillPos == isMob) {
								armorNum = armorType = 0;
								

								fin >> name;
								fin >> race;
								weaponStdAtack = AttackType(race);
								fin >> strength >> agility >> intelligence >> endurance >> luck;
								fin >> LVL >> currentXP >> XPToNextLVL;
								fin >> arenaCnt;
								fin >> equipedItemsCNT >> skillsCNT >> inventoryCNT;
								fin >> money;

								for (usi i = 0; i < SlotsCnt; i++) {
									fin >> equipedItems[i].posInBD;
									if (equipedItems[i].posInBD != -1) {
										items_s *it = new items_s;
										equipedItems[i] = it->ReadItemFromTXT(argv, equipedItems[i].posInBD);
									}
								}



								usi _TMP_inventoryCNT = 0;
								for (usi i = 0; i < inventoryCNT; i++) {
									items_s *it = new items_s;
									ArrPushBack(inventory, _TMP_inventoryCNT);
									fin >> inventory[i].posInBD;
									inventory[i] = it->ReadItemFromTXT(argv, inventory[i].posInBD);
								}

								RecalcStats();
							}
						}
					}
				}
			}

			fin.close();
		}
	}
	void DoNull(char * argv[], char *Slot) {
		const char PRJ_NAME[] = "5_RPG_KURSACH.exe";
		char *BD_NAME = new char[strlen(Slot) + 1];
		strcpy(BD_NAME, Slot);
		char PATH[_MAX_PATH];   //260
		strcpy(PATH, argv[0]);
		char *p = strstr(PATH, PRJ_NAME);

		ofstream fout;
		strcpy(p, BD_NAME);

		fout.open(PATH);
		if (!fout.is_open()) {
			cout << "Cant open " << BD_NAME << endl;
			system("pause");
			return;
		}

		fout << "Lol,_%USERNAME%_died" << '\n';
		fout << race << '\n';
		fout << " " << 5 << " " << 5 << " " << 5 << " " << 5 << " " << luck << " " << '\n';
		fout << " " << 1 << " " << 0 << " " << 1000 << '\n';
		fout << 0 << '\n';
		fout << " " << 0 << " " << 0 << " " << 0 << '\n';
		fout << " " << 0 << '\n';

		for (usi i = 0; i < SlotsCnt; i++)
			fout << -1 << " ";
		fout << '\n';
		fout << '\n';

		delete[] BD_NAME;
		fout.close();
	};
};

int* _FoundInMtx(char arr[22][22], char fnd) {
	int *pos = new int[2];
	pos[0] = pos[1] = -1;

	for (usi i = 0; i < 22; i++)
		for (usi j = 0; j < 22; j++)
			if (fnd == arr[i][j]) {
				pos[0] = i;
				pos[1] = j;
				return pos;
			}

	return pos;
}

char Input_in_scene(Scene scene) {
	char choise;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (scene) {
	case MAIN_MENU:
	{
	REPEAT_INPUT_MAIN_MENU:
		cout << ">";
		do {
			choise = getch();
		} while (!((choise >= '0' && choise <= '3') ||
			choise == '?'
			));
		if (choise == '?') {
			cout << "Просто вибери пунк меню. Все прозоро!" << endl;
			goto REPEAT_INPUT_MAIN_MENU;
		}
	}
	break;
	case LOAD_MENU:
	{
	REPEAT_INPUT_LOAD_MENU:
		cout << ">";
		do {
			choise = getch();
		} while (!((choise >= '1' && choise <= '3') ||
			choise == '?'
			));
		if (choise == '?') {
			cout << "Всьго 3 слоти. Немає 4, 5 чи -1. Тут ВЗАГАЛi це не потрiбно. Але хай буде..." << endl;
			goto REPEAT_INPUT_LOAD_MENU;
		}
	}
	break;
	case TOWN_CHOISE:
	{
	REPEAT_IN_TOWN_CHOISE:
		cout << ">";
		do {
			choise = getch();
			choise = tolower(choise);
		} while (!(
			choise == 'f' || choise == 'F' ||
			choise == 's' || choise == 'S' ||
			choise == 't' || choise == 'T' ||
			choise == 'r' || choise == 'R' ||
			choise == 'b' || choise == 'B' ||
			choise == 'c' || choise == 'C' ||
			choise == '0' ||
			choise == '?'
			));

		if (choise == '?') {
			cout << endl;
			cout << "[";
			red;
			cout << "F";
			grey;
			cout << "ight] - Вибрати одну з "; \
				blue;
			cout << '9';
			grey;
			cout << " локацiй i пiти в";
			blue;
			cout << " бiй" << endl;
			grey;

			cout << "[";
			red;
			cout << "S";
			grey;
			cout << "hop] - вибрати нову ";
			blue;
			cout << "екiпiровку " << endl;
			grey;

			cout << "Skills[";
			red;
			cout << "T";
			grey;
			cout << "] - вивчити новi ";
			blue;
			cout << "вмiння " << endl;
			grey;

			cout << "[";
			red;
			cout << "R";
			grey;
			cout << "est] - пiдвищити  ";
			blue;
			cout << "рiвень " << endl;
			grey;

			cout << "[";
			red;
			cout << "B";
			grey;
			cout << "ackpack] - ";
			blue;
			cout << "iнвентар ";
			grey;
			cout << "/ ";
			blue;
			cout << "екiпiрування речей";
			grey;
			cout << " / ";
			blue;
			cout << "продаж " << endl;
			grey;

			cout << "[";
			red;
			cout << "C";
			grey;
			cout << "haracter list] - вивiд всiх  ";
			blue;
			cout << "стат " << endl;
			grey;

			cout << "(Тут ввiд НЕ регiстрозалежний)" << endl;
			goto REPEAT_IN_TOWN_CHOISE;
		}
	}
	break;
	case INVENTORY_CHOISE:
	{
	REPEAT_INPUT_INVENTORY_CHOISE :
	cout << ">";
	do {
	choise = getch();
	choise = tolower(choise);
	} while (!(
		choise == 's' ||
		choise == 'w' ||
		choise == 'r' ||
		choise == 'e' ||
		choise == 'b' ||
		choise == '0' ||
		choise == '?'
	));
	if (choise == '?') {
	cout << endl;

	cout << "[";
	red;
	cout << "S";
	grey;
	cout << "ell] - продати стару ";
	blue;
	cout << "екiпiровку " << endl;
	grey;

	cout << "[";
	red;
	cout << "W";
	grey;
	cout << "ear] - одягти ";
	blue;
	cout << "екiпiровку " << endl;
	grey;

	cout << "[d";
	red;
	cout << "R";
	grey;
	cout << "op] - Зняти ";
	blue;
	cout << "екiпiровку " << endl;
	grey;

	cout << "[";
	red;
	cout << "E";
	grey;
	cout << "quipment] - показати ";
	blue;
	cout << "екiпiровку " << endl;
	grey;

	cout << "[";
	red;
	cout << "B";
	grey;
	cout << "ackpack] - показати весь ";
	blue;
	cout << "iнвентар " << endl;
	grey;

	cout << "(Тут ввiд НЕ регiстрозалежний)" << endl;
	cout << "(";
	blue;
	cout << "ID ";
	grey;
	cout << "предмета береться з iнвентаря[";
	red;
	cout << "B";
	grey;
	cout << "]. Виняток лише для [d";
	red;
	cout << "R";
	grey;
	cout << "op] - там";
	blue;
	cout << " ID ";
	grey;
	cout << "треба брати з";
	cout << "[";
	red;
	cout << "E";
	grey;
	cout << "quipment] )" << endl;

	goto REPEAT_IN_TOWN_CHOISE;
	}
	}
	break;
	case BATTLE_SCENE:
	{
	REPEAT_IN_BATTLE_SCENE:
		cout << ">";
		do {
			choise = getch();
			choise = tolower(choise);
		} while (!(
			choise == '1' ||
			choise == '0' ||
			choise == '?'
			));
		if (choise == '?') {
			cout << endl;
			cout << "[1] - yes" << endl;
			cout << "[0] - no" << endl;
			cout << "За кожнi 3 бої пiдряд дає шмотку" << endl;
			cout << "X/5 - це кiлькiсть вбивст ворогiв цього рiвня. 5/5 означаж що на наступний раз буде новий тип" << endl;
			goto REPEAT_IN_BATTLE_SCENE;
		}
	}
	break;
	}
	return choise;
}

int PlayerInputBattle(int scene, Mob &player) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char input;
REPEAT_INPUT_MAN:
	cout << ">";
	input = getch();
	if (input == '?') {
		cout << endl;
		cout << "[";
		red;
		cout << "wasd";
		grey;
		cout << "] - ";
		blue;
		cout << "рух" << endl;
		grey;

		cout << "[";
		red;
		cout << "wasd";
		grey;
		cout << "](Впритик до ворога) - ";
		blue;
		cout << "Стандартна атака ";
		grey;
		cout << "в ближньому бою" << endl;

		cout << "[";
		red;
		cout << "Shift";
		grey;
		cout << "]+[";
		red;
		cout << "wasd";
		grey;
		cout << "](Впритик до ворога) - ";
		blue;
		cout << " Силова атака ";
		grey;
		cout << "в ближньому бою" << endl;

		cout << "[";
		red;
		cout << "c";
		grey;
		cout << "] - ";
		blue;
		cout << "Лист персонажа" << endl;
		grey;

		cout << "[";
		red;
		cout << "b";
		grey;
		cout << "] - ";
		blue;
		cout << "Екiпiровка" << endl;
		grey;

		//Ще нема
		//cout << "ijkl атака по замовчуванню в Н сторону " << endl;
		//cout << "ИД скила - использовать скил. А потiм ijkl" << endl;
		goto REPEAT_INPUT_MAN;
	}
	else if (input == 'c') {
		player.PrintInfo();
		goto REPEAT_INPUT_MAN;
	}
	else if (input == 'b') {
		cout << endl;
		for (usi i = 0; i < SlotsCnt; i++) {
			if (player.equipedItems[i].posInBD != -1) {
				cout << "ID: " << i + 1 << endl;
				player.equipedItems[i].PrintInfo();
			}
		}
		goto REPEAT_INPUT_MAN;
	}
	//cin >> input;
	//cout << input << endl;
	return input;
}

//0 - Живий, 1 - мертвий, 2 - втiк
int BattleField(Mob &player, Mob &enemy, int &playerPos1, int &playerPos2) {
	char enemyMarker = toupper( enemy.name[0] );

	char arr[22][22];
	for (usi i = 0; i < 22; i++) {
		for (usi j = 0; j < 22; j++) {
			arr[i][j] = ' ';
		}
	}
	//Y X
	usi posPlayer[2] = { 11, 11 };
	posPlayer[0] = playerPos1;
	posPlayer[1] = playerPos2;
	//Y X
	usi posEnemy[2];
	for (usi i = 0; i < 22; i++)
		for (usi j = 0; j < 22; j++)
			if (i == 0 || j == 0 || i == 21 || j == 21)
				arr[i][j] = ':';

	do {
		posEnemy[0] = rand() % 20 + 1;
		posEnemy[1] = rand() % 20 + 1;
	} while (posEnemy[0] == 11 && posEnemy[1] == 11);
	arr[posPlayer[0]][posPlayer[1]] = '@';
	arr[posEnemy[0]][posEnemy[1]] = enemyMarker;

	char input;
	bool playerDoTurn, botDoTurn;

	const int MAX_FRAME_CNT = 0;
	int frameCounter;

	int botPowerAtcCooldown = 0;
	int anotherMove = 0;

	for (usi i = 0; i < 22; i++) {
		for (usi j = 0; j < 22; j++) {
			cout << arr[i][j] << ends;
		}
		if (i == 0)
			cout << "\tPlayer: " << player.name << " " << player.LVL;
		if (i == 1)
			cout << "\t\tHP: " << player.HPCurrent << "/" << player.HPMax;
		if (i == 2)
			cout << "\t\tMana: " << player.HPCurrent << "/" << player.HPMax;
		if (i == 6)
			cout << "\tEnemy: " << enemy.name << " " << enemy.LVL;
		if (i == 7)
			cout << "\t\tHP: " << enemy.HPCurrent << "/" << enemy.HPMax;

		cout << endl;
	}
	while (player.HPCurrent > 0 && enemy.HPCurrent > 0) {
		//Ввод -> движение(єдина дiя, заради якої потрiбно оновити екран) -> оновити екран -> атаки

		//Ввiд
		input = PlayerInputBattle(0, player);
		playerDoTurn = botDoTurn = 0;
		system("cls");

		if (playerDoTurn == 0) {
			//Для руху
			switch (input) {
			case 'w': case 'a': case 's': case 'd':
			{
				if (input == 'w') {
					if (arr[posPlayer[0] - 1][posPlayer[1]] == ' ') {
						arr[posPlayer[0]][posPlayer[1]] = ' ';
						posPlayer[0]--;
						arr[posPlayer[0]][posPlayer[1]] = '@';
						playerDoTurn = 1;
						frameCounter = 0;
					}
				}
				else if (input == 's') {
					if (arr[posPlayer[0] + 1][posPlayer[1]] == ' ') {
						arr[posPlayer[0]][posPlayer[1]] = ' ';
						posPlayer[0]++;
						arr[posPlayer[0]][posPlayer[1]] = '@';
						playerDoTurn = 1;
						frameCounter = 0;
					}
				}
				else if (input == 'a') {
					if (arr[posPlayer[0]][posPlayer[1] - 1] == ' ') {
						arr[posPlayer[0]][posPlayer[1]] = ' ';
						posPlayer[1]--;
						arr[posPlayer[0]][posPlayer[1]] = '@';
						playerDoTurn = 1;
						frameCounter = 0;
					}
				}
				else if (input == 'd') {
					if (arr[posPlayer[0]][posPlayer[1] + 1] == ' ') {
						arr[posPlayer[0]][posPlayer[1]] = ' ';
						posPlayer[1]++;
						arr[posPlayer[0]][posPlayer[1]] = '@';
						playerDoTurn = 1;
						frameCounter = 0;
					}
				}
			}
			break;
			}
		}

		//Вивiд
		for (usi i = 0; i < 22; i++) {
			for (usi j = 0; j < 22; j++) {
				cout << arr[i][j] << ends;
			}
			if (i == 0)
				cout << "\tPlayer: " << player.name << " " << player.LVL;
			if (i == 1)
				cout << "\t\tHP: " << player.HPCurrent << "/" << player.HPMax;
			if (i == 2)
				cout << "\t\tMana: " << player.HPCurrent << "/" << player.HPMax;
			if (i == 6)
				cout << "\tEnemy: " << enemy.name << " " << enemy.LVL;
			if (i == 7)
				cout << "\t\tHP: " << enemy.HPCurrent << "/" << enemy.HPMax;

			cout << endl;
		}
		cout << endl;
		

		if (playerDoTurn == 0) {
			//Для атак в ближньому бою
			if (input == 'w' || input == 'W') {
				if (arr[posPlayer[0] - 1][posPlayer[1]] == enemyMarker) {
					if (input == 'w') {
						playerDoTurn = 1;
						enemy.GetDMGStandart(
							0, 
							0, 
							player.weaponStdAtack,
							player.DoDMGStandart(0, 0, player.weaponStdAtack, 1, 1, 1, player),
							enemy);
						cout << endl;
					}
					else if (input == 'W') {
						playerDoTurn = 1;
						enemy.GetDMGStandart(
							0,
							0,
							player.weaponStdAtack,
							player.DoDMGStandart(0, 0, player.weaponStdAtack, 1.5, 1.5, 0.75, player),
							enemy);
						cout << endl;
					}
				}
			}
			else if (input == 'd' || input == 'D') {
				if (arr[posPlayer[0]][posPlayer[1] + 1] == enemyMarker) {
					if (input == 'd') {
						playerDoTurn = 1;
						enemy.GetDMGStandart(
							0,
							0,
							player.weaponStdAtack,
							player.DoDMGStandart(0, 0, player.weaponStdAtack, 1, 1, 1, player),
							enemy);
						cout << endl;
					}
					else if (input == 'D') {
						playerDoTurn = 1;
						enemy.GetDMGStandart(
							0,
							0,
							player.weaponStdAtack,
							player.DoDMGStandart(0, 0, player.weaponStdAtack, 1.5, 1.5, 0.75, player),
							enemy);
						cout << endl;
					}
				}
			}
			else if (input == 'a' || input == 'A') {
				if (arr[posPlayer[0]][posPlayer[1] - 1] == enemyMarker) {
					if (input == 'a') {
						playerDoTurn = 1;
						enemy.GetDMGStandart(
							0,
							0,
							player.weaponStdAtack,
							player.DoDMGStandart(0, 0, player.weaponStdAtack, 1, 1, 1, player),
							enemy);
						cout << endl;
					}
					else if (input == 'A') {
						playerDoTurn = 1;
						enemy.GetDMGStandart(
							0,
							0,
							player.weaponStdAtack,
							player.DoDMGStandart(0, 0, player.weaponStdAtack, 1.5, 1.5, 0.75, player),
							enemy);
						cout << endl;
					}
				}
			}
			else if (input == 's' || input == 'S') {
				if (arr[posPlayer[0] + 1][posPlayer[1]] == enemyMarker) {
					if (input == 's') {
						playerDoTurn = 1;
						enemy.GetDMGStandart(
							0,
							0,
							player.weaponStdAtack,
							player.DoDMGStandart(0, 0, player.weaponStdAtack, 1, 1, 1, player),
							enemy);
						cout << endl;
					}
					else if (input == 'S') {
						playerDoTurn = 1;
						enemy.GetDMGStandart(
							0,
							0,
							player.weaponStdAtack,
							player.DoDMGStandart(0, 0, player.weaponStdAtack, 1.5, 1.5, 0.75, player),
							enemy);
						cout << endl;
					}
				}
			}
		}


REPEAT_BOT_TURN:
		if (playerDoTurn == 1) {
			if (arr[posEnemy[0] + 1][posEnemy[1]] == '@' ||
				arr[posEnemy[0] - 1][posEnemy[1]] == '@' ||
				arr[posEnemy[0]][posEnemy[1] + 1] == '@' ||
				arr[posEnemy[0]][posEnemy[1] - 1] == '@'
				) {
				botDoTurn = 1;
				if (botPowerAtcCooldown == 0) {
					player.GetDMGStandart(
						0,
						0,
						enemy.weaponStdAtack,
						enemy.DoDMGStandart(0, 0, enemy.weaponStdAtack, 1.5, 1.5, 0.75, enemy),
						player);
					cout << endl;
					botPowerAtcCooldown = 5;
				}
				else {
					player.GetDMGStandart(
						0,
						0,
						enemy.weaponStdAtack,
						enemy.DoDMGStandart(0, 0, enemy.weaponStdAtack, 1, 1, 1, enemy),
						player);
					--botPowerAtcCooldown;
				}
			}

			if (botDoTurn == 0) {
				if (anotherMove == 2 || anotherMove == 0) {
					if (posPlayer[0] - 1 > posEnemy[0]) {
						botDoTurn = 1;
						posEnemy[0]++;
						swap(arr[posEnemy[0]][posEnemy[1]], arr[posEnemy[0] - 1][posEnemy[1]]);
						anotherMove = 1;
					}
					else if (posPlayer[0] + 1 < posEnemy[0]) {
						botDoTurn = 1;
						posEnemy[0]--;
						swap(arr[posEnemy[0]][posEnemy[1]], arr[posEnemy[0] + 1][posEnemy[1]]);
						anotherMove = 1;
					}
				}
			}
			if (botDoTurn == 0) {
				if (anotherMove == 1 || anotherMove == 0) {
					if (posPlayer[1] > posEnemy[1]) {
						botDoTurn = 1;
						posEnemy[1]++;
						swap(arr[posEnemy[0]][posEnemy[1]], arr[posEnemy[0]][posEnemy[1] - 1]);
						anotherMove = 2;
					}
					else if (posPlayer[1] < posEnemy[1]) {
						botDoTurn = 1;
						posEnemy[1]--;
						swap(arr[posEnemy[0]][posEnemy[1]], arr[posEnemy[0]][posEnemy[1] + 1]);
						anotherMove = 2;
					}
				}
			}
		}

		if (botDoTurn == 0) {
			playerDoTurn = 1;
			anotherMove = rand() % 2 + 1;
			goto REPEAT_BOT_TURN;
		}
		//arr[posPlayer[0]][posPlayer[1]] = '@';
		//arr[posEnemy[0]][posEnemy[1]] = enemyMarker;

		
		//Для перевиводу ХП.
		HANDLE hCon;
		COORD cPos;
		hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		cPos.Y = 0;
		cPos.X = 0;
		SetConsoleCursorPosition(hCon, cPos);
		//Вивiд
		for (usi i = 0; i < 22; i++) {
			for (usi j = 0; j < 22; j++) {
				cout << arr[i][j] << ends;
			}
			if (i == 0)
				cout << "\tPlayer: " << player.name << " " << player.LVL;
			if (i == 1)
				cout << "\t\tHP: " << player.HPCurrent << "/" << player.HPMax;
			if (i == 2)
				cout << "\t\tMana: " << player.HPCurrent << "/" << player.HPMax;
			if (i == 6)
				cout << "\tEnemy: " << enemy.name << " " << enemy.LVL;
			if (i == 7)
				cout << "\t\tHP: " << enemy.HPCurrent << "/" << enemy.HPMax;

			cout << endl;
		}
	}
	cout << endl << endl << endl;
	cout << endl << endl << endl;
	cout << endl << endl << endl;
	if (player.HPCurrent <= 0) {
		cout << player.name << "! Твої ХП впали нижче 0. Пiсля нажаття будь-якої кнопки персонаж буде обнулений. " << endl;
		char nothing = getch();
		return 1;
	}
	else if (enemy.HPCurrent <= 0) {	
		cout << player.name << " безжалiсно добиває " << enemy.name << endl;;
		cout << "Лут: " << endl;
	}
	playerPos1 = posPlayer[0];
	playerPos2 = posPlayer[1];
	return 0;
}

int main(int argc, char * argv[]) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	setlocale(0, "RUS");
	srand(time(0));
	char SLOT_NAMES[3][18] = { "saves\\Player1.txt", "saves\\Player2.txt", "saves\\Player3.txt" };
	LOG_STRC log(argv);
	log.print("Гра запущена");

	int CONFIG_MUSIC = 1;
	{
		{
			const char PRJ_NAME[50] = "5_RPG_KURSACH.exe";
			char BD_NAME[100];
			usi music = rand() % 10;
			strcpy(BD_NAME, "config.txt");
			char PATH[_MAX_PATH];   //260
			strcpy(PATH, argv[0]);
			char *p = strstr(PATH, PRJ_NAME);
			strcpy(p, BD_NAME);
			ifstream fin(PATH);
			fin >> CONFIG_MUSIC;
			fin.close();
		}
		if (CONFIG_MUSIC == 1) {
			const char PRJ_NAME[50] = "5_RPG_KURSACH.exe";
			char BD_NAME[100];
			usi music = rand() % 10;
			strcpy(BD_NAME, "sound\\MAINMENU.wav");

			if (music == 0)
				strcpy(BD_NAME, "sound\\MAINMENU.wav");
			else if (music == 1)
				strcpy(BD_NAME, "sound\\necroTown.wav");
			else if (music == 2)
				strcpy(BD_NAME, "sound\\EvilTheme.wav");
			else if (music == 3)
				strcpy(BD_NAME, "sound\\GoodTheme.wav");
			else if (music == 4)
				strcpy(BD_NAME, "sound\\SWAMP.wav");
			else if (music == 5)
				strcpy(BD_NAME, "sound\\COMBAT01.wav");
			else if (music == 6)
				strcpy(BD_NAME, "sound\\COMBAT02.wav");
			else if (music == 7)
				strcpy(BD_NAME, "sound\\COMBAT03.wav");
			else if (music == 8)
				strcpy(BD_NAME, "sound\\COMBAT04.wav");
			else if (music == 9)
				strcpy(BD_NAME, "sound\\DUNGEON.wav");

			char PATH[_MAX_PATH];   //260
			strcpy(PATH, argv[0]);
			char *p = strstr(PATH, PRJ_NAME);
			strcpy(p, BD_NAME);
			PlaySoundA(p, 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
			
		}
		else {
			PlaySoundA(0, 0, SND_ASYNC);
		}
	}

	char MainMenu;
	usi PLAYER_SLOT;
	do {
		REPEAT_AFTER_MUSIC:
		cout << "[1] - Нова гра" << endl;
		cout << "[2] - Завантажити гру" << endl;
		cout << "[3] - On/Off music" << endl;
		cout << "[0] - Вихiд" << endl;
		MainMenu = Input_in_scene(MAIN_MENU);
		system("cls");
		if (MainMenu > '0' && MainMenu <= '3') {
			//менюха загрузок
			Mob player;
			player.LOG_STRC_Getptr(&log);
			switch (MainMenu) {
			case '1':
			{
				char name[20];
				cout << "iмя: ";
				cin >> name;
				cout << "Слот для збереження[1-3]: " << endl;
				do {
					cin >> PLAYER_SLOT;
				} while (!(PLAYER_SLOT >= 1 && PLAYER_SLOT <= 3));
				system("cls");
				player.FirstFillPlayer(name);
				PLAYER_SLOT--;
				player.SavePlayer(argv, SLOT_NAMES[PLAYER_SLOT]);
			}
			break;
			case '2':
			{
				usi LoadMenuGame;
				cout << "[1] - Завантажити гру 1" << endl;
				cout << "[2] - Завантажити гру 2" << endl;
				cout << "[3] - Завантажити гру 3" << endl;
				LoadMenuGame = Input_in_scene(LOAD_MENU);
				PLAYER_SLOT = (int(LoadMenuGame) - 48) - 1;
				system("cls");
				player.LoadPlayer(argv, SLOT_NAMES[PLAYER_SLOT]);
			}
			break;
			case '3':
			{
				if (CONFIG_MUSIC == 1)
					CONFIG_MUSIC = 0;
				else
					CONFIG_MUSIC = 1;
				{
					const char PRJ_NAME[50] = "5_RPG_KURSACH.exe";
					char BD_NAME[100];
					usi music = rand() % 10;
					strcpy(BD_NAME, "config.txt");
					char PATH[_MAX_PATH];   //260
					strcpy(PATH, argv[0]);
					char *p = strstr(PATH, PRJ_NAME);
					strcpy(p, BD_NAME);
					ofstream fout(PATH);
					fout << CONFIG_MUSIC;
					fout.close();
				}
				if (CONFIG_MUSIC == 1) {
					const char PRJ_NAME[50] = "5_RPG_KURSACH.exe";
					char BD_NAME[100];
					usi music = rand() % 10;
					strcpy(BD_NAME, "sound\\MAINMENU.wav");

					if (music == 0)
						strcpy(BD_NAME, "sound\\MAINMENU.wav");
					else if (music == 1)
						strcpy(BD_NAME, "sound\\necroTown.wav");
					else if (music == 2)
						strcpy(BD_NAME, "sound\\EvilTheme.wav");
					else if (music == 3)
						strcpy(BD_NAME, "sound\\GoodTheme.wav");
					else if (music == 4)
						strcpy(BD_NAME, "sound\\SWAMP.wav");
					else if (music == 5)
						strcpy(BD_NAME, "sound\\COMBAT01.wav");
					else if (music == 6)
						strcpy(BD_NAME, "sound\\COMBAT02.wav");
					else if (music == 7)
						strcpy(BD_NAME, "sound\\COMBAT03.wav");
					else if (music == 8)
						strcpy(BD_NAME, "sound\\COMBAT04.wav");
					else if (music == 9)
						strcpy(BD_NAME, "sound\\DUNGEON.wav");

					char PATH[_MAX_PATH];   //260
					strcpy(PATH, argv[0]);
					char *p = strstr(PATH, PRJ_NAME);
					strcpy(p, BD_NAME);
					PlaySoundA(p, 0, SND_FILENAME | SND_ASYNC | SND_LOOP);

				}
				else {
					PlaySoundA(0, 0, SND_ASYNC);
				}
			}
			goto REPEAT_AFTER_MUSIC;
				break;
			}
			if (MainMenu != '0') {
				player.RecalcStats();
			}
			//Кiнець Блоку створення/Загрузки перса

			//Власне цикл гри
			char GameChoose;
			int arenaKillKill = 0;
			do {
				if (player.XPToNextLVL <= player.currentXP) {
					blue;
					cout << "Отримано новий рiвень! Натиснiть [";
					red;
					cout << "R";
					blue;
					cout << "] щоб розкинути стати" << endl;
					grey;
				}
				cout << "[f] - В бiй" << endl;
				cout << "[s] - По магазинах" << endl;
				cout << "[t] - За вмiннями" << endl;
				cout << "[r] - Вiдпочити" << endl;
				cout << "[b] - iнвентар" << endl;
				cout << "[c] - Лист персонажа" << endl;
				cout << "[0] - Вихiд" << endl;
				GameChoose = Input_in_scene(TOWN_CHOISE);
				system("cls");
				player.RecalcStats();
				switch (GameChoose) {
				case 'f': {
					int vexaCnt = 0, plPos1 = 11, plPos2 = 11;
REPEAT_BATTLE:
					if (arenaKillKill >= 5) {
						player.arenaCnt++;
						arenaKillKill = 0;
					}

					Mob vrag;
					vrag.LOG_STRC_Getptr(&log);
					vrag.LoadPlayer(argv, "0", player.arenaCnt);
					//vrag.PrintInfo();

					if (BattleField(player, vrag, plPos1, plPos2) == 1) {
						player.DoNull(argv, SLOT_NAMES[PLAYER_SLOT]);
						system("cls");
						goto REPEAT_AFTER_MUSIC;
						//goto DIED_MARK;
					};
					arenaKillKill++;
					vexaCnt++;

					cout << "Money: " << player.arenaCnt * 50 << endl;
					player.money += player.arenaCnt * 50 + arenaKillKill * 10;
					player.currentXP += player.arenaCnt * 100 + arenaKillKill * 10;

					player.HPCurrent += player.HPHeal;
					if (player.HPCurrent > player.HPMax)
						player.HPCurrent = player.HPMax;					
					
					if (vexaCnt == 3) {
						vexaCnt = 0;
						items_s *it = new items_s;
						ArrPushBack(player.inventory, player.inventoryCNT);
						player.inventory[player.inventoryCNT - 1] = it->ReadItemFromTXT(argv, 100);
						blue;
						cout << "Отримано шмот!" << endl;
						grey;
					}

					cout << endl << "Продовжити бiй? " << arenaKillKill << "/5" << endl;
					char battleInput = Input_in_scene(BATTLE_SCENE);
					system("cls");
					
					if (battleInput == '1') {
						goto REPEAT_BATTLE;
					}
					else if (battleInput == '0') {

					}
					
				}
				break;
				case 's': {
					char ShopStr[4];
					usi ShopChoise = 15;
					do {
						cout << "Тип нової екiпiровки: " << endl;
						cout << "[1] - Голова" << endl;
						cout << "[2] - Броня" << endl;
						cout << "[3] - Лева рука" << endl;
						cout << "[4] - Права рука" << endl;
						cout << "[5] - Ботинки" << endl;
						cout << "[6] - Кольца" << endl;
						cout << "[7] - Амулет" << endl;
						cout << "[8] - Плащ" << endl;
						cout << "[9] - Пояс" << endl;
						cout << "[10] - Перчатки" << endl;
						cout << "[11] - Наплечники" << endl;
						cout << "[0] - Вихiд" << endl;

						do {
							cout << ">";
							cin >> ShopStr;
							if(ShopStr[0] != '?')
								ShopChoise = atoi(ShopStr);
							else {
								ShopChoise = 15;
								cout << "Спочатку введiть номер слота для екiпiровки, а потiм ";
								blue;
								cout << "ID ";
								grey;
								cout << "предмета, який хочете купити." << endl;
								cout << "Введiть ";
								blue;
								cout << "ID";
								grey;
								cout << " 0 для того, щоб нiчого не купляти" << endl;
							}
						} while (!(ShopChoise >= 0 && ShopChoise <= 11));
						system("cls");
						if (ShopChoise != 0) {
							if (ShopChoise <= 6)
								--ShopChoise;

							items_s TheRealCostil;
							TheRealCostil.PrintInfoForShop(argv, ShopChoise);
							cout << "Введiть ID предмета, який бажаєте купити: ";
							usi ID;
							cin >> ID;
							system("cls");
							ShopChoise = 1;
							if (ID != 0) {
								items_s *it = new items_s;
								it->ReadItemFromTXT(argv, ID);
								if (it->price <= player.money) {
									player.money -= it->price;
									ArrPushBack(player.inventory, player.inventoryCNT);
									player.inventory[player.inventoryCNT - 1] = it->ReadItemFromTXT(argv, ID);
									cout << "Куплено! Залишок: " << player.money << endl << endl;
								}
								else {
									cout << "Не вистачає грошей." << player.money << "/" << it->price << endl << endl;
								}
							}
						}
					} while (ShopChoise != 0);
				}
						  break;
				case 't':
					red;
					cout << "Ще не реалiзовано" << endl;
					grey;
					break;
				case'r':
					player.LVL_UP();
					break;
				case 'b':
					char inventoryStr;
					usi choseInInventory;
					do {
						cout << "[s] - Продати" << endl;
						cout << "[w] - Екiпiрувати" << endl;
						cout << "[r] - Зняти" << endl;
						cout << "[e] - Переглянути екiпiроване" << endl;
						cout << "[b] - Показати iнвентар" << endl;
						cout << "[0] - Вихiд" << endl;
						do {
							inventoryStr = Input_in_scene(INVENTORY_CHOISE);
							if (inventoryStr == 's')
								choseInInventory = 1;
							else if (inventoryStr == 'w')
								choseInInventory = 2;
							else if (inventoryStr == 'r')
								choseInInventory = 3;
							else if (inventoryStr == 'e')
								choseInInventory = 4;
							else if (inventoryStr == 'b')
								choseInInventory = 5;
							else if (inventoryStr == '0')
								choseInInventory = 0;
						} while (!(choseInInventory >= 0 && choseInInventory <= 5));
						system("cls");
						if (choseInInventory != 0) {
							int ID = 1;
							if (choseInInventory >= 1 && choseInInventory <= 3) {
								cout << "Введiть ID предмета: ";
								do {
									cin >> ID;
								} while (ID < 0);
								--ID;
								system("cls");
							}
							if (ID != -1) {
								if (choseInInventory == 5) {
									for (usi i = 0; i < player.inventoryCNT; i++) {
										cout << "ID: " << i + 1 << endl;
										player.inventory[i].PrintInfo();
									}
									cout << endl << endl << "Money:" << player.money << endl;
								}
								else if (choseInInventory == 4) {
									for (usi i = 0; i < SlotsCnt; i++) {
										if (player.equipedItems[i].posInBD != -1) {
											cout << "ID: " << i + 1 << endl;
											player.equipedItems[i].PrintInfo();
										}
									}
								}
								else if (choseInInventory == 1) {
									if (ID < player.inventoryCNT) {
										player.money += player.inventory[ID].price / 5;
										ArrDeleteByIndex(player.inventory, player.inventoryCNT, ID);
									}
								}
								else if (choseInInventory == 2) {
									if (ID < player.inventoryCNT) {
										if (player.equipedItems[player.inventory[ID].slot].posInBD != -1) {
											//Якщо слот занятий

											if (player.inventory[ID].slot == LeftRing) {
												if (player.equipedItems[RightRing].posInBD != -1) {
													cout << "Обидва слоти пiд кiльце занятi" << endl;
												}
												else {
													player.equipedItems[RightRing] = player.inventory[ID];
													ArrDeleteByIndex(player.inventory, player.inventoryCNT, ID);
												}
											}
											else
												cout << "Спочатку потрiбно зняти одягнену у той же слот екiпiровку. Не поверх же вдягати!?" << endl;
										}
										else {
											//Якщо слот вiльний

											player.equipedItems[player.inventory[ID].slot] = player.inventory[ID];
											ArrDeleteByIndex(player.inventory, player.inventoryCNT, ID);
										}
									}
								}
								else if (choseInInventory == 3) {
									if (ID < SlotsCnt) {
										if (player.equipedItems[ID].posInBD != -1) {
											ArrPushBack(player.inventory, player.inventoryCNT);
											player.inventory[player.inventoryCNT - 1] = player.equipedItems[ID];
											player.equipedItems[ID].ReadItemFromTXT(argv, 0);
											player.equipedItems[ID].posInBD = -1;
										}
									}
								}
							}
						}
					} while (choseInInventory != 0);
					break;
				case 'c':
					player.PrintInfo();
					break;
				default:
					break;
				}

				if (GameChoose == '0')
					player.SavePlayer(argv, SLOT_NAMES[PLAYER_SLOT]);
			} while (GameChoose != '0');
			//Кiнець циклу гри
		}
		system("cls");
	} while (MainMenu != '0');

	DIED_MARK:
	log.print("Вихiд");
	system("pause");
	return 0;
}