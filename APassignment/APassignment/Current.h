#pragma once
#include <iostream>
#include "Account.h"
using namespace std;


class Current : public Account {//inherits from account
	public:

		Current() {

		}
		virtual ~Current() {

		}

		void deposit(float sum) override {//deposit function
			balance += sum;
			_history->Insert(sum, "deposit");//deposit transaction
		}

		void withdraw(float sum) override {//withdraw function
			if (sum > balance || sum > overdraft) {//checks
				cout << "Cannot withdraw above the balance or overdraft limit " << endl;
				return;
			}
			balance -= sum;
			_history->Insert(sum, "withdraw");//withdraw transaction
		}

		void toString() override {
			cout << "Overriden" << endl; //needs to work
		}
		//guards
		void setOverdraft(unsigned int value) {
			overdraft = value;
		}
		
		int getOverdraft() {
			return overdraft;
		}
		friend ostream& operator<<(ostream& os, const Current ac) {//overloads output operator
			if (ac.balance != NULL) {
				cout << "balance : " << ac.balance << endl;
			}
			return os;
		}
	private:
		unsigned int overdraft = 500;


};
