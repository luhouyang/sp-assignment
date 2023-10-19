#include <iostream>
#include <string.h>
#include <conio.h>      // _getch()
#include <windows.h>    // system("cls")
#include <fstream>      // file handing
#include <stdlib.h>
#include <cstdlib>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77 
#define ENTER '\r'

using namespace std;

// Utils
#pragma region Utils
void printPadding() {
    cout << "\n\n#############################################\n\n";
}

int menuHorizontal() {
    int selectIdx = 1;      //Keeps track of which option is selected.
    int numChoices = 2;     //The number of choices we have.
    bool selecting = true;  //True if we are still waiting for the user to press enter.

    string mssg[2] = {"<---prev", "next--->"};
    cout << "\t" << mssg[0] << "\t\t";
    cout << "\033[1;36m" << mssg[1] << "\033[1;0m";

    char32_t key; //Store key outside of loop for efficiency.
    while (selecting) { //As long as we are selecting...
        switch ((key = _getch())) { //Check value of the last inputed character.
            case KEY_LEFT:
                if (selectIdx > 0) { //Dont decrement if we are at the first option.
                    --selectIdx;
                    cout << "\r";
                    cout << "\t" << "\033[1;36m" << mssg[0] << "\t\t";
                    cout << "\033[1;0m" << mssg[1]; 
                }
                break;
            case KEY_RIGHT:
                if (selectIdx < numChoices - 1) { //Dont increment if we are at the last option.
                    ++selectIdx;
                    cout << "\r";
                    cout << "\t" << "\033[1;0m" << mssg[0] << "\t\t";
                    cout << "\033[1;36m" << mssg[1] << "\033[1;0m"; 
                }
                break;
            case ENTER:
                //We are done selecting the option.
                selecting = false;
                break;
            default: break;
        }
    }
    return selectIdx;
}

int menuLinear(string choices[], int size) {
    bool selecting = true;
    int selectIdx = 0;
    int prevIdx = 0;
    const int numChoices = size;
    string* colour = new string[numChoices];
    
    for (int i=0; i<numChoices; i++) {
        colour[i] = "\033[1;0m";
    }
    colour[selectIdx] = "\033[1;36m";
    printPadding();
    for (int i=0; i<size; i++) {
        cout << colour[i] << choices[i] << "\n";
    }
    printPadding();

    char32_t key;
    while (selecting) {
        switch ((key = _getch())) {
            case KEY_UP: 
                if (selectIdx > 0) {
                    --selectIdx;
                    colour[prevIdx] = "\033[1;0m";
                    colour[selectIdx] = "\033[1;36m";
                    prevIdx = selectIdx;
                    system("cls");
                    printPadding();
                    for (int i=0; i<size; i++) {
                        cout << colour[i] << choices[i] << "\n";
                    }
                    cout << "\033[1;0m";
                    printPadding();
                }
                break;
            case KEY_DOWN:
                if (selectIdx < (size-1)) {
                    ++selectIdx;
                    colour[prevIdx] = "\033[1;0m";
                    colour[selectIdx] = "\033[1;36m";
                    prevIdx = selectIdx;
                    system("cls");
                    printPadding();
                    for (int i=0; i<size; i++) {
                        cout << colour[i] << choices[i] << "\n";
                    }
                    cout << "\033[1;0m";
                    printPadding();
                }
                break;
            case ENTER:
                cout << "\033[1;0m";
                selecting = false;
                break;
            default: break;
        }
    }
    delete[] colour;
    return selectIdx;
}
#pragma endregion Utils

// User
#pragma region User
class User {
    private:
        string userName;
        string password;
        string secureQuestionAns;
    public:
        bool loggedIn = false;
        int userMenuIdx = 0;

        void menu();
        void insert(string storeData);
        void login();
        void signUp();
        void forgotPass();
};

void User::menu() {
    system("cls");
    string userAuthSelection[] = {"\tLogin\t\t\t--1--", "\tSign Up\t\t\t--2--", "\tForgot Password\t\t--3--", "\tExit\t\t\t--4--"};
    userMenuIdx = menuLinear(userAuthSelection, 4);
    switch (userMenuIdx) {
            case 0:
                login();
                break;
            case 1:
                signUp();
                break;
            case 2:
                forgotPass();
                break;
            case 3:
                exit(0);
                break;
            default:
                cout << "\t\tInvalid Selection";
        }
}

void User::insert(string storeData) {
    system("cls");
    cout << storeData;
    fstream file;
    file.open("userData.txt", ios::app | ios::out);
    file << storeData << "\n";
    file.close();
}

void User::login() {
    system("cls");
    cout << "Enter user name: ";
    cin >> userName;
    cout << "Enter password: ";
    cin >> password;
}

void User::signUp() {
    system("cls");
    cout << "Enter user name: ";
    cin >> userName;
    cout << "Enter password: ";
    cin >> password;
    cout << "What is your favourite colour?: ";
    cin >> secureQuestionAns;
    insert(userName + "," + password + "," + secureQuestionAns);
}

void User::forgotPass() {
    system("cls");
    cout << "Enter user name: ";
    cin >> userName;
    cout << "What is your favourite colour?: ";
    cin >> secureQuestionAns;
}
#pragma endregion User

// main
int main(){
    User user;
    while (!user.loggedIn) {
        user.menu();
    }

    string shopMenuSelection[] = {"\tView Records\t\t--1--", "\tSell Item\t\t--2--", "\tBuy Item\t\t--3--", "\tLogout\t\t\t--4--"};
    int shopMenuIdx = menuLinear(shopMenuSelection, 4);
    cout << "Index Menu selected: " << shopMenuIdx;

    printPadding();
    cout << "\t\t--------------\n";
    cout << "\t\tMonthly Report\n";
    cout << "\t\tMoney: 123456\n";
    cout << "\t\tStuff: Fruit?\n";
    cout << "\t\t--------------\n";

    int arrowIdx = menuHorizontal();
    printPadding();
    cout << "Index selected: " << arrowIdx;

    return 0;
}

