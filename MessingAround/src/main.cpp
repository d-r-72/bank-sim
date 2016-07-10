#include <iostream>
#include <conio.h>

#include "bank.h"

int main()
{
	bank bankOfDavid(1'000'000);

	bankOfDavid.load_accounts("src/accounts.txt");
	bool done = false;

	while (!done)
	{
		int ans;
		printf("1: open_account\n2: print_account_info\n3: print_bank_accounts\n4: deposit_funds\n5: withdrawal_funds\n6: display_transactions\n7: delete_account\n8: take_loan\n9: transfer_funds\n");
		ans = _getch();
		
		switch (ans)
		{
		case '1':
		{
			std::string name;
			in::get_input(name, "\nPlease enter name of owner: ");
			bankOfDavid.open_account(name);
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
			break;
		}
		case '5':
		{
			int accountId;
			in::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.withdrawal_funds(accountId);
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
			break;
		}
		case '8':
		{
			int accountId;
			in::get_input(accountId, "\nPlease enter an account number: ");
			bankOfDavid.take_loan(accountId);
			break;
		}
		case '9':
		{
			int fId, sId;
			in::get_input(fId, "\nPlease enter your account number: ");
			in::get_input(sId, "\nPlease enter the other accounts account id: ");
			bankOfDavid.transfer_funds(fId, sId);
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

	bankOfDavid.save_accounts("src/accounts.txt");

	int k;
	std::cin >> k;
	return 0;
}