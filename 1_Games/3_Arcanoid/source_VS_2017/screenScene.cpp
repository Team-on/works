#include "precompiledHeaders.h"
#include "screenScene.h"

void screenScene::CopyScrBufToScrCurr() const {
	for (uchar i = 0; i < sizey; ++i)
		for (uchar j = 0; j < sizex; ++j)
			screenCurr[i][j] = screenBuf[i][j];
}

screenScene::screenScene() : sizex(0), sizey(0), screenBuf(nullptr), screenCurr(nullptr) { }

screenScene::screenScene(uchar Sizex, uchar Sizey) : sizex(Sizex), sizey(Sizey), screenBuf(new screenObj*[sizey]), screenCurr(new screenObj*[sizey]) {
	for (uchar i = 0; i < sizey; ++i) {
		screenBuf[i] = new screenObj[sizex];
		screenCurr[i] = new screenObj[sizex];
	}
	
}

screenScene::~screenScene(){
	if (screenBuf != nullptr) {
		for (uchar i = 0; i < sizey; ++i) {
			delete[] screenBuf[i];
			delete[] screenCurr[i];
		}
		delete[] screenBuf;
		delete[] screenCurr;
	}
}

void screenScene::gotoxy(uchar x, uchar y) const {
	SetConsoleCursorPosition(HANDLE_OUTPUT, { x, y });
}

void screenScene::ClearArr() {
	outputStyle prevStyle;
	for (uchar i = 0; i < sizey; ++i) {
		for (uchar j = 0; j < sizex; ++j) {
			screenBuf[i][j] = ' ';
			screenBuf[i][j].SetStyle(prevStyle);
		}
	}
}

void screenScene::ClearScr() const {
	gotoxy(0, 0);
	outputStyle prevStyle = { outputStyle::color::LightGray, outputStyle::color::Black };
	prevStyle.SetConsoleColor();

	COORD maxWindow = GetLargestConsoleWindowSize(HANDLE_OUTPUT);
	for (uchar i = 0; i < maxWindow.Y; ++i) {
		for (uchar j = 0; j < maxWindow.X; ++j)
			cout << ' ';
		cout << endl;
	}
	gotoxy(0, 0);
}

void screenScene::BeforeExit() const {
	outputStyle RETURN_PREV_CONSOLE_STYLE;
	RETURN_PREV_CONSOLE_STYLE.SetConsoleColor();
	ClearScr();
}

void screenScene::SetTitle(const char *title) const {
	SetConsoleTitleA(title);
}

void screenScene::MaximizeWindow() const {
	HWND hwnd;
	char Title[1024];
	GetConsoleTitle(Title, 1024);
	hwnd = FindWindow(NULL, Title); 
	//Pos to (0;0)
	MoveWindow(hwnd, 0, 0, 2, 2, TRUE);

	//Console size
	COORD maxWindow = GetLargestConsoleWindowSize(HANDLE_OUTPUT); // размер самого большого возможного консольного окна

	maxWindow.Y -= 2;
	maxWindow.X -= 3;

	maxWindow.X = 60;
	maxWindow.Y = 45;

	SMALL_RECT srctWindow = { 0, 0, maxWindow.X, maxWindow.Y};
	SMALL_RECT minWindow = { 0, 0, 2, 2 };
	SetConsoleWindowInfo(HANDLE_OUTPUT, true, &minWindow);

	//Console buffer
	maxWindow.Y += 1;
	maxWindow.X += 1;
	SetConsoleScreenBufferSize(HANDLE_OUTPUT, maxWindow);
	SetConsoleWindowInfo(HANDLE_OUTPUT, true, &srctWindow);
}

void screenScene::Print() const {
	outputStyle prevStyle = screenBuf[0][0].GetStyle();
	prevStyle.SetConsoleColor();

	for (uchar i = 0; i < sizey; ++i) {
		for (uchar j = 0; j < sizex; ++j) {
			if (screenCurr[i][j] != screenBuf[i][j]) {
				if (prevStyle != screenBuf[i][j].GetStyle()) {
					prevStyle = screenBuf[i][j].GetStyle();
					prevStyle.SetConsoleColor();
				}
				gotoxy(j, i);
				cout << screenBuf[i][j];
			}	
		}
	}
	CopyScrBufToScrCurr();
}

const uchar screenScene::GetScreenSizex() const {
	return sizex;
}
const uchar screenScene::GetScreenSizey() const {
	return sizey;
}

screenObj *& screenScene::operator[] (uchar a) const{
	return screenBuf[a];
}