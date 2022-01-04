/* ------------------------------------------------------
CMP2801M: Advanced Programming
Driver program for "LincBank" Assessment Item 1
Semester A 2021

Written by James Brown (jamesbrown@lincoln.ac.uk)

During marking, we will use the exact same notation
as provided in the brief, so make sure you follow that guideline.

You should avoid removing parts of this driver program, but
add to it the necessary code to produce your implementation.

Good luck!
------------------------------------------------------ */
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include "Account.h";
#include "Savings.h";
#include "Current.h";


using namespace std;

//exception class
struct flowException : public exception {//overflow or underflow error
	const char* what() const throw() {
		return "over/under flow error";
	}
};

int main()
{
	vector<Account*> allAccounts;//vector of account pointers to allow for a data structure of polymorphic classes that can hold both base and derived classes
	Account* accPtr = new Account;
	Current* currPtr = new Current;
	Savings* savPtr = new Savings;

	//testing purposes
	allAccounts.push_back(new Current());
	allAccounts[allAccounts.size() - 1]->balance = 15;

	std::vector <std::string> parameters;
	std::string userCommand;

	//use defensive programming such as static asserts here
	// you may also want to store a collection of opened accounts here

	std::cout << "~~~ Welcome to LincBank! ~~~" << std::endl;

	while (userCommand != "exit")
	{
		parameters.clear(); // clear ready for next command
		std::cout << std::endl << ">>> ";

		std::getline(std::cin, userCommand);
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");
		cout << "Value pointed to by token " << *token << endl;
		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
			
		}

		// Define all commands as per the brief
		cout << "Parameters size is" << parameters.size() << endl;
		std::string command = parameters[0];
		if (command.compare("options") == 0)
		{
			cout << "open - allows you to open a current(1), savings(2), or ISA(3) accounts " << endl <<
				"view - allows you to see either all of your accounts or a specific account based on its number " << endl <<
				"withdraw - allows you to remove balance from an account " << endl <<
				"deposit - allows you to place balance into an account " << endl <<
				"transfer - allows you to move the balance from one account into another " << endl <<
				"project - calculates your balance based on interest in a user-defined number of years " << endl <<
				"exit - closes the application " << endl <<
				"options - view these options again " << endl;
			// display the various commands to the user
		}
		else if (command.compare("open") == 0)//opens a new account
		{
			//check if there is room for a new account
			//get input asking for what kind of account they want
			if (allAccounts.size() < 5) {//checks if the number of accounts that have been made is within limits
				string choice = "";

				cout << "Would you like to open a (1)Current account, (2)Savings account, or (3)ISA account" << endl <<
					"Please press the number associated with the account to open " << endl;

				getline(cin, choice);//user input for what account they want to make

				if (choice == "1") {//creates a new current account
					bool currentExists = false;
					for (auto i = 0; i < allAccounts.size(); i++) {
						if (typeid(*allAccounts[i]) == typeid(Current)) {//checks if there is already a current account
							currentExists = true;
							cout << "Can only have one current account. Returning to menu " << endl;
						}
					}
					if (!currentExists) {
						allAccounts.push_back(new Current());//adds a new current account to the vector
						cout << "opened an an account of type: " << typeid(*allAccounts[allAccounts.size() - 1]).name() << endl;
						cout << "length of allAccounts = " << allAccounts.size() << endl;
						allAccounts[allAccounts.size() - 1]->balance = 15;
					}

				}
				else if (choice == "2") {//creates a new savings account
					allAccounts.push_back(new Savings());//adds savings account to vector
					cout << "opened an an account of type: " << typeid(*allAccounts[allAccounts.size() - 1]).name() << endl;
					allAccounts[allAccounts.size()-1]->balance = 20;//tests balance and transfer

				}
				else if (choice == "3") {
					cout << "Picked ISA" << endl;
				}
				else {
					cout << "Invalid number! Returning to menu " << endl; //debug 
				}
			}
			else {
				cout << "You can only have 5 accounts " << endl;//prevents user from having more than 5 accounts
			}	
		}
		else if (command.compare("view") == 0)
		{
			// display an account according to an index (starting from 1)
			// alternatively, display all accounts if no index is provided
			//will need to be debugged to check if index is numerical or not
			try {
				int viewChoice;
				cout << "Press 'ENTER to see all accounts, otherwise press a number between 0-4 to see a specific account" << endl;
				cin >> viewChoice;
				if (cin.fail()) {//for some reason 'cin' becomes ambiguous in a try block so cannot do it
					throw logic_error("Invalid data type inputted");
				}
				if (viewChoice > allAccounts.size() - 1) {
					throw out_of_range("Exceeded number of accounts");
				}
				if (viewChoice > numeric_limits<int>::max() || viewChoice < numeric_limits<int>::min()) {
					throw flowException();
				}
				cout << *allAccounts[viewChoice] << endl;//defaults to 0 
			
			}
			catch (logic_error e) {
				cout << e.what() << endl;
			}
			catch (out_of_range e) {
				cout << e.what() << endl;
			}
			catch (flowException e) {
				cout << e.what() << endl;
			}

		}
		else if (command.compare("withdraw") == 0)
		{
			// allow user to withdraw funds from an account
			//get float input. debug incase of non-float input
			int indexChoice;
			double sum;//check if value exceeds the max value
			try {//exception handling block
				//cout << "Which of you accounts would you like to deposit to" << endl;
				//cout << "Once you have selected an account, enter the amount of money you would like to deposit " << endl;
				//cin >> indexChoice;
				//if (cin.fail()) {//throws an exception if input for indexChoice is not an int
				//	cout << "Failure" << endl;
				//	throw logic_error("Invalid input");
				//}
				//if (indexChoice >= allAccounts.size()) {//throws an exception if indexChoice is greater than total accounts
				//	throw out_of_range("You don't have that many accounts");
				//}
				//if (indexChoice > numeric_limits<int>::max() || indexChoice < numeric_limits<int>::min()) {
				//	throw flowException();
				//}
				cout << endl << "Enter sum" << endl;

				cin >> sum;//does the same as above, but double data type

				if (cin.fail()) {
					cout << "Failure" << endl;
					throw logic_error("Invalid input");
				}
				if (sum > numeric_limits<double>::max() || sum < numeric_limits<double>::min()) {//checks if input violates max/min values
					throw flowException();
				}
				allAccounts[allAccounts.size()-1]->deposit(sum);
			}
			catch (logic_error e) {
				cout << e.what() << endl;
			}
			catch (out_of_range e) {
				cout << e.what() << endl;
			}
			catch (flowException e) {
				cout << e.what() << endl;
			}
			
		}
		else if (command.compare("deposit") == 0)
		{
			// allow user to deposit funds into an account
			int indexChoice;
			double sum;
			try {//exception handling block
				//commented out for lecturer

				//cout << "Which of you accounts would you like to deposit to" << endl;

				//cin >> indexChoice;

				//if (cin.fail()) {
				//	cout << "Failure " << endl;
				//	throw logic_error("Invalid input");
				//}
				//if (indexChoice >= allAccounts.size()) {
				//	throw out_of_range("You don't have that many accounts");
				//}
				//if (indexChoice > numeric_limits<int>::max() || indexChoice < numeric_limits<int>::min()) {
				//	throw flowException();
				//}

				cout << "Now the sum " << endl;

				cin >> sum;

				if (cin.fail()) {
					cout << "Failure " << endl;
					throw logic_error("Invalid input");
				}
				if (sum > numeric_limits<double>::max() || sum < numeric_limits<double>::min()) {
					throw flowException();
				}

				allAccounts[allAccounts.size()-1]->deposit(sum);//makes a deposit of inputed sum in account of user's choice
			}
			catch (logic_error e) {
				cout << "Logic error occured" << endl;
				cout << e.what() << endl;
				break;//could use a default
			}
			catch (out_of_range e) {
				cout << "Out of range error occured" << endl;
				cout << e.what() << endl;
				break;//could use a default
			}
			catch (flowException e) {
				cout << e.what() << endl;
			}
		}
		else if (command.compare("transfer") == 0)
		{
			// allow user to transfer funds between accounts
			// i.e., a withdrawal followed by a deposit!
			//use the view function
			
			int indexChoice1;
			int indexChoice2;

			try {

				cout << "Which account would you like to transfer " << endl;
				cin >> indexChoice1;

				if (cin.fail()) {
					cout << "Failure " << endl;
					throw logic_error("Invalid source ");
				}
				if (indexChoice1 >= allAccounts.size()) {
					throw out_of_range("You don't have that many accounts");
				}
				if (indexChoice1 > numeric_limits<int>::max() || indexChoice1 < numeric_limits<int>::min()) {
					throw flowException();
				}
			}
			catch (logic_error e) {
				cout << e.what() << endl << "Exiting " << endl;
				break;
			}
			catch (out_of_range e) {
				cout << e.what() << endl << "Exiting " << endl;
			}

			try {
				//commented out until questioned lecturer
				// 
				//cout << "What index would you like to transfer to " << endl;
				//cin >> indexChoice2;

				//if (cin.fail()) {
				//	cout << "Failure " << endl;
				//	throw logic_error("Invalid destination ");
				//}
				//if (indexChoice2 >= allAccounts.size()) {
				//	throw out_of_range("You don't have that many accounts");
				//}
				//if (indexChoice2 > numeric_limits<int>::max() || indexChoice2 < numeric_limits<int>::min()) {
				//	throw flowException();
				//}
				//transfer process
				cout << "src balance: " << allAccounts[indexChoice1]->balance << "destination balance: " << allAccounts[allAccounts.size()-1]->balance << endl;//testing
				double sum = allAccounts[indexChoice1]->balance;//temporary storage for 1st choice balance
				allAccounts[indexChoice1]->withdraw(allAccounts[indexChoice1]->balance);//takes out entire balance of first account
				allAccounts[allAccounts.size() - 1]->deposit(sum);//deposits entire balance of account 1 into account 2
				cout << "src balance: " << allAccounts[indexChoice1]->balance << "destination balance: " << allAccounts[allAccounts.size() - 1]->balance << endl;//testing
			}
			catch (logic_error e) {
				cout << "Gone wrong with logic" << endl;
				cout << e.what() << endl << "Exiting " << endl;
				break;
			}
			catch (out_of_range e) {
				cout << "Gone wrong with range" << endl;
				cout << e.what() << endl << "Exiting " << endl;
			}
			catch (flowException e) {
				cout << e.what() << endl;
			}
		}
		else if (command.compare("project") == 0)
		{
			// compute compound interest t years into the future
			int indexChoice;
			int years;
			try {
				//commented out in case of lecturer issues

				//cout << "Which of you accounts would you like to project" << endl;
				//cin >> indexChoice;//user input for getting the user's index of choice

				//if (cin.fail()) {//can this debug be placed into function alongside the above input
				//	cout << "Failure " << endl;
				//	throw logic_error("Invalid input");
				//}
				//if (indexChoice >= allAccounts.size()) {
				//	throw out_of_range("You don't have that many accounts");
				//}
				//if (typeid(*allAccounts[indexChoice]) != typeid(Savings)) {//checks if user account choice is savings type
				//	throw bad_typeid();
				//}
				//if (indexChoice > numeric_limits<int>::max() || indexChoice < numeric_limits<int>::min()) {
				//	throw flowException();
				//}


				cout << "Now the number of years into the future " << endl;
				cin >> years;

				if (cin.fail()) {
					cout << "Failure " << endl;
					throw logic_error("Invalid input");
				}
				if (typeid(*allAccounts[allAccounts.size() - 1]) != typeid(Savings)) {
					throw bad_typeid();
				}
				if (years > numeric_limits<int>::max() || years < numeric_limits<int>::min()) {
					throw flowException();
				}

				cout << "Projected balance : " << ((Savings*)allAccounts[allAccounts.size()-1])->computeInterest(years);//down casts to derived class and activates computeInterest function

			}
			catch (logic_error e) {
				cout << e.what() << endl;
				break;//could use a default
			}
			catch (out_of_range e) {
				cout << e.what() << endl;
				break;//could use a default
			}
			catch (bad_typeid) {
				cout << "Was not a Savings Account " << endl;
				break;
			}
			catch (flowException e) {
				cout << e.what() << endl;
			}
			
		}
		else if (command.compare("search"))//(STRETCH) Allows user to search for a particular transaction that occured in an account's history
		{
			int valueToSearch = 0;
			int indexChoice = 0;
			try {

				//cout << "Which account would you like to search in. Please enter the index" << endl;
				//cin >> indexChoice;//what account does user want to use

				//if (cin.fail()) {//can this debug be placed into function alongside the above input
				//	cout << "Failure " << endl;
				//	throw logic_error("Invalid input");
				//}
				//if (indexChoice >= allAccounts.size()) {
				//	throw out_of_range("You don't have that many accounts");
				//}
				//if (indexChoice > numeric_limits<int>::max() || indexChoice < numeric_limits<int>::min()) {
				//	throw flowException();
				//}

				cout << "What value would you like to search for" << endl;
				cin >> valueToSearch;// what does user want to search for

				if (cin.fail()) {//can this debug be placed into function alongside the above input
					cout << "Failure " << endl;
					throw logic_error("Invalid input");
				}
				if (valueToSearch > numeric_limits<int>::max() || valueToSearch < numeric_limits<int>::min()) {
					throw flowException();
				}

				allAccounts[indexChoice]->_history->searchAmount(valueToSearch);//activates search function
			}
			catch (logic_error e) {
				cout << e.what() << endl;
			}
			catch (out_of_range e) {
				cout << e.what() << endl;
			}
			catch (flowException e) {
				cout << e.what() << endl;
			}

		}

	}

	std::cout << "Press any key to quit...";
	std::getchar();

	for (Account* ac : allAccounts) {// deletes data in allAccounts to prevent memory leaks
		delete ac;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file