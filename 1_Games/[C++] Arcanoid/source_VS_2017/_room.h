#ifndef __ROOM_H_
#define __ROOM_H_

#include "_mobBasic.h"
#include "dungeonMap.h"

class _room{
	//������� ������
	dungeonMap map;
	//������ � ���� ������ � �����
	_mobBasic *mob;
	uint mobSize;
	//��������� �� ������
	_mobBasic *player;

	void PlaceObjectsOnMap();
public:
	//�a������� �����
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

	//map ������ � ��� ���� �������� �����. �� ���� ������������� ���� �������� PlaceObjectsOnMap(), � ���� ����������� ������
	//�������������� � �������
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



