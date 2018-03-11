#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

#include <conio.h>

#include <string>
#include <vector>

#include <algorithm>

using namespace std;

typedef unsigned short int usint;
typedef unsigned int uint;
typedef unsigned long long int ullint;
typedef long long int llint;
typedef unsigned char uchar;


class Avtosalon {
public:
	struct _CAR{
		usint year;
		string name;
		double engine;
		uint price;

		_CAR() { }
		_CAR(usint Year, string Name, double Engine, uint Price) {
			year = Year;
			name = Name;
			engine = Engine;
			price = Price;
		}
		_CAR(const _CAR & rhs) {
			year = rhs.year;
			name = rhs.name;
			engine = rhs.engine;
			price = rhs.price;
		}

		bool operator==(_CAR rhs) {
			return (year == rhs.year) && (name == rhs.name) && (engine == rhs.engine) && (price == rhs.price);
		}
		bool operator!=(_CAR rhs) {
			return !(*this == rhs);
		}
	};

private:
	vector <_CAR> car;

public:
	bool Load(const string &loadPath) {
		ifstream in(loadPath);
		if (!in.is_open())
			return 0;

		in.close();
		return 1;
	}
	bool Save(const string &savePath) const {
		ofstream out(savePath);
		if (!out.is_open())
			return 0;


		out.close();
		return 1;
	}

	void AddCar(const _CAR Car){
		car.push_back(Car);
	}

	void DeleteCar(const _CAR Car) {
		auto rez = remove(car.begin(), car.end(), Car);
		usint length = 0;
		for (auto i = car.begin(); i != rez; ++i, ++length);
		car.resize(length);
	}
	void DeleteCar(bool(*funcPtr)(const _CAR&)) {
		auto rez = remove_if(car.begin(), car.end(), funcPtr);
		usint length = 0;
		for (auto i = car.begin(); i != rez; ++i, ++length);
		car.resize(length);
	}

	const string List() const {
		return List([](const _CAR& rhs)->bool {return 1; });
	}
	const string List( bool(*funcPtr)(const _CAR&) ) const {
		string rez;
		char tmp[20];
		char tmp2[20];

		for (auto &i : car) {
			if (funcPtr(i)) {
				rez += i.name;
				for (int j = i.name.length(); j <= 32; ++j)		rez += ' ';
				_itoa(i.year, tmp, 10);
				rez += tmp;
				rez += ' ';
				for (int j = strlen(tmp); j <= 10; ++j)		rez += ' ';
				_itoa(i.engine, tmp, 10);
				_itoa(int(i.engine * 1000) % 1000, tmp2, 10);
				while (tmp2[strlen(tmp2) - 1] == '0') 
					tmp2[strlen(tmp2) - 1] = 0;
				rez += tmp;
				if (tmp2[0] != 0) {
					rez += '.';
					rez += tmp2;
				}
				rez += ' ';
				for (int j = strlen(tmp) + ((strlen(tmp2) != 0)? strlen(tmp2) + 1 :0); j <= 10; ++j)		rez += ' ';
				_itoa(i.price, tmp, 10);
				rez += tmp;
				rez += '\n';
			}
		}

		rez.resize(rez.length() - 1);
		rez.shrink_to_fit();

		return rez;
	}

	void SortBy( bool (*funcPtr)(const Avtosalon::_CAR&, const Avtosalon::_CAR &) ) {
		sort(car.begin(), car.end(), funcPtr);
	}

	vector <_CAR> Find( bool(*funcPtr)(const _CAR&) ) const {
		vector <_CAR> rez;
		for (auto &i : car)
			if (funcPtr(i))
				rez.push_back(i);
		rez.shrink_to_fit();
		return rez;
	}
};

int main(int argc, char ** argv) {
	setlocale(NULL, "RUS");
	atexit([]() {cout << "\n......\nEND...\n......"; _getch(); });

	string DB_PATH = argv[0];
	DB_PATH.resize(DB_PATH.find_last_of('\\') + 1);
	DB_PATH += "avtosalon.db";
	DB_PATH.shrink_to_fit();

	Avtosalon salon;

	salon.AddCar(Avtosalon::_CAR(2001, "Avto1", 1, 100));
	salon.AddCar(Avtosalon::_CAR(2015, "Avto2", 2.2, 10));
	salon.AddCar(Avtosalon::_CAR(2008, "Avto3", 3, 1000));
	salon.AddCar(Avtosalon::_CAR(1980, "Avto4", 4, 350));
	salon.AddCar(Avtosalon::_CAR(2017, "Avto5", 5.5, 10000));

	salon.AddCar(Avtosalon::_CAR(2020, "ERROR_CAR", 5.5, 10000));
	salon.AddCar(Avtosalon::_CAR(2020, "ERROR_CAR", 51235.52412, 1123521350000));
	salon.AddCar(Avtosalon::_CAR(2020, "ERROR_CAR522153", 5235.442145, 1235));

	salon.DeleteCar(
		[](const Avtosalon::_CAR &car)->bool {
		//return strstr(car.name.c_str(), "Avto") != NULL;
		//return car.name == "ERROR_CAR";
		return strstr(car.name.c_str(), "ERROR") != NULL;
	}
	);

	salon.SortBy(
		[](const Avtosalon::_CAR &car1, const Avtosalon::_CAR &car2)->bool {
			return car1.price < car2.price;
			//return car1.name.compare(car2.name) > 0;
	}
	);

	cout << salon.List() << endl << endl;

	for (auto &i : salon.Find(
		[](const Avtosalon::_CAR &car)->bool {
		return car.engine > 2.5;
	})
	)
		cout << i.name << '\t' << i.engine << '\t' << i.price << endl;
	cout << endl;

	return EXIT_SUCCESS;
}
