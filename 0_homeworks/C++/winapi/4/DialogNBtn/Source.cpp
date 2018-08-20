#include <windows.h>
#include "resource.h"

HWND textBox, textBoxProgrammaly, image;
HINSTANCE hInst;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProcNonModal(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow){
	hInst = hInstance;

	/*MSG msg;
	HWND hDialog = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProcNonModal);
	ShowWindow(hDialog, nCmdShow);

	while(GetMessage(&msg, 0, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;*/

	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp){
	switch(message){
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;

	case WM_INITDIALOG:
	{
		image = GetDlgItem(hWnd, IDC_STATIC2);
		textBox = GetDlgItem(hWnd, IDC_STATIC1);
		textBoxProgrammaly = CreateWindowEx(NULL, TEXT("STATIC"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE, 50, 50, 200, 100, hWnd, NULL, hInst, 0
		);

		SendMessage(image, STM_SETIMAGE, IMAGE_BITMAP, 
			(LPARAM)(LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1)))
		);
	}
		return TRUE;
	
	case WM_MOUSEMOVE:
		TCHAR text[20];
		wsprintf(text, TEXT("x=%d y = %d"), LOWORD(lp), HIWORD(lp));
		SetWindowText(textBox, text);
		return TRUE;

	case WM_LBUTTONDOWN:
		SetWindowText(textBoxProgrammaly, TEXT("Left mouse button"));
		return TRUE;
	case WM_RBUTTONDOWN:
		SetWindowText(textBoxProgrammaly, TEXT("Right mouse button"));
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK DlgProcNonModal(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp){
	switch(mes){
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}