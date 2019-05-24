#include "Bank.h"
#include "Account.h"
#include <iostream>

/*
  Bank constructor
*/
Bank::Bank() {}

/*
  Bank destructor
*/
Bank::~Bank() {}

/*
  Store's account's account number and pin number into an unordered map.
  Store's the account object into a vector to keep a list of all the Bank's accounts.
*/
void Bank::add_account(Account acc)
{
	account_data_list.insert({ acc.get_account_number(), acc.get_pin_number() });
	account_list.push_back(acc);
}

/*
  Takes an account number and searches for it in the account_list (an unordered map) 
  returning true if found.
*/
bool Bank::account_number_exists(int acc_num)
{
	if (account_data_list.count(acc_num))
		return true;
	return false;
}

/*
  Takes an account number and pin number and first searches for the account number (similar to
  the account_number_exists method) and then checks if the value of the account number matches
  the pin number given.
*/
bool Bank::verify_pin(int acc_num, int pin_num)
{
	if (account_data_list.count(acc_num))
	{
		// Checks if account number's value (pin) is equal to given pin number
		if (account_data_list.find(acc_num)->second == pin_num)
		{
			return true;
		}
	}
	return false;
}

/*
  Takes a 'from' account number and a 'to' account number, calling the withdraw function on the
  'from' account and then the deposit function on the 'to' account.
*/
void Bank::transfer_funds(int from_account_number, int to_account_number, double amount)
{
	/* Should have already checked if this is valid, but if not the withdraw_funds function will do so */
	get_account(from_account_number).withdraw_funds(amount);
	get_account(to_account_number).deposit_funds(amount);
}

/*
  Looks through the account list to look for the account number provided. If found, because add_account inserts
  the user information to both the account list and the user list, the method returns the user at the index 
  where the account number was found.
*/
Account Bank::get_account(int acc_num)
{
	int acc_index = std::distance(account_data_list.begin(), account_data_list.find(acc_num));
	return account_list.at(acc_index);
}
