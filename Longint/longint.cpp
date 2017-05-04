#include "longint.h"
#include <string>


longint::longint()
{
	number = "0";
	sign = false;
}

longint::longint(string s)
{
	if (s[0] == '-')
	{
		sign = true;
		s.erase(0, 1);
	}
	else
		sign = false;
	number += s;
}

longint::longint(long long a)
{
	if (a == 0)
	{
		number = "0";
		sign = false;
	}
	if (a < 0)
	{
		sign = true;
		a = -a;
	}
	else
		sign = false;
	while (a > 0)
	{
		int remainder = a % 10;
		number = _Int_String(remainder) + number;
		a /= 10;
	}
}

longint::~longint()
{
	number.clear();
}

longint longint::operator+(const longint &y) const
{
	longint result;
	if (sign != y.sign && number.compare(y.number) != 0)
	{
		if (number.compare(y.number) == -1)
			result = y._sub(*this);
		else
			result = this->_sub(y);
		return result;
	}
	result = _add(y);
	return result;
}

longint longint::operator-(const longint &y) const
{
	longint result;
	
	if (sign == y.sign && this->abs() == y.abs())
		// a - a or -a - (-a)
		return 0;
	if (!sign && y.sign) // a - (-b)
	{
		result = _add(y.abs());
		return result;
	}
	if (sign && !y.sign) // -a - b
	{
		result = _add(-y);
		return result;
	}
	if (sign == y.sign) // -a - (-b) or a - b
	{
		if (this->abs() < y.abs())
			result = -y._sub(*this);
		else
			result = this->_sub(y);
		return result;
	}
}

longint longint::operator*(const longint &y) const
{
	longint result;
	result = _mul(y);
	return result;
}

longint longint::operator/(const longint &y) const
{
	longint result;
	_div(y, &result, NULL);
	return result;
}

longint longint::operator%(const longint &y) const
{
	longint result;
	_div(y, NULL, &result);
	return result;
}

longint &longint::operator+=(const longint &y)
{
	*this = this->operator+(y);
	return *this;
}

longint &longint::operator-=(const longint &y)
{
	*this = this->operator-(y);
	return *this;
}

longint &longint::operator*=(const longint &y)
{
	*this = this->operator*(y);
	return *this;
}

longint &longint::operator/=(const longint &y)
{
	*this = this->operator/(y);
	return *this;
}

longint &longint::operator%=(const longint &y)
{
	*this = this->operator%(y);
	return *this;
}

longint &longint::operator++() // prefix increment
{
	*this = *this + 1;
	return  *this;
}

longint longint::operator++(const int a) // postfix increment
{
	longint t = *this;
	*this = *this + 1;
	return t;
}

longint &longint::operator--() // prefix decrement
{
	*this = *this - 1;
	return  *this;
}

longint longint::operator--(const int a) // postfix decrement
{
	longint t = *this;
	*this = *this - 1;
	return t;
}

longint longint::operator-() const // unary minus
{
	longint result = *this;
	result.sign = result.sign ? false : true;
	return result;
}

bool longint::operator==(const longint &y) const
{
	if (_compare(y) == 0)
		return true;
	return false;
}

bool longint::operator!=(const longint &y) const
{
	return !operator==(y);
}

bool longint::operator>=(const longint &y) const
{
	return !operator<(y);
}

bool longint::operator<=(const longint &y) const
{
	return !operator>(y);
}

bool longint::operator>(const longint &y) const
{
	if (_compare(y) == 1)
		return true;
	return false;
}

bool longint::operator<(const longint &y) const
{
	if (_compare(y) == -1)
		return true;
	return false;
}

std::ostream &operator<<(std::ostream &out, const longint &y)
{
	if (y.sign)
		out << "-";
	out << y.number;
	return out;
}

int longint::_compare(const longint y) const
{
	if ( sign && !y.sign)                                 return -1;
	if (!sign && y.sign)                                  return 1;
	if ( sign == y.sign && number.compare(y.number) == 0) return 0;
	if (!sign && number.length() < y.number.length())     return -1;
	if ( sign && number.length() < y.number.length())     return 1;
	if (!sign && number.length() > y.number.length())     return 1;
	if ( sign && number.length() > y.number.length())     return -1;
	return number.compare(y.number);
}

size_t longint::sprint(char *buf, size_t buf_len)
{
	if (buf == NULL)
		return number.length() + 1;
	if (buf_len <= number.length())
		return -1;
	if (sign)
		*buf++ = '-';
	for (size_t i = 0; i < buf_len; i++)
		buf[i] = number[i];
	return number.length();
}

longint longint::abs() const
{
	longint result = *this;
	result.sign = false;
	return result;
}

longint longint::power(longint &y)
{
	if (y.number == "0")
		return 1;
	else if (y.sign)
		return 0;
	else
	{
		longint result(1);
		while (y != 0)
		{
			if (y % 2 != 0)
			{
				result *= *this;
				y -= 1;
			}
			*this *= *this;
			y /= 2;
		}
		return result;
	}
}

longint longint::_add(const longint y) const
{
	if (sign != y.sign && this->abs() == y.abs())
		// numbers are not equal in sign but equal in modulus
		return 0;

	longint result("");
	bool f = false;
	size_t i = number.length(), j = y.number.length();

	while (i != 0 || j != 0)
	{
		int sum;
		if (i == 0 && j != 0)
			sum = _String_Int(y.number[--j]);
		else
			if (i != 0 && j == 0)
				sum = _String_Int(number[--i]);
			else
				sum = _String_Int(number[--i]) + _String_Int(y.number[--j]);

		if (f) sum += 1;
		f = sum >= 10 ? true : false;
		if (sum >= 10 && (i != 0 || j != 0))
			sum %= 10;
		result.number = _Int_String(sum) + result.number;
	}
	result.sign = sign || y.sign;
	_delZero(result);
	return result;
}

longint longint::_sub(const longint y) const
{
	longint result("");
	int i = number.length(), j = y.number.length();
	bool f = false;

	while (i != 0 || j != 0)
	{
		int dif;
		if (i == 0 && j != 0)
			dif = 0 - _String_Int(y.number[--j]);
		else
			if (i != 0 && j == 0)
				dif = _String_Int(number[--i]);
			else
				dif = _String_Int(number[--i]) - _String_Int(y.number[--j]);

		if (f) dif -= 1;
		int n = dif;
		if (dif < 0 && dif != 0)
			dif = 10 - std::abs(dif);
		dif = std::abs(dif);
		f = n < 0 ? true : false;
		result.number = _Int_String(dif) + result.number;
	}
	result.sign = sign;
	_delZero(result);
	return result;
}

longint longint::_mul(const longint y) const
{
	if (number == "0" || y.number == "0") // multiplication by zero
		return 0;
	
	int j = y.number.length() - 1;
	int extra = 0;
	longint sch, result(""), sum("");

	while (j >= 0)
	{
		for (int i = number.length() - 1; i >= 0; i--)
		{
			int mult = _String_Int(number[i]) * _String_Int(y.number[j]);
			extra = (mult += extra) >= 10 ? mult / 10 : 0;
			if (i != 0)
				mult %= 10;
			sum.number = _Int_String(mult) + sum.number;
		}
		_addZero(sum, sch++);
		result = result + sum;
		sum.number.clear();
		extra = 0;
		j--;
	}
	result.sign = sign ^ y.sign;
	return result;
}

void longint::_div(longint y, longint *d, longint *m) const
{
	if (y == 0)
		std::_DEBUG_ERROR("Cannot divide by zero.");
	
	longint result, divident(""), count;
	size_t i = 0;

	while (divident < y.abs() && i < number.length())
		divident.number += number[i++];
	if (divident < y.abs())
	{
		if (d) 
			*d = 0;
		if (m)
		{
			*m = *this;
			m->sign = sign;
		}
	}
	else
	{
		while (true)
		{ // long division
			while (count * y.abs() <= divident)
				count++;
			if (count * y.abs() > divident)
				count--;
			result = result * 10 + count;
			divident = divident - (count * y.abs());
			if (i < number.length())
			{
				divident.number += number[i++];
				_delZero(divident);
				count = 0;
			}
			else
				break;
		}

		_delZero(result);
		if (d)
		{
			*d = result;
			d->sign = sign ^ y.sign;
		}
		if (m)
		{
			*m = divident;
			divident.sign = sign;
		}
	}
}

string longint::_Int_String(int a)
{
	switch (a)
	{
	case 0  : return "0" ;
	case 1  : return "1" ;
	case 2  : return "2" ;
	case 3  : return "3" ;
	case 4  : return "4" ;
	case 5  : return "5" ;
	case 6  : return "6" ;
	case 7  : return "7" ;
	case 8  : return "8" ;
	case 9  : return "9" ;
	case 10 : return "10";
	case 11 : return "11";
	case 12 : return "12";
	case 13 : return "13";
	case 14 : return "14";
	case 15 : return "15";
	case 16 : return "16";
	case 17 : return "17";
	case 18 : return "18";
	case 19 : return "19";
	case 20 : return "20";
	case 21 : return "21";
	case 22 : return "22";
	case 23 : return "23";
	case 24 : return "24";
	case 25 : return "25";
	case 26 : return "26";
	case 27 : return "27";
	case 28 : return "28";
	case 29 : return "29";
	case 30 : return "30";
	case 31 : return "31";
	case 32 : return "32";
	case 33 : return "33";
	case 34 : return "34";
	case 35 : return "35";
	case 36 : return "36";
	case 37 : return "37";
	case 38 : return "38";
	case 39 : return "39";
	case 40 : return "40";
	case 41 : return "41";
	case 42 : return "42";
	case 43 : return "43";
	case 44 : return "44";
	case 45 : return "45";
	case 46 : return "46";
	case 47 : return "47";
	case 48 : return "48";
	case 49 : return "49";
	case 50 : return "50";
	case 51 : return "51";
	case 52 : return "52";
	case 53 : return "53";
	case 54 : return "54";
	case 55 : return "55";
	case 56 : return "56";
	case 57 : return "57";
	case 58 : return "58";
	case 59 : return "59";
	case 60 : return "60";
	case 61 : return "61";
	case 62 : return "62";
	case 63 : return "63";
	case 64 : return "64";
	case 65 : return "65";
	case 66 : return "66";
	case 67 : return "67";
	case 68 : return "68";
	case 69 : return "69";
	case 70 : return "70";
	case 71 : return "71";
	case 72 : return "72";
	case 73 : return "73";
	case 74 : return "74";
	case 75 : return "75";
	case 76 : return "76";
	case 77 : return "77";
	case 78 : return "78";
	case 79 : return "79";
	case 80 : return "80";
	case 81 : return "81";
	case 82 : return "82";
	case 83 : return "83";
	case 84 : return "84";
	case 85 : return "85";
	case 86 : return "86";
	case 87 : return "87";
	case 88 : return "88";
	case 89 : return "89";
	}
}

int longint::_String_Int(int a)
{
	switch (a)
	{
	case 48 : return 0;
	case 49 : return 1;
	case 50 : return 2;
	case 51 : return 3;
	case 52 : return 4;
	case 53 : return 5;
	case 54 : return 6;
	case 55 : return 7;
	case 56 : return 8;
	case 57 : return 9;
	}
}

void longint::_addZero(longint &y, longint count) const
{
	longint sch;
	while (sch != count)
	{
		y.number += "0";
		sch++;
	}
}

void longint::_delZero(longint &y) const
{
	size_t count = 0, i = 0;
	if (y.number[0] == '0')
	{
		while (y.number[i++] == '0')
			count++;
		if (count == y.number.length())
			y.number = "0";
		else
			y.number.erase(0, count);
	}
}