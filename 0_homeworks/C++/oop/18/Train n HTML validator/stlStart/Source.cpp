#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

#include <time.h>

#include <stack>
#include <vector>
#include <string>

using namespace std;

class Train {
	unsigned int number;
	string destinationPoint;
	struct DATA{
		unsigned char day : 5, mnt : 4;
		unsigned short year;
		string toStr() const {
			string rez;
			char tmp[10];
			_itoa(day, tmp, 10);
			rez = tmp;
			rez += ":";
			_itoa(mnt, tmp, 10);
			rez += tmp;
			rez += ":";
			_itoa(year, tmp, 10);
			rez += tmp;
			return rez;
		}

	}departureTime;

public:
	Train(unsigned int Number, string DestinationPoint, Train::DATA DepartureTime) {
		number = Number;
		destinationPoint = DestinationPoint;
		departureTime = DepartureTime;
	}

	friend class TrainStantion;
};

class TrainStantion {
	vector <Train> train;
public:
	TrainStantion() {}

	void SetTrainInfo(unsigned int Number, string DestinationPoint, Train::DATA DepartureTime) {
		train.push_back({ Number, DestinationPoint, DepartureTime });
	}
	string GetTrainInfo(int trainPos) const{
		if (trainPos < 0 || trainPos >= train.size())
			throw exception("Out of range in TrainStantion->GetTrainInfo()");

		char tmp[10];
		int currLen = 6;
		string rezult;
		
		rezult = " | ";	
		_itoa(train[trainPos].number, tmp, 10);
		rezult += tmp;
		currLen += strlen(tmp);
		while (++currLen <= 16) 
			rezult.push_back(' ');
		rezult += " | ";

		rezult += train[trainPos].destinationPoint;
		currLen += train[trainPos].destinationPoint.length() + 3;
		while (++currLen <= 36) 
			rezult.push_back(' ');
		rezult += " | ";

		rezult += train[trainPos].departureTime.toStr();
		currLen += train[trainPos].departureTime.toStr().length() + 3;
		while (++currLen <= 50) 
			rezult.push_back(' ');
		rezult += " | ";

		return rezult;
	}
	string GetTrainInfo() const {
		string rezult;
		char tmp[10];
		int currLen;

		for (auto &i : train) {		
			currLen = 6;

			rezult += " | ";
			_itoa(i.number, tmp, 10);
			rezult += tmp;
			currLen += strlen(tmp);
			while (++currLen <= 16)
				rezult.push_back(' ');
			rezult += " | ";

			rezult += i.destinationPoint;
			currLen += i.destinationPoint.length() + 3;
			while (++currLen <= 36)
				rezult.push_back(' ');
			rezult += " | ";

			rezult += i.departureTime.toStr();
			currLen += i.departureTime.toStr().length() + 3;
			while (++currLen <= 50)
				rezult.push_back(' ');
			rezult += " |\n";
		}

		return rezult;
	}
};

class HTMLValidator {
	ifstream file;
public:
	HTMLValidator() {}

	HTMLValidator(string path) : file(path) {}

	~HTMLValidator() {
		file.close();
	}

	bool Open(string path) {
		if (file.is_open())
			file.close();
		file.open(path);
		return file.is_open();
	}

	string Validate(){
		string rez = "Error strings:\n";
		string buff;
		char lastSym = 0;

		while (!file.eof()) {
			getline(file, buff);
			bool isError = 0;
			for (auto &i : buff) {
				if (i == '<' && lastSym == '<')
					rez += buff + '\n';  
				else if(i == '<')
					lastSym = '<';
				else if (i == '>' && lastSym == '<')
					lastSym = '>';
				else if (i == '>')
					rez += buff + '\n';
			}
		}

		if (rez.size() == 15)
			rez = "Clear code";

		return rez;
	}
};

/*
1) Создайте приложение «Валидатор HTML-файлов». Приложе-
ние запрашивает у пользователя путь к файлу, после чего прове-
ряет файл на валидность. Критерием валидности для вашего про-
екта являются правила: все открытые теги должны закрываться,
если был знак < его должен закрыть знак >. По итогам валидации
нужно отобразить результат проверки на экран. Используйте для
работы с файлами потоки, а для работы со строками класс string.
Примеры:
Содержимое валидного файла
<html>
<body>To be or not to be</body>
</html>
Содержимое невалидного файла
<html>
<body To be or not to be</body>
</html>
*/


void main(int argc, char ** argv) {
	srand(time(NULL));
	atexit([]() {system("pause"); });

	string html_PATH = argv[0];
	html_PATH.resize(html_PATH.find_last_of('\\') + 1);
	html_PATH += "index.html";
	html_PATH.shrink_to_fit();

	HTMLValidator html(html_PATH);

	cout << html.Validate() << endl;

	/*
	TrainStantion stantion;

	for(int i = 0; i < 20; ++i)
		stantion.SetTrainInfo(
			rand() % 1000000, 
			string("stantion ") + char(('0' + rand() % 10)) + char(('0' + rand() % 10)),
			{unsigned char(rand() % 31 + 1),unsigned char(10), 2001}
	);
	cout << stantion.GetTrainInfo(0) << endl;
	cout << stantion.GetTrainInfo() << endl;
	*/
}