#pragma once
class Person
{
private:
	char *name, *surname;
	int age;
	static int counter;
public:
	static void GetCnt();

	Person();
	Person(const Person &prs);
	Person(const char *name, const char *surname, const int age);
	~Person();

	void Show();
	void Rename(const char *name, const char *surname);
	void GetAll(const char *name, const char *surname, const int age);
};

