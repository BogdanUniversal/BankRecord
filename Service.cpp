#include "Service.h"

/**
 * Default constructor.
 */
Service::Service()
{
	this->fileOption = 0;
	this->repoBA_CSV = NULL;
	this->repoC_CSV = NULL;
	this->repoBA_HTML = NULL;
	this->repoC_HTML = NULL;
}

/**
 * Constructor with a parameter that is the desired filetype.
 *
 * @param fileOption = bool (0 if CSV, 1 if HTML).
 */
Service::Service(bool fileOption)
{
	this->fileOption = fileOption;
	if (this->fileOption == 0)
	{
		this->repoBA_CSV = new RepositoryFileCSV<BankAccount>("BankAccounts.csv");
		this->repoC_CSV = new RepositoryFileCSV<Card>("Cards.csv");
		this->repoBA_HTML = NULL;
		this->repoC_HTML = NULL;
	}
	else
	{
		this->repoBA_HTML = new RepositoryFileHTML<BankAccount>("BankAccounts.html");
		this->repoC_HTML = new RepositoryFileHTML<Card>("Cards.html");
		this->repoBA_CSV = NULL;
		this->repoC_CSV = NULL;
	}
}

/**
 * Destructor.
 */
Service::~Service()
{
	if (this->fileOption == 0)
	{
		this->repoBA_CSV->clear();
		this->repoC_CSV->clear();
		delete this->repoBA_CSV;
		this->repoBA_CSV = NULL;
		delete this->repoC_CSV;
		this->repoC_CSV = NULL;
	}
	else
	{
		this->repoBA_HTML->clear();
		this->repoC_HTML->clear();
		delete this->repoBA_HTML;
		this->repoBA_HTML = NULL;
		delete this->repoC_HTML;
		this->repoC_HTML = NULL;
	}
}

/**
 * Adds a bank account to the desired file.
 *
 * @param bA = BankAccount.
 */
void Service::addBankAccount(BankAccount* bA)
{
	if (this->fileOption == 0)
		this->repoBA_CSV->add(bA);
	else
		this->repoBA_HTML->add(bA);
}

/**
 * Adds a card in the desired file.
 *
 * @param card = Card.
 */
void Service::addCard(Card* card)
{
	bool ok = 0;
	std::vector<BankAccount*> localRepoBA;
	if (this->fileOption == 0) localRepoBA = this->repoBA_CSV->getAll();
	else localRepoBA = this->repoBA_HTML->getAll();

	for (size_t i = 0; i < localRepoBA.size(); i++)
		if (card->getIBAN() == localRepoBA[i]->getIBAN())
			ok = 1;

	if (this->fileOption == 0 && ok == 1)
		this->repoC_CSV->add(card);
	else if (this->fileOption == 1 && ok == 1)
		this->repoC_HTML->add(card);
	else std::cout << "IBAN doesn't exist!" << '\n';
}

/**
 * Deletes a bank account from the given position from the desired file.
 *
 * @param position = size_t.
 */
void Service::delBankAccount(size_t position)
{
	if (this->fileOption == 0)
		this->repoBA_CSV->del(position);
	else
		this->repoBA_HTML->del(position);
}

/**
 * Deletes a card from the given position from the desired file.
 *
 * @param position = size_t.
 */
void Service::delCard(size_t position)
{
	if (this->fileOption == 0)
		this->repoC_CSV->del(position);
	else
		this->repoC_HTML->del(position);
}

/**
 * Updates a bank account from the given position from the desired file.
 *
 * @param position = size_t, bA = BankAccount.
 */
void Service::updateBankAccount(size_t position, BankAccount* bA)
{
	if (this->fileOption == 0)
		this->repoBA_CSV->update(position,bA);
	else
		this->repoBA_HTML->update(position,bA);
}

/**
 * Updates a card from the given position from the desired file.
 *
 * @param position = size_t, card = Card.
 */
void Service::updateCard(size_t position, Card* card)
{
	bool ok = 0;
	std::vector<BankAccount*> localRepoBA;
	if (this->fileOption == 0) localRepoBA = this->repoBA_CSV->getAll();
	else localRepoBA = this->repoBA_HTML->getAll();

	for (size_t i = 0; i < localRepoBA.size(); i++)
		if (card->getIBAN() == localRepoBA[i]->getIBAN())
			ok = 1;

	if (this->fileOption == 0 && ok == 1)
		this->repoC_CSV->update(position, card);
	else if (this->fileOption == 1 && ok == 1)
		this->repoC_HTML->update(position, card);
	else std::cout << "IBAN doesn't exist!" << '\n';
}

/**
 * Method that returns a bank account that has the given username and password from the desired file.
 *
 * @param userName = string, password = string.
 * @return BankAccount.
 */
BankAccount* Service::getBankAccount(string userName, string password)
{
	std::vector<BankAccount*> localRepoBA;
	BankAccount* b;
	if (this->fileOption == 0) localRepoBA = this->repoBA_CSV->getAll();
	else localRepoBA = this->repoBA_HTML->getAll();

	for (size_t i = 0; i < localRepoBA.size(); i++)
		if (userName == localRepoBA[i]->getUserName() && password == localRepoBA[i]->getPassword())
		{
			b = new BankAccount(localRepoBA[i]->getUserName(), localRepoBA[i]->getPassword(), localRepoBA[i]->getPermissions(), localRepoBA[i]->getIBAN(), localRepoBA[i]->getBalance());
			return b;
		}
}

/**
 * Method that returns all cards that have the given IBAN.
 *
 * @param IBAN = string.
 * @return associatedCards = vector<Card*>.
 */
vector<Card*> Service::getCards(string IBAN)
{
	std::vector<Card*> localRepoC;
	std::vector<Card*> associatedCards;
	if (this->fileOption == 0) localRepoC = this->repoC_CSV->getAll();
	else localRepoC = this->repoC_HTML->getAll();

	for (size_t i = 0; i < localRepoC.size(); i++)
		if (IBAN == localRepoC[i]->getIBAN())
			associatedCards.push_back(localRepoC[i]);

	return associatedCards;
}

/**
 * Method that returns the number of bank accounts from the desired file.
 *
 * @return the size = size_t.
 */
size_t Service::getBankAccountSize()
{
	if (this->fileOption == 0) return this->repoBA_CSV->getSize();
	else return this->repoBA_HTML->getSize();
}

/**
 * Method that returns the number of cards from the desired file.
 *
 * @return the size = size_t.
 */
size_t Service::getCardSize()
{
	if (this->fileOption == 0) return this->repoC_CSV->getSize();
	else return this->repoC_HTML->getSize();
}

/**
 * Method that returns all bank accounts from the desired file.
 *
 * @return vector<BankAccount>.
 */
std::vector<BankAccount*> Service::getAllBankAccount()
{
	if (this->fileOption == 0)
		return this->repoBA_CSV->getAll();
	else
		return this->repoBA_HTML->getAll();
}

/**
 * Method that returns all cards from the desired file.
 *
 * @return vector<Card>.
 */
std::vector<Card*> Service::getAllCard()
{
	if (this->fileOption == 0)
		return this->repoC_CSV->getAll();
	else
		return this->repoC_HTML->getAll();
}