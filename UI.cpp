#include "UI.h"

/**
 * Default constructor.
 */
UI::UI()
{
	this->s = new Service();
	this->permissions = 0;
	this->fileOption = 0;
	this->userName = "";
	this->password = "";
}

/**
 * Destructor.
 */
UI::~UI()
{
	delete this->s;
	this->s = NULL;
	this->permissions = 0;
	this->fileOption = 0;
	this->userName = "";
	this->password = "";
}

void UI::printFileOptionMenu()
{
	std::cout << "Choose file type:" << '\n';
	std::cout << "1. CSV" << '\n';
	std::cout << "2. HTML" << '\n';
	std::cout << "0. Exit" << '\n';
}

void UI::enterCommandMenu(string& command)
{
	std::cout << "Please enter your option: ";
	std::cin >> command;
	std::cout << '\n';
}
void UI::wrongCommand()
{
	std::cout << "Wrong option chosen!" << '\n';
}

/**
 * Initializes the service and the file option based on the command.
 *
 * @param command = string.
 */
void UI::fileOptionMenu(string command)
{
	if (command == "1")
	{
		this->fileOption = 0;
		s = new Service(0);
	}
	else if (command == "2")
	{
		this->fileOption = 1;
		s = new Service(1);
	}
}

void UI::printLoginMenu()
{
	std::cout << "1. Login" << '\n';
	std::cout << "0. Back" << '\n';
}

bool UI::loginMenu()
{
	std::cout << "Please enter your login details!" << '\n';
	std::cout << "Username: ";
	string userName;
	std::cin >> userName;
	std::cout << '\n' << "Password: ";
	string password;
	std::cin >> password;
	std::cout << '\n';

	int ok = 0;
	vector<BankAccount*> localRepoBA = this->s->getAllBankAccount();
	for (size_t i = 0; i < localRepoBA.size(); i++)
		if (localRepoBA[i]->getUserName() == userName && localRepoBA[i]->getPassword() == password)
		{
			ok = 1;
			this->userName = localRepoBA[i]->getUserName();
			this->password = localRepoBA[i]->getPassword();
			this->permissions = localRepoBA[i]->getPermissions();
		}
	
	if (ok == 1 && this->permissions == 1)
	{
		std::cout << "Admin permissions granted!" << '\n';
		return 1;
	}
	else if (ok == 1 && this->permissions == 0)
	{
		std::cout << "User permissions granted!" << '\n';
		return 1;
	}
	else
	{
		std::cout << "Wrong credentials!" << '\n';;
		return 0;
	}
}

void UI::printMainMenu()
{
	std::cout << "1. Bank accounts" << '\n';
	std::cout << "2. Cards" << '\n';
	std::cout << "0. Back" << '\n';
}

void UI::bankAccountUserMenu()
{
	std::cout << "Current account:" << '\n';
	std::cout << this->s->getBankAccount(this->userName, this->password)<<'\n';
	std::cout << "0. Back" << '\n';
}

void UI::printBankAccountAdminMenu()
{
	std::cout << "Current account:" << '\n';
	std::cout << *(s->getBankAccount(this->userName, this->password)) << '\n';
	std::cout << "1. Add bank account" << '\n';
	std::cout << "2. Remove bank account" << '\n';
	std::cout << "3. Update bank account" << '\n';
	std::cout << "4. Show all bank accounts" << '\n';
	std::cout << "0. Back" << '\n';
}

void UI::addBankAccountMenu()
{
	string userName;
	string password;
	bool permissions;
	string IBAN;
	float balance;

	std::cout << "Username: ";
	std::cin >> userName;
	std::cout << '\n' << "Password: ";
	std::cin >> password;
	std::cout << '\n' << "Permissions: ";
	std::cin >> permissions;
	std::cout << '\n' << "IBAN: ";
	std::cin >> IBAN;
	std::cout << '\n' << "Balance: ";
	std::cin >> balance;
	std::cout << '\n';

	this->s->addBankAccount(new BankAccount(userName, password, permissions, IBAN, balance));
}

void UI::delBankAccountMenu()
{
	size_t position;
	size_t size = this->s->getBankAccountSize() - 1;
	std::cout << "Please enter a position(0-" << size << "): ";
	std::cin >> position;
	std::cout << '\n';

	this->s->delBankAccount(position);
}

void UI::updateBankAccountMenu()
{
	size_t position;
	size_t size = this->s->getBankAccountSize() - 1;

	std::cout << "Please enter a position(0-" << size << "): ";
	std::cin >> position;
	std::cout << '\n';

	string userName;
	string password;
	bool permissions;
	string IBAN;
	float balance;

	std::cout << "Username: ";
	std::cin >> userName;
	std::cout << '\n' << "Password: ";
	std::cin >> password;
	std::cout << '\n' << "Permissions: ";
	std::cin >> permissions;
	std::cout << '\n' << "IBAN: ";
	std::cin >> IBAN;
	std::cout << '\n' << "Balance: ";
	std::cin >> balance;
	std::cout << '\n';
	this->s->updateBankAccount(position, new BankAccount(userName, password, permissions, IBAN, balance));
}

void UI::showAllBankAccounts()
{
	vector<BankAccount*> localRepoBA = this->s->getAllBankAccount();
	std::cout << "All bank accounts:" << '\n';
	for (size_t i = 0; i < localRepoBA.size(); i++)
		cout << i << ". " << *localRepoBA[i]<<'\n';
	std::cout << '\n';
}

void UI::cardUserMenu()
{
	vector<Card*> localRepoC = this->s->getCards(this->s->getBankAccount(this->userName, this->password)->getIBAN());
	std::cout << "Your cards:" << '\n';
	for (size_t i = 0; i < localRepoC.size(); i++)
		std::cout << i << ". " << *localRepoC[i] << '\n';
	std::cout << "0. Back" << '\n';
}

void UI::printCardAdminMenu()
{
	std::cout << "Your cards:" << '\n';
	vector<Card*> localRepoC = this->s->getCards(this->s->getBankAccount(this->userName, this->password)->getIBAN());
	for (size_t i = 0; i < localRepoC.size(); i++)
		std::cout << i << ". " << *localRepoC[i] << '\n';

	std::cout << '\n' << "1. Add card" << '\n';
	std::cout << "2. Remove card" << '\n';
	std::cout << "3. Update card" << '\n';
	std::cout << "4. Show all cards" << '\n';
	std::cout << "0. Back" << '\n';
}

void UI::addCardMenu()
{
	string IBAN;
	string network;
	long long int number;
	float balance;

	std::cout << "IBAN: ";
	std::cin >> IBAN;
	std::cout << '\n' << "Network: ";
	std::cin >> network;
	std::cout << '\n' << "Number: ";
	std::cin >> number;
	std::cout << '\n' << "Balance: ";
	std::cin >> balance;
	std::cout << '\n';

	this->s->addCard(new Card(IBAN, network, number, balance));
}

void UI::delCardMenu()
{
	size_t position;
	size_t size = this->s->getCardSize()-1;
	std::cout << "Please enter a position(0-" << size << "): ";
	std::cin >> position;
	std::cout << '\n';

	this->s->delCard(position);
}

void UI::updateCardMenu()
{
	size_t position;
	size_t size = this->s->getCardSize()-1;

	std::cout << "Please enter a position(0-" << size << "): ";
	std::cin >> position;
	std::cout << '\n';

	string IBAN;
	string network;
	long long int number;
	float balance;

	std::cout << '\n' << "IBAN: ";
	std::cin >> IBAN;
	std::cout << '\n' <<"Network: ";
	std::cin >> network;
	std::cout << '\n' << "Number: ";
	std::cin >> number;
	std::cout << '\n' << "Balance: ";
	std::cin >> balance;
	std::cout << '\n';
	this->s->updateCard(position, new Card(IBAN, network, number, balance));
}

void UI::showAllCards()
{
	vector<Card*> localRepoC = this->s->getAllCard();
	std::cout << "All cards:" << '\n';
	for (size_t i = 0; i < localRepoC.size(); i++)
		cout << i << ". " << *localRepoC[i] << '\n';
	std::cout << '\n';
}

void UI::run()
{
	string command="1";
	bool ok;
	while (command != "0")
	{
		this->printFileOptionMenu();
		this->enterCommandMenu(command);
		if (command == "1" || command == "2")
		{
			this->fileOptionMenu(command);
			while (true)
			{
				this->printLoginMenu();
				this->enterCommandMenu(command);
				if (command == "1")
				{
					ok = this->loginMenu();
					if (ok == 1)
						while (true)
						{
							this->printMainMenu();
							this->enterCommandMenu(command);
							if (command == "1")
							{
								if (this->permissions == 0)
								{
									while (true)
									{
										this->bankAccountUserMenu();
										this->enterCommandMenu(command);
										if (command == "0")
											break;
										else this->wrongCommand();
									}
								}
								else
									while (command != "0")
									{
										this->printBankAccountAdminMenu();
										this->enterCommandMenu(command);
										if (command == "0" || command == "1" || command == "2" || command == "3" || command == "4")
										{
											switch (stoi(command))
											{
											case 0:
											{
												break;
											}
											case 1:
											{
												this->addBankAccountMenu();
												break;
											}
											case 2:
											{
												this->delBankAccountMenu();
												break;
											}
											case 3:
											{
												this->updateBankAccountMenu();
												break;
											}
											case 4:
											{
												this->showAllBankAccounts();
												break;
											}
											}
										}
										else this->wrongCommand();
									}
							}
							else if (command == "2")
							{
								if (this->permissions == 0)
								{
									this->cardUserMenu();
									this->enterCommandMenu(command);
									if (command == "0")
										break;
									else this->wrongCommand();
								}
								else
									while (command != "0")
									{
										this->printCardAdminMenu();
										this->enterCommandMenu(command);
										if (command == "0" || command == "1" || command == "2" || command == "3" || command == "4")
										{
											switch (stoi(command))
											{
											case 0:
											{
												break;
											}
											case 1:
											{
												this->addCardMenu();
												break;
											}
											case 2:
											{
												this->delCardMenu();
												break;
											}
											case 3:
											{
												this->updateCardMenu();
												break;
											}
											case 4:
											{
												this->showAllCards();
												break;
											}
											}
										}
										else this->wrongCommand();
									}
							}
							else if (command == "0")
							{
								command = "1";
								break;
							}
							else this->wrongCommand();
						}
				}
				else if (command == "0")
				{
					command = "1";
					break;
				}
				else this->wrongCommand();
			}
		}
		else if(command != "0") this->wrongCommand();
	}
}