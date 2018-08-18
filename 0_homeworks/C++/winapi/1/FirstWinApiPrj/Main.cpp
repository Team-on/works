// ���� WINDOWS.H �������� �����������, �������, � ��������� 
// ������� ������������ ��� ��������� ���������� ��� Windows. 
#include <windows.h>
#include <tchar.h>


// �������� ������� ���������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("WinAPI app");	/* ��� ������ ���� */

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow){
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	// 1. ����������� ������ ����
	wcl.cbSize = sizeof(wcl);	// ������ ��������� WNDCLASSEX
								// ������������ �� ����, ���� ������ ������ �� ����������� ��� �� ���������
	wcl.style = CS_HREDRAW | CS_VREDRAW;	// CS (Class Style) - ����� ������ ����
	wcl.lpfnWndProc = WindowProc;	// ����� ������� ���������
	wcl.cbClsExtra = 0;		// ������������ Windows 
	wcl.cbWndExtra = 0; 	// ������������ Windows 
	wcl.hInstance = hInst;	// ���������� ������� ����������
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� ����������� ������
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// �������� ������������ �������	
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ���������� ���� ����� ������
	wcl.lpszMenuName = NULL;	// ���������� �� �������� ����
	wcl.lpszClassName = szClassWindow;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����

						// 2. ����������� ������ ����
	if(!RegisterClassEx(&wcl))
		return 0; // ��� ��������� ����������� - �����

	// 3. �������� ����
	// ��������� ���� �  ���������� hWnd ������������� ���������� ����
	hWnd = CreateWindowEx(
		0,//WS_EX_TRANSPARENT,		// ����������� ����� ����
		szClassWindow,	//��� ������ ����
		TEXT("WinAPI app main window"), // ��������� ����
		WS_OVERLAPPEDWINDOW,				// ����� ����
											/* ���������, �����, ����������� ������ �������, ��������� ����, ������ ������������ � ���������� ����  */
		CW_USEDEFAULT,	// �-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// y-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// ������ ����
		CW_USEDEFAULT,	// ������ ����
		HWND_DESKTOP,			// ���������� ������������� ����
		NULL,			// ���������� ���� ����
		hInst,			// ������������� ����������, ���������� ����
		NULL			// ��������� �� ������� ������ ����������
	);		

					// 4. ����������� ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); // ����������� ����


	MessageBox(hWnd, TEXT("1"), TEXT("2"), MB_OK | MB_ICONINFORMATION);

						// 5. ������ ����� ��������� ���������

	while(GetMessage(&lpMsg, NULL, 0, 0)) // ��������� ���������� ��������� �� ������� ���������
	{
		TranslateMessage(&lpMsg);	// ���������� ���������
		DispatchMessage(&lpMsg);	// ��������������� ���������
	}
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam){
	int result;
	switch(uMessage){
	case WM_DESTROY: // ��������� � ���������� ���������
		PostQuitMessage(0); // ������� ��������� WM_QUIT
		break;
	default:
		// ��� ���������, ������� �� �������������� � ������ ������� ������� 
		// ������������ ������� Windows �� ��������� �� ���������
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
