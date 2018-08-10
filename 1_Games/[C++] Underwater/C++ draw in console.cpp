/*
// draw two lines and a circle on your console screen
// original BCX basic code by Sir Joe Caverly
// translated to C code and modified to work with Dev-C++
// link with GDI32.lib or with Dev-C++ link libgdi32.a via
// Project>>Project Options>>Parameters>>Add Lib>>libgdi32.a
// this is a Windows Console Application
#include <windows.h>    // Win32API Header File
#include <cstring>
#include <cstdio>
using namespace std;
#define Red  RGB (255,0,0)
#define Lime RGB (206,255,0)
#define Blue RGB (0,0,255)
static HWND    hConWnd;
int     BCX_Line(HWND, int, int, int, int, int = 0, HDC = 0);
int     BCX_Circle(HWND, int, int, int, int = 0, int = 0, HDC = 0);
HWND    GetConsoleWndHandle(void);
int main()
{
	printf("abcd...");
	hConWnd = GetConsoleWndHandle();
	if (hConWnd)
	{
		// be creative here, draw your own circles or lines
		//   hwin, centerX, centerY, radius, pencolor 
		BCX_Circle(hConWnd, 150, 130, 105, Blue);
		//   hwin, ulcX, ulcY, lrcX, lrcY, pencolor 
		BCX_Line(hConWnd, 5, 5, 300, 250, Red);
		BCX_Line(hConWnd, 295, 5, 5, 250, Lime);

		getchar();  // wait
	}
	return 0;
}
int BCX_Line(HWND Wnd, int x1, int y1, int x2, int y2, int Pen, HDC DrawHDC)
{
	int a, b = 0;
	HPEN hOPen;
	// penstyle, width, color
	HPEN hNPen = CreatePen(PS_SOLID, 2, Pen);
	if (!DrawHDC) DrawHDC = GetDC(Wnd), b = 1;
	hOPen = (HPEN)SelectObject(DrawHDC, hNPen);
	// starting point of line
	MoveToEx(DrawHDC, x1, y1, NULL);
	// ending point of line
	a = LineTo(DrawHDC, x2, y2);
	DeleteObject(SelectObject(DrawHDC, hOPen));
	if (b) ReleaseDC(Wnd, DrawHDC);
	return a;
}
// converts circle(centerX,centerY,radius,pen) to WinApi function
// ellipse inside box with upper left and lower right coordinates
int BCX_Circle(HWND Wnd, int X, int Y, int R, int Pen, int Fill, HDC DrawHDC)
{
	int a, b = 0;
	if (!DrawHDC) DrawHDC = GetDC(Wnd), b = 1;
	// penstyle, width, color
	HPEN   hNPen = CreatePen(PS_SOLID, 2, Pen);
	HPEN   hOPen = (HPEN)SelectObject(DrawHDC, hNPen);
	HBRUSH hOldBrush;
	HBRUSH hNewBrush;
	// if true will fill circle with pencolor
	if (Fill)
	{
		hNewBrush = CreateSolidBrush(Pen);
		hOldBrush = (HBRUSH)SelectObject(DrawHDC, hNewBrush);
	}
	else
	{
		hNewBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		hOldBrush = (HBRUSH)SelectObject(DrawHDC, hNewBrush);
	}
	a = Ellipse(DrawHDC, X - R, Y + R, X + R, Y - R);
	DeleteObject(SelectObject(DrawHDC, hOPen));
	DeleteObject(SelectObject(DrawHDC, hOldBrush));
	if (b) ReleaseDC(Wnd, DrawHDC);
	return a;
}
// the hoop ...
HWND GetConsoleWndHandle(void)
{

	return GetConsoleWindow();
}
*/


// put a bitmap image on a Windows Console display
// BCX basic original by Joe Caverly and Kevin Diggins
// BCX generated C code modified for PellesC/Dev-C++

#include <stdio.h>
#include <string.h>
#include <windows.h>    // Win32Api Header File 

static HWND  hConWnd;
HWND BCX_Bitmap(char*, HWND = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0, int = 0);
HWND GetConsoleWndHandle(void);
int main()
{
	hConWnd = GetConsoleWndHandle();
	if (hConWnd)
	{
		// select a bitmap file you have or use one of the files in the Windows folder
		// filename, handle, ID, ulcX, ulcY, width, height   0,0 auto-adjusts
		BCX_Bitmap("C:\\Windows\\greenstone.bmp", hConWnd, 123, 1, 1, 0, 0);

		getchar();  // wait
	}
	return 0;
}
// draw the bitmap
HWND BCX_Bitmap(char* Text, HWND hWnd, int id, int X, int Y, int W, int H, int Res, int Style, int Exstyle)
{
	HWND A;
	HBITMAP hBitmap;

	// set default style
	if (!Style) Style = WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | SS_BITMAP | WS_TABSTOP;

	// form for the image
	A = CreateWindowEx(Exstyle, L"static", NULL, Style, X, Y, 0, 0, hWnd, (HMENU)id, GetModuleHandle(0), NULL);

	// Text contains filename
	hBitmap = (HBITMAP)LoadImage(0, L"D:\\home\\test1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	// auto-adjust width and height
	if (W || H) hBitmap = (HBITMAP)CopyImage(hBitmap, IMAGE_BITMAP, W, H, LR_COPYRETURNORG);
	SendMessage(A, (UINT)STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBitmap);
	if (W || H) SetWindowPos(A, HWND_TOP, X, Y, W, H, SWP_DRAWFRAME);
	return A;
}
// tricking Windows just a little ...
HWND GetConsoleWndHandle(void)
{
	return GetConsoleWindow();
}

//https://www.daniweb.com/programming/software-development/code/216430/add-a-little-graphics-to-your-console
//https://www.daniweb.com/programming/software-development/code/216431/put-a-bitmap-image-on-your-console-c