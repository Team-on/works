#ifndef _INPUT_QUEUE_H_
#define _INPUT_QUEUE_H_

class InputQueue{
public:
	enum InputKey {NONE, ArrowUp, ArrowDown, ArrowLeft, ArrowRight, Space};
	InputQueue();
	~InputQueue();

	void SetKey(InputKey Key) { key = Key; }
	InputKey GetKey() { InputKey tmp = key; key = NONE; return tmp; }

private:
	InputKey key;

};

#endif