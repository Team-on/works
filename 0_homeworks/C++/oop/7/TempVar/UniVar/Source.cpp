#include <iostream>

using namespace std;

class xstring{
private:
	char *str;
public:
	xstring(){
		str = nullptr;
	}
	xstring(char *Str){
		str = new char[strlen(Str) + 1];
		strcpy(str, Str);
	}
	xstring(xstring& copy){
		str = new char[strlen(copy.str) + 1];
		strcpy(str, copy.str);
	}
	~xstring(){
		if (str != nullptr)
			delete[] str;
	}

	char* GetStr() const {
		char *ret = new char[strlen(str)];
		strcpy(ret, str);
		return ret;
	}

	xstring& operator=(xstring& rhs){
		if (this == &rhs)
			return *this;
		if (str != nullptr)
			delete[] str;
		str = new char[strlen(rhs.str) + 1];
		strcpy(str, rhs.str);
		return *this;
	}
	xstring& operator=(char* rhs){
		if (str != nullptr)
			delete[] str;
		str = new char[strlen(rhs) + 1];
		strcpy(str, rhs);
		return *this;
	}

	xstring operator*(xstring& rhs)const{
		char *rezult = new char[((str > rhs.str)? strlen(str) : strlen(rhs.str)) + 1];
		rezult[0] = '\0';
		int rsize = -1;
		for (int i = 0; i < strlen(str); ++i)
		for (int j = 0; j < strlen(rhs.str); ++j)
		if (str[i] == rhs.str[j]){
			for (int k = 0; k < rsize; ++k)
				if (rezult[k] == str[i])
					break;	
			rezult[++rsize] = str[i];
		}
		rezult[++rsize] = '\0';
		xstring rez(rezult);
		delete[] rezult;
		return rez;;
	}
	xstring operator/(xstring& rhs)const{
		char *rezult = new char[((strlen(str) > strlen(rhs.str)) ? strlen(str) : strlen(rhs.str)) + 1];
		rezult[0] = '\0';
		int rsize = -1;  bool isUni = 0;
		for (int i = 0; i < strlen(str); ++i){
			for (int j = 0; j < strlen(rhs.str); ++j){
				if (str[i] == rhs.str[j]){
					isUni = 1;
					break;
				}
			}
			if (isUni == 0){
				for (int k = 0; k < rsize; ++k)
				if (rezult[k] == str[i])
					break;
				rezult[++rsize] = str[i];
			}
			isUni = 0;
		}
		rezult[++rsize] = '\0';
		xstring rez(rezult);
		delete[] rezult;
		return rez;;
	}
	xstring operator+(xstring& rhs)const{
		char *rezult = new char[strlen(str) + strlen(rhs.str) + 2];	
		strcpy(rezult, str);
		strcat(rezult, rhs.str);
		xstring rez(rezult);
		delete[] rezult;
		return rez;;
	}
	xstring operator-(xstring& rhs)const{
		if (strlen(str) - strlen(rhs.str) + 1 >= 1){
			char *rezult = new char[strlen(str) - strlen(rhs.str) + 1];
			rezult[0] = '\0';
			strncpy(rezult, str, strlen(str) - strlen(rhs.str));
			rezult[strlen(str) - strlen(rhs.str)] = '\0';
			xstring rez(rezult);
			delete[] rezult;
			return rez;
		}
		char *rezult = new char[1];
		rezult[0] = '\0';
		xstring rez(rezult);
		delete[] rezult;
		return rez;
	}
	xstring operator+(char *rhs) const{
		char *rezult = new char[strlen(str) + strlen(rhs) + 1];
		strcpy(rezult, str);
		strcat(rezult, rhs);
		xstring rez(rezult);
		delete[] rezult;
		return rez;;
	}

	xstring& operator*=(xstring& rhs){
		char *rezult = new char[((str > rhs.str) ? strlen(str) : strlen(rhs.str)) + 1];
		int rsize = -1;
		for (int i = 0; i < strlen(str); ++i)
		for (int j = 0; j < strlen(rhs.str); ++j)
		if (str[i] == rhs.str[j]){
			for (int k = 0; k < rsize; ++k)
			if (rezult[k] == str[i])
				break;
			rezult[++rsize] = str[i];
		}
		rezult[++rsize] = '\0';
		*this = rezult;
		delete[] rezult;
		return *this;;
	}
	xstring& operator/=(xstring& rhs){
		char *rezult = new char[((strlen(str) > strlen(rhs.str)) ? strlen(str) : strlen(rhs.str)) + 1];
		int rsize = -1;  bool isUni = 0;
		for (int i = 0; i < strlen(str); ++i){
			for (int j = 0; j < strlen(rhs.str); ++j){
				if (str[i] == rhs.str[j]){
					isUni = 1;
					break;
				}
			}
			if (isUni == 0){
				for (int k = 0; k < rsize; ++k)
				if (rezult[k] == str[i])
					break;
				rezult[++rsize] = str[i];
			}
			isUni = 0;
		}
		rezult[++rsize] = '\0';
		*this = rezult;
		delete[] rezult;
		return *this;;
	}
	xstring& operator+=(xstring& rhs){
		char *rezult = new char[strlen(str) + strlen(rhs.str) + 1];
		strcpy(rezult, str);
		strcat(rezult, rhs.str);
		*this = rezult;
		delete[] rezult;
		return *this;
	}

	bool operator==(xstring& rhs) {
		return strcmp(str, rhs.str) == 0;
	}
	bool operator>(xstring& rhs) {
		return strlen(str) > strlen(rhs.str);
	}

	xstring operator!()const{
		char *rezult = new char[strlen(str) + 1];
		strcpy(rezult, str);
		strrev(rezult);
		xstring rez(rezult);
		delete[] rezult;
		return rez ;
	}

	void Print() const{
		cout << str;
	}
	friend xstring operator+(char* str, xstring &rhs);
	friend ostream& operator<<(ostream& out, xstring &rhs);
	friend istream& operator>>(istream& in, xstring &rhs);
};
xstring operator+(char* str, xstring &rhs){
	char *rezult = new char[strlen(str) + strlen(rhs.str) + 2];
	strcat(rezult, rhs.str);
	strcpy(rezult, str);
	xstring rez(rezult);
	delete[] rezult;
	return rez;
}
ostream& operator<<(ostream& out, xstring &rhs){
	out << rhs.str;
	return out;
}
istream& operator>>(istream& in, xstring &rhs){
	char tmp[200];
	in.getline(tmp, 199);
	rhs.str = new char[strlen(tmp) + 1];
	strcpy(rhs.str, tmp);
	return in;
}

class var{
	union{
		int i;
		double d;
		xstring *s;
	} val;
	enum TYPE{EMPTY, INT_TYPE, DOUBLE_TYPE, STRING_TYPE };
	unsigned int type : 2;
	void ftoa(double d, char *buf) const{
		/*itoa(d, buf, 10);
		int len = strlen(buf);
		buf[len] = '.';
		buf[len + 1] = '\0';
		for (int i = 1; i <= 5; i++){
			int len = strlen(buf);
			buf[len] = int(d * pow(10, i)) % int(pow(10, i - 1)) + '0';
			buf[len + 1] = '\0';
			cout << buf << endl;
		}*/
		sprintf(buf, "%f", float(d));
		//cout << buf << endl;
		for (int i = strlen(buf) - 1; i >= 0; i--){
			if (buf[i] == '0' && buf[i - 1] != '.')
				buf[i] = '\0';
			else
				break;
		}
	}
public:
	var(){
		type = EMPTY;
		val.s = nullptr;
	}
	var(var& v){
		type = v.type;
		if (type != STRING_TYPE)
			val = v.val;
		else
			val.s = new xstring(*(v.val.s));	
	}	
	var(char *v) {
		val.s = new xstring(v);
		type = STRING_TYPE;
	}	
	var(int v) {
		val.i = v;
		type = INT_TYPE;
	}
	var(double v){
		val.d = v;
		type = DOUBLE_TYPE;
	}	
	~var() { }

	operator int()const{
		if (type == INT_TYPE)
			return val.i;
		if (type == DOUBLE_TYPE)
			return int(val.d);
		return atoi(val.s->GetStr());
	}
	operator double()const{
		if (type == DOUBLE_TYPE)
			return val.d;
		if (type == INT_TYPE)
			return double(val.i);
		return atof(val.s->GetStr());
	}
	operator char*()const{
		if (type == STRING_TYPE)
			return val.s->GetStr();
		char rez[200];
		if (type == DOUBLE_TYPE)
			itoa(val.d, rez, 10);
		else //if (type == INT_TYPE)
			itoa(val.i, rez, 10);
		char *rez2 = new char[strlen(rez) + 1];
		return rez2;
	}
	operator xstring()const{
		if (type == STRING_TYPE)
			return *this;
		char *rez = new char[200];
		if (type == DOUBLE_TYPE)
			itoa(val.d, rez, 10);
		else //if (type == INT_TYPE)
			itoa(val.i, rez, 10);
		xstring rezult(rez);
		delete[] rez;
		return rezult;
	}
	char* toChar() const{
		if (type == STRING_TYPE)
			return val.s->GetStr();
		char rez[200];
		if (type == DOUBLE_TYPE)
			ftoa(val.d, rez);
		else //if (type == INT_TYPE)
			itoa(val.i, rez, 10);
		char *rez2 = new char[strlen(rez) + 1];
		strcpy(rez2, rez);
		return rez2;
	}

	void Print() const {
		if (type == STRING_TYPE)
			val.s->Print();
		else if (type == DOUBLE_TYPE)
			cout << val.d;
		else
			cout << val.i;
	}

	var& operator=(var& rhs){
		if (this == &rhs)
			return *this;
		if (rhs.type != STRING_TYPE)
			val = rhs.val;
		else{
			val.s = new xstring(*(rhs.val.s));
		}
		type = rhs.type;
		return *this;
	}

	var operator+(var &rhs) const {
		if (type == EMPTY)
			return rhs;
		var rezult;
		rezult.type = type;
		if (type == rhs.type){
			if (type == INT_TYPE)
				rezult.val.i = val.i + rhs.val.i;
			else if (type == DOUBLE_TYPE)
				rezult.val.d = val.d + rhs.val.d;
			else{
				rezult.val.s = new xstring(*(val.s) + rhs.toChar());// +*(rhs.val.s);
			}
		}
		else if (type == INT_TYPE){
			rezult.val.i = this->val.i + int(rhs);
		}
		else if (type == DOUBLE_TYPE){
			rezult.val.d = this->val.d + double(rhs);
		}
		else if (type == STRING_TYPE){
			rezult.val.s = new xstring(*(val.s));
			*(rezult.val.s) = *(rezult.val.s) + rhs.toChar();
		}
		return rezult;
	}
	var operator-(var &rhs) const {
		if (type == EMPTY)
			return rhs;
		var rezult;
		rezult.type = type;
		if (type == rhs.type){
			if (type == INT_TYPE)
				rezult.val.i = val.i - rhs.val.i;
			else if (type == DOUBLE_TYPE)
				rezult.val.d = val.d - rhs.val.d;
			else{
				rezult.val.s = new xstring(*(val.s) - xstring(rhs));// +*(rhs.val.s);
			}
		}
		else if (type == INT_TYPE){
			rezult.val.i = this->val.i - int(rhs);
		}
		else if (type == DOUBLE_TYPE){
			rezult.val.d = this->val.d - double(rhs);
		}
		else if (type == STRING_TYPE){
			rezult.val.s = new xstring(*(val.s));
			*(rezult.val.s) = *(rezult.val.s) - xstring(rhs);
		}
		return rezult;
	}
	var operator*(var &rhs) const {
		if (type == EMPTY)
			return rhs;
		var rezult;
		rezult.type = type;
		if (type == rhs.type){
			if (type == INT_TYPE)
				rezult.val.i = val.i * rhs.val.i;
			else if (type == DOUBLE_TYPE)
				rezult.val.d = val.d * rhs.val.d;
			else{
				rezult.val.s = new xstring(*(val.s) * xstring(rhs));// +*(rhs.val.s);
			}
		}
		else if (type == INT_TYPE){
			rezult.val.i = this->val.i * int(rhs);
		}
		else if (type == DOUBLE_TYPE){
			rezult.val.d = this->val.d * double(rhs);
		}
		else if (type == STRING_TYPE){
			rezult.val.s = new xstring(*(val.s));
			*(rezult.val.s) = *(rezult.val.s) * xstring(rhs);
		}
		return rezult;
	}
	var operator/(var &rhs) const {
		if (type == EMPTY)
			return rhs;
		var rezult;
		rezult.type = type;
		if (type == rhs.type){
			if (type == INT_TYPE)
				rezult.val.i = val.i / rhs.val.i;
			else if (type == DOUBLE_TYPE)
				rezult.val.d = val.d / rhs.val.d;
			else{
				rezult.val.s = new xstring(*(val.s) / xstring(rhs));// +*(rhs.val.s);
			}
		}
		else if (type == INT_TYPE){
			rezult.val.i = this->val.i / int(rhs);
		}
		else if (type == DOUBLE_TYPE){
			rezult.val.d = this->val.d / double(rhs);
		}
		else if (type == STRING_TYPE){
			rezult.val.s = new xstring(*(val.s));
			*(rezult.val.s) = *(rezult.val.s) / xstring(rhs);
		}
		return rezult;
	}

	var& operator+=(var &rhs) {
		if (type == EMPTY){
			*this = rhs;
			return *this;
		}
		type = rhs.type;
		if (type == rhs.type){
			if (type == INT_TYPE)
				val.i = val.i + rhs.val.i;
			else if (type == DOUBLE_TYPE)
				val.d = val.d + rhs.val.d;
			else{
				val.s = new xstring(*(val.s) + xstring(rhs));
			}
		}
		return *this;
	}
	var& operator-=(var &rhs) {
		if (type == EMPTY){
			*this = rhs;
			return *this;
		}
		type = rhs.type;
		if (type == rhs.type){
			if (type == INT_TYPE)
				val.i = val.i - rhs.val.i;
			else if (type == DOUBLE_TYPE)
				val.d = val.d - rhs.val.d;
			else{
				val.s = new xstring(*(val.s) - xstring(rhs));
			}
		}
		return *this;
	}
	var& operator*=(var &rhs) {
		if (type == EMPTY){
			*this = rhs;
			return *this;
		}
		type = rhs.type;
		if (type == rhs.type){
			if (type == INT_TYPE)
				val.i = val.i * rhs.val.i;
			else if (type == DOUBLE_TYPE)
				val.d = val.d * rhs.val.d;
			else{
				val.s = new xstring(*(val.s) * xstring(rhs));
			}
		}
		return *this;
	}
	var& operator/=(var &rhs) {
		if (type == EMPTY){
			*this = rhs;
			return *this;
		}
		type = rhs.type;
		if (type == rhs.type){
			if (type == INT_TYPE)
				val.i = val.i / rhs.val.i;
			else if (type == DOUBLE_TYPE)
				val.d = val.d / rhs.val.d;
			else{
				val.s = new xstring(*(val.s) / xstring(rhs));
			}
		}
		return *this;
	}

	bool operator==(var &rhs){
		if (type == rhs.type) {
			if (type == INT_TYPE)
				return val.i == rhs.val.i;
			else if (type == DOUBLE_TYPE)
				return val.d == rhs.val.d;
			else if (type != EMPTY)
				return *(val.s) == *(rhs.val.s);		
		}
		else if (type == INT_TYPE) 
			return this->val.i == int(rhs);
		else if (type == DOUBLE_TYPE) 
			return this->val.d == double(rhs);
		else if (type == STRING_TYPE)
			return *(val.s) == xstring(rhs);
		//Якщо this == empty
		return 0;
	}
	bool operator!=(var &rhs) {
		return !(this->operator==(rhs));
	}
	bool operator>(var &rhs) {
		if (type == rhs.type) {
			if (type == INT_TYPE)
				return val.i > rhs.val.i;
			else if (type == DOUBLE_TYPE)
				return val.d > rhs.val.d;
			else if (type != EMPTY)
				return *(val.s) > *(rhs.val.s);
		}
		else if (type == INT_TYPE)
			return this->val.i > int(rhs);
		else if (type == DOUBLE_TYPE)
			return this->val.d > double(rhs);
		else if (type == STRING_TYPE)
			return *(val.s) > xstring(rhs);
		return 0;
	}
	bool operator>=(var &rhs) {
		return (this->operator>(rhs) || this->operator==(rhs));
	}
	bool operator<(var &rhs) {
		return !(this->operator>=(rhs));
	}
	bool operator<=(var &rhs) {
		return !(this->operator>(rhs));
	}

	friend ostream& operator<<(ostream &out, var &s);
	friend istream& operator>>(istream& in, var &rhs);
};
ostream& operator<<(ostream &out, var &s){
	if (s.type == s.STRING_TYPE)
		out << s.val.s->GetStr();
	else if (s.type == s.DOUBLE_TYPE)
		out << s.val.d;
	else
		out << s.val.i;
	return out;
}
istream& operator>>(istream& in, var &rhs){
	cout << "\n\tType(1 - INT, 2 - DOUBLE, 3 - STRING): ";
	unsigned short int t;
	cin >> t;
	if (&cin == &in)
		cin.ignore();
	if (rhs.type == var::STRING_TYPE)
		delete rhs.val.s;
	rhs.type = t;
	cout << "\tValue: ";
	if (t == 1)
		in >> rhs.val.i;
	else if (t == 2)
		in >> rhs.val.d;
	else {
		rhs.val.s = new xstring;
		in >> *(rhs.val.s);
	}
	return in;
}


/*
Для класу var необхідно перевантажити:
арифметичні оператори: +, -, *, /, +=, -=, *=, /=
оператори порівняння: <, >, <=, >=, ==, !=
Додати також до класу var приведення до типу: int, double, char*.
*/

void main(){
	/*var(var::*ptr[4])(var&) const = {
		&var::operator+,
		&var::operator-,
		&var::operator/,
		&var::operator*
	};*/
	//rezult = (first.*ptr[1])(second);

	var first, second, rezult;

	cout << "First: "; cin >> first;

	while (1){
		char op[4];
		cout << "Value: " << first << endl;
		cout << "Input operation: " << endl;
		cout << "+, -, *, / , +=, -=, *=, /=, =" << endl;
		cout << "<, >, <=, >=, ==, !=" << endl;
		cin >> op;   //cin.getline(op, 3);
		system("cls");
		if (strcmp(op, "=") == 0) {
			cout << "New: "; cin >> first;
		}
		else if (strcmp(op, "+") == 0) {
			cout << "Second: "; cin >> second;
			rezult = first + second;
			cout << first << ' ' << op << ' ' << second << " = " << rezult << endl;
		}
		else if (strcmp(op, "-") == 0) {
			cout << "Second: "; cin >> second;
			rezult = first - second;
			cout << first << ' ' << op << ' ' << second << " = " << rezult << endl;
		}
		else if (strcmp(op, "*") == 0) {
			cout << "Second: "; cin >> second;
			rezult = first * second;
			cout << first << ' ' << op << ' ' << second << " = " << rezult << endl;
		}
		else if (strcmp(op, "/") == 0) {
			cout << "Second: "; cin >> second;
			rezult = first / second;
			cout << first << ' ' << op << ' ' << second << " = " << rezult << endl;
		}
		else if (strcmp(op, "+=") == 0) {
			cout << "Second: "; cin >> second;
			first += second;
		}
		else if (strcmp(op, "-=") == 0) {
			cout << "Second: "; cin >> second;
			first -= second;
		}
		else if (strcmp(op, "*=") == 0) {
			cout << "Second: "; cin >> second;
			first *= second;
		}
		else if (strcmp(op, "/=") == 0) {
			cout << "Second: "; cin >> second;
			first /= second;
		}
		else if (strcmp(op, "==") == 0) {
			cout << "Second: "; cin >> second;
			cout << (first == second) << endl;
		}
		else if (strcmp(op, "!=") == 0) {
			cout << "Second: "; cin >> second;
			cout << (first != second) << endl;
		}
		else if (strcmp(op, "<=") == 0) {
			cout << "Second: "; cin >> second;
			cout << (first <= second) << endl;
		}
		else if (strcmp(op, ">=") == 0) {
			cout << "Second: "; cin >> second;
			cout << (first >= second) << endl;
		}
		else if (strcmp(op, "<") == 0) {
			cout << "Second: "; cin >> second;
			cout << (first < second) << endl;
		}
		else if (strcmp(op, ">") == 0) {
			cout << "Second: "; cin >> second;
			cout << (first > second) << endl;
		}

	}
	system("pause");
}