#include "User.h"
#include <string>

using std::string;


/**
 * Default constructor.
 */
User::User()
{
	this->userName = "";
	this->password = "";
	this->permissions = 0;
}

/**
 * Constructor with parameters.
 *
 * @param values userName = string, password = string, permissions = bool.
 */
User::User(string userName, string password, bool permissions)
{
	this->userName = userName;
	this->password = password;
	this->permissions = permissions;
}

/**
 * Destructor.
 */
User::~User()
{
	this->userName = "";
	this->password = "";
	this->permissions = 0;
}

/**
 * Get method for username attribute.
 *
 * @return username = string.
 */
string User::getUserName()
{
	return this->userName;
}


/**
 * Get method for password attribute.
 *
 * @return password = string.
 */
string User::getPassword()
{
	return this->password;
}

/**
 * Get method for permissions attribute.
 *
 * @return permissions = bool.
 */
bool User::getPermissions()
{
	return this->permissions;
}
