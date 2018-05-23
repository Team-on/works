#include "preCompiled.h"
#include "globalVars.h"

HGE *hge = nullptr;
POINT screenSize;

Menu *menu = nullptr;

Game *game = nullptr;
GameInfo *gameInfo = nullptr;
Difficult *difficult = nullptr;

InputQueue *inputQueue = new InputQueue();

SoundMusic *soundMusic = nullptr;
SoundSound *soundSound = nullptr;