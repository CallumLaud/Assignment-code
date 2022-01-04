#pragma once
#include <iostream>
#include  <ctime>
#include "Transaction.h";
using namespace std;

class Account {
public:
	double balance;//holds account balance
	Transaction* _history = new Transaction;//pointer to transactions

	Account() {
		//_history->Insert(50.0f, "deposit");
		//_history->Insert(25.0f);
		//_history->Insert(100.0f);
		//_history->Insert(25.0f);
		//_history->Insert(100.0f);
		//_history->Insert(50.0f);
		//_history->ToString();
		//cout << "Next version: " << endl;
		//_history->deleteNode(25.0f);
		//_history->ToString();
		//delete _history;
	}
	virtual ~Account() {//need to declare virtual destructor as account pointer will be used to id derived classes
		delete _history; //delete pointer to prevent memory leak;
	}

	//abstract functions
	virtual void deposit(float sum) {

	}
	virtual void withdraw(float sum) {

	}
	virtual void toString() {

	}

	Account operator +(const Account& acc) {//override oeprator for adding accounts
		Account newAcc;
		newAcc.balance = this->balance + acc.balance;
		//needs finishing
		return newAcc;
		
	}

	friend ostream& operator<<(ostream& os, const Account ac) {//override operator for output 
		if (ac.balance != NULL) {
			cout << "balance : " << ac.balance << endl;
		}
		return os;
	}
};