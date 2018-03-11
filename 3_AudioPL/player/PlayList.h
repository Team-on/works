#pragma once
#include "MusicFile.h"

class PlayList{
private:
	char *workingFolder;
	char *pathToDB;

	MusicFile *list;
	int sizeCurr;
	int sizeMax;
	int songCurr;

	
	void DeleteByIndex(const int index);
public:
	void PushBack(MusicFile newFile);

	PlayList();
	PlayList(char workingFolder[]);
	~PlayList();

	void PlayList::ShowAllCreatedPlaylist();
	bool LoadPlaylist(char playlistName[]);
	void SavePlaylist(char playlistName[]) const;

	//������� ����, ���� ������� ������������ � ����
	void SetWorkingFolder(char workingFolderNew[]);

	//��������� �� .MP3 � ����� (����������!)
	void MP3InFolder();

	bool IsAllPlayed() const;
	void NullAllPlayed();
	char * GetNextRandSong();

	void SortByName();

	void ClearPlaylist();

	//�������� ��� ��� ����� � ������
	void PrintAllList() const;
	void PrintCurrentTrackName() const;

	char * GetCurrSongPath() const;

	char * GetNextSong();
	char * GetPrevSong();
	char * GetSongName(int shift) const;
	char * GetSongNameAbs(int absolurePos) const;
	int  GetPos(int shift) const;
	int  GetSongCurrId() const;
	void SetSongCurrId(int newId);
	int GetSizeCurr() const;

	void _SetSongCurr(int newPos);
	int  _GetSongCurr() const;
};

