// CalculatorCracker.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Hook.h"
#include "commctrl.h"

#define MAX_LOADSTRING 100
#define HOOK_CODE WH_CALLWNDPROC

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HHOOK hook;
												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_HOOK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOOK));

	MSG msg;

	MessageBox(NULL, TEXT("Press CapsLock to steal Task manager\nShift - steal buttons"), TEXT("Info"), MB_OK | MB_ICONINFORMATION);

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_HOOK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_HOOK);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd) {
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam) {
	HWND hWindow = (HWND)lParam;
	TCHAR caption[MAX_PATH] = { 0 }, classname[100] = { 0 }, text[500] = { 0 };
	GetWindowText(hWnd, caption, 100);
	GetClassName(hWnd, classname, 100);

	if (lstrcmp(classname, TEXT("Button")) == 0 && lstrcmp(caption, TEXT("&End Process")) == 0) {
		MessageBox(hWnd, caption, TEXT("bUTTON"), MB_OK | MB_ICONSTOP);
		if(!hook)
			hook = SetWindowsHookExW(HOOK_CODE, HookProc, NULL, NULL);
		else
			MessageBox(hWnd, TEXT("Hook already createrd"), TEXT("Error"), MB_OK | MB_ICONSTOP);
		//SetParent(hWnd, hWindow);
		//SetWindowPos(hWnd, hWnd, 10, 10, 20, 20, NULL);
	}
	return TRUE;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
	HWND hWindow = (HWND)lParam;
	TCHAR caption[MAX_PATH] = { 0 }, classname[100] = { 0 }, text[500] = { 0 };
	GetWindowText(hWnd, caption, 100);
	GetClassName(hWnd, classname, 100);
	if (lstrlen(caption)) {
		lstrcat(text, TEXT("Window name: "));
		lstrcat(text, caption);

		//if (lstrcmp(caption, TEXT("Windows Task Manager")))
		//	return TRUE;
		lstrcat(text, TEXT("\n"));
		lstrcat(text, TEXT("Window class: "));
		lstrcat(text, classname);
		if (MessageBox(hWindow, text, TEXT("All windows list:"), MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
			return FALSE;
	}
	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_KEYDOWN:
		if (wParam == VK_CAPITAL) {
			//HWND h = FindWindow(NULL/*TEXT("#32770 (Dialog)")*/, TEXT("Windows Task Manager"));
			//if (!h)
			//	MessageBox(hWnd, TEXT("Cant open \"Windows Task Manager\""), TEXT("Ошибка!!!"), MB_OK | MB_ICONSTOP);
			//else
			//	SetParent(h, hWnd);
		}
		else if (wParam == VK_SHIFT) {
			HWND h = FindWindow(NULL/*TEXT("#32770 (Dialog)")*/, TEXT("Windows Task Manager"));
			if (!hook)
				hook = SetWindowsHookExW(HOOK_CODE, &HookProc, GetModuleHandle(TEXT("Windows Task Manager")), NULL);
			else
				MessageBox(hWnd, TEXT("Hook already createrd"), TEXT("Error"), MB_OK | MB_ICONSTOP);

			LVNI_ALL;
			SetBkMode(GetDC(0), TRANSPARENT);

			//if (!h)
			//	MessageBox(hWnd, TEXT("Cant open \"Windows Task Manager\""), TEXT("Ошибка!!!"), MB_OK | MB_ICONSTOP);
			//else
			//	EnumChildWindows(h, EnumChildProc, (LPARAM)hWnd);
		}
		else if (wParam == VK_ESCAPE)
			EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(hWnd));
		//else if (wParam == VK_CONTROL)
		//	EnumChildProc(hWnd, reinterpret_cast<LPARAM>(hWnd));
		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId) {
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		UnhookWindowsHookEx(hook);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	MessageBox(NULL, TEXT("asgasg"), TEXT("bUTTON"), MB_OK | MB_ICONSTOP);
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}