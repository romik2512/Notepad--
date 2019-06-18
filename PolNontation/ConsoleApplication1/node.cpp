#include "stdafx.h"
#include "node.h"

int customStack::size = 0;

customStack::customStack() {
	next = NULL;
}

void customStack::push(token newValue) {
	customStack* buf = new customStack;
	buf->value = newValue;
	buf->next = next;
	next = buf;
	size++;
}

token customStack::pop() {
	if (size > 0) {
		token val = next->value;
		customStack *buf = next;
		next = next->next;
		delete buf;
		size--;
		return val;
	}
	else {
		token empty;
		empty.type = NO_TYPE;
		empty.value = "";
		return empty;
	}
}

token customStack::top() {
	if (size > 0) {
		token val = next->value;
		return val;
	}
	else {
		token empty;
		empty.type = NO_TYPE;
		empty.value = "";
		return empty;
	}
}

int customStack::getSize() {
	return size;
}

bool customStack::isEmpty() {
	return size == 0 ? true : false;
}

int customQueue::size = 0;

customQueue::customQueue() {
	last = NULL;
	first = NULL;
}

void customQueue::push(token newValue) {
	queueItem *buf = new queueItem;
	buf->value = newValue;
	buf->next = NULL;
	if (first != NULL) {
		last->next = buf;
		last = buf;
	}
	else {
		first = last = buf;
	}
	size++;
}

token customQueue::pop() {
	if (first != NULL) {
		queueItem *buf = first;
		token val = buf->value;
		first = first->next;
		delete buf;
		size--;
		return val;
	}
	else {
		token empty;
		empty.type = NO_TYPE;
		return empty;
	}
}

int customQueue::getSize() {
	return size;
}

bool customQueue::isEmpty() {
	return size == 0 ? true : false;
}

std::string customQueue::toString() {
	std::string outputData = "";
	queueItem *buf = first;
	while (buf != NULL) {
		outputData += buf->value.value += " ";
		buf = buf->next;
	}
	return outputData;
}
