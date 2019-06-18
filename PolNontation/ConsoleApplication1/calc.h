#pragma once
#include "node.h"

class calc
{
public:
	std::string getRPN(std::string &str); 
	token count(std::string &str);
private:
	void getAllTokens(std::string &str);
	int sort();
	std::vector<token> tokens;
	customStack bufferStack;
	customQueue exitQueue;
	
};

