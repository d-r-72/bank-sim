#include <iostream>
#include <conio.h>

#include "bank.h"

int main()
{
	bank bankOfDavid(3000000);

	bool done = false;

	while (!done)
	{
		int ans;
		printf("1: open_account\n2: print_account_info\n");
		ans = _getch();
		

		switch (ans)
		{
		case '1':
		{
			std::string name;
			printf("Please enter name of owner: ");
			std::cin >> name;
			bankOfDavid.open_account(name);
			break;
		}
		case 2:
		{
			int accountId;
			printf("Please enter an account number: ");
			std::cin >> accountId;
			bankOfDavid.print_account_info(accountId);
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