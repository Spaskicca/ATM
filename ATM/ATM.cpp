#include <iostream>
#include <map>
#include <string>

using namespace std;

//Initial bancnote quantities 

map <int, int>  atm = {
    {100,79},
    {50,95},
    {20,80},
    {10,115}
};

const int MaxWithdrawalLimit = 800; //maximum withdraw Limit 

//function to display the currennt state of ATM
  
void DisplayATMState () {
    cout << "Curent state of ATM: " << endl;
    for (const auto &  note:atm) {
        cout << "Banknote " << note.first << "Leva:" << note.second << endl;
        
    }
    cout << endl;
}
bool withdrawMoney(int amount) {
    if (amount > MaxWithdrawalLimit) {
        cout << "The request amount exceedes the maximum limit. Please contact your bank " << endl;

        return false;
    }

    map <int, int> temp_atm = atm; //Copy of the current state of the ATM 
    map <int, int> withdraw;

    for (auto it = atm.rbegin(); it != atm.rend(); ++it) {
        int noteValue = it->first;
        int noteCount = temp_atm[noteValue];

        int neededNotes = amount / noteValue;
        int actualNotes = min(neededNotes, noteCount);

        if (actualNotes > 0) {
            withdraw[noteValue] = actualNotes;
            amount -= actualNotes * noteValue;
            temp_atm[noteValue] -= actualNotes;
        }
    }
    if (amount > 0) {
        cout << "Insufficient banknotes to dispense the requested amount." << endl;
        return false;
    }

    // Deduct the withdrawn notes from ATM
    atm = temp_atm;

    cout << "Withdrawal successful. Dispensed banknotes:" << endl;
    for (const auto& note : withdraw) {
        cout << "Banknote " << note.first << " leva: " << note.second << endl;
    }

    DisplayATMState();
    return true;
}
int main() {
    string command;
    while (true) {
        cout << "Enter the amount you want to withdraw or type 'exit' to close: ";
        cin >> command;

        if (command == "exit") {
            break;
        }
        int amount;
        try {
            amount = stoi(command);
            if (amount < 0) {
                cout << "Invalid input. Negative amounts cannot be withdrawn. Please enter a valid amount." << endl;
                continue;
            }
        }
        catch (invalid_argument&) {
            cout << "Invalid input. Please enter a valid amount or 'exit'." << endl;
            continue;
        }
        if (withdrawMoney(amount)) {
            cout << " Did you recive your money? (yes/no):" <<endl;
            string response;
            cin >> response;
            if (response == "yes") {
                cout << "Thank you for using ATM" << endl;
            }
            else {
                cout << "Please contact the bank for assistence" << endl;
            }
        }
    }
    return 0;
}

