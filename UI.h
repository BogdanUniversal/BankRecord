#pragma once
#include "Service.h"

class UI
{
private:
	Service* s;
	bool fileOption;
	string userName;
	string password;
	bool permissions;
public:
	UI();
	~UI();
	void printFileOptionMenu();
	void enterCommandMenu(string& command);
	void wrongCommand();
	void fileOptionMenu(string command);
	bool loginMenu();
	void printLoginMenu();
	void printMainMenu();
	void bankAccountUserMenu();
	void printBankAccountAdminMenu();
	void addBankAccountMenu();
	void delBankAccountMenu();
	void updateBankAccountMenu();
	void showAllBankAccounts();
	void cardUserMenu();
	void printCardAdminMenu();
	void addCardMenu();
	void delCardMenu();
	void updateCardMenu();
	void showAllCards();
	void run();
};
