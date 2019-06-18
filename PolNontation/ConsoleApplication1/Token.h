#pragma once

enum tokenType {
	NO_TYPE = 0,
	NUMBER = 1,
	OPERATOR_LOW_PRIOR = 2,
	OPERATOR_MID_PRIOR = 3,
	OPERATOR_HIGH_PRIOR = 4,
	OPERATOR_MAX_PRIOR = 5,
	OPEN_BRACKET = 6,
	CLOSE_BRACKET = 7
};

struct token {
	std::string value;
	tokenType type;
	void clear();
	token();
};