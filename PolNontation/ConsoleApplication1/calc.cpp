#include "stdafx.h"
#include "calc.h"


std::string calc::getRPN(std::string &str) {
	getAllTokens(str);
	int code = sort();
	if (code == 1) {
		return "Ошибка при записи выражения";
	}
	else {
		return exitQueue.toString();
	}
}

void calc::getAllTokens(std::string &str) {
	token currentToken;
	std::string value;
	tokenType type = NO_TYPE;
	for (char currentChar : str) {
		if (currentChar >= 48 && currentChar <= 57) {
			currentToken.value += currentChar;
			currentToken.type = NUMBER;
		}
		else if (currentToken.type == NUMBER) {
			tokens.push_back(currentToken);
		}
		if (currentChar == '+' || currentChar == '-') {
			currentToken.value = currentChar;
			currentToken.type = OPERATOR_LOW_PRIOR;
			tokens.push_back(currentToken);
			currentToken.clear();
		}
		if (currentChar == '*' || currentChar == '/') {
			currentToken.value = currentChar;
			currentToken.type = OPERATOR_HIGH_PRIOR;
			tokens.push_back(currentToken);
			currentToken.clear();
		}
		if (currentChar == '^') {
			currentToken.value = currentChar;
			currentToken.type = OPERATOR_MAX_PRIOR;
			tokens.push_back(currentToken);
			currentToken.clear();
		}
		if (currentChar == '(') {
			currentToken.value = currentChar;
			currentToken.type = OPEN_BRACKET;
			tokens.push_back(currentToken);
			currentToken.clear();
		}
		if (currentChar == ')') {
			currentToken.value = currentChar;
			currentToken.type = CLOSE_BRACKET;
			tokens.push_back(currentToken);
			currentToken.clear();
		}
	}
	if (currentToken.type != NO_TYPE) {
		tokens.push_back(currentToken);
	}
}

void token::clear() {
	value = "";
	type = NO_TYPE;
}

token::token() {
	value = "";
	type = NO_TYPE;
}

int calc::sort() {
	for (auto& item : tokens) {
		if (item.type == NUMBER) {
			exitQueue.push(item);
		}
		if (item.type == OPERATOR_LOW_PRIOR) {
			while (bufferStack.top().type == OPERATOR_HIGH_PRIOR || bufferStack.top().type == OPERATOR_LOW_PRIOR || bufferStack.top().type == OPERATOR_MAX_PRIOR) {
				exitQueue.push(bufferStack.pop());
			}
		}
		if (item.type == OPERATOR_HIGH_PRIOR) {
			while (bufferStack.top().type == OPERATOR_HIGH_PRIOR || bufferStack.top().type == OPERATOR_MAX_PRIOR) {
				exitQueue.push(bufferStack.pop());
			}
		}
		if (item.type == OPERATOR_MAX_PRIOR) {
			while (bufferStack.top().type == OPERATOR_MAX_PRIOR) {
				exitQueue.push(bufferStack.pop());
			}
		}
		if (item.type == OPERATOR_HIGH_PRIOR || item.type == OPERATOR_LOW_PRIOR || item.type == OPERATOR_MAX_PRIOR) {
			bufferStack.push(item);
		}
		if (item.type == OPEN_BRACKET) {
			bufferStack.push(item);
		}
		if (item.type == CLOSE_BRACKET) {
			while (bufferStack.top().type != OPEN_BRACKET && !bufferStack.isEmpty()) {
				exitQueue.push(bufferStack.pop());
			}
			if (bufferStack.top().type == OPEN_BRACKET) {
				bufferStack.pop();
			}
			else {
				return 1;
			}
		}
		if (item.type == NO_TYPE) {
			return 1;
		}
	}
	if (!bufferStack.isEmpty()) {
		if (bufferStack.top().type == OPEN_BRACKET || bufferStack.top().type == CLOSE_BRACKET) {
			return 1;
		}
		else {
			while (!bufferStack.isEmpty()) {
				exitQueue.push(bufferStack.pop());
			}
		}
	}
	return 0;
}

token calc::count(std::string &str) {
	token buf_1, buf_2, buf_3;
	if (exitQueue.isEmpty()) {
		getAllTokens(str);
		int code = sort();
		if (code == 1) {
			buf_1.clear();
			return buf_1;
		}
	}
	while (!exitQueue.isEmpty()) {
		buf_1 = exitQueue.pop();
		if (buf_1.type != NUMBER) {
			buf_2 = bufferStack.pop();
			buf_3 = bufferStack.pop();
			if (buf_1.value.find_first_of('+') != std::string::npos) {
				buf_1.value = std::to_string(stod(buf_3.value) + stod(buf_2.value));
				buf_1.type = NUMBER;
			}
			if (buf_1.value.find_first_of('-') != std::string::npos) {
				buf_1.value = std::to_string(stod(buf_3.value) - stod(buf_2.value));
				buf_1.type = NUMBER;
			}
			if (buf_1.value.find_first_of('*') != std::string::npos) {
				buf_1.value = std::to_string(stod(buf_3.value) * stod(buf_2.value));
				buf_1.type = NUMBER;
			}
			if (buf_1.value.find_first_of('/') != std::string::npos) {
				buf_1.value = std::to_string(stod(buf_3.value) / stod(buf_2.value));
				buf_1.type = NUMBER;
			}
			if (buf_1.value.find_first_of('^') != std::string::npos) {
				buf_1.value = std::to_string(pow(stod(buf_3.value), stod(buf_2.value)));
				buf_1.type = NUMBER;
			}
		}
		bufferStack.push(buf_1);
	}
	return bufferStack.pop();
}