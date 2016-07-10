#ifndef INPUT_H
#define INPUT_H

namespace in
{
	template <class U>
	void get_input(U & ret, const std::string msg)
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
}

#endif // !INPUT_H
