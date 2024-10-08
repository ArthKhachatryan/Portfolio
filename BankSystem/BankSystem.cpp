#include <iostream>
#include <vector>
using namespace std;

class Account {

public:
    string accNum;

    Account(string accNum, string name, double balance) : accNum(accNum), name(name), balance(balance) {}

    void deposit(double depMoney) {
        balance += depMoney;
        cout << "The deposit of $" << depMoney << " has been completed."<< endl;
    }

    void withdraw(double withdMoney) {
        if (withdMoney > balance) {
            cout << "Insufficient funds!" << endl;
        } else {
            balance -= withdMoney;
            cout << "The withdrawal of $" << withdMoney << " has been completed." << endl;
        }
    }

    void showBalance() {
        cout << "Account: " << accNum << ", Name: " << name << ", Balance: " << balance << endl;
    }

    private:
    string name;
    double balance;
};

class Bank {
private:
    vector<Account> accounts;

public:
    void createAccount(string accNum, string name, double deposit) {
        accounts.emplace_back(accNum, name, deposit);
        cout << "Account created: " << accNum << endl;
    }

    Account* findAccount(const string& accNum) {
        for (Account& account : accounts) {
            if (account.accNum == accNum) {
                return &account;
            }
        }
        cout << "Account not found!" << endl;
        return nullptr;
    }
};

int main() {
	Bank BestBank;
	int option;
	string accNum, name;
	double money;

	do {
		cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Exit\nChoose an option: ";
		cin >> option;

		if (option == 1) {
			cout << "Enter account number: ";
			cin >> accNum;
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter deposit: ";
			cin >> money;
			BestBank.createAccount(accNum, name, money);
		} else if (option == 2) {
			cout << "Enter account number: ";
			cin >> accNum;
			cout << "Enter amount to deposit: ";
			cin >> money;
			if (Account* acc = BestBank.findAccount(accNum)) {
				acc->deposit(money);
			}
		} else if (option == 3) {
			cout << "Enter account number: ";
			cin >> accNum;
			cout << "Enter amount to withdraw: ";
			cin >> money;
			if (Account* acc = BestBank.findAccount(accNum)) {
				acc->withdraw(money);
			}
		} else if (option == 4) {
			cout << "Enter account number: ";
			cin >> accNum;
			if (Account* acc = BestBank.findAccount(accNum)) {
				acc->showBalance();
			}
		} else if (option == 5) {
			cout << "Exiting..." << endl;
		} else {
			cout << "Invalid input!" << endl;
		}

	} while (option != 5);

	return 0;
}
