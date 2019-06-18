#pragma once
class customStack {
public:
	customStack();
	void push(token newValue);
	static int getSize();
	bool isEmpty();
	token top();
	token pop();
private:
	static int size;
	token value;
	customStack *next;
};

struct queueItem {
	token value;
	queueItem *next;
};

class customQueue {
public:
	customQueue();
	void push(token newValue);
	static int getSize();
	std::string toString();
	bool isEmpty();
	token pop();
private:
	static int size;
	queueItem *first, *last;
};

