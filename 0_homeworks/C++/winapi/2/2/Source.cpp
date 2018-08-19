// Файл WINDOWS.H содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows. 
#include <windows.h>
#include <tchar.h>
#include "resource.h"

//прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение"); /* Имя класса окна */

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow){
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	/* 1. Определение класса окна  */

	wcl.cbSize = sizeof(wcl);	// размер структуры WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// окно сможет получать сообщения о двойном щелчке (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// адрес оконной процедуры
	wcl.cbClsExtra = 0;		// используется Windows 
	wcl.cbWndExtra = 0; 	// используется Windows 
	wcl.hInstance = hInst;	// дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// загрузка стандартной иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// загрузка стандартного курсора
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//заполнение окна белым цветом			
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassWindow;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна


						/*  2. Регистрация класса окна  */

	if(!RegisterClassEx(&wcl))
		return 0;	// при неудачной регистрации - выход


					/*  3. Создание окна  */

					// создается окно и  переменной hWnd присваивается дескриптор окна
	hWnd = CreateWindowEx(
		0,		// расширенный стиль окна
		szClassWindow,	// имя класса окна
		TEXT("Каркас  Windows приложения"),	// заголовок окна
											/* Заголовок, рамка, позволяющая менять размеры, системное меню,
											кнопки развёртывания и свёртывания окна  */
		WS_OVERLAPPEDWINDOW,	// стиль окна
		CW_USEDEFAULT,	// х-координата левого верхнего угла окна
		CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		CW_USEDEFAULT,	// ширина окна
		CW_USEDEFAULT,	// высота окна
		NULL,			// дескриптор родительского окна
		NULL,			// дескриптор меню окна
		hInst,		// идентификатор приложения, создавшего окно
		NULL);		// указатель на область данных приложения

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// перерисовка окна
	MessageBox(hWnd, TEXT("Press CapsLock to enumerate all windows\nІ багато інших обработчиків собитий"), TEXT("Info"), MB_OK | MB_ICONINFORMATION);

						/* 5. Запуск цикла обработки сообщений  */

						// получение очередного сообщения из очереди сообщений
	while(GetMessage(&lpMsg, NULL, 0, 0)){
		TranslateMessage(&lpMsg);	// трансляция сообщения
		DispatchMessage(&lpMsg);	// диспетчеризация сообщений
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
		wsprintf(str, TEXT("Нажата клавиша %c"), (char)wParam);
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
