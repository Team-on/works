#include "Header.h"

#include "MusicPlayer.h"
#include "Func.h"

//#define DEBUG

void main(int argc, char **argv){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	RECT r;
	POINT p;
	HWND wh = GetConsoleWindow();
	MusicPlayer player(argv[0]);
	{
		SMALL_RECT src = { 0,0, 50, 37 };
		SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &src);
		SetConsoleTitle("Light player");
		//Устанока розміру шрифта
		typedef BOOL(WINAPI *SETCONSOLEFONT)(HANDLE, DWORD);
		SETCONSOLEFONT SetConsoleFont;
		HMODULE hmod = GetModuleHandleA("KERNEL32.DLL");
		SetConsoleFont = (SETCONSOLEFONT)GetProcAddress(hmod, "SetConsoleFont");
		SetConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		/*///
		PCONSOLE_FONT_INFOEX p = new CONSOLE_FONT_INFOEX;
		p->nFont = 0;
		p->FontWeight = 400;
		p->dwFontSize.X = 8;
		p->dwFontSize.Y = 12;
		p->FaceName;
		p->FontFamily;
		SetCurrentConsoleFontEx(hConsole, 0, p);
		delete p;
		///*/
		//GetAsyncKeyState(VK_LBUTTON) вертає стан фізичної, а не логічної кнопки. GetSystemMetrics(SM_SWAPBUTTON); має виправити це
		GetSystemMetrics(SM_SWAPBUTTON);
		srand(time(NULL));
	}

	//Рамка
	{                          //16
	 	cout << "###################################################\n";   // 0
		cout << "# ~~~~~~~~~~~~ #                                  #\n";   // 1
		cout << "# [   Add    ] #    [ Track name & DesktopCpy]    #\n";   // 2
		cout << "# ~~~~~~~~~~~~ #                                  #\n";   // 3
		cout << "# [  Sleep   ] ####################################\n";   // 4
		cout << "# ~~~~~~~~~~~~ #                                  #\n";   // 5
		cout << "# [   Sort   ] # [          Track bar           ] #\n";   // 6
		cout << "# ~~~~~~~~~~~~ #                                  #\n";   // 7
		cout << "# [  Clear   ] ####################################\n";   // 8
		cout << "# ~~~~~~~~~~~~ #                                  #\n";   // 9
		cout << "# [          ] #   [loop]   <]  ||  [>   [rand]   #\n";   // 10
		cout << "# ~~~~~~~~~~~~ #                                  #\n";   // 11
		cout << "# [          ] #     [+]  [-]    [ Volume Bar ]   #\n";   // 12
		cout << "# ~~~~~~~~~~~~ #                                  #\n";   // 13
		cout << "###################################################\n";   // 14
		cout << "#---------#---------------------------------------#\n"; // 15
	    cout << "# [ XXX ] # [      Shortlist track name         ] #\n";
		cout << "#---------#---------------------------------------#\n"; // 17
		cout << "# [ XXX ] # [      Shortlist track name         ] #\n";
		cout << "#---------#---------------------------------------#\n"; // 19
		cout << "# [ XXX ] # [      Shortlist track name         ] #\n";
		cout << "#---------#---------------------------------------#\n"; // 21
		cout << "# [ XXX ] # [      Shortlist track name         ] #\n";
		cout << "#---------#---------------------------------------#\n"; // 23
		cout << "# [ XXX ] # [      Shortlist track name         ] #\n";
		cout << "#---------#---------------------------------------#\n"; // 25
		cout << "# [ XXX ] # [      Shortlist track name         ] #\n";
		cout << "#---------#---------------------------------------#\n"; // 27
		cout << "# [ XXX ] # [      Shortlist track name         ] #\n";
		cout << "#---------#---------------------------------------#\n"; // 29
		cout << "# [ XXX ] # [      Shortlist track name         ] #\n";
		cout << "#---------#---------------------------------------#\n"; // 31
		cout << "# [ XXX ] # [      Shortlist track name         ] #\n";
		cout << "#---------#---------------------------------------#\n"; // 33
		cout << "# [ XXX ] # [      Shortlist track name         ] #\n";
		cout << "#---------#---------------------------------------#\n";   // 35
		cout << "###################################################";     // 36
																		   // 37 coord курсора
	#ifdef DEBUG
		_getch();
	#endif 
	}
	gotoxy(33, 12, hConsole);
	player.PrintCurrVolume(14, 7, 0, ' ');
	gotoxy(17, 6, hConsole);
	player.PrintTrackPersent(4, 8, 7, ' ');

	/*{
		char *path = add();
		if (path[strlen(path) - 1] == '\\') {
			//Folder
			player.CreateNewPlaylist("defailt", path);
			//player.AddToPlaylist(path);
		}
		else {
			//file
			player.CreateNewPlaylistEmpty();
			player.AddSongToPlaylist(path);
		}
	}

	//player.CreateNewPlaylist("defailt", "D:\\music"); 
	player.SavePlaylist("default");
	*/
	player.LoadPlaylist("default");

	time_t currTimer = 0, prevTime = 0;

	bool isNextTrack = 1;
	bool isMouseClick = 0;
	bool volumeBarClick = 0;
	bool audioStreamBarClick = 0;

	bool DesktopCopy = 0;

	bool flagMenuPunctHover[6] = { 0 };
	bool flagMenuPunctOff[6] = { 0 };
	bool flagMenuVolumeHover[2] = { 0 };
	bool flagMenuVolumeOff[2] = { 0 };
	bool flagMenuMisicControlBtnHover[5] = { 0 };
	bool flagMenuMisicControlBtnOff[5] = { 0 };
	bool shortlistClick[10] = { 0 };	

	while (1) {
		//Считка координат вікна
		GetWindowRect(wh, &r);
		GetCursorPos(&p);

		//Проверка чи плеєр активний. Хітра штука, яка порівнює дескриптори вікон. Якщо найвище вікно(з найбільшим z-level) це плеєр, то робляться всі виводки і перевірки. Інакше лише програється музика. gj!
		if (wh == GetForegroundWindow()) {

		//Проверка координат наводки
		if (p.x - r.left >= 264 && p.x - r.left <= 387 && p.y - r.top >= 168 && p.y - r.top <= 180) {
				//If the high-order bit is 1, the key is down; otherwise, it is up.
				if (isMouseClick = (GetKeyState(VK_LBUTTON) & 0b10000000) != 0)
					volumeBarClick = 1;
		}
		else if (p.x - r.left >= 142 && p.x - r.left <= 398 && p.y - r.top >= 94 && p.y - r.top <= 108) {
			if (isMouseClick = (GetKeyState(VK_LBUTTON) & 0b10000000) != 0)
				audioStreamBarClick = 1;
		}
		else if (p.x - r.left >= 24 && p.x - r.left <= 119 && p.y - r.top >= 42 && p.y - r.top <= 59) {
				flagMenuPunctHover[0] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 24 && p.x - r.left <= 119 && p.y - r.top >= 66 && p.y - r.top <= 83) {
				flagMenuPunctHover[1] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 24 && p.x - r.left <= 119 && p.y - r.top >= 90 && p.y - r.top <= 107) {
				flagMenuPunctHover[2] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 24 && p.x - r.left <= 119 && p.y - r.top >= 114 && p.y - r.top <= 131) {
				flagMenuPunctHover[3] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 24 && p.x - r.left <= 119 && p.y - r.top >= 138 && p.y - r.top <= 155) {
				flagMenuPunctHover[4] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 24 && p.x - r.left <= 119 && p.y - r.top >= 162 && p.y - r.top <= 179) {
				flagMenuPunctHover[5] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 176 && p.x - r.left <= 196 && p.y - r.top >= 168 && p.y - r.top <= 179) {
				flagMenuVolumeHover[0] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 216 && p.x - r.left <= 236 && p.y - r.top >= 168 && p.y - r.top <= 179) {
				flagMenuVolumeHover[1] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 229 && p.x - r.left <= 244 && p.y - r.top >= 143 && p.y - r.top <= 154) {
				flagMenuMisicControlBtnHover[0] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 262 && p.x - r.left <= 277 && p.y - r.top >= 143 && p.y - r.top <= 154) {
				flagMenuMisicControlBtnHover[1] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 295 && p.x - r.left <= 310 && p.y - r.top >= 143 && p.y - r.top <= 154) {
				flagMenuMisicControlBtnHover[2] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 335 && p.x - r.left <= 379 && p.y - r.top >= 143 && p.y - r.top <= 154) {
				flagMenuMisicControlBtnHover[3] = 1;
				isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
			}
		else if (p.x - r.left >= 159 && p.x - r.left <= 204 && p.y - r.top >= 143 && p.y - r.top <= 154) {
			flagMenuMisicControlBtnHover[4] = 1;
			isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0);
		}
		else if (p.x - r.left >= 133 && p.x - r.left <= 406 && p.y - r.top >= 48 && p.y - r.top <= 60) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					DesktopCopy = 1;
			}

		else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 211 && p.y - r.top <= 232) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					shortlistClick[0] = 1;
			}
		else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 235 && p.y - r.top <= 255) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					shortlistClick[1] = 1;
			}
		else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 259 && p.y - r.top <= 280) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					shortlistClick[2] = 1;
			}
		else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 283 && p.y - r.top <= 304) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					shortlistClick[3] = 1;
			}
		else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 307 && p.y - r.top <= 328) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					shortlistClick[4] = 1;
			}
		else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 331 && p.y - r.top <= 352) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					shortlistClick[5] = 1;
			}
		else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 355 && p.y - r.top <= 376) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					shortlistClick[6] = 1;
			}
		else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 379 && p.y - r.top <= 400) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					shortlistClick[7] = 1;
			}
		else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 403 && p.y - r.top <= 424) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					shortlistClick[8] = 1;
			}
		else if (p.x - r.left >= 0 && p.x - r.left <= 411 && p.y - r.top >= 427 && p.y - r.top <= 448) {
				if (isMouseClick = (GetAsyncKeyState(VK_LBUTTON) == -32767 ? 1 : 0))
					shortlistClick[9] = 1;
			}
		
		//Обработка нажатий 
		//Тут же виводиться звук
		//Взагалі краще змінювати флаг для команди, а не брати її напряму
		if (isMouseClick) {
			isMouseClick = 0;

			if (volumeBarClick) {
				volumeBarClick = 0;
				player.SetVolume((p.x - r.left - 269) / ((382 - 269) / 100));
				gotoxy(33, 12, hConsole);
				player.PrintCurrVolume(14, 7, 0, ' ');
			}
			else if (audioStreamBarClick) {
				audioStreamBarClick = 0;
				player.SetAudioStream(round((p.x - r.left - 142) * 1.0 / ((398 - 142) * 1.0 / 100)));
			}
			else if (flagMenuVolumeHover[1]) {
				player.SetVolume(player.GetVolume() - 3);
				gotoxy(33, 12, hConsole);
				player.PrintCurrVolume(14, 7, 0, ' ');
			}
			else if (flagMenuVolumeHover[0]) {
				player.SetVolume(player.GetVolume() + 3);
				gotoxy(33, 12, hConsole);
				player.PrintCurrVolume(14, 7, 0, ' ');
			}

			else if (flagMenuMisicControlBtnHover[0]) {
				isNextTrack = 1;
				player.Play(2);
			}
			else if (flagMenuMisicControlBtnHover[1]) {
				player.Stop();
				isNextTrack = player.Play(0);
			}
			else if (flagMenuMisicControlBtnHover[2]) {
				isNextTrack = 1;
				player.Play(1);
			}
			else if (flagMenuMisicControlBtnHover[3])  {
				if(player.GetRand())
					player.SetRand(0);
				else
					player.SetRand(1);;
			}
			else if (flagMenuMisicControlBtnHover[4]) {
				if (player.GetLoopMode())
					player.SetLoopMode(0);
				else
					player.SetLoopMode(1);;
			}
			else if (DesktopCopy) {
				CopyToDesktop(player);
				DesktopCopy = 0;
			}

			else if (shortlistClick[0]) {
				shortlistClick[0] = 0;
				isNextTrack = 1;
				player.ChangeCurrSong(-4);
				player.Replay();
			}
			else if (shortlistClick[1]) {
				shortlistClick[1] = 0;
				isNextTrack = 1;
				player.ChangeCurrSong(-3);
				player.Replay();
			}
			else if (shortlistClick[2]) {
				shortlistClick[2] = 0;
				isNextTrack = 1;
				player.ChangeCurrSong(-2);
				player.Replay();
			}
			else if (shortlistClick[3]) {
				shortlistClick[3] = 0;
				isNextTrack = 1;
				player.ChangeCurrSong(-1);
				player.Replay();
			}
			else if (shortlistClick[4]) {
				shortlistClick[4] = 0;
				player.Reset();
			}
			else if (shortlistClick[5]) {
				shortlistClick[5] = 0;
				isNextTrack = 1;
				player.ChangeCurrSong(1);
				player.Replay();;
			}
			else if (shortlistClick[6]) {
				shortlistClick[6] = 0;
				isNextTrack = 1;
				player.ChangeCurrSong(2);
				player.Replay();
			}
			else if (shortlistClick[7]) {
				shortlistClick[7] = 0;
				isNextTrack = 1;
				player.ChangeCurrSong(3);
				player.Replay();
			}
			else if (shortlistClick[8]) {
				shortlistClick[8] = 0;
				isNextTrack = 1;
				player.ChangeCurrSong(4);
				player.Replay();
			}
			else if (shortlistClick[9]) {
				shortlistClick[9] = 0;
				isNextTrack = 1;
				player.ChangeCurrSong(5);
				player.Replay();
			}

			else if (flagMenuPunctHover[3]) {
				player.Stop();
				player.ClearPlaylist();
				isNextTrack = 1;
			}
			else if (flagMenuPunctHover[2]) {
				player.Sort(1);
				isNextTrack = 1;
			}
			else if (flagMenuPunctHover[1]) {
				off(1, currTimer, prevTime);
			}
			else if (flagMenuPunctHover[0]) {
				char *path = add();
				if (player.IsEmpty()){
					if (path[strlen(path) - 1] == '\\') {
						//Folder
						player.CreateNewPlaylist("default", path);
					}
					else {
						//file
						player.CreateNewPlaylistEmpty();
						player.AddSongToPlaylist(path);
					}
				}
				else {
					if (path[strlen(path) - 1] == '\\') {
						//Folder
						player.CreateNewPlaylist("default", path);
					}
					else {
						//file
						player.AddSongToPlaylist(path);
					}
				}
			}
			isNextTrack = 1;
		}

		//Перерисовка виділених областей
		else if (flagMenuPunctHover[0]) {
			gotoxy(2, 2, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[   Add    ]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuPunctHover[0] = 0;
			flagMenuPunctOff[0] = 1;
		}
		else if (flagMenuPunctOff[0]) {
			gotoxy(2, 2, hConsole);
			cout << "[   Add    ]";
			flagMenuPunctOff[0] = 0;
		}		
		else if (flagMenuPunctHover[5]) {
			gotoxy(2, 12, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[          ]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuPunctHover[5] = 0;
			flagMenuPunctOff[5] = 1;
		}
		else if (flagMenuPunctOff[5]) {
			gotoxy(2, 12, hConsole);
			cout << "[          ]";;
			flagMenuPunctOff[5] = 0;
		}
		if (flagMenuPunctHover[2]) {
			gotoxy(2, 6, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[   Sort   ]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuPunctHover[2] = 0;
			flagMenuPunctOff[2] = 1;
		}
		else if (flagMenuPunctOff[2]) {
			gotoxy(2, 6, hConsole);
			cout << "[   Sort   ]";;
			flagMenuPunctOff[2] = 0;
		}		
		if	(flagMenuPunctHover[4]) {
			gotoxy(2, 10, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[          ]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuPunctHover[4] = 0;
			flagMenuPunctOff[4] = 1;
		}
		else if (flagMenuPunctOff[4]) {
			gotoxy(2, 10, hConsole);
			cout << "[          ]";;
			flagMenuPunctOff[4] = 0;
		}
		if (flagMenuPunctHover[3]) {
			gotoxy(2, 8, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[  Clear   ]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuPunctHover[3] = 0;
			flagMenuPunctOff[3] = 1;
		}
		else if (flagMenuPunctOff[3]) {
			gotoxy(2, 8, hConsole);
			cout << "[  Clear   ]";
			flagMenuPunctOff[3] = 0;
		}
		if (flagMenuPunctHover[1]) {
			gotoxy(2, 4, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[  Sleep   ]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuPunctHover[1] = 0;
			flagMenuPunctOff[1] = 1;
		}
		else if (flagMenuPunctOff[1]) {
			gotoxy(2, 4, hConsole);
			cout << "[  Sleep   ]";
			flagMenuPunctOff[1] = 0;
		}

		else if (flagMenuVolumeHover[0]) {
			gotoxy(21, 12, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[+]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuVolumeHover[0] = 0;
			flagMenuVolumeOff[0] = 1;
		}		
		else if (flagMenuVolumeOff[0]) {
				gotoxy(21, 12, hConsole);
				cout << "[+]";;
				flagMenuVolumeOff[0] = 0;
			}	
		else if (flagMenuVolumeHover[1]) {
			gotoxy(26, 12, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[-]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuVolumeHover[1] = 0;
			flagMenuVolumeOff[1] = 1;
		}
		else if (flagMenuVolumeOff[1]) {
			gotoxy(26, 12, hConsole);
			cout << "[-]";
			flagMenuVolumeOff[1] = 0;
		}

		else if (flagMenuMisicControlBtnHover[0]) {
			gotoxy(28, 10, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "<]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuMisicControlBtnHover[0] = 0;
			flagMenuMisicControlBtnOff[0] = 1;
		}
		else if (flagMenuMisicControlBtnOff[0]) {
			gotoxy(28, 10, hConsole);
			cout << "<]";
			flagMenuMisicControlBtnOff[0] = 0;
		}

		else if (flagMenuMisicControlBtnHover[1]) {
			gotoxy(32, 10, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "||";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuMisicControlBtnHover[1] = 0;
			flagMenuMisicControlBtnOff[1] = 1;
		}
		else if (flagMenuMisicControlBtnOff[1]) {
			gotoxy(32, 10, hConsole);
			cout << "||";
			flagMenuMisicControlBtnOff[1] = 0;
		}

		else if (flagMenuMisicControlBtnHover[2]) {
			gotoxy(36, 10, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[>";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuMisicControlBtnHover[2] = 0;
			flagMenuMisicControlBtnOff[2] = 1;
		}
		else if (flagMenuMisicControlBtnOff[2]) {
			gotoxy(36, 10, hConsole);
			cout << "[>";
			flagMenuMisicControlBtnOff[2] = 0;
		}

		else if (flagMenuMisicControlBtnHover[3]) {
			gotoxy(41, 10, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[rand]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuMisicControlBtnHover[3] = 0;
			flagMenuMisicControlBtnOff[3] = 1;
		}
		else if (flagMenuMisicControlBtnOff[3]) {
			gotoxy(41, 10, hConsole);
			if(player.GetRand())
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
			cout << "[rand]";
			if (player.GetRand())
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuMisicControlBtnOff[3] = 0;
		}
		else if (flagMenuMisicControlBtnHover[4]) {
			gotoxy(19, 10, hConsole);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
			cout << "[loop]";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuMisicControlBtnHover[4] = 0;
			flagMenuMisicControlBtnOff[4] = 1;
		}
		else if (flagMenuMisicControlBtnOff[4]) {
			gotoxy(19, 10, hConsole);
			if (player.GetLoopMode())
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
			cout << "[loop]";
			if (player.GetLoopMode())
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 7));
			flagMenuMisicControlBtnOff[4] = 0;
		}
	
		//Вивод трека і шортліста
		if (isNextTrack) {
			for (int i = -4; i <= 5; i++) {
				gotoxy(0, 24 + i * 2, hConsole);
				player.PrintNextTrackName(i);
			}
			gotoxy(20, 2, hConsole);
			player.PrintCurrentTrackName();
			isNextTrack = 0;
		}
		isNextTrack = player.Play(3);

		//Виводи полоски трека і координат миши
		if (player.IsTrackPosChange()) {
			gotoxy(17, 6, hConsole);
			player.PrintTrackPersent(4, 8, 7, ' ');
		}

		if(currTimer != 0)
			off(0, currTimer, prevTime);
#ifdef DEBUG
		gotoxy(0, 37, hConsole);
		cout << p.x - r.left << ":" << p.y - r.top << "    " ;
#endif
		//Не убирати. Інакше плеєр жратиме весь ЦП.
		Sleep(1);
		}
		else {
			//Для перерисовки після згортання
			isNextTrack += player.Play(3);
			Sleep(1000);
		}
	}

}

