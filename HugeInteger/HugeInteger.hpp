#ifndef HUGE_INTEGER_H
#define HUGE_INTEGER_H

#include <string>

class HugeInteger {
public:
	HugeInteger();

	HugeInteger(std::string string_number);

	HugeInteger(int number);

	HugeInteger(const HugeInteger& number);

	~HugeInteger();
	
	int get() const;

	bool getSign() const;

	void set(int array[40]);

	void setSign(bool b);

	bool isZero() const;

	friend std::ostream& operator<< (std::ostream& out, const HugeInteger& number);

	friend std::istream& operator>> (std::istream& in, HugeInteger& number);

	HugeInteger& operator+=(const HugeInteger& right);

	HugeInteger& operator-=(const HugeInteger& right);

	HugeInteger& operator*=(const HugeInteger& right);

	HugeInteger& operator/=(const HugeInteger& right);

	friend bool operator==(const HugeInteger& left, const HugeInteger& right);

	friend bool operator!=(const HugeInteger& left, const HugeInteger& right);

	friend bool operator>(const HugeInteger& left, const HugeInteger& right);

	friend bool operator<(const HugeInteger& left, const HugeInteger& right);

	friend bool operator>=(const HugeInteger& left, const HugeInteger& right);

	friend bool operator<=(const HugeInteger& left, const HugeInteger& right);

	friend const HugeInteger operator+(const HugeInteger& left, const HugeInteger& right);

	friend const HugeInteger operator-(const HugeInteger& left, const HugeInteger& right);

	friend const HugeInteger operator*(const HugeInteger& left, const HugeInteger& right);

	friend const HugeInteger operator/(const HugeInteger& left, const HugeInteger& right);

private:
	int *number_;

	bool is_positive_;

	int compare(const HugeInteger& other) const;
};
#endif