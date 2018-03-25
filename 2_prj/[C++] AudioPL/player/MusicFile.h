#pragma once
#include <string.h>
#include <fstream>
using namespace std;

class MusicFile {
private:
	char *path;
	bool isPlayed;
	char *name;

public:
	explicit MusicFile();
	MusicFile(const MusicFile &file);
	explicit MusicFile(char * newPath);
	~MusicFile();

	MusicFile& operator=(const MusicFile &rhs);

	//���������� ���� �� �����
	void SetPath(char newPath[]);
	//������� ���� �� �����
	char* GetPath() const;

	void SetIsPlayed(bool newIsPlayed);
	bool GetIsPlayed() const;

	//������� ��� �����
	char* GetName() const;

	void Copy(MusicFile &newFile);

	void ReadFromDB(ifstream &fin);
	void SaveToDB(ofstream &fout) const;
};
