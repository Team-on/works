#include "stdafx.h"
#include "resource.h"

HINSTANCE wInst;
HWND buttons[3][3];

BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow){
	wInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WndProc);
}

BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp){
	switch(message){
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG:
	{
		//SendMessage(GetDlgItem(hWnd, IDC_RADIO1),
		//	BM_SETIMAGE, IMAGE_BITMAP,
		//	(LPARAM)(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1)))
		//);
		//SendMessage(GetDlgItem(hWnd, IDC_RADIO2),
		//	BM_SETIMAGE, IMAGE_BITMAP,
		//	(LPARAM)(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP2)))
		//);
		
		CheckDlgButton(hWnd, IDC_RADIO1, BST_CHECKED);
		CheckDlgButton(hWnd, IDC_RADIO4, BST_CHECKED);

		for(char i = 0; i < 3; ++i){
			for(char j = 0; j < 3; ++j){
				TCHAR text[10];
				wsprintf(text, TEXT("%d %d"), i, j);

				buttons[i][j] = CreateWindow(TEXT("BUTTON"), text, WS_CHILD | WS_VISIBLE | BS_FLAT | BS_BITMAP,
					i * 50 + 180, j * 50 + 80, 50, 50, hWnd, NULL, wInst, NULL);

				SendMessage(buttons[i][j], BM_SETIMAGE, IMAGE_BITMAP,
					(LPARAM)(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP3)))
				);
			}
		}
	}
		return TRUE;

	}
	return FALSE;
}