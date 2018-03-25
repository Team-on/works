#include "Func.h"

void gotoxy(short x, short y, HANDLE CONSOLE_HANDLE) {
	SetConsoleCursorPosition(CONSOLE_HANDLE, { x, y });
}

void CopyToDesktop(MusicPlayer &pl) {
	if (pl.currPlaylistName != nullptr) {
		char command[_MAX_PATH * 2 + 8], *songName;

		for (int i = strlen(pl.playlist.GetCurrSongPath()) - 1; i >= 0; i--) {
			if (pl.playlist.GetCurrSongPath()[i] == '\\') {
				songName = new char[strlen(&pl.playlist.GetCurrSongPath()[i + 1]) + 1];
				strcpy(songName, &pl.playlist.GetCurrSongPath()[i + 1]);
				break;
			}
		}

		gotoxy(18, 37, GetStdHandle(STD_OUTPUT_HANDLE));
		strcpy(command, "@ copy \"");
		//strcpy(command, "cp \"");
		strcat(command, pl.playlist.GetCurrSongPath());
		strcat(command, "\" ");
		strcat(command, "\"%HOMEDRIVE%%HOMEPATH%\\Desktop\\");
		strcat(command, songName);
		strcat(command, "\"");
		system(command);
		gotoxy(26, 37, GetStdHandle(STD_OUTPUT_HANDLE));
		cout << "                 ";
		gotoxy(0, 0, GetStdHandle(STD_OUTPUT_HANDLE));
		delete[] songName;
	}
}

void off(bool t, time_t &currTimer, time_t &prevTime) {
	if (t == 1) {
		gotoxy(0, 37, GetStdHandle(STD_OUTPUT_HANDLE));
		cout << "       Time (minute) : ";
		cin >> currTimer;
		if (currTimer == 0) {
			gotoxy(0, 37, GetStdHandle(STD_OUTPUT_HANDLE));
			cout << "                            ";
			system("shutdown -a");
		}
		else {
			char *time = new char[12];
			currTimer *= 60;
			itoa(currTimer, time, 10);
			char *command = new char[30];
			strcpy(command, "shutdown -s -t ");
			strcat(command, time);

			//cout << command << endl;
			system("shutdown -a");
			system(command);

			

			gotoxy(0, 37, GetStdHandle(STD_OUTPUT_HANDLE));
			cout << "                                ";

			delete[] command;
			delete[] time;
		}
		gotoxy(0, 0, GetStdHandle(STD_OUTPUT_HANDLE));
	}
	else {
		//gotoxy(0, 37, GetStdHandle(STD_OUTPUT_HANDLE));
		//cout << "                                ";
		gotoxy(0, 37, GetStdHandle(STD_OUTPUT_HANDLE));
		time_t second = time(NULL);
		if (prevTime - second != 0) {
			prevTime = second;
			cout << " [ Remaing : ";
			//Less than 5 min
			if (currTimer <= 300) {
				cout << currTimer-- << " sec";
			}
			//Less than 1 hour
			else if (currTimer <= 3600) {
				cout << currTimer-- / 60 << " min";
			}
			else {
				cout << currTimer / 3600 << ':' << currTimer % 3600 / 60  << " hour";
				currTimer--;
			}

			cout << " ]     ";
		}
	}
}

char *add()
{
FUNC_CPP_ADD_REPEAT:


	int choice = 0;

	char *putty = new char[_MAX_PATH];
	GetLogicalDriveStringsA(1000, putty);
	//cout << "#         #                                       #\n";
	//cout << "#---------#---------------------------------------#\n";
	//cout << "###################################################\n";

	bool t = false;
	int poz = 0;

	HWND wh = GetConsoleWindow();
	RECT r;
	POINT p;
	bool isMouseClick = 0;
	
	while (t == false)
	{	

		gotoxy(0, 16, GetStdHandle(STD_OUTPUT_HANDLE));
		int i = 0;
		//cout << "#---------#---------------------------------------#\n";

		for (char *p = putty; GetDriveTypeA(p) == 3; i++)
		{
			if (i == poz)
			{
				cout << "#   ###-> #                 " << p << "                   #\n\n";
			}
			else
			{
				cout << "#         #                 " << p << "                   #\n\n";
			}
			p += strlen(p) + 1;
		}
		for (int g = i; g < 10; g++)
		{
			cout << "#         #                                       #\n\n";
		}
		cout << "###################################################\n";

		{
			GetWindowRect(wh, &r);
			GetCursorPos(&p);
			if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 211 && p.y - r.top <= 232) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					poz = 0;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 235 && p.y - r.top <= 255) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					poz = 1;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 259 && p.y - r.top <= 280) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					poz = 2;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 283 && p.y - r.top <= 304) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					poz = 3;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 307 && p.y - r.top <= 328) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					poz = 4;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 331 && p.y - r.top <= 352) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					poz = 5;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 355 && p.y - r.top <= 376) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					poz = 6;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 379 && p.y - r.top <= 400) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					poz = 7;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 403 && p.y - r.top <= 424) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					poz = 8;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 427 && p.y - r.top <= 448) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					poz = 9;
			}
		}

		if (poz >= i) {
			poz = i - 1;
		}
		if (isMouseClick) {
			isMouseClick = 0;
			goto DRIVE_SELECTION_CASE_ENTER;
		}

		if (_kbhit()) {
			switch (_getch())
			{
			case'w': case 72: poz > 0 ? poz-- : NULL; break;
			case's': case 80: poz < i - 1 ? poz++ : NULL; break;
			case 13:
			{
			DRIVE_SELECTION_CASE_ENTER:
				char *put;
				put = putty;
				while (poz > 0)
				{
					put += 1 + strlen(put);
					--poz;
				}
				strcpy(putty, put);
				putty[strlen(putty) + 1] = '\0';	putty[strlen(putty)] = '*';
				t = true;
			}
			}
		}

		Sleep(1);
	}

	int down_up = 0;
	while (1)
	{
		
		gotoxy(0, 16, GetStdHandle(STD_OUTPUT_HANDLE));
		WIN32_FIND_DATA FindFileData;
		HANDLE hf;
		char arr[CHAR_MAX][256];
		hf = FindFirstFile(putty, &FindFileData);
		int chot = 0;
		if (hf != INVALID_HANDLE_VALUE) {
			do {
				strcpy(arr[chot++], FindFileData.cFileName);
			} while (FindNextFile(hf, &FindFileData) != 0);
			FindClose(hf);
		}
		//cout << "#         #                                       #\n";
		//cout << "#---------#---------------------------------------#\n";
		//cout << "###################################################\n";
	//	cout << "#---------#---------------------------------------#\n";
		for (int i = down_up; i < 10 + down_up; i++)
		{
			
			if (choice == i)
			{
				cout << "#  ###->  #   ";
				for (int j = 0; j < 35; j++)
				{
					if (j < strlen(arr[i]))
						cout << arr[i][j];
					else
						cout << " ";
				}
				cout << " #\n" << endl;
			}
			else
			{
				cout << "#         #   ";
				for (int j = 0; j < 35; j++)
				{
					if (j < strlen(arr[i]))
						cout << arr[i][j];
					else
						cout << " ";
				}
				cout << " #\n" << endl;
			}
		}

		bool rightMouseClick = 0;
		{
			GetWindowRect(wh, &r);
			GetCursorPos(&p);
			if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 211 && p.y - r.top <= 232) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					choice = 0;
				else if (rightMouseClick = (GetAsyncKeyState(VK_RBUTTON) == -32767 ? 1 : 0))
					choice = 0;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 235 && p.y - r.top <= 255) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					choice = 1;
				else if (rightMouseClick = (GetAsyncKeyState(VK_RBUTTON) == -32767 ? 1 : 0))
					choice = 1;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 259 && p.y - r.top <= 280) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					choice = 2;
				else if (rightMouseClick = (GetAsyncKeyState(VK_RBUTTON) == -32767 ? 1 : 0))
					choice = 2;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 283 && p.y - r.top <= 304) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					choice = 3;
				else if (rightMouseClick = (GetAsyncKeyState(VK_RBUTTON) == -32767 ? 1 : 0))
					choice = 3;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 307 && p.y - r.top <= 328) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					choice = 4;
				else if (rightMouseClick = (GetAsyncKeyState(VK_RBUTTON) == -32767 ? 1 : 0))
					choice = 4;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 331 && p.y - r.top <= 352) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					choice = 5;
				else if (rightMouseClick = (GetAsyncKeyState(VK_RBUTTON) == -32767 ? 1 : 0))
					choice = 5;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 355 && p.y - r.top <= 376) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					choice = 6;
				else if (rightMouseClick = (GetAsyncKeyState(VK_RBUTTON) == -32767 ? 1 : 0))
					choice = 6;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 379 && p.y - r.top <= 400) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					choice = 7;
				else if (rightMouseClick = (GetAsyncKeyState(VK_RBUTTON) == -32767 ? 1 : 0))
					choice = 7;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 403 && p.y - r.top <= 424) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					choice = 8;
				else if (rightMouseClick = (GetAsyncKeyState(VK_RBUTTON) == -32767 ? 1 : 0))
					choice = 8;
			}
			else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 427 && p.y - r.top <= 448) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					choice = 9;
				else if (rightMouseClick = (GetAsyncKeyState(VK_RBUTTON) == -32767 ? 1 : 0))
					choice = 9;
			}
		}
		if (choice >= 10 + down_up) {
			choice = 9 + down_up;
		}

		int get = NULL;
		
		if (isMouseClick) {
			isMouseClick = 0;
			get = 13;
		}
		if (rightMouseClick) {
			rightMouseClick = 0;
			get = 32;
		}

		if (_kbhit()) {
			get = _getch();
		}


		if (get != NULL) {
			switch (get)
			{
			case'w': case 72:
			{
				if (choice == down_up || choice == 0)
				{
					if (down_up > 0)
						down_up--;
					choice = down_up;
				}
				else
					choice > 0 ? choice-- : NULL;
			}break;
			case's': case 80:
			{
				if (choice < chot - 1 && choice + 1>9)
				{
					down_up++;
					choice++;
				}
				else
					choice < chot - 1 ? choice++ : NULL;
			}break;
			}
			if (choice == 1 && get == 13)
			{
				choice = 0;
				for (int i = strlen(putty) - 3; i > 3; i--)
				{
					if (putty[i] == '\\')
					{
						putty[i + 1] = '*';
						putty[i + 2] = '\0';
						i = 0;
					}
				}
				for (int i = 0; i < 10; ++i) {
					gotoxy(0, 16 + i * 2, GetStdHandle(STD_OUTPUT_HANDLE));
					cout << "#         #                                       #\n";
					arr[i][0] = 0;
				}
			}
			else if (choice == 0 && get == 13)
			{
				choice = 0;
				for (int i = 0; i < strlen(putty); i++)
				{
					if (putty[i] == '\\')
					{
						putty[i + 1] = '*';
						putty[i + 2] = '\0';
						break;
					}
				}
				for (int i = 0; i < 10; ++i) {
					gotoxy(0, 16 + i * 2, GetStdHandle(STD_OUTPUT_HANDLE));
					cout << "#         #                                       #\n";
					arr[i][0] = 0;
				}
			}
			else if (get == 13 /*ENTER*/)
			{
				if (arr[choice][strlen(arr[choice]) - 1] == '3' && arr[choice][strlen(arr[choice]) - 2] == 'p' && arr[choice][strlen(arr[choice]) - 3] == 'm'&& arr[choice][strlen(arr[choice]) - 4] == '.')
				{
					putty[strlen(putty) - 1] = '\0';
					strcat(putty, arr[choice]);
					return putty;
				}
				strcat(putty, arr[choice]);
				for (int i = 0; i < strlen(putty); i++)
					if (putty[i] == '*')
						for (int j = i; j < strlen(putty); j++)
							swap(putty[j], putty[j + 1]);
				putty[strlen(putty) + 2] = '\0';
				putty[strlen(putty)] = '\\';
				putty[strlen(putty) + 1] = '\\';
				choice = down_up = 0;

				for (int i = 0; i < 10; ++i) {
					gotoxy(0, 16 + i * 2, GetStdHandle(STD_OUTPUT_HANDLE));
					cout << "#         #                                       #\n";
					arr[i][0] = 0;
				}
			}
			else if (get == 32 /*SPACE*/)
			{
				putty[strlen(putty) - 1] = 0;
				strcat(putty, arr[choice]);
				putty[strlen(putty) + 1] = '\0';
				putty[strlen(putty)] = '\\';
				return putty;
			}
			else if (get == 27 /*ESC*/) {
				goto FUNC_CPP_ADD_REPEAT;
			}
			get = 0;
		}

		Sleep(1);
	}
}
