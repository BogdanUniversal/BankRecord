#include "BankAccount.h"
#include <sstream>
#include <vector>
#include <iomanip>

//Derived from User class.

/**
 * Default constructor that calls the default constructor of User class.
 */
BankAccount::BankAccount() : User()
{
	this->IBAN = "";
	this->balance = 0;
}


/**
 * Constructor with parameters that calls the constructor with parameters of User class.
 *
 * @param values userName = string, password = string, permissions = bool, IBAN = string, balance = float.
 */
BankAccount::BankAccount(string userName, string password, bool permissions, string IBAN, float balance) : User(userName, password, permissions)
{
	this->IBAN = IBAN;
	this->balance = balance;
}


/**
 * Constructor with a string parameter, that splits the string by the "," or "/" separator.
 *
 * @param values str = string.
 */
BankAccount::BankAccount(string str)
{
	vector<string> vS;
	string delimiter;

	if (str.find(",") >= 0 && str.find(",") < str.size())
		delimiter = ",";
	else
		delimiter = "/";

	int start = 0;
	int end = str.find(delimiter);
	while (end != -1) {
		vS.push_back(str.substr(start, end - start));
		start = end + delimiter.size();
		end = str.find(delimiter, start);
	}
	vS.push_back(str.substr(start, end - start));

	this->userName = vS[0];
	this->password = vS[1];
	if (vS[2] == "0") this->permissions = 0;
	else this->permissions = 1;
	this->IBAN = vS[3];
	this->balance = stof(vS[4]);
}


/**
 * Destructor.
 */
BankAccount::~BankAccount()
{
	this->IBAN = "";
	this->balance = 0;
}


/**
 * Get method for IBAN attribute.
 *
 * @return IBAN = string.
 */
string BankAccount::getIBAN()
{
	return this->IBAN;
}

/**
 * Get method for balance attribute.
 *
 * @return balance = float.
 */
float BankAccount::getBalance()
{
	return this->balance;
}


/**
 * Converts a BankAccount object to a string with values separated by "," separator.
 *
 * @return stringCSV = string.
 */
string BankAccount::toStringCSV()
{
	string stringPermissions;
	if (this->permissions == 0)
		stringPermissions = "0";
	else
		stringPermissions = "1";

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << this->balance;
	std::string stringBalance = stream.str();

	string stringCSV = this->userName + "," + this->password + "," + stringPermissions + "," + this->IBAN+"," + stringBalance;

	return stringCSV;
}


/**
 * Converts a BankAccount object to a string with values separated by "/" separator.
 *
 * @return stringHTML = string.
 */
string BankAccount::toStringHTML()
{
	string stringPermissions;
	if (this->permissions == 0)
		stringPermissions = "0";
	else
		stringPermissions = "1";

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << this->balance;
	std::string stringBalance = stream.str();

	string stringHTML = this->userName + "/" + this->password + "/" + stringPermissions + "/" + this->IBAN + "/" + stringBalance;

	return stringHTML;
}


/**
 * Overloads the "<<" operator and has access to its attributes by being a friend class.
 *
 * @param output = ostream, bA = BankAccount.
 * @return output = ostream.
 */
ostream& operator<<(ostream& output, const BankAccount& bA)
{
	ostringstream ss;
	ss << bA.balance;
	string stringBalance(ss.str());

	output << "Name: " << bA.userName << ", " << "Password: " << bA.password << ", " << "Permissions: " << bA.permissions << ", " << "IBAN: " << bA.IBAN << ", " << "Balance: " << stringBalance;
	return output;
}

/**
 * Overloads the "==" operator.
 *
 * @param bA = BankAccount.
 * @return 1 if equality conditions are met, else returns 0 = bool.
 */
bool BankAccount::operator==(const BankAccount& bA)
{
	return this->userName == bA.userName && this->password == bA.password && this->IBAN == bA.IBAN;
}