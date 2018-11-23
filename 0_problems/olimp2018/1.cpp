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
	fin.open("task1.dat", ios_base::in);
	fout.open("task1.rez", ios_base::trunc);

    vector<string> v;
	int vecSize = 0, max = 0, cnt = 0;
	v.push_back(string());
	char c;

	while(true){
		fin.get(c);

		if(c == '.' || c == '!' || c == '?')
			break;

		if(c == ' ' || c == ',' || c == '-' || c == ':' || c == ';'){
			v.push_back(string());
			++vecSize;
		}
		else{
			v[vecSize].push_back(c);
		}
	}

	for(int i = 0; i <= vecSize; ++i){
		if(v[i].length() != 0)
			++cnt;
		if(v[i].length() > v[max].length())
			max = i;
	}

	fout << cnt << ' ' << v[max].length();

	fin.close();
	fout.close();
    return 0;
}
