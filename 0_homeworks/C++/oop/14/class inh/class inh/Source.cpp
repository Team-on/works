#include <iostream>
#include <cmath>
using namespace std;

class Animal {
	char *name;
protected:
	unsigned int age : 8;

	Animal() {
		name = nullptr;
	}
public:
	Animal(const char *Name) {
		SetName(Name);
	}

	void SetName(const char *Name) {
		if (Name != nullptr) {
			if (name != nullptr)
				delete[] name;
			name = new char[strlen(Name) + 1];
			strcpy(name, Name);
		}
		else
			name = nullptr;
	}
	char *GetName() const{
		return name;
	}
};

class Dog : public Animal {
private:
	char *shortName;
public:
	Dog() : Animal()  {
		age = 0; 
	}
	Dog(const char *Name, int age)  {
		SetName(Name);
		this->age = age;
		shortName = new char[4];
		strncpy(shortName, Name, 3);
		shortName[3] = 0;
	}
	~Dog() {
		delete[] shortName;
	}

	char * GetShortName() const {
		return shortName;
	}

	void Sound() {
		cout << "DogSound.mp3" << endl;
	}
};

class Cat : protected Animal {
public:
	Cat() {
		age = 0;
	}
	Cat(const char *Name, int age) {
		SetName(Name);
		this->age = age;
	}

	char *Name() const {
		return GetName();
	}

	void Sound() {
		cout << "CatSound.mp3" << endl;
	}
};

class Bird : public Animal {
	int length;
public:
	Bird() {
		age = 0;
	}
	Bird(const char *Name, int age, int Length = 10) {
		SetName(Name);
		this->age = age;
		length = Length;
	}

	void Sound() {
		cout << "BirdSound.mp3" << endl;
	}

	void Fly() {
		cout << GetName() << " - fly " << length << endl;
	}
};

void func(Animal a) {
	cout << a.GetName() << endl;
}


class String {
protected:
	char *str;
public:
	String() {
		str = new char[1];
		str[0] = 0;
	}
	~String() {
		if (str != nullptr)
			delete[] str;
	}
	String(const String& rhs) {
		str = new char[strlen(rhs.str) + 1];
		strcpy(str, rhs.str);
	}
	String(const char * Str) {
		str = new char[strlen(Str) + 1];
		strcpy(str, Str);
	}	
	String& operator=(const String& rhs) {
		if (&rhs == this)
			return *this;

		if (str != nullptr)
			delete[] str;

		str = new char[strlen(rhs.str) + 1];
		strcpy(str, rhs.str);

		return *this;
	}
	
	int Strlen() const {
		return strlen(str);
	}

	void Clear() {
		this->~String();
		str = nullptr;
	}

	String operator+(const String& rhs) const {
		char *rezult = new char[Strlen() + rhs.Strlen() + 1];
		strcpy(rezult, str);
		strcat(rezult, rhs.str);
		String rez(rezult);
		delete[] rezult;
		return rez;
	}
	String& operator+=(const String& rhs) {
		char *rezult = new char[Strlen() + rhs.Strlen() + 1];
		strcpy(rezult, str);
		strcat(rezult, rhs.str);
		delete[] str;
		str = new char[strlen(rezult) + 1];
		strcpy(str, rezult);
		delete[] rezult;
		return *this;
	}
	friend String operator+(const char* lhs, const String& rhs);

	friend ostream& operator<<(ostream& out, const String& rhs);

	bool operator==(const String& rhs) const {
		return strcmp(str, rhs.str) == 0;
	}
	bool operator!=(const String& rhs) const {
		return !(*this == rhs);
	}
	bool operator<(const String& rhs) const {
		return strcmp(str, rhs.str) == 1;
	}
	bool operator<=(const String& rhs) const {
		return (*this < rhs) || (*this == rhs);
	}
	bool operator>(const String& rhs) const {
		return !(*this <= rhs);
	}
	bool operator>=(const String& rhs) const {
		return !(*this < rhs);
	}

};
String operator+(const char* lhs, const String& rhs) {
	return String(lhs) + rhs;
}

ostream& operator<<(ostream& out, const String& rhs) {
	if (rhs.str != nullptr)
		out << rhs.str;
	else
		out << "ERROR: STRING = NULLPTR";
	return out;
}

class ByteString : public String {
	/*
	str[0]	-			Старший
	str[Strlen() - 1] -	Молодший
	*/
public:
	ByteString() { }
	~ByteString() { }
	ByteString(const ByteString& rhs) {
		str = new char[strlen(rhs.str) + 1];
		strcpy(str, rhs.str);
	}
	ByteString(const char * Str) {
		for(int i = 0; i < strlen(Str); ++i)
			if (Str[i] != '0' && Str[i] != '1') {
				str = new char[1];
				str[0] = 0;
				return;
			}
		str = new char[strlen(Str) + 1];
		strcpy(str, Str);
	}
	ByteString& operator=(const ByteString& rhs) {
		if (&rhs == this)
			return *this;

		if (str != nullptr)
			delete[] str;

		for (int i = 0; i < strlen(rhs.str); ++i)
			if (rhs.str[i] != '0' && rhs.str[i] != '1') {
				str = new char[1];
				str[0] = 0;
				return *this;
			}

		str = new char[strlen(rhs.str) + 1];
		strcpy(str, rhs.str);

		return *this;
	}

	bool operator==(const ByteString& rhs) const {
		return strcmp(str, rhs.str) == 0;
	}
	bool operator!=(const ByteString& rhs) const {
		return !(*this == rhs);
	}

	void Invert() {
		for (int i = 0; i < Strlen(); ++i)
			str[i] = (str[i] == '0' ? '1' : '0');

		++(str[Strlen() - 1]);

		for (int i = Strlen() - 1; i > 0; --i) {
			if (str[i] == '2') {
				str[i] = '0';
				++(str[i - 1]);
			}
		}
		if (str[0] == '2') {
			str[0] = '0';
		}
		
	}

	long long int GetInt() const {
		long long int rez = 0;
		if (str[0] == '0') {
			for (int i = 1; i < Strlen(); ++i)
				rez += ((str[i] == '0') ? 0 : pow(2, Strlen() - 1 - i));
		}
		else {
			//Замість інверсії, просто міняємо логічні сенси 0 і 1. Далі + 1 і робиться відємне.
			for (int i = 1; i < Strlen(); ++i)
				rez += ((str[i] == '0') ? pow(2, Strlen() - 1 - i)  : 0 );
			++rez;
			rez = -rez;
		}
			
		return rez;
	}

	ByteString operator+(const ByteString& rhs) const {
			char *shorter, *longer;
			int sizeS, sizeL;
			if (strlen(str) >= strlen(rhs.str)) {
				sizeS = strlen(rhs.str);
				sizeL = strlen(str);
				longer = new char[sizeL + 1];
				shorter = new char[sizeL + 1];
				strcpy(longer, str);
				strcpy(shorter, rhs.str);
			}
			else {
				sizeS = strlen(str);
				sizeL = strlen(rhs.str);
				longer = new char[sizeL + 1];
				shorter = new char[sizeL + 1];
				strcpy(longer, rhs.str);
				strcpy(shorter, str);
			}

			if (longer[0] == '1') {
				char * tmp = Invert(longer, sizeL + 1);
				delete[] longer;
				longer = tmp;
			}
			if (shorter[0] == '1') {
				char * tmp = Invert(shorter, sizeL + 1);
				delete[] shorter;
				shorter = tmp;	
			}

			strrev(shorter);
			strrev(longer);

			char *rez = new char[sizeL + 3];
			strcpy(rez, longer);
			rez[sizeL + 1] = '\0';
			rez[sizeL + 2] = '\0';
			for (int i = sizeS; i < sizeL; i++)
				shorter[i] = '0';
			shorter[sizeL] = '\0';

			int i = 0;
			for (; i < sizeL; i++) {
				rez[i] += shorter[i] - '0';
				if (rez[i] == '2') {
					rez[i] = '0';
					++rez[i + 1];
				}
				else if (rez[i] == '3') {
					rez[i] = '1';
					++rez[i + 1];
				}
			}

			if (str[0] == rhs.str[0]) {
				rez[i] = str[0];
			}
			
			strrev(rez);
			ByteString rezultStr(rez);
			delete[] rez;
			delete[] shorter;
			delete[] longer;
			return rezultStr;
		}

private:
	char* Invert(char* strF, int size) const {
		char *strRez = new char[size];
		strRez[strlen(strF)] = 0;
		for (int i = 0; i < strlen(strF); ++i)
			strRez[i] = (strF[i] == '0' ? '1' : '0');

		++(strRez[strlen(strRez) - 1]);

		for (int i = strlen(strRez) - 1; i > 0; --i) {
			if (strRez[i] == '2') {
				strRez[i] = '0';
				++(strRez[i - 1]);
			}
		}
		if (strRez[0] == '2') {
			strRez[0] = '0';
		}
		return strRez;
	}
};

/*
Описать класс «Битовая строка» производный от
класса «Строка»
(Строки данного класса могут содержать только симво-
лы ‘0’ и ‘1’). Если в основе инициализирующей строки
встретятся любые символы, отличные от допустимых, то
«Битовая строка» становится пустой. Содержимое строки
рассматривается как двоичное представление целого числа
со знаковым разрядом. Отрицательные числа хранятся
в дополнительном коде.
Методы:

8) сложение битовых строк (перегрузить операторы +
и +=);

*/

int main() {
	ByteString bs("00000001"); 
	/*
	cout << "1 - " << bs << " - " << bs.GetInt() << endl;
	bs = "0101";
	cout << "5 - " << bs << " - " << bs.GetInt() << endl;
	bs = "0"; 
	cout << "0 - " << bs << " - " << bs.GetInt() << endl;
	bs = "11"; 
	cout << "-1 - " << bs << " - " << bs.GetInt() << endl;
	bs = "1011";
	cout << "-5 - " << bs << " - " << bs.GetInt() << endl;
	bs = "01111111"; 
	cout << "127 - " << bs << " - " << bs.GetInt() << endl;
	bs = "10000001";
	cout << "-127 - " << bs << " - " << bs.GetInt() << endl;
	bs = "10000000"; 
	cout << "-128 - " << bs << " - " << bs.GetInt() << endl << endl;

	bs = "0101";
	cout << bs << ' ' << bs.GetInt() << endl;
	bs.Invert();
	cout << bs << ' ' << bs.GetInt() << endl;
	bs = "0";
	cout << bs << ' ' << bs.GetInt() << endl;
	bs.Invert();
	cout << bs << ' ' << bs.GetInt() << endl;	
	bs = "11";
	cout << bs << ' ' << bs.GetInt() << endl;
	bs.Invert();
	cout << bs << ' ' << bs.GetInt() << endl << endl;
	*/

	bs = "01";
	cout << bs << " + " << bs << endl;
	bs = bs + bs;
	cout << bs << ' ' << bs.GetInt() << endl << endl;

	bs = "0101";
	ByteString add("01");
	cout << bs << " + " << add << endl;
	bs = bs + add;
	cout << bs << ' ' << bs.GetInt() << endl << endl;

	bs = "0101";
	add = "0101";
	cout << bs << " + " << add << endl;
	bs = bs + add;
	cout << bs << ' ' << bs.GetInt() << endl << endl;

	bs = "0111";
	add = "0111";
	cout << bs << " + " << add << endl;
	bs = bs + add;
	cout << bs << ' ' << bs.GetInt() << endl << endl << endl << endl;

	bs = "11";
	cout << bs << " + " << bs << endl;
	bs = bs + bs;
	cout << bs << ' ' << bs.GetInt() << endl << endl;

	bs = "1111";
	add = "1100";
	cout << bs << " + " << add << endl;
	bs = bs + add;
	cout << bs << ' ' << bs.GetInt() << endl << endl;

	bs = "11";
	add = "1100";
	cout << bs << " + " << add << endl;
	bs = bs + add;
	cout << bs << ' ' << bs.GetInt() << endl << endl;

	bs = "1101";
	add = "11";
	cout << bs << " + " << add << endl;
	bs = bs + add;
	cout << bs << ' ' << bs.GetInt() << endl << endl;

	bs = "1101";
	add = "1101";
	cout << bs << " + " << add << endl;
	bs = bs + add;
	cout << bs << ' ' << bs.GetInt() << endl << endl;

	bs = "1111";
	add = "1111";
	cout << bs << " + " << add << endl;
	bs = bs + add;
	cout << bs << ' ' << bs.GetInt() << endl << endl;

	//bs = "11";
	//cout << bs << " + " << bs << endl;
	//bs = bs + bs;
	//cout << bs << ' ' << bs.GetInt() << endl << endl;


	/*
	String a("abc"), b("123");
	cout << a << ends << b << endl;

	cout << a + " C-Style " << endl;
	cout << "C-Style " + a << endl;

	a += b;
	cout << a << endl;
	a += "C-String";
	cout << a << endl;

	a.Clear();
	cout << a << endl;
	*/

	/*
	Dog a("%dog_name%", 2);
	cout << a.GetName() << endl;
	a.Sound();
	cout <<  a.GetShortName() << endl;
	cout << endl;

	Cat b("%cat_name%", 2);
	//cout << b.GetName() << endl;
	cout << b.Name() << endl;
	b.Sound();
	cout << endl;

	Bird c("%bird_name%", 1);
	cout << c.GetName() << endl;
	c.Sound();
	c.Fly();
	cout << endl;

	func(a); func(c);
	//func(b);
	cout << endl;

	Animal **arr = new Animal *[2];
	arr[0] = &a;
	//arr[2] = &b;
	arr[1] = &c;

	for (int i = 0; i < 2; ++i)
		cout << arr[i]->GetName() << endl;
	*/

	system("pause");
	return EXIT_SUCCESS;
}



