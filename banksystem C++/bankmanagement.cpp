// Purpose: Bank Management System using File Handling and OOPs Concepts
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

// Class representing Bank Account and includes methods for various operations
class BankAccount
{
	int accountNumber;
	char accountHolderName[50];
	int balance;
	char accountType;

public:
	void createAccount();		  // create account function
	void displayAccount() const;  // display account function
	void modifyAccount();		  // modify account function
	void deposit(int);			  // deposit function
	void withdraw(int);			  // withdraw function
	void showBalance() const;	  // show balance function
	int getAccountNumber() const; // get account number function
	int getBalance() const;		  // get balance function
	char getAccountType() const;  // get account type function
};

// Function to create account and write to file which uses Inheritance
void BankAccount::createAccount()
{
	system("CLS");
	cout << "\n\t\t\tEnter the Account Number: ";
	cin >> accountNumber;
	cout << "\n\n\t\t\tEnter the Name of the Account Holder: ";
	cin.ignore();
	cin.getline(accountHolderName, 50);
	cout << "\n\t\t\tEnter Type of the Account (C/S): ";
	cin >> accountType;
	accountType = toupper(accountType);
	cout << "\n\t\t\tEnter The Initial Amount: ";
	cin >> balance;
	cout << "\n\n\t\t\tAccount Created..";
}

// Function to display account details
void BankAccount::displayAccount() const
{
	cout << "\n\t\t\tAccount Number: " << accountNumber;
	cout << "\n\t\t\tAccount Holder Name: " << accountHolderName;
	cout << "\n\t\t\tAccount Type: " << accountType;
	cout << "\n\t\t\tBalance: " << balance;
}

// Function to modify account details
void BankAccount::modifyAccount()
{
	cout << "\n\t\t\tAccount Number: " << accountNumber;
	cout << "\n\t\t\tModify Account Holder Name: ";
	cin.ignore();
	cin.getline(accountHolderName, 50);
	cout << "\n\t\t\tModify Account Type: ";
	cin >> accountType;
	accountType = toupper(accountType);
	cout << "\n\t\t\tModify Balance: ";
	cin >> balance;
}

// Function to deposit amount in account
void BankAccount::deposit(int amount)
{
	balance += amount;
}

// Function to withdraw amount from account
void BankAccount::withdraw(int amount)
{
	balance -= amount;
}

// Function to show balance of account
void BankAccount::showBalance() const
{
	cout << "\n\t\t\tAccount Number: " << accountNumber;
	cout << "\n\t\t\tAccount Holder Name: " << accountHolderName;
	cout << "\n\t\t\tAccount Type: " << accountType;
	cout << "\n\t\t\tBalance: " << balance;
}

// Function to get account number
int BankAccount::getAccountNumber() const
{
	return accountNumber;
}

// Function to get balance
int BankAccount::getBalance() const
{
	return balance;
}

// Function to get account type
char BankAccount::getAccountType() const
{
	return accountType;
}

// Function prototypes
void writeAccountToFile();
void displaySingleAccount(int);	  // Displays a single bank account detail
void modifySingleAccount(int);	  // Modifies a single bank account detail
void deleteSingleAccount(int);	  // Deletes a single bank account detail
void displayAllAccounts();		  // Displays all bank account details
void depositOrWithdraw(int, int); // Deposits or withdraws amount from a bank account

int main()
{
	char choice;
	int accountNumber;
	do
	{
		system("CLS");
		cout << "\n\n\t\t\t\t======================\n";
		cout << "\t\t\t\tBANK MANAGEMENT SYSTEM";
		cout << "\n\t\t\t\t======================\n";
		cout << "\t\t\t\t    ::MAIN MENU::\n";
		cout << "\n\t\t\t\t1. NEW ACCOUNT";
		cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
		cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
		cout << "\n\t\t\t\t4. BALANCE ENQUIRY";
		cout << "\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
		cout << "\n\t\t\t\t6. CLOSE AN ACCOUNT";
		cout << "\n\t\t\t\t7. MODIFY AN ACCOUNT";
		cout << "\n\t\t\t\t8. EXIT";
		cout << "\n\n\t\t\t\tSelect Your Option (1-8): ";
		cin >> choice;

		switch (choice)
		{
		case '1':
			writeAccountToFile();
			break;
		case '2':
			system("CLS");
			cout << "\n\n\t\t\tEnter The Account Number: ";
			cin >> accountNumber;
			depositOrWithdraw(accountNumber, 1);
			break;
		case '3':
			system("CLS");
			cout << "\n\n\t\t\tEnter The Account Number: ";
			cin >> accountNumber;
			depositOrWithdraw(accountNumber, 2);
			break;
		case '4':
			system("CLS");
			cout << "\n\n\t\t\tEnter The Account Number: ";
			cin >> accountNumber;
			displaySingleAccount(accountNumber);
			break;
		case '5':
			displayAllAccounts();
			break;
		case '6':
			system("CLS");
			cout << "\n\n\t\t\tEnter The Account Number: ";
			cin >> accountNumber;
			deleteSingleAccount(accountNumber);
			break;
		case '7':
			system("CLS");
			cout << "\n\n\t\t\tEnter The Account Number: ";
			cin >> accountNumber;
			modifySingleAccount(accountNumber);
			break;
		case '8':
			system("CLS");
			cout << "\n\n\t\t\tCreated By Himanshu Singh";
			break;
		default:
			cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (choice != '8');
	return 0;
}

// Creates a new bank account and writes it to a binary file ("accounts.dat")
void writeAccountToFile()
{
	BankAccount account;
	ofstream outFile;									  // write binary data to file
	outFile.open("accounts.dat", ios::binary | ios::app); // append to file
	account.createAccount();
	outFile.write(reinterpret_cast<char *>(&account), sizeof(BankAccount)); // write to file
	outFile.close();
}

// Displays a single bank account detail
void displaySingleAccount(int accountNumber)
{
	BankAccount account;
	bool found = false;
	ifstream inFile;
	inFile.open("accounts.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened! Press any key...";
		return;
	}
	cout << "\n\t\t\tBALANCE DETAILS\n";
	while (inFile.read(reinterpret_cast<char *>(&account), sizeof(BankAccount)))
	{
		if (account.getAccountNumber() == accountNumber)
		{
			account.displayAccount();
			found = true;
		}
	}
	inFile.close();
	if (!found)
	{
		cout << "\n\n\t\t\tAccount number does not exist";
	}
}

// Modifies a single bank account detail
void modifySingleAccount(int accountNumber)
{
	bool found = false;
	BankAccount account;
	fstream File;
	File.open("accounts.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be opened! Press any key...";
		return;
	}
	while (!File.eof() && !found)
	{
		File.read(reinterpret_cast<char *>(&account), sizeof(BankAccount));
		if (account.getAccountNumber() == accountNumber)
		{
			account.displayAccount();
			cout << "\n\n\t\t\tEnter The New Details of the account" << endl;
			account.modifyAccount();
			int pos = static_cast<int>(-sizeof(BankAccount));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *>(&account), sizeof(BankAccount));
			cout << "\n\n\t\t\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if (!found)
	{
		cout << "\n\n\t\t\tRecord Not Found";
	}
}

// Deletes a single bank account detail
void deleteSingleAccount(int accountNumber)
{
	BankAccount account;
	ifstream inFile;
	ofstream outFile;
	inFile.open("accounts.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened! Press any key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *>(&account), sizeof(BankAccount)))
	{
		if (account.getAccountNumber() != accountNumber)
		{
			outFile.write(reinterpret_cast<char *>(&account), sizeof(BankAccount));
		}
	}
	inFile.close();
	outFile.close();
	remove("accounts.dat");
	rename("Temp.dat", "accounts.dat");
	cout << "\n\nRecord Deleted..";
}

// Displays all bank account details
void displayAllAccounts()
{
	system("CLS");
	BankAccount account;
	ifstream inFile;
	inFile.open("accounts.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened! Press any key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char *>(&account), sizeof(BankAccount)))
	{
		account.displayAccount();
	}
	inFile.close();
}

// Deposits or withdraws amount from a bank account
void depositOrWithdraw(int accountNumber, int option)
{
	int amount;
	bool found = false;
	BankAccount account;
	fstream File;
	File.open("accounts.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be opened! Press any key...";
		return;
	}
	while (!File.eof() && !found)
	{
		File.read(reinterpret_cast<char *>(&account), sizeof(BankAccount));
		if (account.getAccountNumber() == accountNumber)
		{
			account.displayAccount();
			if (option == 1)
			{
				cout << "\n\n\t\t\tDEPOSIT AMOUNT";
				cout << "\n\n\t\t\tEnter the amount to be deposited: ";
				cin >> amount;
				account.deposit(amount);
			}
			else if (option == 2)
			{
				cout << "\n\n\t\t\tWITHDRAW AMOUNT";
				cout << "\n\n\t\t\tEnter the amount to be withdrawn: ";
				cin >> amount;
				int newBalance = account.getBalance() - amount;
				if (newBalance < 0)
				{
					cout << "Insufficient balance";
				}
				else
				{
					account.withdraw(amount);
				}
			}
			int pos = static_cast<int>(-sizeof(BankAccount));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *>(&account), sizeof(BankAccount));
			cout << "\n\n\t\t\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if (!found)
	{
		cout << "\n\n\t\t\tRecord Not Found";
	}
}
