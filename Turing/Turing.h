#pragma once

#include <vector>
#include <string>


class Turing {

public:
	Turing(const char *path);

	~Turing();

	std::vector<char> getAlphabet();
	std::string getStr();
	std::vector<std::string> getProgram();
	void execution(const char *path);

private:
	std::vector<char> _alphabet;
	std::string _str;
	std::vector<std::string> _program;

	bool _isUncPath;

	int _findLetter(char c);
};

