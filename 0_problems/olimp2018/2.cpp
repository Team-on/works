//pupil049 xrpzf
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
	ifstream fin;
	ofstream fout;
	fin.open("task2.dat", ios_base::in);
	fout.open("task2.rez", ios_base::trunc);

    int real, want, curr;
	string s;

	fin >> curr >> want;
	fin.ignore();
	getline(fin, s);
	real = curr;

	if(
		(s == "heat" && want > real) ||
		(s == "freeze" && want < real) ||
		(s == "auto")
	)
		real = want;

	fout << real;

	fin.close();
	fout.close();
	return 0;
}
