#include "TestDomain.h"
#include <cassert>

TestDomain::TestDomain()
{
	this->testBankAccount();
	this->testCard();
}

void TestDomain::testBankAccount()
{
	BankAccount* b1 = new BankAccount();
	assert(b1->getUserName() == "");
	assert(b1->getPassword() == "");
	assert(b1->getPermissions() == 0);
	assert(b1->getIBAN() == "");
	assert(b1->getBalance() == 0);
	BankAccount* b2 = new BankAccount("bogdan","parola",1,"robtrl31eas",3152.2);
	assert(b2->getUserName() == "bogdan");
	assert(b2->getPassword() == "parola");
	assert(b2->getPermissions() == 1);
	assert(b2->getIBAN() == "robtrl31eas");
	assert((b2->getBalance() - 3152.2) < FLT_EPSILON);
	assert(!((*b1) == (*b2)));
	BankAccount* b3 = new BankAccount("bogdan", "parola", 1, "robtrl31eas", 999.2);
	assert((*b2) == (*b3));
	delete b1;
	b1 = NULL;
	delete b2;
	b2 = NULL;
	delete b3;
	b3 = NULL;
}

void TestDomain::testCard()
{
	Card* c1 = new Card();
	assert(c1->getIBAN() == "");
	assert(c1->getNetwork() == "");
	assert(c1->getNumber() == 0);
	assert(c1->getBalance() == 0);
	Card* c2 = new Card("robtrl123", "Visa", 1234567891, 123.45);
	assert(c2->getIBAN() == "robtrl123");
	assert(c2->getNetwork() == "Visa");
	assert(c2->getNumber() == 1234567891);
	assert((c2->getBalance() - 123.45) < FLT_EPSILON);
	assert(!((*c1) == (*c2)));
	Card* c3 = new Card("robeaz12354", "Mastercard", 1234567891, 123.45);
	assert((*c2) == (*c3));
	delete c1;
	c1 = NULL;
	delete c2;
	c2 = NULL;
	delete c3;
	c3 = NULL;
}