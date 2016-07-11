#include <iostream>
#include <conio.h>
#include <list>

#include "bank.h"

int main()
{
	bank bankOfDavid(1'000'000, "src/accounts.txt");

	std::list<std::string> options;
	std::list<std::string>::iterator iter;
	options.push_back("1: open_account");
	options.push_back("2: print_account_info");
	options.push_back("3: print_bank_accounts");
	options.push_back("4: deposit_funds");
	options.push_back("5: withdrawal_funds");
	options.push_back("6: display_transactions");
	options.push_back("7: delete_account");
	options.push_back("8: take_loan");
	options.push_back("9: transfer_funds");
	options.push_back("Press Q to quit!");


	bankOfDavid.load_accounts("src/accounts.txt");
	bool done = false;

	while (!done)
	{
		int ans;

		for (iter = options.begin(); iter != options.end(); iter++)
			std::cout << *iter << std::endl;

		ans = _getch();
		
		switch (ans)
		{
		case '1':
		{
			std::string name;
			in::get_input(name, "\nPlease enter name of owner: ");
			bankOfDavid.open_account(name);
			//bankOfDavid.save_accounts();
			break;
		}
		case '2':
		{
			int accountId;
			in::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.print_account_info(accountId);
			break;
		}
		case '3':
			bankOfDavid.print_bank_accounts();
			break;
		case '4':
		{
			int accountId;
			in::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.deposit_funds(accountId);
			//bankOfDavid.save_accounts();
			break;
		}
		case '5':
		{
			int accountId;
			in::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.withdrawal_funds(accountId);
			//bankOfDavid.save_accounts();
			break;
		}
		case '6':
		{
			int accountId;
			in::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.display_transactions(accountId);
			break;
		}
		case '7':
		{
			int accountId;
			in::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.delete_account(accountId);
			//bankOfDavid.save_accounts();
			break;
		}
		case '8':
		{
			int accountId;
			in::get_input(accountId, "\nPlease enter an account number: ");
			//bankOfDavid.take_loan(accountId);
			break;
		}
		case '9':
		{
			int fId, sId;
			in::get_input(fId, "\nPlease enter your account number: ");
			in::get_input(sId, "\nPlease enter the other accounts account id: ");
			bankOfDavid.transfer_funds(fId, sId);
			//bankOfDavid.save_accounts();
			break;
		}
		case 'q':
		case 'Q':
			done = true;
			break;
		default:
			std::cout << "Not an option\n";
			break;
		}
	}
	bankOfDavid.save_accounts();
	return 0;
}