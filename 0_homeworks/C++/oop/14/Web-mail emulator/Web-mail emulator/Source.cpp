#include <iostream>

using namespace std;

class Mail {

public:
	void TakeMail();
	void SendMail();
};

class WebServise {

public:
	void GetData();
	void DelData();
};

class WebMail : public Mail, public WebServise {

};

int main(int argc, char *argv[]) {



	return EXIT_SUCCESS;
}