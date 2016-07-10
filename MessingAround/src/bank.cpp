#include "bank.h"

bank::bank()
{
}


bank::~bank()
{
}

void bank::open_account(const std::string name)
{
	for (int i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->_owner == name)
		{
			std::cerr << name << " already belongs to bank\n";
			_getch();
			exit(1);
		}
	}

	_accounts.push_back(new account);
	_accounts.back()->_owner = name;
	set_up_account(*_accounts.back());
}

void bank::delete_account(const int accId)
{
	bool found = false;
	for (int i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->_accId == accId)
		{
			int pin;
			bool done = false;
			while (!done)
			{
				inCh::get_input(pin, "Please enter the accounts pin: ");
				if (pin == _accounts[i]->_pin)
				{
					char a;
					inCh::get_input(a, "Are you sure (y,n)");

					switch (a)
					{
					case 'y':
					case 'Y':
					{
						_accounts[i]->_accId = 0;
						_accounts[i]->_funds = 0;
						_accounts[i]->_debt = 0;
						_accounts[i]->_owner = "";
						_accounts[i]->_pin = 0;
						_accounts[i]->_transactionHistory.clear();
						break;
					}
					default:
						break;
					}
					done = true;
				}
				else
				{
					printf("Incorrect pin\n");
				}
			}
		}
	}

	if (!found)
	{
		std::cout << "\nThis account number does not belong to this bank\n";
		_getch();
		exit(1);
	}
}

void bank::print_account_info(const int accId)
{
	bool found = false;
	for (int i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->_accId == accId)
		{
			int enteredPin;
			bool done = false;
			do
			{
				const std::string msg = "\nPlease enter account number " + std::to_string(accId) + "'s pin number: ";
				inCh::get_input(enteredPin, msg);

				if (_accounts[i]->_pin == enteredPin)
				{
					printf("\nThe account number %d belonging to %s has %d debt and %d funds\n"
						, _accounts[i]->_accId
						, _accounts[i]->_owner.c_str()
						, _accounts[i]->_debt
						, _accounts[i]->_funds);
					found = true;
					done = true;
				}
				else
				{
					printf("\n%i is the incorrect account pin for account number %d\n", enteredPin, accId);
				}
			} while (done == false);
		}
	}
	if (!found)
	{
		std::cout << "\nThis account number does not belong to this bank\n";
		_getch();
		exit(1);
	}
}

void bank::print_bank_accounts()
{
	for (int i = 0; i < _accounts.size(); i++)
	{
		printf("\n\n%d: ACCID: %d OWNER: %s DEBT: %d FUNDS: %d\n\n"
			, i
			, _accounts[i]->_accId
			, _accounts[i]->_owner.c_str()
			, _accounts[i]->_debt
			, _accounts[i]->_funds);
	}
}

void bank::deposit_funds(const int accId)
{
	bool found = false;
	for (int i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->_accId == accId)
		{
			unsigned int amn;
			inCh::get_input(amn, "Please enter an amount to deposit: ");

			_accounts[i]->_funds += amn;

			time_t date = time(0);
			char * curDate = asctime(std::localtime(&date));

			std::string transaction = std::to_string(accId) + " " + curDate + " " + "+" + std::to_string(amn);
			_accounts[i]->_transactionHistory.push_back(transaction);

			found = true;
		}
	}
	if (!found)
	{
		std::cout << "\nThis account number does not belong to this bank\n";
		_getch();
		exit(1);
	}
}

void bank::withdrawal_funds(const int accId)
{
	bool found = false;
	for (int i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->_accId == accId)
		{
			int amn;
			inCh::get_input(amn, "Please enter an amount to withdrawal: ");

			_accounts[i]->_funds -= amn;

			time_t date = time(0);
			char * curDate = asctime(std::localtime(&date));

			std::string transaction = std::to_string(accId) + " " + curDate + " " + "-" + std::to_string(amn);
			_accounts[i]->_transactionHistory.push_back(transaction);

			found = true;
		}
	}
	if (!found)
	{
		std::cout << "\nThis account number does not belong to this bank\n";
		_getch();
		exit(1);
	}
}

void bank::display_transactions(const int accId)
{
	bool found = false;
	for (int i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->_accId == accId)
		{
			for (int j = 0; j < _accounts[i]->_transactionHistory.size(); j++)
			{
				std::cout << "\n" << _accounts[i]->_transactionHistory[j] << "\n" << std::endl;
			}
			found = true;
		}
	}
	if (!found)
	{
		std::cout << "\nThis account number does not belong to this bank\n";
		_getch();
		exit(1);
	}
}

void bank::set_up_account(account & acc)
{
	acc._accId = rand() % 1000000;

	printf("\n%s's account number is: %d\n", acc._owner.c_str(), acc._accId);

	acc._debt = 0;
	acc._funds = 0;

	int pin = 0;
	const std::string msg = "\nPlease enter a new pin for " + acc._owner + "'s account: ";
	inCh::get_input(pin, msg);

	acc._pin = pin;
}
