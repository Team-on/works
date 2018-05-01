#ifndef __SETTING_GAME_H_
#define __SETTING_GAME_H_

//����� ���������� ����. ����� ���� ������� ���� ����������, ��� �� ��������� �������� ���� �� ���������. ���� ���� ���� �����������, ��� �� ���� mutable. )
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



