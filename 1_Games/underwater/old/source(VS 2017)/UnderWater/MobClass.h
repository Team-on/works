#pragma once
class MobClass{
public:
	enum CLASS_TYPE { WARRIOR, MAGE, ROGUE};
private:	
	char *className;
	CLASS_TYPE id;

public:
	MobClass();
	MobClass(MobClass& rhs);
	MobClass(CLASS_TYPE ID, char *ClassName);
	
	~MobClass();

	void operator= (MobClass &rhs);

	void SetName(char *Name);
	char * GetName() const;
};

