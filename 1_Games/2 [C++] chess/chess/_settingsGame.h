#ifndef __SETTING_GAME_H_
#define __SETTING_GAME_H_

//Самий костильний клас. Треба було зробити його глобальним, але не константні глобальні змінні не проходили. Тому клас типу константний, але всі змінні mutable. )
class _settingsGame{
private:
	mutable COORD clickPos;
public:
	_settingsGame();
	~_settingsGame();

	void SetClickPos(COORD pos) const;

	COORD GetClickPos() const;
};

#endif // !__SETTING_H_



