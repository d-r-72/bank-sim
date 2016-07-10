#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <ctime>
#include <fstream>

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

struct loan
{
	int _amount;
	int _account;
};

class bank
{
public:
	bank();
	bank(uint16_t initFund)
		: _bankFunds(initFund) { }
	~bank();

	void open_account(const std::string name);
	void delete_account(const int accId);

	void print_account_info(const int accId);
	void print_bank_accounts();
	
	void deposit_funds(const int accId);
	void withdrawal_funds(const int accId);

	void display_transactions(const int accId);

	void take_loan(const int accId);

	void load_accounts(const std::string & fileName);
	void save_accounts(const std::string & fileName);
	
	void transfer_funds(const int fAccId, const int sAccid);

private:
	template <class A>
	void report_error(const std::string & msg, A wrongInfo);	
		
	bool account_in_bank(const int accId);

	void set_up_account(account & acc);

	uint16_t _bankFunds;

	std::vector<loan *> _loans;
	std::vector<account *> _accounts;
};

#endif // !BANK_H