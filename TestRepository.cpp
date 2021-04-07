#include "TestRepository.h"
#include "RepositoryFileHTML.h"
#include <cassert>
#include <iostream>

TestRepository::TestRepository()
{
	this->t=new TestDomain();
	this->testRepository();
	this->testRepositoryCSV();
	std::cout << "Tests complete!" << "\n\n";
}

void TestRepository::testRepository()
{
	Repository<BankAccount>* r1 = new Repository<BankAccount>();
	BankAccount* b1 = new BankAccount("bogdan", "parola", 1, "robtrl31eas", 3152.2);
	r1->add(b1);
	assert((*r1).getSize() == 1);
	r1->del(0);
	assert((*r1).getSize() == 0);
	r1->add(b1);
	BankAccount* b2 = new BankAccount("bogdan2", "parola2", 1, "robtrl31eas2", 3152.2);
	r1->add(b2);
	assert((*r1).getSize() == 2);
	BankAccount* b3 = new BankAccount("bogdan3", "parola3", 1, "robtrl31eas3", 31523.2);
	r1->update(1, b3);
	assert(*((*r1).getObject(1)) == *(b3));
	delete r1;
	r1 = NULL;
	delete b1;
	b1 = NULL;
	delete b2;
	b2 = NULL;
	delete b3;
	b3 = NULL;
}

void TestRepository::testRepositoryCSV()
{
	RepositoryFileCSV<BankAccount>* r1= new RepositoryFileCSV<BankAccount>("TestBankAccounts.csv");
	assert(r1->getSize() == 2);
	BankAccount* b1 = new BankAccount();
	r1->add(b1);
	assert(r1->getSize() == 3);
	assert(*(r1->getObject(2)) == *(b1));
	r1->del(2);
	assert(r1->getSize() == 2);	
	delete r1;
	r1 = NULL;
	delete b1;
	b1 = NULL;
	RepositoryFileCSV<Card>* r2 = new RepositoryFileCSV<Card>("TestCards.csv");
	assert(r2->getSize() == 2);
	Card* c1 = new Card();
	r2->add(c1);
	assert(r2->getSize() == 3);
	assert(*(r2->getObject(2)) == *(c1));
	r2->del(2);
	assert(r2->getSize() == 2);
	delete r2;
	r2 = NULL;
	delete c1;
	c1 = NULL;
}

void TestRepository::testRepositoryHTML()
{
	RepositoryFileHTML<BankAccount>* r1 = new RepositoryFileHTML<BankAccount>("TestBankAccounts.html");
	assert(r1->getSize() == 2);
	BankAccount* b1 = new BankAccount();
	r1->add(b1);
	assert(r1->getSize() == 3);
	assert(*(r1->getObject(2)) == *(b1));
	r1->del(2);
	assert(r1->getSize() == 2);
	delete r1;
	r1 = NULL;
	delete b1;
	b1 = NULL;
	RepositoryFileHTML<Card>* r2 = new RepositoryFileHTML<Card>("TestCards.html");
	assert(r2->getSize() == 2);
	Card* c1 = new Card();
	r2->add(c1);
	assert(r2->getSize() == 3);
	assert(*(r2->getObject(2)) == *(c1));
	r2->del(2);
	assert(r2->getSize() == 2);
	delete r2;
	r2 = NULL;
	delete c1;
	c1 = NULL;
}