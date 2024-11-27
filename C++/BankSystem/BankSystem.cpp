#include <iostream>
#include <vector>
using namespace std;

class Account {
public:
    string accNum;

    Account(string accNum, string name, double balance) : accNum(accNum), name(name), balance(balance) {}

    void deposit(double depMoney) {
        balance += depMoney;
        cout << "The deposit of $" << depMoney << " has been completed." << endl;
    }

    void withdraw(double withdMoney) {
        if (withdMoney > balance) {
            cout << "Insufficient funds!" << endl;
        } else {
            balance -= withdMoney;
            cout << "The withdrawal of $" << withdMoney << " has been completed." << endl;
        }
    }

    void showBalance() const {
        cout << "Account: " << accNum << ", Name: " << name << ", Balance: $" << balance << endl;
    }

    string getAccountNumber() const {
        return accNum;
    }

    double getBalance() const {
        return balance;
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

    void deleteAccount(const string& accNum) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (it->getAccountNumber() == accNum) {
                accounts.erase(it);
                cout << "Account " << accNum << " has been deleted." << endl;
                return;
            }
        }
        cout << "Account not found!" << endl;
    }

    void transferMoney(const string& fromAccNum, const string& toAccNum, double amount) {
        Account* fromAcc = findAccount(fromAccNum);
        Account* toAcc = findAccount(toAccNum);

        if (fromAcc && toAcc) {
            if (fromAcc->getBalance() >= amount) {
                fromAcc->withdraw(amount);  // Withdraw from the source account
                toAcc->deposit(amount);     // Deposit to the destination account
                cout << "Transfer of $" << amount << " from " << fromAccNum << " to " << toAccNum << " completed." << endl;
            } else {
                cout << "Insufficient funds for transfer!" << endl;
            }
        }
    }
};

int main() {
    Bank BestBank;
    int option;
    string accNum, name, fromAccNum, toAccNum;
    double money;

    do {
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Delete Account\n6. Transfer Money\n7. Exit\nChoose an option: ";
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
            cout << "Enter account number to delete: ";
            cin >> accNum;
            BestBank.deleteAccount(accNum);
        } else if (option == 6) {
            cout << "Enter source account number: ";
            cin >> fromAccNum;
            cout << "Enter destination account number: ";
            cin >> toAccNum;
            cout << "Enter amount to transfer: ";
            cin >> money;
            BestBank.transferMoney(fromAccNum, toAccNum, money);
        } else if (option == 7) {
            cout << "Exiting..." << endl;
        } else {
            cout << "Invalid input!" << endl;
        }

    } while (option != 7);

    return 0;
}
