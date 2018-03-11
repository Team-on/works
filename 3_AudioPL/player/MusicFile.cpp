#include "MusicFile.h"

MusicFile::MusicFile(){
	isPlayed = 0;
	path = nullptr;
	name = nullptr;
}
MusicFile::MusicFile(const MusicFile &file) {
	name = nullptr;
	path = nullptr;
	SetPath(file.GetPath());
	isPlayed = 0;
}

MusicFile::MusicFile(char * newPath) {
	name = nullptr;
	path = nullptr;
	isPlayed = 0;
	SetPath(newPath);
}

void MusicFile::Copy(MusicFile &newFile) {
	if (path != nullptr)
		delete[] path;
	if (name != nullptr)
		delete[] name;
	isPlayed = 0;
	SetPath(newFile.GetPath());
}

MusicFile& MusicFile::operator=(const MusicFile &rhs) {
	SetPath(rhs.GetPath());
	return *this;
}

MusicFile::~MusicFile(){
	if (path != nullptr)
		delete[] path;
	if (name != nullptr)
		delete[] name;
}

void MusicFile::SetPath(char newPath[]){
	if (path != nullptr)
		delete[] path;
	if (name != nullptr)
		delete[] name;
	path = new char[strlen(newPath) + 1];
	strcpy(path, newPath);

	//Для установки имени
	for (int i = strlen(path) - 1; i >= 0; i--) {
		if (path[i] == '\\') {
			name = new char[strlen(&path[i + 1]) + 1];
			strncpy(name, &path[i + 1], strlen(&path[i + 1]) - 4);
			name[strlen(&path[i + 1]) - 4] = '\0';
			break;
		}
	}

}

char * MusicFile::GetPath() const{
	return path;
}

char * MusicFile::GetName() const {
	return name;
}

void MusicFile::SetIsPlayed(bool newIsPlayed){
	isPlayed = newIsPlayed;
}

bool MusicFile::GetIsPlayed() const{
	return isPlayed;
}

void MusicFile::ReadFromDB(ifstream &fin) {
	char tmp[_MAX_PATH];
	fin.getline(tmp, _MAX_PATH);
	SetPath(tmp);
}
void MusicFile::SaveToDB(ofstream &fout) const {
	fout << path << endl;
}