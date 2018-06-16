#include "precompiledHeaders.h"
#include "AI_mob.h"

AI_mob::AI_mob(){
	pos.X = pos.Y = 0;
	symbol = '@';

	reaction.SetBase(-1);

	barHealth.SetMax(100);
	barHealth.SerCurr(40);
	barMana.SetMax(3);
	barMana.SerCurr(1);
	barStamina.SetMax(1000);
	barStamina.SerCurr(947);
}


AI_mob::~AI_mob(){

}

bool AI_mob::AI_Move(_room &room, AI_COMMAND moveDir) {
		if (moveDir == AI_COMMAND::NONE)
			return 0;

		//auto map = room.GetLogicMap();
		auto mob = *this;

		COORD moveDirection[4] = {
			{ mob.GetPos().X - 1 , mob.GetPos().Y },
		{ mob.GetPos().X + 1 , mob.GetPos().Y },
		{ mob.GetPos().X , mob.GetPos().Y + 1 },
		{ mob.GetPos().X , mob.GetPos().Y - 1 }
		};
		int mobTurn = moveDir - 1;

		//if (map[moveDirection[mobTurn].Y][moveDirection[mobTurn].X].GetIsSolid() == false) {
			//mob.SetPos({ moveDirection[mobTurn].X, moveDirection[mobTurn].Y });
			//return 1;
		//}
		//else {
			//Wall 
			//return 0;
		//}
	
		return 0;
}

bool AI_mob::AI_MoveIfSeeWithoutWall(_room &room) {
		COORD mobPos = this->GetPos();
		AI_COMMAND moveDirX = AI_COMMAND::NONE, moveDirY = AI_COMMAND::NONE;

		int rnd = rand() % 4;
		if (rnd == 0)
			moveDirX = AI_COMMAND::MOVE_LEFT;
		else if (rnd == 1)
			moveDirX = AI_COMMAND::MOVE_RIGHT;
		else if (rnd == 2)
			moveDirY = AI_COMMAND::MOVE_DOWN;
		else if (rnd == 3)
			moveDirY = AI_COMMAND::MOVE_UP;

		bool rez = 0;
		if (rand() % 2)
			rez = AI_Move(room, moveDirX);
		else
			rez = AI_Move(room, moveDirY);
		if (!rez) {
			if (moveDirX == AI_COMMAND::NONE && moveDirY != AI_COMMAND::NONE)
				rez = AI_Move(room, moveDirY);
			if (moveDirY == AI_COMMAND::NONE && moveDirX != AI_COMMAND::NONE)
				rez = AI_Move(room, moveDirX);
		}
		return rez;
}

bool AI_mob::AI_DoTurn(_room &room) {
	return AI_MoveIfSeeWithoutWall(room);
}

