#ifndef _GLOBAL_VARS_H_
#define _GLOBAL_VARS_H_

#include "game.h"
#include "gameInfo.h"
#include "InputQueue.h"
#include "difficult.h"
#include "menu.h"
#include "SoundMusic.h"
#include "SoundSound.h"

extern HGE *hge;
extern POINT screenSize;

extern Menu *menu;

extern Game *game;
extern GameInfo *gameInfo;
extern Difficult *difficult;

extern InputQueue *inputQueue;

extern SoundMusic *soundMusic;
extern SoundSound *soundSound;

#endif