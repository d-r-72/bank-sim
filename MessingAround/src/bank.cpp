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
			exit(1);
		}
	}

	_accounts.push_back(new account);
	_accounts.back()->_owner = name;
	set_up_account(*_accounts.back());
}

void bank::print_account_info(const int accId)
{
	for (int i = 0; i < _accounts.size(); i++)
	{
		if (_accounts[i]->_accId == accId)
		{
			int enteredPin;
			bool done = false;
			do
			{
				const std::string msg = "Please enter account number " + std::to_string(accId) + "'s pin number: ";
				get_input(enteredPin, msg);

				if (_accounts[i]->_pin == enteredPin)
				{
					printf("The account number %d belonging to %s has %d debt and %d funds"
						, _accounts[i]->_accId
						, _accounts[i]->_owner.c_str()
						, _accounts[i]->_debt
						, _accounts[i]->_funds);
					
					done = true;
				}
				else
				{
					printf("%i is the incorrect account pin for account number %d\n", enteredPin, accId);
				}
			} while (done == false);
		}
		else
		{
			std::cerr << "Account Num: " << accId << " does not belong to this bank\n";
			_getch();
			exit(1);
		}
	}
}

void bank::set_up_account(account & acc)
{
	acc._accId = rand() % 15;

	printf("%s's account number is: %d\n", acc._owner.c_str(), acc._accId);

	acc._debt = 0;
	acc._funds = 0;

	int pin = 0;
	const std::string msg = "Please enter a new pin for " + acc._owner + "'s account: ";
	get_input(pin, msg);

	acc._pin = pin;
}

template <class U>
void bank::get_input(U & ret, const std::string msg)
{
	bool done = false;
	do
	{
		std::cout << msg << std::endl;
		std::cin >> ret;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			done = true;
		}
	} while (done == false);
} 