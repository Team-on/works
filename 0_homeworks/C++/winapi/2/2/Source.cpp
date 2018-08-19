// ���� WINDOWS.H �������� �����������, �������, � ��������� 
// ������� ������������ ��� ��������� ���������� ��� Windows. 
#include <windows.h>
#include <tchar.h>
#include "resource.h"

//�������� ������� ���������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("��������� ����������"); /* ��� ������ ���� */

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow){
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	/* 1. ����������� ������ ����  */

	wcl.cbSize = sizeof(wcl);	// ������ ��������� WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// ���� ������ �������� ��������� � ������� ������ (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// ����� ������� ���������
	wcl.cbClsExtra = 0;		// ������������ Windows 
	wcl.cbWndExtra = 0; 	// ������������ Windows 
	wcl.hInstance = hInst;	// ���������� ������� ����������
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� ����������� ������
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// �������� ������������ �������
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//���������� ���� ����� ������			
	wcl.lpszMenuName = NULL;	// ���������� �� �������� ����
	wcl.lpszClassName = szClassWindow;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����


						/*  2. ����������� ������ ����  */

	if(!RegisterClassEx(&wcl))
		return 0;	// ��� ��������� ����������� - �����


					/*  3. �������� ����  */

					// ��������� ���� �  ���������� hWnd ������������� ���������� ����
	hWnd = CreateWindowEx(
		0,		// ����������� ����� ����
		szClassWindow,	// ��� ������ ����
		TEXT("������  Windows ����������"),	// ��������� ����
											/* ���������, �����, ����������� ������ �������, ��������� ����,
											������ ������������ � ���������� ����  */
		WS_OVERLAPPEDWINDOW,	// ����� ����
		CW_USEDEFAULT,	// �-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// y-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// ������ ����
		CW_USEDEFAULT,	// ������ ����
		NULL,			// ���������� ������������� ����
		NULL,			// ���������� ���� ����
		hInst,		// ������������� ����������, ���������� ����
		NULL);		// ��������� �� ������� ������ ����������

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// ����������� ����
	MessageBox(hWnd, TEXT("Press CapsLock to enumerate all windows\n� ������ ����� ����������� �������"), TEXT("Info"), MB_OK | MB_ICONINFORMATION);

						/* 5. ������ ����� ��������� ���������  */

						// ��������� ���������� ��������� �� ������� ���������
	while(GetMessage(&lpMsg, NULL, 0, 0)){
		TranslateMessage(&lpMsg);	// ���������� ���������
		DispatchMessage(&lpMsg);	// ��������������� ���������
	}
	return lpMsg.wParam;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam){
	HWND hWindow = (HWND)lParam; 
	TCHAR caption[MAX_PATH] = { 0 }, classname[100] = { 0 }, text[500] = { 0 };
	GetWindowText(hWnd, caption, 100);
	GetClassName(hWnd, classname, 100);
	if(lstrlen(caption)){
		lstrcat(text, TEXT("Window name: "));
		lstrcat(text, caption);
		lstrcat(text, TEXT("\n"));
		lstrcat(text, TEXT("Window class: "));
		lstrcat(text, classname);
		if(MessageBox(hWindow, text, TEXT("All windows list:"), MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
			return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam){
	TCHAR str[50];
	switch(uMessage){
	case WM_CREATE:
		SetClassLong(hWnd, GCL_HICON, LONG(LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1))));
	break;
	
	case WM_KEYDOWN:
		if(wParam == VK_CAPITAL)
			EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(hWnd));
		break;

	case WM_LBUTTONDBLCLK:
		MessageBox(0,
			TEXT("Double left click"),
			TEXT("WM_LBUTTONDBLCLK"),
			MB_OK | MB_ICONINFORMATION);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(
			0,
			TEXT("left click press"),
			TEXT("WM_LBUTTONDOWN"),
			MB_OK | MB_ICONINFORMATION);
		break;
	case WM_LBUTTONUP:
		MessageBox(
			0,
			TEXT("left click release"),
			TEXT("WM_LBUTTONUP"),
			MB_OK | MB_ICONINFORMATION);
		break;
	case WM_RBUTTONDOWN:
		MessageBox(
			0,
			TEXT("right click press"),
			TEXT("WM_RBUTTONDOWN"),
			MB_OK | MB_ICONINFORMATION);
		break;
	case WM_MOUSEWHEEL:
		wsprintf(str, TEXT("%s"), GET_WHEEL_DELTA_WPARAM(wParam) == WHEEL_DELTA ? TEXT("wheel up") : TEXT("wheel down"));
		SetWindowText(hWnd, str);
		break;
	case WM_MOUSEMOVE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect); 
		WORD x = LOWORD(lParam), y = HIWORD(lParam);

		wsprintf(str, TEXT("X=%d  Y=%d"), x, y);
		SetWindowText(hWnd, str);

		if(x >= rect.right / 4 && x <= rect.right * 3 / 4 &&
			y >= rect.bottom / 4 && y <= rect.bottom * 3 / 4)
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		else
			SetCursor(LoadCursor(NULL, IDC_HAND));
	}
		break;
	case WM_CHAR:
		wsprintf(str, TEXT("������ ������� %c"), (char)wParam);
		MessageBox(0, str, TEXT("WM_CHAR"), MB_OK | MB_ICONINFORMATION);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
