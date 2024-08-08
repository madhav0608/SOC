#include <bits/stdc++.h>
using namespace std;

class BankAccount{
private:
    double balance = 0;

public:

    BankAccount(){

    }

    BankAccount(double initial_balance){
        balance = initial_balance;
    }

    void deposit(double amount){
        if(amount < 0){
            cout << "Error. Amount is negative \n";
        }else{
            balance += amount;
            cout << "Deposit successful. Current balance : " << balance << endl;
        }
    }

    void withdraw(double amount){
        if(balance < amount){
            cout << "Error. Insufficient balance \n";
        }else if(amount < 0){
            cout << "Error. Amount is negative \n";
        }else{
            balance -= amount;
            cout << "Withdrawal successful. Remaining balance : " << balance << endl;
        }

    }

    double getBalance(){
        return balance;
    }

};

int main(){
    BankAccount primary;
    primary.deposit(-1000);
    primary.deposit(1000);
    primary.withdraw(1500);
    primary.withdraw(500);
    cout << primary.getBalance() << endl;
}