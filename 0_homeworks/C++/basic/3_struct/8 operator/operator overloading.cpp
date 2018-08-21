#include <iostream>
using namespace std;

class Drib{
private:
	int ch, zn;
	void Scor(){
		int dil = (ch < zn) ? zn : ch;
		while (2 <= dil--){
			if (ch % dil == 0 && zn % dil == 0){
				ch /= dil;
				zn /= dil;
			}
		}
	}
public:
	Drib(const int &chNew = 1, const int &znNew = 1){
		ch = chNew;
		if (znNew != 0)
			zn = znNew;
		else
			zn = 1;
		Scor();
	}
	~Drib(){}

	void SetCh(const int &chNew){
		ch = chNew;
		Scor();
	}
	void SetZn(const int &znNew){
		if (znNew != 0)
			zn = znNew;
		else
			zn = 1;
		Scor();
	}

	void Print() const{
		cout << ch << "/" << zn;
	}
	void Printl() const{
		cout << ch << "/" << zn << endl;
	}

	operator int() const{
		if (int((ch * 1. / zn) * 10) % 10 < 5)
			return ch / zn;
		else
			return ch / zn + 1;
	}
	operator double() const{
			return ch * 1. / zn;
	}

	Drib& operator+(const int &a) const{
		Drib tmp(this->ch + zn * a, this->zn);
		tmp.Scor();
		return tmp;
	}
	Drib& operator+(const Drib &a) const{
		Drib tmp(this->ch * a.zn + a.ch * this->zn, this->zn * a.zn);
		tmp.Scor();
		return tmp;
	}
	void operator+=(const int &a){
		this->ch += this->zn * a;
		this->Scor();
	}
	void operator+=(const Drib &a){
		this->ch = this->zn * a.ch + a.zn * this->ch;
		this->zn *= a.zn;
		this->Scor();
	}

	Drib& operator-(const int &a) const{
		Drib tmp(this->ch - zn * a, this->zn);
		tmp.Scor();
		return tmp;
	}
	Drib& operator-(const Drib &a) const{
		Drib tmp(this->ch * a.zn - a.ch * this->zn, this->zn * a.zn);
		tmp.Scor();
		return tmp;
	}
	void operator-=(const int &a){
		this->ch -= this->zn * a;
		this->Scor();
	}
	void operator-=(const Drib &a){
		//*this = *this + a;
		this->ch = a.zn * this->ch - this->zn * a.ch;
		this->zn *= a.zn;
		this->Scor();
	}

	Drib& operator*(const int &a) const{
		Drib tmp(this->ch * a, this->zn);
		tmp.Scor();
		return tmp;
	}
	Drib& operator*(const Drib &a) const{
		Drib tmp(this->ch * a.ch, this->zn * a.zn);
		tmp.Scor();
		return tmp;
	}
	void operator*=(const int &a){
		*this = *this * a;
		this->Scor();
	}
	void operator*=(const Drib &a){
		*this = *this * a;
		this->Scor();
	}

	Drib& operator/(const int &a) const{
		Drib tmp(this->ch, this->zn * a);
		tmp.Scor();
		return tmp;
	}
	Drib& operator/(const Drib &a) const{
		Drib tmp(this->ch * a.zn, this->zn * a.ch);
		tmp.Scor();
		return tmp;
	}
	void operator/=(const int &a){
		*this = *this / a;
		this->Scor();
	}
	void operator/=(const Drib &a){
		*this = *this / a;
		this->Scor();
	}
	
	bool operator==(const Drib &a){
		if (this->zn == a.zn && this->ch == a.ch)
			return 1;
		return 0;
	}
	bool operator!=(const Drib &a){
		return !(*this == a);
	}
	bool operator<(const Drib &a){
		if (this->zn == a.zn){
			if (this->ch < a.ch)
				return 1;
			else if (this->ch > a.ch)
				return 0;
		}
		else if (this->zn > a.zn)
			return 1;
		return 0;
	}
	bool operator<=(const Drib &a){
		if (this->zn == a.zn){
			if (this->ch <= a.ch)
				return 1;
			else if (this->ch >= a.ch)
				return 0;
		}
		else if (this->zn >= a.zn)
			return 1;
		return 0;
	}
	bool operator>(const Drib &a){
		if (this->zn == a.zn){
			if (this->ch > a.ch)
				return 1;
			else if (this->ch < a.ch)
				return 0;
		}
		else if (this->zn < a.zn)
			return 1;
		return 0;
	}
	bool operator>=(const Drib &a){
		if (this->zn == a.zn){
			if (this->ch >= a.ch)
				return 1;
			else if (this->ch <= a.ch)
				return 0;
		}
		else if (this->zn <= a.zn)
			return 1;
		return 0;
	}

	Drib& operator!(){
		swap(this->ch, this->zn);
		return *this;
	}

	Drib& operator=(const Drib &a){
		this->ch = a.ch;
		this->zn = a.zn;
		return *this;
	}

	friend istream& operator >> (istream &s, Drib&v);
	friend ostream& operator << (ostream &s, Drib&v);

	Drib& operator++(){
		*this += 1;
		return *this;
	}
	Drib& operator--(){
		*this -= 1;
		return *this;
	}
	Drib operator++(int k){
		Drib tmp = *this;
		*this += 1;
		return tmp;
	}
	Drib operator--(int k){
		Drib tmp = *this;
		*this -= 1;
		return tmp;
	}
};


istream& operator >> (istream &is, Drib&v){
	is >> v.ch >> v.zn;
	return is;
}

ostream& operator << (ostream &os, Drib&v){
	os << v.ch << "/" << v.zn;
	return os;
}

void main(){
	Drib a(2, 3);
	Drib b;
	b = a--;
	int i = 0;
	cout << !i << endl;
	cout << a << endl;
	cout << !b << endl;
	//cin >> a;
	//cout << a++ << ends << a << endl;
}

