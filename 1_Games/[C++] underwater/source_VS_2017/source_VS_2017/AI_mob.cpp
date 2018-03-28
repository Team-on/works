#include "precompiledHeaders.h"
#include "AI_mob.h"


AI_mob::AI_mob(){

}


AI_mob::~AI_mob(){

}

/*
bool _room::AI_SeePlayer(_mobBasic &mob) {
	COORD mobPos = mob.GetPos();
	COORD startPos = { mobPos.X - mob.lengthOfView.GetCurr(), mobPos.Y - mob.lengthOfView.GetCurr() },
		endPos = { mobPos.X + mob.lengthOfView.GetCurr(), mobPos.Y + mob.lengthOfView.GetCurr() };
	if (startPos.X <= player->GetPos().X && player->GetPos().X <= endPos.X)
		if (startPos.Y <= player->GetPos().Y && player->GetPos().Y <= endPos.Y)
			return 1;
	return 0;
}

bool _room::AI_Move(_mobBasic &mob, AI_COMMAND moveDir) {
	if (moveDir == AI_COMMAND::NONE)
		return 0;

	COORD moveDirection[4] = {
		{ mob.GetPos().X - 1 , mob.GetPos().Y },
	{ mob.GetPos().X + 1 , mob.GetPos().Y },
	{ mob.GetPos().X , mob.GetPos().Y + 1 },
	{ mob.GetPos().X , mob.GetPos().Y - 1 }
	};
	int mobTurn = moveDir - 1;

	if (map[moveDirection[mobTurn].Y][moveDirection[mobTurn].X].GetIsSolid() == false) {
		for (uint i = 0; i < mobSize; ++i) {
			if (this->mob[i].GetPos() == moveDirection[mobTurn]) {
				return 0;
			}
			if (this->player->GetPos() == moveDirection[mobTurn]) {
				return 0;
			}
		}
		mob.SetPos({ moveDirection[mobTurn].X, moveDirection[mobTurn].Y });
		return 1;
	}
	else {
		//Wall 
		return 0;
	}

}

bool _room::AI_MoveIfSeeWithoutWall(_mobBasic &mob) {
	bool seePlayer = AI_SeePlayer(mob);
	if (seePlayer) {
		COORD playerPos = player->GetPos(), mobPos = mob.GetPos();
		AI_COMMAND moveDirX = AI_COMMAND::NONE, moveDirY = AI_COMMAND::NONE;

		if (playerPos.X < mobPos.X)
			moveDirX = AI_COMMAND::MOVE_LEFT;
		else if (playerPos.X > mobPos.X)
			moveDirX = AI_COMMAND::MOVE_RIGHT;

		if (playerPos.Y > mobPos.Y)
			moveDirY = AI_COMMAND::MOVE_DOWN;
		else if (playerPos.Y < mobPos.Y)
			moveDirY = AI_COMMAND::MOVE_UP;

		bool rez = 0;
		if (rand() % 2)
			rez = AI_Move(mob, moveDirX);
		else
			rez = AI_Move(mob, moveDirY);
		if (!rez) {
			if (moveDirX == AI_COMMAND::NONE && moveDirY != AI_COMMAND::NONE)
				rez = AI_Move(mob, moveDirY);
			if (moveDirY == AI_COMMAND::NONE && moveDirX != AI_COMMAND::NONE)
				rez = AI_Move(mob, moveDirX);
		}
		return rez;
	}
	return 0;
}

bool _room::AI_DoTurn(_mobBasic &mob) {
	return AI_MoveIfSeeWithoutWall(mob);
}
*/
