#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdio>

#include "StringActions.h";
#include "NumberActions.h";
#include "GetIsYesNo.h";

enum enAction
{
	quick_withdraw = 1,
	normal_withdraw = 2,
	deposit = 3,
	check_balance = 4,
	logout = 5,
	exit_programme = 6
};

enum enQuickWithdrawAmount
{
	twenty = 1,
	fifty = 2,
	one_hundred = 3,
	two_hundred = 4,
	four_hundred = 5,
	six_hundred = 6,
	eight_hundred = 7,
	one_thousand = 8,
	exit_quick_withdraw_action = 9
};

struct stClient
{
	std::string account_number;
	std::string pin_code;
	double balance_amount;
	enAction action;
};

const std::vector <short> v_withdraw_amount =
{
	0,
	20,
	50,
	100,
	200,
	400,
	600,
	800,
	1000
};

const char* login_head_message =
"-------------------------------\n"
"\t Login Screen \n"
"-------------------------------\n";

const char* invalid_client_error_message =
"Invalid Account number/PIN code\n"
"Please Enter A Valid Account number/PIN code\n";

const char* read_number_action_message =
"-------------------------------\n"
"\t ATM Menue Screen \n"
"-------------------------------\n"
"\t [1] Quick Withdraw.\n"
"\t [2] Normal Withdraw.\n"
"\t [3] Deposit.\n"
"\t [4] Check Balance.\n"
"\t [5] Logout.\n"
"\t [6] Exit.\n"
"-------------------------------\n"
"Choose What Do You Want To Do [1-5]";

const char* quick_withdraw_screen =
"-------------------------------\n"
"\t Quick Withdraw Screen \n"
"[1] 20 \t\t [2] 50\n"
"[3] 100 \t [4] 200\n"
"[5] 400 \t [6] 600\n"
"[7] 800 \t [8] 1000\n"
"[9] Exit\n"
"-------------------------------\n";

const char* normal_withdraw_screen =
"-------------------------------\n"
"\t Normal Withdraw Screen \n"
"-------------------------------\n";

const char* deposit_screen =
"-------------------------------\n"
"\t Deposit Screen \n"
"-------------------------------\n";

const char* check_balance_screen = 
"-------------------------------\n"
"\t Balance Screen \n"
"-------------------------------\n";

const std::string clients_file_name = "clients.txt";
const std::string delimiter = ", ";
const std::string confirm_action_message = "Do you want to confirm this action (Y/N): ";

// Read Client

void ShowHeadScreen(std::string message)
{
	system("cls");
	std::cout << message;
}

stClient ReadClientInfo()
{
	stClient client;
	client.account_number = StringActions::ReadString("Enter Account Number");
	client.pin_code = StringActions::ReadString("Enter PIN code");

	return client;
}

stClient StrToClientData(std::string str)
{
	std::vector <std::string> v_client;
	StringActions::SplitString(str, v_client, delimiter);

	stClient client;
	client.account_number = v_client[0];
	client.pin_code = v_client[1];
	client.balance_amount = stoi(v_client[2]);

	return client;
}

std::vector <stClient> GetVecClientsFromTxtFile()
{
	std::vector <stClient> v_client;

	std::fstream file;
	file.open(clients_file_name, std::ios::in);

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			v_client.push_back(StrToClientData(line));
		}

		file.close();
	}

	return v_client;
}

bool AreClientsMatched(stClient client1, stClient client2)
{
	return (client1.account_number == client2.account_number) && (client1.pin_code == client2.pin_code);
}

bool IsClientInVecClient(stClient& client, std::vector <stClient>& v_client)
{
	for (stClient st : v_client)
	{
		if (AreClientsMatched(st, client))
		{
			client.balance_amount = st.balance_amount;
			return true;
		}
	}

	return false;
}

bool IsExistClient(stClient& client, std::vector <stClient>& v_client)
{
	return IsClientInVecClient(client, v_client);
}

stClient ReadClient(std::vector <stClient>& v_client)
{
	ShowHeadScreen(login_head_message);
	stClient client = ReadClientInfo();

	if (IsExistClient(client, v_client))
		return client;
	else
	{
		ShowHeadScreen(invalid_client_error_message);
		system("pause");
		ReadClient(v_client);
	}
}

enAction ReadAction()
{
	system("cls");

	return (enAction)NumberActions::ReadIntNumberBetweenFromAndTo(1, 6, read_number_action_message);
}

// Quick Withdraw

void PrintBalanceMessage(double balance, std::string str_message = "")
{
	const char* message = str_message.c_str();
	printf("%s: %.2f\n", message, balance);
}

enQuickWithdrawAmount ReadQuickWithdrawAmount()
{
	return (enQuickWithdrawAmount)NumberActions::ReadIntNumberBetweenFromAndTo(1, 9,
		"Chose Withdraw Amount [1-8]");
}

bool IsWithdrawPermitted(double balance_amount, int withdraw_amount)
{
	return (balance_amount >= withdraw_amount) ? true : false;
}

bool ConfirmAction()
{
	std::cout << confirm_action_message << std::endl;
	return GetIsYesNo::GetIsYesNo();
}

void MakeWithdrawAction(double& balance_amount, int withdraw_amount, std::string message = "")
{
	balance_amount -= withdraw_amount;
	if (!message.empty())
	{
		std::cout << message << std::endl;
		PrintBalanceMessage(balance_amount, "Your Balance Is");
	}
}

void DoQuickWithdraw(stClient& client)
{
	ShowHeadScreen(quick_withdraw_screen);
	PrintBalanceMessage(client.balance_amount, "Your Balance Is");

	enQuickWithdrawAmount quick_withdraw_amount_action = ReadQuickWithdrawAmount();

	if (quick_withdraw_amount_action == enQuickWithdrawAmount::exit_quick_withdraw_action)
		return;

	if (IsWithdrawPermitted(client.balance_amount, quick_withdraw_amount_action))
	{
		if (ConfirmAction())
			MakeWithdrawAction(client.balance_amount, v_withdraw_amount[quick_withdraw_amount_action],
				"Withdraw has been processed successfully!");
		else
			std::cout << "Cancelled!\n";
	}
	else
	{
		std::cout << "Sorry, withdrawal amount exceeded!\n";
		system("pause");
		DoQuickWithdraw(client);
	}
}

// Normal Withdraw

int ReadWithdrawAmount()
{
	int withdraw_amount = NumberActions::ReadPositiveIntNumber("Enter Witdrawal Amount (of 5's)");

	if (withdraw_amount % 5 == 0)
		return withdraw_amount;
	else
	{
		std::cout << "Not of 5's!\n";
		ReadWithdrawAmount();
	}
}

void DoNormalWithdraw(stClient& client)
{
	ShowHeadScreen(normal_withdraw_screen);
	PrintBalanceMessage(client.balance_amount, "Your Balance Is");

	int withdraw_amount = ReadWithdrawAmount();

	if (IsWithdrawPermitted(client.balance_amount, withdraw_amount))
	{
		if (ConfirmAction())
			MakeWithdrawAction(client.balance_amount, withdraw_amount,
				"Withdraw has been processed successfully!");
		else
			std::cout << "Cancelled!\n";
	}
	else
	{
		std::cout << "Sorry, withdrawal amount exceeded!\n";
		system("pause");
		DoNormalWithdraw(client);
	}
}

// Deposit

void MakeDeposit(double& balance_amount, int deposit_amount)
{
	if (ConfirmAction())
	{
		balance_amount += deposit_amount;
		std::cout << "Deposit has been processed successfully!\n";
		PrintBalanceMessage(balance_amount, "New Balance Is");
	}
	else
		std::cout << "Cancelled!\n";
}

void DoDeposit(stClient& client)
{
	ShowHeadScreen(deposit_screen);
	PrintBalanceMessage(client.balance_amount, "Your Balance Is");

	int deposit_amount = NumberActions::ReadPositiveIntNumber("Enter Deposit Amount");
	MakeDeposit(client.balance_amount, deposit_amount);
}

// Check Balance

void CheckBalance(double balance_amount)
{
	system("cls");
	std::cout << check_balance_screen;
	PrintBalanceMessage(balance_amount, "Your Balance Is");
}

// Perform Actions

void DoAction(stClient& client)
{
	switch (client.action)
	{
	case enAction::quick_withdraw:
		DoQuickWithdraw(client);
		break;
	case enAction::normal_withdraw:
		DoNormalWithdraw(client);
		break;
	case enAction::deposit:
		DoDeposit(client);
		break;
	case enAction::check_balance:
		CheckBalance(client.balance_amount);
		break;
	default:
		return;
	}
	system("pause");
}

void UpdateVecClient(stClient client, std::vector <stClient>& v_client)
{
	for (stClient& st : v_client)
	{
		if (st.account_number == client.account_number)
		{
			st = client;
			break;
		}
	}
}

void EraseFile(std::string file_name = clients_file_name)
{
	std::fstream file;
	file.open(file_name, std::ios::out);
	file.close();
}

std::string ClientToStr(stClient client)
{
	return client.account_number + delimiter +
		client.pin_code + delimiter +
		std::to_string(client.balance_amount);
}

void AddStrToFile(std::string str, std::string file_name = clients_file_name)
{
	std::fstream file;
	file.open(file_name, std::ios::out | std::ios::app);
	if (file.is_open())
	{
		file << str << std::endl;
		file.close();
	}
}

void SaveVecClientsIntoTxtFile(std::vector <stClient> v_client)
{
	EraseFile();
	for (stClient st : v_client)
	{
		AddStrToFile(ClientToStr(st));
	}
}

void PerformActionsIntoTxtFile(stClient client, std::vector <stClient>& v_client)
{
	UpdateVecClient(client, v_client);
	SaveVecClientsIntoTxtFile(v_client);
}

void Login()
{
	std::vector <stClient> v_client = GetVecClientsFromTxtFile();
	stClient client = ReadClient(v_client);

	while(client.action != enAction::exit_programme)
	{
		client.action = ReadAction();

		if (client.action == enAction::logout)
			Login();

		DoAction(client);
		PerformActionsIntoTxtFile(client, v_client);
	}
}

int main()
{
	Login();

	return 0;
}