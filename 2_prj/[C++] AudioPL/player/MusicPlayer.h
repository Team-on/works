#pragma once
#include <iostream>
#pragma comment(lib, "audiere\\lib\\audiere.lib")
#include "audiere\include\audiere.h"
using namespace audiere;
#include "PlayList.h"

class MusicPlayer{
private:
	PlayList playlist;
	AudioDevicePtr musicDevice;
	OutputStreamPtr currentMusic;

	char *currPlaylistName;
	int loopMode;
	bool isRand;
	int  volume;
	float shift;
	float balance;

	bool firstPlay;
	bool isStop;

	int prevTrackPersent;
public:
	MusicPlayer();
	MusicPlayer(char argv0[]);
	~MusicPlayer();

	void  PrintAllPlaylists();
	void  LoadPlaylist(char playlistName[]);
	void  SavePlaylist(char playlistName[]);
	void  CreateNewPlaylist(char playlistName[], char folder[]);
	void  CreateNewPlaylistEmpty();
	void  AddToPlaylist(char folder[]);
	void  AddSongToPlaylist(char songPath[]);

	void  PrintCurrentPlaylist();
	void  PrintCurrentTrackName();
	void  PrintNextTrackName(int relativeTrackPos);
	void  PrintTrackPersent(int backgroundFull, int backgroundEmpty, int textColor, char symbol);
	void  PrintCurrVolume(int backgroundFull, int backgroundEmpty, int textColor, char symbol);
	bool  IsTrackPosChange();

	bool  IsEmpty() const;

	// 1 - by name
	void Sort(int sortMode);

	// [0 .. 100]
	void  SetAudioStream(int newPersent);

	// [0 .. 100]
	void  SetVolume(int newVolume);
	int   GetVolume();
	// 0 - off, 1 - on
	void  SetRand(bool newRand);
	bool  GetRand();
	// 0 - Нема, 1 - для цього треку
	void  SetLoopMode(int newLoopMode);
	int   GetLoopMode();

	// -1 left , 1 right
	void  SetBalance(float newBalance);
	float GetBalance();
	// [0.5 .. 2]
	void  SetPitchShift(float newShift);
	float GetPitchShift();

	void ClearPlaylist();

	void ChangeCurrSong(int shift);
	friend void CopyToDesktop(MusicPlayer &pl);

	//Mode: 0 - грати наступний після закінчення(але не перший раз, 1 - Наступний силою, 2 - Попередній силою, 3 - грати наступний після закінчення(але не перший раз)
	int   Play(int mode = 0);
	void  Replay();
	void  Stop();
	void  Reset();

};

