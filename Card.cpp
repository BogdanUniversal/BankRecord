#include "Card.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

Card::Card()
/**
 * Default constructor.
 */
{
	this->IBAN = "";
	this->network = "";
	this->number = 0;
	this->balance = 0;
}

/**
 * Constructor with parameters.
 *
 * @param IBAN = string, network = string , number(credit card number) = long long int, balance = float.
 */
Card::Card(string IBAN, string network, long long int number, float balance)
{
	this->IBAN = IBAN;
	this->network = network;
	this->number = number;
	this->balance = balance;
}


/**
 * Constructor with a string parameter, that splits the string by the "," or "/" separator.
 *
 * @param values str = string.
 */
Card::Card(string str)
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

	this->IBAN = vS[0];
	this->network = vS[1];

	stringstream numberInt(vS[2]);
	numberInt >> this->number;

	this->balance = stof(vS[3]);
}


/**
 * Destructor.
 */
Card::~Card()
{
	this->IBAN = "";
	this->network = "";
	this->number = 0;
	this->balance = 0;
}


/**
 * Get method for IBAN attribute.
 *
 * @return IBAN = string.
 */
string Card::getIBAN()
{
	return this->IBAN;
}

/**
 * Get method for network attribute.
 *
 * @return network = string.
 */
string Card::getNetwork()
{
	return this->network;
}

/**
 * Get method for number attribute.
 *
 * @return number = long long int.
 */
int Card::getNumber()
{
	return this->number;
}

/**
 * Get method for balance attribute.
 *
 * @return balance = float.
 */
float Card::getBalance()
{
	return this->balance;
}


/**
 * Converts a Card object to a string with values separated by "," separator.
 *
 * @return stringCSV = string.
 */
string Card::toStringCSV()
{
	ostringstream ss;
	ss << this->number;
	string stringNumber(ss.str());

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << this->balance;
	std::string stringBalance = stream.str();

	string stringCSV = this->IBAN + "," + this->network + "," + stringNumber + "," + stringBalance;
	return stringCSV;
}


/**
 * Converts a Card object to a string with values separated by "/" separator.
 *
 * @return stringHTML = string.
 */
string Card::toStringHTML()
{
	ostringstream ss;
	ss << this->number;
	string stringNumber(ss.str());

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << this->balance;
	std::string stringBalance = stream.str();

	string stringHTML = this->IBAN + "/" + this->network + "/" + stringNumber + "/" + stringBalance;
	return stringHTML;
}

/**
 * Overloads the "<<" operator and has access to its attributes by being a friend class.
 *
 * @param output = ostream, c = Card.
 * @return output = ostream.
 */
ostream& operator<<(ostream& output, const Card& c)
{
	std::ostringstream ss;
	ss << c.balance;
	std::string stringBalance(ss.str());

	output << "IBAN: " << c.IBAN << ", " << "Network: " << c.network << ", " << "Card number: " << c.number << ", " << "Balance: " << stringBalance;
	return output;
}

/**
 * Overloads the "==" operator.
 *
 * @param c = Card.
 * @return 1 if equality conditions are met, else returns 0 = bool.
 */
bool Card::operator==(const Card& c)
{
	return this->number == c.number;
}