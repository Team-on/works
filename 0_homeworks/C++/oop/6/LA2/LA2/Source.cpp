#include <iostream>

using namespace std;

class LA{
private:
	char *value;
	bool isNeg;
	int k;
public:
	explicit LA(){
		value = new char[2];
		strcpy(value, "0");
		isNeg = 0;
	}
	/*explicit*/ LA(LA &num){
		value = new char[strlen(num.value) + 1];
		strcpy(value, num.value);
		isNeg = num.isNeg;
	}
	explicit LA(char num[]){
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
	explicit LA(long long num){
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
	void Copy(char str[], bool negIgnore = 0){
		delete[] value;
		if (str[0] == '-'){
			if (!negIgnore)
				isNeg = 1;
			value = new char[strlen(str)];
			strcpy(value, &str[1]);
		}
		else{
			if (!negIgnore)
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
		strrev(value);
		if (isNeg == 1)
			cout << "-";
		cout << value;
		strrev(value);
	}

	LA operator+(LA &num){
		if (isNeg == 0 && num.isNeg == 1){
			num.isNeg = 0;
			LA rezultt = *this - num;
			num.isNeg = 1;
			/*for (int i = (strlen(value) > strlen(num.value)? strlen(num.value) : strlen(value) ); i >= 0; i--) {
				if (longer[i] < shorter[i]) {
					swap(shorter, longer);
					rezult.isNeg = 1;
					break;
				}
				else if (longer[i] == shorter[i]) {
					continue;
				}
				else {
					//rezult.isNeg = 1;
					break;
				}
			}*/
			return rezultt;
		}
		if (isNeg == 1 && num.isNeg == 0){
			isNeg = 0;
			LA rezultt = num - *this;
			isNeg = 1;
			return rezultt;
		}
		if (isNeg == 1 && num.isNeg == 1){
			num.isNeg = 0;
			isNeg = 0;
			LA rezultt = num + *this;
			num.isNeg = 1;
			isNeg = 1;
			rezultt.isNeg = 1;
			return rezultt;
		}
		if (isNeg == 0 && num.isNeg == 0){
			char *shorter, *longer;
			int sizeS, sizeL;
			if (strlen(value) >= strlen(num.value)){
				sizeS = strlen(num.value);
				sizeL = strlen(value);
				longer = new char[sizeL + 1];
				shorter = new char[sizeL + 1];
				strcpy(longer, value);
				strcpy(shorter, num.value);
			}
			else{
				sizeS = strlen(value);
				sizeL = strlen(num.value);
				longer = new char[sizeL + 1];
				shorter = new char[sizeL + 1];
				strcpy(longer, num.value);
				strcpy(shorter, value);
			}

			char *rez = new char[sizeL + 2];
			strcpy(rez, longer);
			rez[sizeL + 1] = '\0';
			for (int i = sizeS; i < sizeL; i++)
				shorter[i] = '0';
			shorter[sizeL] = '\0';

			int i;
			for (i = 0; i < sizeL; i++){
				rez[i] += shorter[i] - '0';
				if (rez[i] > '9'){
					rez[i] -= 10;
					++rez[i + 1];
				}
			}
			if (rez[i])
				rez[i] += '0';

			delete[] shorter;
			delete[] longer;
			LA rezult(rez);
			delete[] rez;
			return rezult;
		}
	}
	LA operator-(LA &num){
		if (isNeg == 0 && num.isNeg == 1){
			num.isNeg = 0;
			LA rezultt = *this + num;
			num.isNeg = 1;
			return rezultt;
		}
		if (isNeg == 1 && num.isNeg == 0){
			isNeg = 0;
			LA rezultt = num + *this;
			rezultt.isNeg = 1;
			isNeg = 1;
			return rezultt;
		}
		if (isNeg == 1 && num.isNeg == 1){
			isNeg = 0;
			num.isNeg = 0;
			LA rezultt = num - *this;
			isNeg = 1;
			num.isNeg = 1;
			return rezultt;
		}
		if (isNeg == 0 && num.isNeg == 0){
			char *shorter, *longer;
			int sizeS, sizeL;
			LA rezult;
			if (strlen(value) >= strlen(num.value)){
				sizeS = strlen(num.value);
				sizeL = strlen(value);
				longer = new char[sizeL + 1];
				shorter = new char[sizeL + 1];
				strcpy(longer, value);
				strcpy(shorter, num.value);
			}
			else{
				sizeS = strlen(value);
				sizeL = strlen(num.value);
				longer = new char[sizeL + 1];
				shorter = new char[sizeL + 1];
				strcpy(longer, num.value);
				strcpy(shorter, value);
				rezult.isNeg = 1;
			}

			for (int i = sizeS; i < sizeL; i++)
				shorter[i] = '0';
			shorter[sizeL] = '\0';

			
			//cout << longer << endl << shorter << endl;
			for (int i = sizeL - 1; i >= 0; i--){
				if (longer[i] < shorter[i]){
					swap(shorter, longer);
					rezult.isNeg = 1;
					break;
				}
				else if (longer[i] == shorter[i]){
					continue;
				}
				else{
					//rezult.isNeg = 1;
					break;
				}
			}

			char *rez = new char[sizeL + 2];
			strcpy(rez, longer);
			rez[sizeL + 1] = '\0';

			int i;
				for (i = 0; i < sizeL; i++){
					rez[i] = rez[i] - shorter[i] + '0';
					if (rez[i] < '0'){
						rez[i] += 10;
						--rez[i + 1];
					}
				}
			if (rez[i - 1] == '0' && i - 1 != 0)
				rez[i - 1] = '\0';

			delete[] shorter;
			delete[] longer;
			rezult.Copy(rez, 1);
			delete[] rez;
			return rezult;
		}
	}
	LA operator*(LA &num) {
		if (isNeg == 0 && num.isNeg == 1) {
			num.isNeg = 0;
			LA rezultt = *this * num;
			num.isNeg = 1;
			rezultt.isNeg = 1;
			return rezultt;
		}
		if (isNeg == 1 && num.isNeg == 0) {
			isNeg = 0;
			LA rezultt = *this * num;
			isNeg = 1;
			rezultt.isNeg = 1;
			return rezultt;
		}
		if ((isNeg == 0 && num.isNeg == 0) || (isNeg == 1 && num.isNeg == 1)) {
			char *shorter, *longer;
			int sizeS, sizeL;
			if (strlen(value) >= strlen(num.value)) {
				sizeS = strlen(num.value);
				sizeL = strlen(value);
				longer = new char[sizeL + 1];
				shorter = new char[sizeL + 1];
				strcpy(longer, value);
				strcpy(shorter, num.value);
			}
			else {
				sizeS = strlen(value);
				sizeL = strlen(num.value);
				longer = new char[sizeL + 1];
				shorter = new char[sizeL + 1];
				strcpy(longer, num.value);
				strcpy(shorter, value);
			}

			char *rez = new char[sizeL * sizeL + 2];
			for (int i = 0; i < sizeL + 2; i++)
				rez[i] = '\0';
			for (int i = sizeS; i < sizeL; i++)
				shorter[i] = '0';
			shorter[sizeL] = '\0';

			int i;
			for (i = 0; i < sizeL; i++) {
				long long int tmp = 0;
				for (int j = 0; j < sizeL; j++) {
					tmp += (longer[j] - '0') * (shorter[i] - '0') * pow(10,j);
				}
				//cout << tmp << endl;
				tmp += rez[i];
				rez[i] = tmp % 10 + '0';
				rez[i + 1] = tmp / 10;
			}
			//cout << i << "/" << sizeL << endl;
			for (; i < sizeL * sizeL + 1; i++) {
				if (rez[i]) {
					rez[i + 1] = rez[i] / 10;
					rez[i] = rez[i] % 10 + '0';
				}
				else
					break;
			}
			delete[] shorter;
			delete[] longer;
			LA rezult(rez);
			delete[] rez;
			return rezult;
		}
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
	LA c = a + b;
	c.PrintV(); cout << endl;

	a.PrintV();
	cout << " - ";
	b.PrintV();
	cout << " = ";
	LA d = a - b;
	d.PrintV(); cout << endl;

	a.PrintV();
	cout << " * ";
	b.PrintV();
	cout << " = ";
	LA e = a * b;
	e.PrintV(); cout << endl;

	system("pause");
}