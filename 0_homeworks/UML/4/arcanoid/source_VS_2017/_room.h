#ifndef __ROOM_H_
#define __ROOM_H_

#include "_mobBasic.h"
#include "dungeonMap.h"

class _room{
	//Ланшафт кімнати
	dungeonMap map;
	//Массив з всіма мобами в кімнаті
	_mobBasic *mob;
	uint mobSize;
	//Указатель на игрока
	_mobBasic *player;

	void PlaceObjectsOnMap();
public:
	//Рaзведана карта
	bool **isViewedBefore;


	_room(usint mapSizeX, usint mapSizeY);
	~_room();

	//---------------- Init ---------------------------------------

	void SetPlayerPrt(_mobBasic & playerPtr) { player = &playerPtr; }
	_mobBasic* GetPlayerPrt() const { return player; }

	// ------------------- Main loop -----------------------

	//1 - player turn
	void DoMobTurns(const unsigned long long int ticTimer);

	// --------------- other ----------------------------

	_mobBasic *MobOnPos(COORD pos);

	//--------------- Map gen ---------------------------

	void SetMap(const dungeonMap &newMap);
	void GenerateRandomMaze();

	//------------------------- output -------------------------------
	usint GetSizex() const;
	usint GetSizey() const;

	//map зберігає в собі лише ландшафт карти. Всі інше доставляється туди функцією PlaceObjectsOnMap(), а потім виставлений массив
	//синхронізуються з виводом
	dungeonMap & GetDisplayInfo();
	dungeonMap & GetMap();

private:
	//--------------------- AI alg------------------------
	bool AI_SeePlayer(_mobBasic &mob);

	bool AI_Move(_mobBasic &mob, AI_COMMAND moveDir);

	bool AI_MoveIfSeeWithoutWall(_mobBasic &mob);

	bool AI_DoTurn(_mobBasic &mob);

};

#endif // !__ROOM_H_



