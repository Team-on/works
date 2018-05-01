#ifndef _SCREEN_SCENE_H_
#define _SCREEN_SCENE_H_

#include "screenObj.h"

class screenScene{
	const uchar sizex, sizey;
	screenObj **screenBuf;
	mutable screenObj **screenCurr;

	void CopyScrBufToScrCurr() const;

public:
	screenScene();
	screenScene(uchar Sizex, uchar Sizey);
	~screenScene();

	void gotoxy(uchar x, uchar y) const;

	void ClearArr();
	void ClearScr() const;

	//������� ���� ������� � ��������� ����� �� �����������
	void BeforeExit() const;

	void SetTitle(const char *title) const;
	void MaximizeWindow() const;

	//���� screenBuf �� ����� � ���� ��������� � screenCurr
	//screenCurr ������ ������ ������� �� �����, ��� ���� �� �������� �� 2 ����
	void Print() const;

	const uchar GetScreenSizex() const;
	const uchar GetScreenSizey() const;

	screenObj *& operator[] (uchar a) const;
};

#endif // !_SCREEN_SCENE_H_



