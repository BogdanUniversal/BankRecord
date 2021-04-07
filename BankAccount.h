#pragma once

#include "User.h"
#include <string>

using namespace std;

class BankAccount : public User
{
private:
	string IBAN;
	float balance;

public:
	BankAccount();
	BankAccount(string userName, string password, bool permissions, string IBAN, float balance);
	BankAccount(string str);
	~BankAccount();
	string getIBAN();
	float getBalance();
	string toStringCSV();
	string toStringHTML();
	friend ostream& operator<<(ostream& output, const BankAccount& bA);
	bool operator==(const BankAccount& bA);
};
