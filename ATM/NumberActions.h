#pragma once

#include <iostream>

namespace NumberActions
{
	void DisplayMessage(std::string message)
	{
		if (!message.empty())
			std::cout << message << " : " << std::endl;
	}

	bool IsIntAndPositive(int n)
	{
		if (n < 0)
		{
			std::cout << "Wrong number, please enter a positive integer number : \n";
			return false;
		}

		return true;
	}

	int ReadValidNumber()
	{
		int number;

		std::cin >> number;

		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');

			std::cout << "Invalid number, please enter a valid number : \n";
			std::cin >> number;
		}

		return number;
	}

	int ReadPositiveIntNumber(std::string message = "")
	{
		int number;

		DisplayMessage(message);
		
		do
		{
			number = ReadValidNumber();
		} while (!IsIntAndPositive(number));

		return number;
	}

	int ReadIntNumber(std::string message = "")
	{
		int number;

		DisplayMessage(message);

		number = ReadValidNumber();

		return number;
	}

	bool IsBetweenFromAndTo(int number, int from, int to)
	{
		if (number < from || number > to)
		{
			std::cout << "Wrong number, please enter a number between " << from << " and " << to << " :\n";
			return false;
		}

		return true;
	}

	int ReadIntNumberBetweenFromAndTo(int from, int to, std::string message = "")
	{
		int number;

		DisplayMessage(message);

		do
		{
			number = ReadValidNumber();
		} while (!IsBetweenFromAndTo(number, from, to));

		return number;
	}

	double ReadValidDoubleNumber()
	{
		double number;

		std::cin >> number;

		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');

			std::cout << "Invalid number, please enter a valid number : \n";
			std::cin >> number;
		}

		return number;
	}

	bool IsDoubleAndPositive(double n)
	{
		if (n < 0)
		{
			std::cout << "Wrong number, please enter a positive number : \n";
			return false;
		}

		return true;
	}

	double ReadDoublePositiveNumber(std::string message = "")
	{
		DisplayMessage(message);

		double number;

		do
		{
			number = ReadValidDoubleNumber();
		} while (!IsDoubleAndPositive(number));

		return number;
	}

	bool IsBetweenFromAndTo(double number, int from, int to)
	{
		if (number < from || number > to)
		{
			std::cout << "Wrong number, please enter a number between " << from << " and " << to << " :\n";
			return false;
		}

		return true;
	}

	double ReadDoubleNumberBetweenFromAndTo(short from, short to, std::string message = "")
	{
		double number;

		DisplayMessage(message);

		do
		{
			number = ReadValidDoubleNumber();
		} while (!IsBetweenFromAndTo(number, from, to));

		return number;
	}
}