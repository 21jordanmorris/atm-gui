#include <iostream>
#include <unordered_map>
#include <vector>
#include "Account.h"
#pragma once
class Bank
{
private:
	/* 
	  Holds a list of the Bank's account numbers with their corresponding pin number
	*/
	std::unordered_map<int, int> account_data_list;
	/* 
	  Holds a list of all the account objects added to the Bank 
	*/
	std::vector<Account> account_list;
public:
	Bank();
	~Bank();

	void add_account(Account acc);
	bool account_number_exists(int acc_num);
	bool verify_pin(int acc_num, int pin_num);
	void transfer_funds(int from_account_number, int to_account_number, double amount);
	Account get_account(int acc_num);
};

