#ifndef __SETTING_GAME_H_
#define __SETTING_GAME_H_

//Самий костильний клас. Треба було зробити його глобальним, але не константні глобальні змінні не проходили. Тому клас типу константний, але всі змінні mutable. )
class _settingsGame{
public:
	enum SCREEN_MOVE_TYPE {
		fast = 1,
		slow
	};
private:
	mutable SCREEN_MOVE_TYPE screenMoveType;
	mutable COORD clickPos;
public:
	_settingsGame();
	~_settingsGame();

	void SetScreenMoveType(SCREEN_MOVE_TYPE type) const;
	void SetClickPos(COORD pos) const;

	SCREEN_MOVE_TYPE GetScreenMoveType() const;
	COORD GetClickPos() const;
};

#endif // !__SETTING_H_



