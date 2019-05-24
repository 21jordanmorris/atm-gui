#include "Account.h"
#include <stdexcept>
#include <iostream>


/*
  Account constructor with no desired starting balance (defaults to 0).
*/
Account::Account(int account_num, int pin_num)
{
	account_number = account_num;
	pin_number = pin_num;
	balance = 0;
	balance_pointer = &balance;
}

/*
  Account destructor
*/
Account::~Account() {}

/* 
  Account constructor that allows a non-zero starting balance.
*/
Account::Account(int account_num, int pin_num, double bal)
{
	account_number = account_num;
	pin_number = pin_num;
	if (bal < 0)
		throw std::invalid_argument("Balance cannot be a negative number.");
	balance = bal;
	balance_pointer = &balance;
}

/*
  Deposit funds from user account
  amount: desired amount to be added to balance
*/
void Account::deposit_funds(double amount)
{
	if (amount < 0)
		std::cout << "Deposit must be a non-zero positive amount.";
	else
	{
		*balance_pointer += amount;
		std::cout << "$" << amount << " has been added to your account." << std::endl;
	}
}

/*
  Check if user has enough funds to retrieve withdrawl amount
*/
bool Account::can_withdraw_funds(double amount)
{
	if (*balance_pointer - amount < 0)
		return false;
	return true;
}
/*
  Withdraw funds from user account with multiple checks to make sure transaction is valid.
  amount: desired amount to be taken from balance
*/
void Account::withdraw_funds(double amount)
{
	*balance_pointer -= amount;
}

/*
  Getter function for the user's account balance.
*/
double Account::get_balance()
{
	return *balance_pointer;
}

/* 
  Getter function for the user's account number.
 */
int Account::get_account_number()
{
	return account_number;
}

/* 
  Getter function for the user's pin number.
 */
int Account::get_pin_number()
{
	return pin_number;
}
