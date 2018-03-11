#ifndef _GLOBAL_VAR_H_
#define _GLOBAL_VAR_H_

extern const HANDLE HANDLE_INPUT;
extern const HANDLE HANDLE_OUTPUT;

extern _settingsGame settings;

extern LOG_GAME gameLog;

enum AI_COMMAND {
	NONE,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_DOWN,
	MOVE_UP
};
enum direction { LEFT, RIGHT, DOWN, UP, NONE_DIR };

#endif // !_GLOBAL_VAR_H_
