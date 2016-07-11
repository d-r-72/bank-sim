#include "bank.h"

bank::bank()
{
}

bank::~bank()
{
	clean_up();
}

template <typename T>
void bank::report_error(const std::string & msg, T wrongInfo)
{
	std::cout << msg << wrongInfo << std::endl;
	printf("Enter any key to return...\n");
	_getch();
}

bool bank::account_in_bank(const int accId)
{
	bool result = false;

	for (int i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->_accId == accId)
		{
			result = true;
		}
	}

	return result;
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
	if (account_in_bank(accId))
	{
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
							_accounts[i] = _accounts.back();
							_accounts.pop_back();
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
	}
	else
	{
		report_error("This account is not in the bank: ", accId);
		return;
	}
}

void bank::print_account_info(const int accId)
{
	if (account_in_bank(accId))
	{
		for (auto i : _accounts)
		{
			if (i->_accId == accId)
			{
				int enteredPin;
				bool done = false;
				do
				{
					const std::string msg = "\nPlease enter account number " + std::to_string(accId) + "'s pin number: ";
					in::get_input(enteredPin, msg);

					if (i->_pin == enteredPin)
					{
						printf("\nThe account number %d belonging to %s has %d debt and %d funds\n"
							, i->_accId
							, i->_owner.c_str()
							, i->_debt
							, i->_funds);
						done = true;
					}
					else
					{
						printf("\n%i is the incorrect account pin for account number %d\n", enteredPin, accId);
					}
				} while (done == false);
			}
		}
	}
	else
	{
		report_error("This account is not in the bank: ", accId);
		return;
	}
}

void bank::print_bank_accounts()
{
	for(auto i : _accounts)
	{
		printf("\n\nACCID: %d OWNER: %s PIN: %d DEBT: %d FUNDS: %d\n"
			, i->_accId
			, i->_owner.c_str()
			, i->_pin
			, i->_debt
			, i->_funds);
	}
}

void bank::deposit_funds(const int accId)
{
	if (account_in_bank(accId))
	{
		for (auto i : _accounts)
		{
			if (i->_accId == accId)
			{
				int amn;
				in::get_input(amn, "Please enter an amount to deposit: ");

				i->_funds += amn;

				time_t date = time(0);
				char * curDate = asctime(std::localtime(&date));

				std::string transaction = std::to_string(accId) + " " + curDate + " " + "+" + std::to_string(amn);
				i->_transactionHistory.push_back(transaction);
			}
		}
	}
	else
	{
		report_error("This account is not in the bank: ", accId);
		return;
	}
}

void bank::withdrawal_funds(const int accId)
{
	if (account_in_bank(accId))
	{
		for (auto i : _accounts)
		{
			if (i->_accId == accId)
			{
				int amn;
				in::get_input(amn, "Please enter an amount to withdrawal: ");

				i->_funds -= amn;

				time_t date = time(0);
				char * curDate = asctime(std::localtime(&date));

				std::string transaction = std::to_string(accId) + " " + curDate + " " + "-" + std::to_string(amn);
				i->_transactionHistory.push_back(transaction);
			}
		}
	}
	else
	{
		report_error("This account is not in the bank: ", accId);
		return;
	}
}

void bank::display_transactions(const int accId)
{
	if (account_in_bank(accId))
	{
		for (auto i : _accounts)
		{
			if (i->_accId == accId)
			{
				for (int j = 0; j < i->_transactionHistory.size(); j++)
					std::cout << "\n" << i->_transactionHistory[j] << "\n" << std::endl;
			}
		}
	}
	else
	{
		report_error("This account is not in the bank: ", accId);
		return;
	}
}

void bank::take_loan(const int accId)
{
	if (account_in_bank(accId))
	{
		for (auto i : _accounts)
		{
			if (i->_accId == accId)
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
					i->_funds += amount;
					_bankFunds -= amount;
					_loans.push_back(new loan);
					_loans.back()->_account = accId;
					_loans.back()->_amount = amount;
				}
			}
		}
	}
	else
	{
		report_error("This account is not in the bank: ", accId);
		return;
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

void bank::save_accounts()
{
	for (int i = 0; i < _accounts.size(); i++)
	{
		_saveFile << _accounts[i]->_owner << ' ' << _accounts[i]->_accId << ' ' << _accounts[i]->_pin << ' ' << _accounts[i]->_debt << ' ' << _accounts[i]->_funds << std::endl;
	}
}

void bank::transfer_funds(const int fAccId, const int sAccid)
{
	if (fAccId == sAccid)
	{
		report_error("Cannot transfer funds into your own account", NULL);
		return;
	}
	else
	{
		if (account_in_bank(fAccId))
		{
			if (account_in_bank(sAccid))
			{
				int amount;
				in::get_input(amount, "Please enter a amount to transfer: ");
				for (auto i : _accounts)
				{
					if (i->_accId == fAccId)
						i->_funds -= amount;
					if (i->_accId == sAccid)
						i->_funds += amount;
				}
			}
			else
			{
				report_error("This account is not in the bank: ", sAccid);
				return;
			}
		}
		else
		{
			report_error("This account is not in the bank: ", fAccId);
			return;
		}
	}
}

void bank::clean_up()
{
	for (int i = 0; i < _loans.size(); i++)
	{
		delete _loans[i];
	}

	_loans.clear();

	for (int i = 0; i < _accounts.size(); i++)
	{
		delete _accounts[i];
	}

	_accounts.clear();
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
