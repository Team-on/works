// Файл WINDOWS.H содержит определения, макросы, и структуры 
// которые используются при написании приложений под Windows. 
#include <windows.h>
#include <tchar.h>


// прототип оконной процедуры
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("WinAPI app");	/* Имя класса окна */

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow){
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	// 1. Определение класса окна
	wcl.cbSize = sizeof(wcl);	// размер структуры WNDCLASSEX
								// Перерисовать всё окно, если изменён размер по горизонтали или по вертикали
	wcl.style = CS_HREDRAW | CS_VREDRAW;	// CS (Class Style) - стиль класса окна
	wcl.lpfnWndProc = WindowProc;	// адрес оконной процедуры
	wcl.cbClsExtra = 0;		// используется Windows 
	wcl.cbWndExtra = 0; 	// используется Windows 
	wcl.hInstance = hInst;	// дескриптор данного приложения
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// загрузка стандартной иконки
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// загрузка стандартного курсора	
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// заполнение окна белым цветом
	wcl.lpszMenuName = NULL;	// приложение не содержит меню
	wcl.lpszClassName = szClassWindow;	// имя класса окна
	wcl.hIconSm = NULL;	// отсутствие маленькой иконки для связи с классом окна

						// 2. Регистрация класса окна
	if(!RegisterClassEx(&wcl))
		return 0; // при неудачной регистрации - выход

	// 3. Создание окна
	// создается окно и  переменной hWnd присваивается дескриптор окна
	hWnd = CreateWindowEx(
		0,//WS_EX_TRANSPARENT,		// расширенный стиль окна
		szClassWindow,	//имя класса окна
		TEXT("WinAPI app main window"), // заголовок окна
		WS_OVERLAPPEDWINDOW,				// стиль окна
											/* Заголовок, рамка, позволяющая менять размеры, системное меню, кнопки развёртывания и свёртывания окна  */
		CW_USEDEFAULT,	// х-координата левого верхнего угла окна
		CW_USEDEFAULT,	// y-координата левого верхнего угла окна
		CW_USEDEFAULT,	// ширина окна
		CW_USEDEFAULT,	// высота окна
		HWND_DESKTOP,			// дескриптор родительского окна
		NULL,			// дескриптор меню окна
		hInst,			// идентификатор приложения, создавшего окно
		NULL			// указатель на область данных приложения
	);		

					// 4. Отображение окна
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); // перерисовка окна


	MessageBox(hWnd, TEXT("1"), TEXT("2"), MB_OK | MB_ICONINFORMATION);

						// 5. Запуск цикла обработки сообщений

	while(GetMessage(&lpMsg, NULL, 0, 0)) // получение очередного сообщения из очереди сообщений
	{
		TranslateMessage(&lpMsg);	// трансляция сообщения
		DispatchMessage(&lpMsg);	// диспетчеризация сообщений
	}
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam){
	int result;
	switch(uMessage){
	case WM_DESTROY: // сообщение о завершении программы
		PostQuitMessage(0); // посылка сообщения WM_QUIT
		break;
	default:
		// все сообщения, которые не обрабатываются в данной оконной функции 
		// направляются обратно Windows на обработку по умолчанию
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
