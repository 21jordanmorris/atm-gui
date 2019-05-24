#include <string>
#pragma once
class Account
{
private:
	int account_number;
	int pin_number;
	double balance;
	double* balance_pointer;
public:
	Account(int account_num, int pin_num);
	Account(int account_num, int pin_num, double balance);
	~Account();

	/*
	  Account Actions
	*/
	void deposit_funds(double amount);
	void withdraw_funds(double amount);
	bool can_withdraw_funds(double amount);

	/*
	  Getters
	*/
	int get_account_number();
	int get_pin_number();
	double get_balance();
};

