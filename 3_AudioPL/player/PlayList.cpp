#include "PlayList.h"

#include <fstream>
#include <io.h>
#include <direct.h>

#include <iostream>
#include <iomanip>
using namespace std;

PlayList::PlayList(){
	list = nullptr;
	workingFolder = nullptr;
	pathToDB = nullptr;
	sizeCurr = sizeMax = 0;
	songCurr = -1;
}
PlayList::PlayList(char argv0[]) : PlayList(){
	pathToDB = new char[strlen(argv0) + 1];
	strcpy(pathToDB, argv0);
}

PlayList::~PlayList(){
	if (list != nullptr)
		delete[] list;
	if (workingFolder != nullptr)
		delete[] workingFolder;
	if (pathToDB != nullptr)
		delete[] pathToDB;
}

void PlayList::ShowAllCreatedPlaylist() {
	char *pathToList;
	for (int i = strlen(pathToDB) - 1; i >= 0; i--) {
		if (pathToDB[i] == '\\') {
			pathToList = new char[strlen(pathToDB) + 12];
			strncpy(pathToList, pathToDB, i + 1);
			pathToList[i + 1] = '\0';
			break;
		}
	}
	strcat(pathToList, "*.lplaylist");

	_finddata_t fileinfo;
	long long a = _findfirst(pathToList, &fileinfo);   // Find files
	long long p = a;
	while (p != -1) {
			if (strcmp(&fileinfo.name[strlen(fileinfo.name) - 10], ".lplaylist") == 0 ) {
				char tmp[_MAX_PATH];
				strncpy(tmp, pathToList, strlen(pathToList) - 11);
				tmp[strlen(pathToList) - 11] = '\0';
				strcat(tmp, fileinfo.name);
				ifstream fin(tmp);
				int cnt;
				fin >> cnt;
				fin.close();
				cout << fileinfo.name << "\t" << cnt << endl;
			}
		p = _findnext(a, &fileinfo);
	}
	delete[] pathToList;
}

bool PlayList::LoadPlaylist(char playlistName[]){
	char *pathToList;
	for (int i = strlen(pathToDB) - 1; i >= 0; i--) {
		if (pathToDB[i] == '\\') {
			pathToList = new char[strlen(pathToDB) + strlen(playlistName) + 2];
			strncpy(pathToList, pathToDB, i + 1);
			pathToList[i + 1] = '\0';
			break;
		}
	}
	strcat(pathToList, playlistName);
	ifstream fin;
	fin.open(pathToList);
	if (fin.is_open()) {
		int sizetmp;
		fin >> sizetmp;
		if (list != nullptr) {
			delete[] list;
			sizeMax = sizeCurr = 0;
			songCurr = 0;
		}
		list = new MusicFile[0];
		fin.ignore();
		for (int i = 0; i < sizetmp; i++) {
			MusicFile newFile;
			newFile.ReadFromDB(fin);
			PushBack(newFile);
		}
		fin.close();
		delete[] pathToList;
		return 1;
	}
	else {
		delete[] pathToList;
		return 0;
	}
}

void PlayList::SavePlaylist(char playlistName[]) const{
	char *pathToList;
	for (int i = strlen(pathToDB) - 1; i >= 0; i--) {
		if (pathToDB[i] == '\\') {
			pathToList = new char[strlen(pathToDB) + strlen(playlistName) + 2];
			strncpy(pathToList, pathToDB, i + 1);
			pathToList[i + 1] = '\0';
			break;
		}
	}

	strcat(pathToList, playlistName);
	ofstream fout;
	fout.open(pathToList);
	if (fout.is_open()) {
		fout << sizeCurr << endl;
		for (int i = 0; i < sizeCurr; i++) {
			list[i].SaveToDB(fout);
		}
	}
	fout.close();
	delete[] pathToList;
}

void PlayList::SetWorkingFolder(char workingFolderNew[]) {
	if (workingFolder != nullptr)
		delete[] workingFolder;
	workingFolder = new char[strlen(workingFolderNew) + 1];
	strcpy(workingFolder, workingFolderNew);
}

void PlayList::MP3InFolder(){
	char findPath[_MAX_PATH];
	strcpy(findPath, workingFolder);
	strcat(findPath, "\\*.*");
	_finddata_t fileinfo;
	long long a = _findfirst(findPath, &fileinfo);   // Find files
	long long p = a;
	while (p != -1) {
	if (fileinfo.attrib == _A_SUBDIR && strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
			char WorkingFolderInSubDir[_MAX_PATH];
			char OldWorkingFolder[_MAX_PATH];

			strcpy(OldWorkingFolder, workingFolder);
			strcpy(WorkingFolderInSubDir, workingFolder);
			strcat(WorkingFolderInSubDir, "\\");
			strcat(WorkingFolderInSubDir, fileinfo.name);

			SetWorkingFolder(WorkingFolderInSubDir);
			MP3InFolder();
			SetWorkingFolder(OldWorkingFolder);
		}
		else {
			if (strcmp(&fileinfo.name[strlen(fileinfo.name) - 4], ".mp3") == 0 ||
				strcmp(&fileinfo.name[strlen(fileinfo.name) - 4], ".MP3") == 0 ||
				strcmp(&fileinfo.name[strlen(fileinfo.name) - 4], ".wav") == 0 ||
				strcmp(&fileinfo.name[strlen(fileinfo.name) - 4], ".WAV") == 0
				) {
				char pathToCurrMP3[_MAX_PATH];
				strcpy(pathToCurrMP3, workingFolder);
				strcat(pathToCurrMP3, "\\");
				strcat(pathToCurrMP3, fileinfo.name);

				MusicFile newFile(pathToCurrMP3);
				PushBack(newFile);
			}
		}
		p = _findnext(a, &fileinfo);
	}

	/*while (p != -1){

		//if (fileinfo.attrib == _A_SUBDIR) {
		//	MP3InFolder();
		//}

		char pathToCurrMP3[_MAX_PATH];
		strcpy(pathToCurrMP3, workingFolder);
		strcat(pathToCurrMP3, "\\");
		strcat(pathToCurrMP3, fileinfo.name);

		MusicFile newFile(pathToCurrMP3);
		PushBack(newFile);

		p = _findnext(a, &fileinfo);
	}*/
}

void PlayList::SortByName() {
	for (int i = 0; i < sizeCurr; ++i) {
		int min = i;
		for (int j = i; j < sizeCurr; ++j)
			if (strcmp(list[min].GetName(), list[j].GetName()) == 1)
				min = j;
		if (min != i)
			swap(list[min], list[i]);
	}
}

void PlayList::ClearPlaylist() {
	delete[] list;
	list = nullptr;
	sizeCurr = sizeMax = 0;
	songCurr = -1;
	delete[] workingFolder;
	workingFolder = nullptr;
}

void PlayList::PrintAllList() const {
	if (list != nullptr) {
		for (int i = 0; i < sizeCurr; i++) {
			cout << setw(3) << i + 1 << " " << list[i].GetName() << endl;
			//cout << list[i].GetIsPlayer() << endl;
			//cout << "==============" << endl;
		}
	}
}
void PlayList::PrintCurrentTrackName() const {
	if (list != nullptr) {
		cout << setw(3) << list[(songCurr < 0 ? 0 : songCurr)].GetName();
	}
}

void PlayList::_SetSongCurr(int newPos) {
	if (newPos >= 0 && newPos < sizeCurr)
		songCurr = newPos;
}
int  PlayList::_GetSongCurr() const {
	return songCurr;
}

void PlayList::PushBack(MusicFile newFile) {
	if (sizeMax < sizeCurr + 1) {
		MusicFile *tmp = new MusicFile[sizeMax + 4];
		sizeMax += 4;
		for (int i = 0; i < sizeCurr; i++)
			tmp[i].Copy(list[i]);
		delete[] list;
		list = tmp;
	}
	list[sizeCurr++].Copy(newFile);
}
void PlayList::DeleteByIndex(const int index) {
	/*if ((index >= 0 && index < sizeCurr) &&
		sizeCurr != 0
		) {
		if (index == sizeCurr - 1)
			sizeCurr--;
		else {
			Abonent *tmp = new Abonent[sizeMax];
			for (int i = 0; i < sizeCurr; i++) {
				if (i < index)
					tmp[i].Copy(book[i]);
				else if (i > index) {
					tmp[i - 1].Copy(book[i]);
				}
			}
			delete[] book;
			book = tmp;
			sizeCurr--;
		}
	}*/
}

char * PlayList::GetCurrSongPath() const {
	return list[songCurr].GetPath();
}

char *  PlayList::GetNextSong() {
	if (songCurr + 1 >= sizeCurr) {
		songCurr = 0;
		list[songCurr].SetIsPlayed(1);
		return list[songCurr].GetPath();
	}
	else {
		songCurr++;
		list[songCurr].SetIsPlayed(1);
		return list[songCurr].GetPath();
	}
}

char *  PlayList::GetPrevSong() {
	if (songCurr - 1 < 0) {
		songCurr = sizeCurr - 1;
		list[songCurr].SetIsPlayed(1);
		return list[songCurr].GetPath();
	}
	else {
		songCurr--;
		list[songCurr].SetIsPlayed(1);
		return list[songCurr].GetPath();
	}
}

char *  PlayList::GetSongName(int shift) const{
	int songCurr = this->songCurr;
	if (songCurr == -1)
		songCurr = 0;
	if (songCurr + shift >= 0 && songCurr + shift < sizeCurr) 
		return list[songCurr + shift].GetName();
	else if (songCurr + shift < 0)
		return list[abs((sizeCurr + songCurr + shift)) % sizeCurr].GetName();
	else if (songCurr + shift >= sizeCurr)
		return list[(songCurr + shift) % sizeCurr].GetName();
}

char * PlayList::GetSongNameAbs(int absolurePos) const {
	return list[absolurePos].GetName();
}

int PlayList::GetPos(int shift) const {
	int songCurr = this->songCurr;
	if (songCurr == -1)
		songCurr = 0;
	if (songCurr + shift >= 0 && songCurr + shift < sizeCurr)
		return songCurr + shift;
	else if (songCurr + shift < 0)
		return abs((sizeCurr + songCurr + shift)) % sizeCurr;
	else if (songCurr + shift >= sizeCurr)
		return (songCurr + shift) % sizeCurr;
}

int PlayList::GetSongCurrId() const {
	return songCurr;
}
void PlayList::SetSongCurrId(int newId) {
	songCurr = newId;
	if (songCurr < 0) {
		songCurr %= sizeCurr;
		if (songCurr == 0)
			songCurr = -1;
		songCurr = sizeCurr + songCurr ;
	}
	else if (songCurr >= sizeCurr) {
		songCurr %= sizeCurr;
	}
}

bool PlayList::IsAllPlayed() const {
	for (int i = 0; i < sizeCurr; ++i)
		if (!list[i].GetIsPlayed())
			return 0;
	return 1;
}
void PlayList::NullAllPlayed() {
	for (int i = 0; i < sizeCurr; ++i)
		list[i].SetIsPlayed(0);
}

char * PlayList::GetNextRandSong() {
	int songCurrRand;
	if (IsAllPlayed())
		NullAllPlayed();
	do {
		songCurrRand = rand() % sizeCurr;
		if (!list[songCurrRand].GetIsPlayed()) {
			list[songCurrRand].SetIsPlayed(1);
			break;
		}
	} while (1);
	songCurr = songCurrRand;
	return list[songCurr].GetPath();
}

int PlayList::GetSizeCurr() const {
	return sizeCurr;
}