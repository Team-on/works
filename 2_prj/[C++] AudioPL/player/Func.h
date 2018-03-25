#pragma once
#include "Header.h"
#include "MusicPlayer.h"

void gotoxy(short x, short y, HANDLE CONSOLE_HANDLE);

void CopyToDesktop(MusicPlayer &pl);

void off(bool t, time_t &currTime, time_t &prevTime);

char *add();
