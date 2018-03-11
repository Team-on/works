#include "MusicPlayer.h"
#include <Windows.h>
#include "Func.h"

MusicPlayer::MusicPlayer(){
	musicDevice = OpenDevice();

	currPlaylistName = nullptr;
	loopMode = 0;
	isRand = 0;
	volume = 50;
	shift = 1;
	balance = 0;
	firstPlay = 1;
	isStop = 0;
}

MusicPlayer::MusicPlayer(char argv0[]) : playlist( argv0 ){
	musicDevice = OpenDevice();

	currPlaylistName = nullptr;
	loopMode = 0;
	isRand = 0;
	volume = 50;
	shift = 1;
	balance = 0;
	firstPlay = 1;
	isStop = 0;
	prevTrackPersent = 0;
}

MusicPlayer::~MusicPlayer(){
	if (currPlaylistName != nullptr)
		delete[] currPlaylistName;
}

void  MusicPlayer::PrintAllPlaylists() {
	playlist.ShowAllCreatedPlaylist();
}
void  MusicPlayer::LoadPlaylist(char playlistName[]) {
	char tmp[_MAX_PATH];
	strcpy(tmp, playlistName);
	strcat(tmp, ".lplaylist");
	bool isFind = playlist.LoadPlaylist(tmp);

	if (currPlaylistName != nullptr)
		delete[] currPlaylistName;
	if (isFind) {
		currPlaylistName = new char[strlen(playlistName) + 1];
		strcpy(currPlaylistName, playlistName);
	}
	else
		currPlaylistName = nullptr;
}
void  MusicPlayer::SavePlaylist(char playlistName[]) {
	char tmp[_MAX_PATH];
	strcpy(tmp, playlistName);
	strcat(tmp, ".lplaylist");
	playlist.SavePlaylist(tmp);
}
void  MusicPlayer::CreateNewPlaylist(char playlistName[], char folder[]) {
	if (currPlaylistName != nullptr)
		delete[] currPlaylistName;
	currPlaylistName = new char[strlen(playlistName) + 1];
	strcpy(currPlaylistName, playlistName);
	playlist.SetWorkingFolder(folder);
	playlist.MP3InFolder();
	SavePlaylist(playlistName);
}

void  MusicPlayer::CreateNewPlaylistEmpty() {
	if (currPlaylistName != nullptr)
		delete[] currPlaylistName;
	currPlaylistName = new char[4];
	strcpy(currPlaylistName, "tmp");
}

void  MusicPlayer::AddToPlaylist(char folder[]) {
	playlist.SetWorkingFolder(folder);
	playlist.MP3InFolder();
}
void  MusicPlayer::AddSongToPlaylist(char songPath[]) {
	MusicFile newFile(songPath);
	playlist.PushBack(newFile);
}

bool  MusicPlayer::IsEmpty() const {
	return currPlaylistName == nullptr;
}

void  MusicPlayer::PrintCurrentPlaylist() {
	playlist.PrintAllList();
}
void  MusicPlayer::PrintCurrentTrackName() {
	if (currPlaylistName != nullptr) {
		char * trackName = new char[27];
		strncpy(trackName, playlist.GetSongName(0), 26);
		trackName[26] = 0;
		while (strlen(trackName) < 26)
			strcat(trackName, " ");

		HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((0 << 4) | 14));
		cout << trackName;
		SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((0 << 4) | 7));
		delete[] trackName;
	}
	else {
		cout << "[ Track name & DesktopCpy]";
	}
}
void  MusicPlayer::PrintNextTrackName(int relativeTrackPos) {
	if (currPlaylistName != nullptr) {
		char *trackPos = new char[4];
		itoa(playlist.GetPos(relativeTrackPos), trackPos, 10);
		while (strlen(trackPos) < 3)
			strcat(trackPos, " ");

		char * trackName = new char[39];
		strncpy(trackName, playlist.GetSongName(relativeTrackPos), 37);
		trackName[37] = 0;
		while (strlen(trackName) < 38)
			strcat(trackName, " ");

		if (relativeTrackPos != 0) {
			cout << "# [ ";
			cout << trackPos;
			cout << " ] # ";
			cout << trackName;
			cout << '#';
		}
		else {
			HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
			cout << "# [ ";
			SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((0 << 4) | 14));
			cout << trackPos;
			SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((0 << 4) | 7));
			cout << " ] # ";
			SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((0 << 4) | 14));
			cout << trackName;
			SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((0 << 4) | 7));
			cout << '#';
		}
		delete[] trackName;
		delete[] trackPos;
	}
	else {
		cout << "# [ XXX ] # [      Shortlist track name         ] #";
	}
}

bool  MusicPlayer::IsTrackPosChange() {
	const double pre = 3.2;
	if (currPlaylistName != nullptr && firstPlay == 0) {
		if (currentMusic->getLength() != 0) {
			int currPersent = round(double(currentMusic->getPosition()) / currentMusic->getLength() * 100 / pre);
			if (currPersent != prevTrackPersent) {
				prevTrackPersent = currPersent;
				return 1;
			}
		}
	}
	return 0;
}
void  MusicPlayer::PrintTrackPersent(int backgroundFull, int backgroundEmpty, int textColor, char symbol) {
	const double pre = 3.2;
		HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((backgroundFull << 4) | textColor));	
		for (int i = 0; i < prevTrackPersent; i++)
			cout << symbol;

		SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((backgroundEmpty << 4) | textColor));
		for (int i = prevTrackPersent; i < 100 / pre; i++)
			cout << symbol;

		SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((0 << 4) | 7));
}

void  MusicPlayer::PrintCurrVolume(int backgroundFull, int backgroundEmpty, int textColor, char symbol) {
	const int pre =7;
			HANDLE CONSOLE_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
			int currPersent = round(double(volume) / pre);
				SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((backgroundFull << 4) | textColor));
				char persent[5] = ""; int persentCout = 0;
				itoa(volume, persent, 10);
				strcat(persent, "%");
				for (int i = 0; i < currPersent; i++) {
					if (i >= 100 / pre / 2 - 1)
						if (persentCout < 5)
							cout << persent[persentCout++];
						else
							cout << symbol;
					else
						cout << symbol;
				}

				SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((backgroundEmpty << 4) | textColor));
				for (int i = currPersent; i < 100 / pre; i++) {
					if (i >= 100 / pre / 2 - 1)
						if (persentCout < 5)
							cout << persent[persentCout++];
						else
							cout << symbol;
					else
						cout << symbol;
				}
				SetConsoleTextAttribute(CONSOLE_HANDLE, (WORD)((0 << 4) | 7));
}

void  MusicPlayer::SetVolume(int newVolume){
	volume = newVolume;
	if (volume > 100)
		volume = 100;
	else if (volume < 0)
		volume = 0;
	if (firstPlay == 0) {
		currentMusic->setVolume(float(volume) / 100);
	}
}
int   MusicPlayer::GetVolume() {
	return volume;
}
void  MusicPlayer::SetRand(bool newRand) {
	isRand = newRand;
	if (newRand == 1) 
		playlist.NullAllPlayed();
}
bool  MusicPlayer::GetRand() {
	return isRand;
}
void  MusicPlayer::SetLoopMode(int newLoopMode) {
	loopMode = newLoopMode;
}
int   MusicPlayer::GetLoopMode() {
	return loopMode;
}

void  MusicPlayer::SetBalance(float newBalance) {
	if (firstPlay == 0) {
		if (newBalance >= -1 && newBalance <= 1)
			balance = newBalance;
		currentMusic->setPan(balance);
	}
}
float MusicPlayer::GetBalance() {
	return balance;
}
void  MusicPlayer::SetPitchShift(float newShift) {
	if (firstPlay == 0) {
		if (newShift >= 0.5 && newShift <= 2)
			shift = newShift;
		currentMusic->setPitchShift(shift);
	}
}
float MusicPlayer::GetPitchShift() {
	return shift;
}

void MusicPlayer::ClearPlaylist() {
	playlist.ClearPlaylist();
	delete[] currPlaylistName;
	currPlaylistName = nullptr;
	firstPlay = 1;
}

void MusicPlayer::ChangeCurrSong(int shift) {	
	if (currPlaylistName != nullptr) {
		playlist.SetSongCurrId(playlist.GetSongCurrId() + shift - 1);
		if (firstPlay) {
			playlist.SetSongCurrId(playlist.GetSongCurrId() + 1);
			firstPlay = 0;
		}
	}
}

void MusicPlayer::Replay() {
	if (currPlaylistName != nullptr) {
		currentMusic = OpenSound(musicDevice, playlist.GetNextSong(), true);
		currentMusic->play();
		currentMusic->setVolume(float(GetVolume()) / 100);
	}
}

void MusicPlayer::Sort(int sortMode) {
	if (currPlaylistName != nullptr) {
		if (sortMode == 1) {
			char* songCurrName = new char[strlen(playlist.GetSongName(0)) + 1];
			strcpy(songCurrName, playlist.GetSongName(0));
			playlist.SortByName();

			for (int i = 0; i < playlist.GetSizeCurr(); ++i)
				if (strcmp(playlist.GetSongNameAbs(i), songCurrName) == 0) {
					playlist.SetSongCurrId(i);
					break;
				}

			delete[] songCurrName;
		}
	}
}

void  MusicPlayer::SetAudioStream(int newPersent) {
	if (currPlaylistName != nullptr) {
		if (firstPlay == 0) {
			if (currentMusic->isSeekable())
				currentMusic->setPosition(currentMusic->getLength() / 100 * newPersent);
		}
	}
}

int  MusicPlayer::Play(int mode) {
	if (currPlaylistName != nullptr) {

		if (firstPlay == 0 && loopMode && isStop == 0 && currentMusic->isPlaying() == 0) {
			currentMusic->play();
			currentMusic->setVolume(float(GetVolume()) / 100);
			return 0;
		}

		if (isRand && isStop == 0 && (mode == 1 || mode == 2)) {
			currentMusic = OpenSound(musicDevice, playlist.GetNextRandSong(), true);
			currentMusic->play();
			currentMusic->setVolume(float(GetVolume()) / 100);
			return 3;
		}

		if (firstPlay && mode != 3) {
			if (isRand == 0) {
				currentMusic = OpenSound(musicDevice, playlist.GetNextSong(), true);
				currentMusic->setRepeat(loopMode);
				currentMusic->play();
			}
			else {
				currentMusic = OpenSound(musicDevice, playlist.GetNextRandSong(), true);
				currentMusic->play();
			}

			currentMusic->setVolume(float(GetVolume()) / 100);
			currentMusic->setPan(balance);
			currentMusic->setPitchShift(shift);
			firstPlay = 0;
			return 32000;
		}
		else if (mode == 0 && isStop == 0 && currentMusic->isPlaying() == 0) {
				currentMusic = OpenSound(musicDevice, playlist.GetNextSong(), true);
				currentMusic->play();
				currentMusic->setVolume(float(GetVolume()) / 100);
				isStop = 0;
				return 0;
		}
		else if (mode == 1) {
			currentMusic = OpenSound(musicDevice, playlist.GetNextSong(), true);
			if (isStop == 0) {
				currentMusic->play();
				currentMusic->setVolume(float(GetVolume()) / 100);
			}
			return 1;
		}
		else if (mode == 2) {
			currentMusic = OpenSound(musicDevice, playlist.GetPrevSong(), true);
			if (isStop == 0) {
				currentMusic->play();
				currentMusic->setVolume(float(GetVolume()) / 100);
				return 2;
			}
		}
		else if (mode == 3 && firstPlay == 0 && isStop == 0 && currentMusic->isPlaying() == 0) {
			if (isRand == 0) {
				currentMusic = OpenSound(musicDevice, playlist.GetNextSong(), true);
				currentMusic->play();
				currentMusic->setVolume(float(GetVolume()) / 100);
			}
			else {
				currentMusic = OpenSound(musicDevice, playlist.GetNextRandSong(), true);
				currentMusic->play();
				currentMusic->setVolume(float(GetVolume()) / 100);
			}
			return 3;
		}
		return 0;
	}
	return 0;
}
void  MusicPlayer::Stop() {
	if (firstPlay == 0) {
		if (isStop == 0) {
			currentMusic->stop();
			isStop = 1;
		}
		else {
			currentMusic->play();
			currentMusic->setVolume(float(GetVolume()) / 100);
			isStop = 0;
		}
	}
}
void  MusicPlayer::Reset() {
	if (firstPlay == 0 && isStop == 0) {
		currentMusic->reset();
	}
}

