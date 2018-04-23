#include <iostream>
#include <stack>
using namespace std;

int CheckBrakes() {
	stack<char> brakes;
	stack<int> position;
	char curr;
	int pos = 0;
	position.push(0);

	do {
		curr = cin.get();
		++pos;
		

		if (curr == '(' || curr == '[' || curr == '{') {
			brakes.push(curr);
			position.push(pos);
		}
		else if (curr == ')' || curr == ']' || curr == '}') {
			if (brakes.size() == 0 ||
				(curr == ')' && brakes.top() != '(') ||
				(curr == ']' && brakes.top() != '[') ||
				(curr == '}' && brakes.top() != '{')
				)
				return pos;

			brakes.pop();
			position.pop();
		}

	} while (curr != '\n');
	return position.top();
}

int main() {
	int res = CheckBrakes();
	if (res)
		cout << res;
	else
		cout << "Success";

	//cout << endl;
	//system("pause");
	return 0;
}