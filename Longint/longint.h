#pragma once
#include <string>

using std::string;

class longint
{
	string number;
	bool sign;

public:
	 longint(         );
	 longint( string  );
	 longint(long long);
	~longint(         );

	longint operator+(const longint&) const;
	longint operator-(const longint&) const;
	longint operator*(const longint&) const;
	longint operator/(const longint&) const;
	longint operator%(const longint&) const;

	longint &operator+=(const longint&);
	longint &operator-=(const longint&);
	longint &operator*=(const longint&);
	longint &operator/=(const longint&);
	longint &operator%=(const longint&);

	longint &operator++(         );
	longint  operator++(const int);
	longint &operator--(         );
	longint  operator--(const int);
	longint  operator- (         ) const;

	bool operator==(const longint&) const;
	bool operator!=(const longint&) const;
	bool operator>=(const longint&) const;
	bool operator<=(const longint&) const;
	bool operator> (const longint&) const;
	bool operator< (const longint&) const;

	friend std::ostream &operator<<(std::ostream&, const longint&);

	size_t sprint(char*, size_t);
	longint power(  longint&   );
	longint power(  long long  );
	longint abs  (             ) const;
private:
	int  _compare(const longint) const;
	longint  _add(const longint) const;
	longint  _sub(const longint) const;
	longint  _mul(const longint) const;
	void     _div(longint, longint*, longint*) const;
	void  _addZero(longint&, longint) const;
	void  _delZero(longint&)          const;

	static string _Int_String(int);
	static int    _String_Int(int);
};

