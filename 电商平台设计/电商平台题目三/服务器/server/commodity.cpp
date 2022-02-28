#include "commodity.h"

int string_to_int(string s) {
	int sum = 0;
	for (const auto& ch : s) {
		sum = (sum * 10 + (ch - '0'));
	}
	return sum;
}
int Commodity::getPrice(int n) {
	return n * value;
}
string Commodity::getAccount() const {
	return account;
}
string Commodity::getName() const {
	return name;
}
string Commodity::getKind() const {
	return kind;
}
int Commodity::getValue() const {
	return value;
}
int Commodity::getStock() const {
	return stock;
}
bool Commodity::changeName(string n) {
	if (n.size() > 0) {
		name = n;
		return true;
	}
	return false;
}
bool Commodity::changeValue(int num) {
	if (value + num >= 0) {
		value += num;
		return true;
	}
	return false;
}
bool Commodity::changeStock(int num) {
	if (stock + num >= 0) {
		stock += num;
		return true;
	}
	return false;
}
bool Commodity::changeDiscount(int num) {
	if (num > 0 && num < 10) {
		discount = num;
		value = value * discount / 10;
		return true;
	}
	return false;
}

Food::Food(vector<string> info) {
	name = info[0];
	account = info[1];
	kind = info[2];
	value = string_to_int(info[3]);
	stock = string_to_int(info[4]);
	discount = 10;
}
int Food::getPrice(int n) {
	return n * value;
}
Clothes::Clothes(vector<string> info) {
	name = info[0];
	account = info[1];
	kind = info[2];
	value = string_to_int(info[3]);
	stock = string_to_int(info[4]);
	discount = 10;
}
int Clothes::getPrice(int n) {
	return n * value;
}
Book::Book(vector<string> info) {
	name = info[0];
	account = info[1];
	kind = info[2];
	value = string_to_int(info[3]);
	stock = string_to_int(info[4]);
	discount = 10;
}
int Book::getPrice(int n) {
	return n * value;
}