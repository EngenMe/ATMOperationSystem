#pragma once

#include <iostream>
#include <string>

namespace StringActions
{
	void DisplayMessage(std::string message)
	{
		if (!message.empty())
			std::cout << message << " : " << std::endl;
	}

	std::string ReadString(std::string message = "")
	{
		DisplayMessage(message);
		
		std::string str;

		std::getline(std::cin >> std::ws, str);

		return str;
	}

	void SplitString(std::string my_string, std::vector <std::string>& v_words, std::string delim = ", ")
	{
		short pos = 0;
		std::string word;

		while ((pos = my_string.find(delim)) != std::string::npos)
		{
			word = my_string.substr(0, pos);

			if (!word.empty())
				v_words.push_back(word);

			my_string.erase(0, pos + delim.length());
		}

		if (!my_string.empty())
			v_words.push_back(my_string);
	}
}
