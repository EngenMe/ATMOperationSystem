#pragma once

#include <iostream>
#include <vector>

#include "CharActions.h";

namespace GetIsYesNo
{
	bool IsIn(char char_to_be_verified, std::vector <char> arr_of_chars)
	{
		for (char c : arr_of_chars)
		{
			if (c == char_to_be_verified)
				return true;
		}

		return false;
	}

	bool GetIsYesNo()
	{
		std::vector <char> arr_yes = { 'Y', 'y' };
		char yes = CharActions::ReadChar();
		
		return (IsIn(yes, arr_yes)) ? true : false;
	}
}
