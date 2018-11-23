//pupil049 xrpzf
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Long{
	string n;
public:
	Long(unsigned long long int a){
		char c[10];
		itoa(a, c, 10);

		n = string(c);
	}

	Long(string s){
		n = string(s);
	}

	Long Add(Long a){
		string buff;
		int mem = 0, start = (n.length() > a.n.length() ? n.length() : a.n.length()) + 1, tmp;
		buff = string(start, '0');

		for(int i = start; i > 0; --i){
			if(n.length() > i - 1)
				mem += n[i - 1] - '0';			
			if(a.n.length() > i - 1)
				mem += a.n[i - 1] - '0';		

			buff[i] = mem % 10 + buff[i];
			mem /= 10;
			if(buff[i] > '9'){
				buff[i] -= 9;
				++mem;
			}
			if(mem != 0){
				buff[i - 1] = mem % 10 + '0';
				mem = 0;
			}
		}

		if(buff[0] == '0')
			buff = buff.substr(1);

		return Long(buff);
	}

	bool LessOrEquelThan(Long a){
		
	}

	bool DevideWithZeroMod(Long a){
	
	}

	string Get(){
		return n;
	}
};

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("task3.dat", ios_base::in);
	fout.open("task3.rez", ios_base::trunc);

    //unsigned long long int sum = 0;
	unsigned int friends, _max, cnt = 0, _i = 1;
	fin >> _max >> friends;

	Long sum(0), max(_max), i(_i);

	//for(; i <= max; ++i){
		//sum += i;
		//if(sum % friends == 0)
		//	++cnt;

		//sum = (i + 1) * i / 2;
		//if(sum % friends == 0)
		//	++cnt;

		//if(
		//	((i % 2 == 0 && ((i / 2) % friends == 0 || (i + 1)		 % friends == 0) ) ||
		//	( i % 2		 && ((i % friends) == 0		|| ((i + 1) / 2) % friends == 0) ))
		//)
		//	++cnt;
	//}

	fout << cnt;

	fin.close();
	fout.close();
	return 0;
}
