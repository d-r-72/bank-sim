#include <iostream>
#include <conio.h>

#include "bank.h"

int main()
{
	bank bankOfDavid;

	bool done = false;

	while (!done)
	{
		int ans;
		printf("\n\n1: open_account\n2: print_account_info\n3: print_bank_accounts\n4: deposit_funds\n5: withdrawal_funds\n6: display_transactions\n7: delete_account\n");
		ans = _getch();
		
		switch (ans)
		{
		case '1':
		{
			std::string name;
			inCh::get_input(name, "\nPlease enter name of owner: ");
			bankOfDavid.open_account(name);
			break;
		}
		case '2':
		{
			int accountId;
			inCh::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.print_account_info(accountId);
			break;
		}
		case '3':
			bankOfDavid.print_bank_accounts();
			break;
		case '4':
		{
			int accountId;
			inCh::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.deposit_funds(accountId);
			break;
		}
		case '5':
		{
			int accountId;
			inCh::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.withdrawal_funds(accountId);
			break;
		}
		case '6':
		{
			int accountId;
			inCh::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.display_transactions(accountId);
			break;
		}
		case '7':
		{
			int accountId;
			inCh::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.delete_account(accountId);
			break;
		}
		default:
			std::cout << "Not an option\n";
			break;
		}
	}

	int k;
	std::cin >> k;
	return 0;
}