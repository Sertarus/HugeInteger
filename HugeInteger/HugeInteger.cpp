#include "HugeInteger.hpp"
#include <iostream>

using namespace std;

HugeInteger::HugeInteger() {
	this->number_ = new int[40]();
	this->is_positive_ = true;
}

HugeInteger::~HugeInteger() {
	delete[] number_;
}

HugeInteger::HugeInteger(string string_number) : HugeInteger() {
	string string_copy = string_number.c_str();
	try {
		if (string_number.empty()) {
			throw "Invalid argument exception";
		}
		else if (string_number.length() > 40) {
			throw "Invalid argument exception";
		}
		else if (string_number.at(0) == '-') {
			this->is_positive_ = false;
			string_copy = string_copy.substr(1);
		}
		else if (isdigit(string_number.at(0)) == 0) {
			throw "Invalid argument exception";
		}
		for (int i = 0; i < 40; i++) {
			if (i < string_copy.length()) {
				if (!isdigit(string_copy.at(string_copy.length() - i - 1))) {
					throw "Invalid argument exception";
				}
				this->number_[i] = int(string_copy.at(string_copy.length() - i - 1)) - '0';
			}
		}
	}
	catch (const char* err) {
		cerr << err << endl;
	}
}

HugeInteger::HugeInteger(int number) : HugeInteger(to_string(number)) {
}

HugeInteger::HugeInteger(const HugeInteger& number) : HugeInteger() {
	for (int i = 0; i < 40; i++) this->number_[i] = number.number_[i];
	is_positive_ = number.is_positive_;
}

int HugeInteger::get() const {
	return *this->number_;
}

bool HugeInteger::getSign() const {
	return is_positive_;
}

void HugeInteger::set(int array[40]) {
	this->number_ = array;
}

void HugeInteger::setSign(bool is_positive) {
	this->is_positive_ = is_positive;
}

bool HugeInteger::isZero() const {
	for (int i = 0; i < 40; i++) {
		if (this->number_[i] != 0) {
			return false;
		}
	}
	return true;
}

int HugeInteger::compare(const HugeInteger& other) const {
	for (int i = 39; i >= 0; i--) {
		if (this->number_[i] > other.number_[i]) return 1;
		if (this->number_[i] < other.number_[i]) return -1;
	}
	return 0;
}

std::ostream& operator<< (std::ostream& out, const HugeInteger& number) {
	if (number.isZero()) {
		cout << "0";
		return out;
	}
	if (!number.is_positive_) {
		cout << "-";
	}
	for (int i = 39; i >= 0; i--) {
		if (number.number_[i] != 0) {
			for (i; i >= 0; i--) {
				cout << number.number_[i];
			}
		}
	}
	cout << endl;
	return out;
}

std::istream& operator>> (std::istream& in, HugeInteger& number) {
	string result_number;
	in >> result_number;
	number = HugeInteger(result_number);
	return in;
}

bool operator==(const HugeInteger& left, const HugeInteger& right) {
	return left.compare(right) == 0;
}

bool operator!=(const HugeInteger& left, const HugeInteger& right) {
	return left.compare(right) != 0;
}

bool operator>(const HugeInteger& left, const HugeInteger& right) {
	return left.compare(right) == 1;
}

bool operator<(const HugeInteger& left, const HugeInteger& right) {
	return left.compare(right) == -1;
}

bool operator>=(const HugeInteger& left, const HugeInteger& right) {
	return left.compare(right) >= 0;
}

bool operator<=(const HugeInteger& left, const HugeInteger& right) {
	return left.compare(right) <= 0;
}

HugeInteger& HugeInteger::operator+=(const HugeInteger& right) {
	int cout = 0;
	if (this->getSign() == right.getSign()) {
		for (int i = 0; i < 40; i++) {
			int new_num = this->number_[i] + right.number_[i] + cout;
			cout = 0;
			if (new_num > 9) {
				new_num -= 10;
				cout = 1;
			}
			this->number_[i] = new_num;
			try {
				if (i == 39 && cout == 1) {
					throw "Bit grid overflow";
				}
			}
			catch (const char* err) {
				cerr << err << endl;
			}
		}
		return *this;
	}
	else {
		if (*this < right) {
			if (this->is_positive_ == true) {
				this->setSign(false);
			}
			else {
				this->setSign(true);
			}
		}
		for (int i = 0; i < 40; i++) {
			int new_num;
			if (*this >= right) {
				new_num = this->number_[i] - right.number_[i] + cout;
			}
			else {
				new_num = right.number_[i] - this->number_[i] + cout;
			}
			cout = 0;
			if (new_num < 0) {
				new_num += 10;
				cout = -1;
			}
			this->number_[i] = new_num;
		}
		return *this;
	}
}

HugeInteger& HugeInteger::operator-=(const HugeInteger& right) {
	HugeInteger right_copy = HugeInteger(right);
	if (right.is_positive_) {
		right_copy.setSign(false);
	}
	else {
		right_copy.setSign(true);
	}
	*this += right_copy;
	return *this;
}

HugeInteger& HugeInteger::operator*=(const HugeInteger& right) {
	HugeInteger result = HugeInteger();
	try {
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			if (i + j >= 40 && number_[i] * right.number_[j] != 0) {
				throw "Bit grid overflow";
			}
			result.number_[i + j] += number_[i] * right.number_[j];
		}
	}
	for (int i = 0; i < 40 - 1; i++) {
		result.number_[i + 1] += result.number_[i] / 10;
		result.number_[i] %= 10;
	}
		if (result.number_[39] > 9) {
			throw "Bit grid overflow";
		}
	}
	catch (const char* err) {
		cerr << err << endl;
	}
	for (int i = 0; i < 40; i++) {
		this->number_[i] = result.number_[i];
	}
	return *this;
}

HugeInteger& HugeInteger::operator/=(const HugeInteger& right) {
	HugeInteger result = HugeInteger();
	HugeInteger right_copy = HugeInteger(right);
	try {
		if (right == result) {
			throw "Divison by zero";
		}
	}
	catch (const char* err) {
		cerr << err << endl;
	}
	int comp = this->compare(right);
	if (comp == -1) {
	}
	else if (comp == 0) {
		result.number_[0] = 1;
	}
	else {
		for (int i = 39; i >= 0; i--) {
			if (this->number_[i] != 0) {
				HugeInteger divident = HugeInteger();
				HugeInteger rest = HugeInteger();
				while (divident < right) {
					divident *= HugeInteger(10);
					divident += this->number_[i];
					i--;
				}
				while (divident >= right) {
					divident -= right;
					result += HugeInteger(1);
				}
				for (i; i >= 0; i--) {
					if (divident < right) {
						result *= HugeInteger(10);
					}
					divident *= HugeInteger(10);
					divident += this->number_[i];
					if (divident >= right) {
						while (divident >= right) {
							divident -= right;
							result += HugeInteger(1);
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < 40; i++) {
		this->number_[i] = result.number_[i];
	}
	return *this;
}

const HugeInteger operator+(const HugeInteger& left, const HugeInteger& right) {
	HugeInteger result = HugeInteger();
	result += left;
	result += right;
	return HugeInteger(result);
}

const HugeInteger operator-(const HugeInteger& left, const HugeInteger& right) {
	HugeInteger result = HugeInteger();
	result += left;
	result -= right;
	return HugeInteger(result);
}

const HugeInteger operator*(const HugeInteger& left, const HugeInteger& right) {
	HugeInteger result = HugeInteger();
	result += left;
	result *= right;
	return HugeInteger(result);
}

const HugeInteger operator/(const HugeInteger& left, const HugeInteger& right) {
	HugeInteger result = HugeInteger();
	result += left;
	result /= right;
	return HugeInteger(result);
}