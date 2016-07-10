#include "bank.h"

bank::bank()
{
}


bank::~bank()
{
}

template <class A>
void bank::report_error(const std::string & msg, A wrongInfo)
{
	std::cout << msg << wrongInfo << std::endl;
	_getch();
	exit(1);
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
				in::get_input(pin, "Please enter the accounts pin: ");
				if (pin == _accounts[i]->_pin)
				{
					char a;
					in::get_input(a, "Are you sure (y,n)");

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
		report_error("\nThis account number does not belong to this bank: ", accId);
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
				in::get_input(enteredPin, msg);

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
		report_error("\nThis account number does not belong to this bank: ", accId);
	}
}

void bank::print_bank_accounts()
{
	for (int i = 0; i < _accounts.size(); i++)
	{
		printf("\n\nACCID: %d OWNER: %s PIN: %d DEBT: %d FUNDS: %d\n"
			, _accounts[i]->_accId
			, _accounts[i]->_owner.c_str()
			, _accounts[i]->_pin
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
			in::get_input(amn, "Please enter an amount to deposit: ");

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
		report_error("\nThis account number does not belong to this bank: ", accId);
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
			in::get_input(amn, "Please enter an amount to withdrawal: ");

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
		report_error("\nThis account number does not belong to this bank: ", accId);
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
		report_error("\nThis account number does not belong to this bank: ", accId);
	}
}

void bank::take_loan(const int accId)
{
	bool found = false;
	for (int i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->_accId == accId)
		{
			int amount;
			in::get_input(amount, "Please enter the amount you would like: ");
			if (amount > _bankFunds)
			{
				printf("Amount is to much\n");
				return;
			}
			else
			{
				_accounts[i]->_funds += amount;
				_bankFunds -= amount;
				_loans.push_back(new loan);
				_loans.back()->_account = accId;
				_loans.back()->_amount = amount;
			}

			found = true;
		}
	}
	if (!found)
	{
		report_error("\nThis account number does not belong to this bank: ", accId);
	}
}

void bank::load_accounts(const std::string & fileName)
{
	std::ifstream file(fileName);

	std::string name;
	int accId;
	int pin;
	int funds;
	int debt;

	while (file >> name >> accId >> pin >> debt >> funds)
	{
		_accounts.push_back(new account);
		_accounts.back()->_owner = name;
		_accounts.back()->_accId = accId;
		_accounts.back()->_pin = pin;
		_accounts.back()->_debt = debt;
		_accounts.back()->_funds = funds;
	}
}

void bank::save_accounts(const std::string & fileName)
{
	std::ofstream file(fileName);

	std::string name;
	int accId;
	int pin;
	int funds;
	int debt;

	for (int i = 0; i < _accounts.size(); i++)
	{
		file << _accounts[i]->_owner << ' ' << _accounts[i]->_accId << ' ' << _accounts[i]->_pin << ' ' << _accounts[i]->_debt << ' ' << _accounts[i]->_funds << std::endl;
	}

	file.close();
}

void bank::set_up_account(account & acc)
{
	std::srand(std::time(0));
	acc._accId = std::rand() % 1000000;

	printf("\n%s's account number is: %d\n", acc._owner.c_str(), acc._accId);

	acc._debt = 0;
	acc._funds = 0;

	int pin = 0;
	const std::string msg = "\nPlease enter a new pin for " + acc._owner + "'s account: ";
	in::get_input(pin, msg);

	acc._pin = pin;
}
