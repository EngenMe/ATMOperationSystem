#pragma once

#include <iostream>

namespace GenerateRandom
{
	void DisplayMessage(std::string message)
	{
		if (!message.empty())
			std::cout << message << " : " << std::endl;
	}

	int GenerateRandomIntFromTo(int from, int to, std::string message = "")
	{
		DisplayMessage(message);
		return rand() % (to - from + 1) + from;
	}
}