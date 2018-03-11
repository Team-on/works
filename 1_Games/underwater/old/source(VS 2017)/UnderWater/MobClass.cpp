#include "MobClass.h"
#include <string.h>


MobClass::MobClass(){
	className = nullptr;
	id = WARRIOR;
}
MobClass::MobClass(MobClass& rhs) {
	id = rhs.id;
	className = nullptr;
	SetName(rhs.GetName());
}
MobClass::MobClass(CLASS_TYPE ID, char *ClassName){
	id = ID;
	className = nullptr;
	SetName(ClassName);
}


MobClass::~MobClass(){
	if (className != nullptr)
		delete[] className;
}
void MobClass::operator= (MobClass &rhs) {
	SetName(rhs.GetName());
	id = rhs.id;
}

void MobClass::SetName(char *Name) {
	if (className != nullptr)
		delete[] className;
	className = new char[strlen(Name) + 1];
	strcpy(className, Name);
}
char * MobClass::GetName() const {
	return className;
}