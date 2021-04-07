#pragma once

#include "TestDomain.h"

class TestRepository
{
private:
	TestDomain* t;
public:
	TestRepository();
	~TestRepository();
	void testRepository();
	void testRepositoryCSV();
	void testRepositoryHTML();
};