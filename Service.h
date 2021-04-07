#pragma once

#include "RepositoryFileHTML.h"
#include "BankAccount.h"
#include "Card.h"

class Service
{
private:
	RepositoryFileCSV<BankAccount>* repoBA_CSV;
	RepositoryFileCSV<Card>* repoC_CSV;
	RepositoryFileHTML<BankAccount>* repoBA_HTML;
	RepositoryFileHTML<Card>* repoC_HTML;
	bool fileOption;
public:
	Service();
	Service(bool fileOption);
	~Service();
	void addBankAccount(BankAccount* bA);
	void addCard(Card* card);
	void delBankAccount(size_t position);
	void delCard(size_t position);
	void updateBankAccount(size_t position, BankAccount* bA);
	void updateCard(size_t position, Card* card);
	BankAccount* getBankAccount(string userName, string password);
	std::vector<Card*> getCards(string IBAN);
	size_t getBankAccountSize();
	size_t getCardSize();
	std::vector<BankAccount*> getAllBankAccount();
	std::vector<Card*> getAllCard();
};