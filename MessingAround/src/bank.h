#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <conio.h>

struct account 
{
	int _funds;
	int _debt;
	int _accId;
	int _pin;

	std::string _owner;
};

class bank
{
public:
	bank();
	bank(uint16_t startFund)
		: _bankFunds(startFund) {}
	~bank();

	void open_account(const std::string name);
	void print_account_info(const int accId);
	void deposit_funds();

private:
	template <class U>
	void get_input(U & ret, const std::string msg);

	void set_up_account(account & acc);

	uint16_t _bankFunds;

	std::vector<account *> _accounts;
};

#endif // !BANK_H