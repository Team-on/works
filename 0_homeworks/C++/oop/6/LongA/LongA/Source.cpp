#include <iostream>

using namespace std;

class LA{
private:
	char *value;
	bool isNeg;
public:
	LA(){
		value = new char[2];
		strcpy(value, "0");
		isNeg = 0;
	}
	LA(LA &num){
		value = new char[strlen(num.value) + 1];
		strcpy(value, num.value);
		isNeg = num.isNeg;
	}
	LA(char num[]){	
			if (num[0] == '-'){
				isNeg = 1;
				value = new char[strlen(num)];
				strcpy(value, &num[1]);
			}
			else{
				isNeg = 0;
				value = new char[strlen(num) + 1];
				strcpy(value, num);
			}
	}
	LA(long long num){
		isNeg = 0;
		if (num < 0){
			isNeg = 1;
			num = abs(num);
		}
		char tmp[21];
		ltoa(num, tmp, 10);
		value = new char[strlen(tmp) + 1];
		strcpy(value, tmp);
	}
	~LA(){
		if (value != nullptr)
			delete[] value;
	}

	void Copy(LA &num){
		if (num.value != nullptr){
			delete[] value;
			value = new char[strlen(num.value) + 1];
			strcpy(value, num.value);
			isNeg = num.isNeg;
		}
	}
	void Copy(char str[]){
		delete[] value;
		if (str[0] == '-'){
			isNeg = 1;
			value = new char[strlen(str)];
			strcpy(value, &str[1]);
		}
		else{
			isNeg = 0;
			value = new char[strlen(str) + 1];
			strcpy(value, str);
		}
	}

	void SetVCin(){
		char tmp[200];
		cin.getline(tmp, 199);
		delete[] value;
		if (tmp[0] == '-'){
			isNeg = 1;
			value = new char[strlen(tmp)];
			strcpy(value, &tmp[1]);
		}
		else{
			isNeg = 0;
			value = new char[strlen(tmp) + 1];
			strcpy(value, tmp);
		}
		strrev(value);
	}
	void PrintV() const{
		char tmp[200];
		strcpy(tmp, value);
		strrev(tmp);
		if (isNeg == 1)
			cout << "-";
		cout << tmp;
	}

	LA Add(LA &num){
		int minS;
		char *min;

		char tmp[200] = { 0 };
		if (strlen(value) < strlen(num.value)){
			minS = strlen(value);
			strcpy(tmp, num.value);
			min = value;
		}
		else{
			minS = strlen(num.value);
			strcpy(tmp, value);
			min = num.value;
		}

		if ((num.isNeg == 0 && isNeg == 0) || (num.isNeg == 1 && isNeg == 1)){
			int i;
			for (i = 0; i < minS && i < 199; i++){
				tmp[i] += min[i] - 48;
				if (tmp[i] > '9'){
					if (tmp[i + 1] == '\0')
						tmp[i + 1] = '0';
					tmp[i + 1]++;
					tmp[i] -= 10;
				}
			}
			for (int i = minS - 1; i < strlen(tmp); i++){
				if (tmp[i] > '9'){
					if (tmp[i + 1] == '\0')
						tmp[i + 1] = '0';
					tmp[i + 1]++;
					tmp[i] -= 10;
				}
			}
			
			LA rez(tmp);
			if (isNeg == 1)
				rez.isNeg = 1;
			return rez;
		}
		else if (num.isNeg == 1){
			num.isNeg = 0;
			LA rez = *this - num;
			//if (isNeg == 1)
				//rez.isNeg = 1;
			
			num.isNeg = 1;
			return rez;
		}
	}
	LA Mult(LA &num){
		LA tmp(*this);
		strrev(num.value);
		int size = atoi(num.value) - 1;
		strrev(num.value);
		for (int i = 0; i < size; i++){
			tmp.Copy(this->Add(tmp));
			//tmp.PrintV(); cout << endl;
		}
		//			tmp.AddWithSave(num);

		if ((num.isNeg == 0 && isNeg == 0) || (num.isNeg == 1 && isNeg == 1))
			tmp.isNeg = 0;		
		else if (num.isNeg == 1 || isNeg == 1)
			tmp.isNeg = 1;

		return tmp;
	}

	LA Sub(LA &num){
		char tmp1[200] = { 0 };
		char tmp2[200] = { 0 };
		bool flag = 1;
		strcpy(tmp1, value);
		strcpy(tmp2, num.value);
		while (strlen(tmp2) < strlen(tmp1)){
			tmp2[strlen(tmp2) + 1] = '\0';
			tmp2[strlen(tmp2)] = '0';
		}

		int i;
		if ((num.isNeg == 0 && isNeg == 0) || (num.isNeg == 1 && isNeg == 1)){
			for (i = 0; i < strlen(tmp1) && i < 199; i++){
				tmp1[i] = tmp1[i] - tmp2[i] + 48;
				if (tmp1[i] < '0'){
					tmp1[i + 1]--;
					tmp1[i] += 10;
				}
			}

			for (i = strlen(tmp1) - 1; i >= 0; i--){
				if (tmp1[i] <= '0' || tmp1[i] > '9'){
					if (tmp1[i - 1] >= '0' && tmp1[i - 1] <= '9')
						tmp1[i] = '\0';
					else
						break;
				}
				else    break;
			}
			LA rez(tmp1);
			return rez;
		}
		else if (num.isNeg == 1){
			num.isNeg = 0;
			LA rez2 = *this + num;
			num.isNeg = 1;
			return rez2;

		}
		else if (isNeg == 1){
			isNeg = 0;
			LA rez2 = *this + num;
			isNeg = 1;
			rez2.isNeg = 1;
			return rez2;

		}
	}

	LA operator+(LA &num){
		return Add(num);
	}
	LA operator-(LA &num){
		return Sub(num);
	}
	LA operator*(LA &num){
		return Mult(num);
	}
};

void main(){
	LA a, b;
	a.SetVCin();
	b.SetVCin();

	a.PrintV();
	cout << " + ";
	b.PrintV();
	cout << " = ";

	LA c = a.operator+(b);
	c.PrintV(); cout << endl;

	a.PrintV();
	cout << " * ";
	b.PrintV();
	cout << " = ";
	LA d = a * b;
	d.PrintV(); cout << endl;

	a.PrintV();
	cout << " - ";
	b.PrintV();
	cout << " = ";
	LA kkk = a - b;
	kkk.PrintV(); cout << endl;

	system("pause");
}