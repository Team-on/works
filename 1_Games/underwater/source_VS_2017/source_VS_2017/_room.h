#ifndef __ROOM_H_
#define __ROOM_H_

#include "AI_mob.h"
#include "dungeonMap.h"

class _room{
	//������� ������
	dungeonMap map;
	//������ � ���� ������ � �����
	AI_mob *mob;
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

	void DoMobTurns(const unsigned long long int ticTimer);

	ullint CalcTicTimerStep() const;
	ullint CalcTicTimerMax() const;
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
};

#endif // !__ROOM_H_



