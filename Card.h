#pragma once
#include <string>

using namespace std;

class Card
{
private:
	string IBAN;
	string network;
	long long int number;
	float balance;
public:
	Card();
	Card(string IBAN, string network, long long int number, float balance);
	Card(string str);
	~Card();
	string getIBAN();
	string getNetwork();
	int getNumber();
	float getBalance();
	string toStringCSV();
	string toStringHTML();
	friend ostream& operator<<(ostream& output, const Card& c);
	bool operator==(const Card& c);
};