#ifndef _INPUT_MY_H_
#define _INPUT_MY_H_

class input_my {
	INPUT_RECORD input;
	DWORD info; 
	DWORD _oldConsoleMode;
public:
	input_my();
	~input_my();

	int ReadInput();
};


#endif // !_INPUT_MY_H_


