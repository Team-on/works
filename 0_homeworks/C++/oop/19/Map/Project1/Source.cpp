#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

void f(std::pair<string, int> a) {
	cout << a.first << ' ' << a.second << endl;
}

void main() {
	//std::_Tree <std::pair <string, int> > ;


	map <string, int> m = { std::pair <string, int>("init", 2),
		std::pair <string, int>("init", 3),
		std::pair <string, int>("init", 4)
	};

	//cout << m.count("init");

	m.insert(std::pair <string, int> ("val1", 1));
	m.insert(std::pair <string, int> ("val2", 2));
	m.insert(std::pair <string, int> ("val3", 3));
	m.insert(std::pair <string, int> ("val4", 4));
	
	m.emplace("str", 125);
	
	m["int"] = 879789;

	/*try {
		int a = m.at("val1");
		cout << a << endl;
	}
	catch (exception err) {
		cout << err.what() << endl;
	}
	*/

	
	/*
	int &a = m.at("str");
	cout << a << endl;
	a = 12512;
	cout << m.at("str");
	cout << endl;
	

	std::map <string, int>::iterator k = m.find("str");
	cout << k->first << ' ' << k->second << endl;
	k->second = 0;
	cout << m.find("str")->second << endl;
	*/

	//a = 5;
	//cout << m.at("val1") << endl;
	
	//for (auto i = m.begin(); i != m.end(); ++i)
	//	cout << i->first << ' ' << i->second << endl;

	for_each(m.rbegin(), m.rend(), 
		f
	);
	cout << endl;
	
	/*
	auto ub = m.upper_bound("val1");
	auto lb = m.lower_bound("val3");
	m.erase(ub, lb);
	m.erase("str");
	*/
	for (auto i = m.begin(); i != m.end(); ++i)
		cout << i->first << ' ' << i->second << endl;

	//for (auto i = m.begin(); i != m.end(); ++i)
	//	cout << i->first << ' ' << i->second << endl;

	m.clear();
	cout << m.empty() << endl;

	system("pause");
}