
#include <iostream>

void ClearBuffer() 
{
	while (true) 
	{
		char c = getchar();
		if (c == '\n')
			break;
	}
}

int main()
{
	while (true) 
	{
		int i;
		std::cin >> i;
		ClearBuffer();

		if (std::cin.fail())
		{
			std::cout << "fail" << std::endl;
			std::cin.clear();
		}
		else
		{
			std::cout << "ok" << std::endl;
		}

	}

	return 0;
	
}
