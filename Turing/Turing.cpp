#include "Turing.h"
#include <iostream>
#include <fstream>


/**
 * Конструктор читает из файла алфавит, входную строку и программу на Тьюринге.
 */
Turing::Turing(const char *path) {
	std::ifstream fin;

	try {
		fin.open(path);
		throw !fin ? true : false;
	} catch (bool what) {
		_isUncPath = what;
		if (_isUncPath)
			return;
	}

	// Read alphabet
	std::string buf;
	std::getline(fin, buf);

	for (int i = 0; i < buf.length(); i++) {
		if (buf[i] != ' ') {
			_alphabet.push_back(buf[i]);
		}
	}
	_alphabet.push_back('l');

	// Read input string
	std::getline(fin, _str);

	// Read Turing program
	while (!fin.eof()) {
		std::getline(fin, buf);
		_program.push_back(buf);
	}
	
	fin.close();
}


Turing::~Turing() {

}


/**
 * Функция возвращает вектор с алфавитом.
 */
std::vector<char> Turing::getAlphabet() {
	return _alphabet;
}


/**
 * Функция возвращает строку для преобразования.
 */
std::string Turing::getStr() {
	return _str;
}


/**
 * Функция возвращает вектор с программой на языке Тьюринга.
 */
std::vector<std::string> Turing::getProgram() {
	return _program;
}


/**
 * Функция принимает путь для файла, куда будет выведен результат.
 *
 * Переменная iVect служит индексом в массиве _program.
 * 
 * Переменная iStr служит индексом в строке. В строку в начало и в
 * конец добавляется l (лямбда) - символ, обозначающий пустую ячейку на языке Тьюринга.
 * 
 * Строка программы на языке Тьюринга выглядит следующим образом:
 *     c1 s1 q1 c2 s2 q2 ... cn sn qn
 * где c1..cn - тот символ, который надо вставить
 * s1..sn - шаг, куда передвинуть головку (направо, налево, никуда)
 * q1..qn - ветка программы, на которую нужно перейти после изменения положения головки
 *
 * Как видно, символ, шаг и ветка идут по три, т.е. каждому символу в алфавите соответствует
 * тройка действий. Суть алгоритма заключается в том, чтобы брать нужную строку программы и
 * удалять тройки до тех пор, пока не доберемся до нужной. Для того чтобы определить, сколько
 * троек нужно удалить, используется функция _findLetter, чтобы определить индекс нужного нам
 * символа в алфавите.
 */
void Turing::execution(const char *path) {
	std::ofstream fout;
	fout.open(path);

	if (_isUncPath) {
		fout << "Uncorrected path!";
		fout.close();
		return;
	}
	
	int iVect = 0;
	int iStr = 1;
	std::string str = _str;
	str = "l" + str + "l";

	while (true) {
		std::string buf = _program[iVect];
		buf += " ";
		buf.erase(0, buf.find(' ') + 1);

		int n;

		try {
			n = _findLetter(str[iStr]);
			if (n == -1)
				throw "Uncorrected char!";
		}
		catch (const char *what) {
			fout << what;
			fout.close();
			return;
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3; j++) {
				buf.erase(0, buf.find(' ') + 1);
			}
		}

		str[iStr] = buf[0]; // replacement
		buf.erase(0, 2);

		try {
			switch (buf[0]) {
				// step
			case 'R': iStr++; break;
			case 'L': iStr--; break;
			case 'N': break;
			default: throw "Uncorrected step";
			}

		} catch (const char *what) {
			fout << what;
			fout.close();
			return;
		}

		buf.erase(0, 2); // status

		if (buf[0] == '!') // if program is end
			break;

		std::string pos;

		for (int i = 0; i < buf.find(' '); i++) { // exeption
			pos += buf[i];
		}

		pos.erase(0, 1);
		iVect = 0;

		for (int i = 0; i < pos.length(); i++) {
			iVect = iVect * 10 + static_cast<int>(pos[i]) - 48;
		}
		
		iVect--;
	}

	for (char c : str) {
		if (c != 'l') {
			fout << c;
		}
	}
	
	fout.close();
}


/**
 * Возвращает индекс символа в алфавите. Если символ не найден, то возвращается -1.
 */
int Turing::_findLetter(char c) {
	for (int i = 0; i < _alphabet.size(); i++) {
		if (_alphabet[i] == c) {
			return i;
		}
	}

	return -1;
}