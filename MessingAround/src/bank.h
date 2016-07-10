#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <ctime>

#include "input.h"

struct account 
{
	int _funds;
	int _debt;
	int _accId;
	int _pin;

	std::vector<std::string> _transactionHistory;

	std::string _owner;
};

class bank
{
public:
	bank();
	~bank();

	void open_account(const std::string name);
	void delete_account(const int accId);

	void print_account_info(const int accId);
	void print_bank_accounts();
	
	void deposit_funds(const int accId);
	void withdrawal_funds(const int accId);

	void display_transactions(const int accId);

private:

	void set_up_account(account & acc);

	std::vector<account *> _accounts;
};

#endif // !BANK_H