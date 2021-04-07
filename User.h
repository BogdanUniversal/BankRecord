#pragma once

#include <string>

using std::string;

class User
{
protected:
	string userName;
	string password;
	bool permissions;

public:
	User();
	User(string userName, string password, bool permissions);
	~User();
	string getUserName();
	string getPassword();
	bool getPermissions();
};
