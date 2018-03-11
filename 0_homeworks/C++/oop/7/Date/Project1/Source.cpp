#include <iostream>

using namespace std;

class Date{
	unsigned int day : 6;
	unsigned int mnt : 5;
	int year;

	bool is366(int year){
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return 1;
		return 0;
	}
	int dayInMnt(int mnt, int year = 400){
		int dayc = 30;
		if (mnt == 2){
			if (is366(year))
				dayc = 29;
			else
				dayc = 28;
		}
		else 
		if (mnt == 1 ||
			mnt == 3 ||
			mnt == 5 ||
			mnt == 7 ||
			mnt == 8 ||
			mnt == 10 ||
			mnt == 12
			)
			dayc = 31;
		return dayc;
	}
public:
	Date() : Date(0,0,0){ }
	Date(int Day, int Mnt, int Year){
		day = Day;
		mnt = Mnt;
		year = Year;
	}
	Date(Date&copy){
		day = copy.day;
		mnt = copy.mnt;
		year = copy.year;
	}

	void Print(){
		cout << day << "/" << mnt << "/" << year;
	}
	void GetCin(){
		int Day, Mnt, Year;
		do{
			cout << "Date(d/m/y): ";
			scanf("%d/%d/%d", &Day, &Mnt, &Year);
			if (!(Day >= 1 && Day <= dayInMnt(Mnt, Year)))
				cout << "Wrong day" << endl;
			if (!(Mnt >= 1 && Mnt <= 12))
				cout << "Wrong month" << endl;
			if (Year <= 0)
				cout << "Wrong year" << endl;
		} while (!(
			(Day >= 1 && Day <= dayInMnt(Mnt, Year))&&
			(Mnt >= 1 && Mnt <= 12) &&
			Year > 0
			));
		day = Day;
		mnt = Mnt;
		year = Year;
	}
	void GetCin_(){
		int Day, Mnt, Year;
		cout << "Date(d/m/y): ";
		scanf("%d/%d/%d", &Day, &Mnt, &Year);
		if (Day < 0)
			Day = 0;
		if (Mnt < 0)
			Mnt = 0;
		day = Day;
		mnt = Mnt;
		year = Year;
	}

	Date& operator=(Date& rhs){
		if (this == &rhs)
			return *this;
		day = rhs.day;
		mnt = rhs.mnt;
		year = rhs.year;
		return *this;
	}
	Date operator+(Date& rhs){
		Date rezult(day + rhs.day, mnt + rhs.mnt, year + rhs.year);
		
		if (rezult.mnt > 12){
			++rezult.year;
			rezult.mnt -= 12;
		}

		while(rezult.day > dayInMnt(rezult.mnt, rezult.year)){
			rezult.day -= dayInMnt(rezult.mnt, rezult.year);
			++rezult.mnt;
			if (rezult.mnt > 12){
				++rezult.year;
				rezult.mnt -= 12;
			}
		}

		return rezult;
	}
	Date operator+(long long& rhs){
		long long Day;
		int Mnt, Year;
		Year = year;
		Mnt = mnt;
		Day = day;

		Day += rhs;
		if (rhs > 0){
			while (Day > dayInMnt(Mnt, Year)){
				if (Day >= 365){
					if (is366(Year) && Day >= 366){
						Day -= 366;
						++Year;
					}
					else{
						Day -= 365;
						++Year;
					}
				}
				else{
					Day -= dayInMnt(Mnt, Year);
					++Mnt;
					if (Mnt > 12){
						++Year;
						Mnt = 1;
					}
				}
			}
		}
		else 
		if (rhs < 0){
			while (Day <= 0){
				Day += dayInMnt(Mnt, Year);
				--Mnt;
				if (Mnt <= 0){
					--Year;
					if (!Year)
						--Year;
					Mnt = 12;
				}
			}
		}
		Date rezult(Day, Mnt, Year);
		return rezult;
	}

	Date operator*(long long& mult){
		long long days = 0;
		for (int i = 1; i < year; i++)
			days += (is366(i)) ? 366 : 365;
		for (int i = 1; i < mnt; i++)
			days += dayInMnt(i, year);
		days += day;
		if (mult)
			days *= mult;
		else
			days = 1;
		Date rezult;
		rezult.year = rezult.mnt = rezult.day = 1;
		while (days > dayInMnt(rezult.mnt, rezult.year)){
			days -= dayInMnt(rezult.mnt, rezult.year);
			++rezult.mnt;
			if (rezult.mnt > 12){
				++rezult.year;
				rezult.mnt = 1;
				}
			}
		rezult.day = days;
		return rezult;
	}
};

void main(){
	Date calendar(4,11,2017);
	char menu;
	do{
		cout << "\t\t\t\tCurr Date: "; calendar.Print(); cout << endl;
		cout << "[1] - =" << endl;
		cout << "[2] - + int" << endl;
		cout << "[3] - + date" << endl;
		cout << "[4] - *" << endl;
		cout << "[0] - exit" << endl;
		cin >> menu;
		switch (menu){
		case '1':
		{
			Date uselessVar;
			uselessVar.GetCin();
			calendar = uselessVar;
		}
		break;
		case '2':
		{
			cin.ignore();
			long long shift;
			cout << "Day shift: ";  cin >> shift;
			//shift = abs(shift);
			calendar = calendar + shift;
		}
		break;
		case '3':
		{
			Date second;
			cin.ignore();
			cout << "Second date: ";  second.GetCin_();
			calendar = calendar + second;
		}
		break;
		case '4':
		{
			cin.ignore();
			long long dayMult;
			cout << "Multiple: ";  cin >> dayMult;
			calendar = calendar * dayMult;
		}
			break;
		}
	} while (menu != '0');
	
	system("pause");
}