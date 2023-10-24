#include <iostream>
#include <string>
#include <algorithm>    // replace()
#include <conio.h>      // _getch()
#include <windows.h>    // system("cls")
#include <fstream>      // file handing
#include <stdlib.h>
#include <cstdlib>
#include <vector>       // vector<string>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77 
#define ENTER '\r'

using namespace std;

/* Utils Documentation
printPadding()                                      -> "\n\n#############################################\n\n"
space2underscore()                                  -> makes life easier, no need to deal with spaces
insert(string storeData, string filePath)
singleChoice(string headerMessage,string colourText)-> show one message, with one choice
menuHorizontal()                                    -> "<---prev            next--->" :: use left/right arrows
menuLinear(string headerMessage, string choices[], int size)
                                                    ->  headerMessage: about page (e.g. "\tWelcome to the Login Page")
                                                    ->  choices[]: what you can do in menu (e.g. {"\tLogin\t\t\t--1--", "\tSign Up\t\t\t--2--", "\tForgot Password\t\t--3--", "\tExit\t\t\t--4--"})
                                                    ->  size: length of choices[]
*/

// Utils
#pragma region Utils
void printPadding() {
    cout << "\n\n#############################################\n\n";
}

string space2underscore(string text)
{
    replace(text.begin(), text.end(), ' ', '_');
    return text;
}

void insert(string storeData, string filePath) {
    system("cls");
    cout << storeData;
    fstream file;
    file.open(filePath, ios::app | ios::out);
    file << storeData << "\n";
    file.close();
}

void singleChoice(string headerMessage, string colourText) {
    bool selecting = true;
    printPadding();
    cout << headerMessage << "\t\t\033[1;36m" << colourText << "\033[1;0m";
    printPadding();
    cout << "press \"Enter\" to select";
    char32_t key;
    while (selecting) {
        switch ((key = _getch())) {
            case ENTER:
                selecting = false;
                break;
            default: break;
        }
    }
}

int menuHorizontal() {
    int selectIdx = 1;      //Keeps track of which option is selected.
    int numChoices = 2;     //The number of choices we have.
    bool selecting = true;  //True if we are still waiting for the user to press enter.

    string mssg[2] = {"<---prev", "next--->"};
    cout << "use \"Left\" & \"Right\" arrow key to navigate\n";
    cout << "press \"Enter\" to select\n";
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

int menuLinear(string headerMessage, string choices[], int size) {
    bool selecting = true;
    int selectIdx = 0;
    int prevIdx = 0;
    const int numChoices = size;
    string* colour = new string[numChoices];
    
    for (int i=0; i<numChoices; i++) {
        colour[i] = "\033[1;0m";
    }
    colour[selectIdx] = "\033[1;36m";

    // output
    printPadding();
    cout << headerMessage;
    printPadding();
    for (int i=0; i<size; i++) {
        cout << colour[i] << choices[i] << "\n";
    }
    printPadding();
    cout << "use \"Up\" & \"Down\" arrow key to navigate\n";
    cout << "press \"Enter\" to select\n";

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
                    cout << headerMessage;
                    printPadding();
                    for (int i=0; i<size; i++) {
                        cout << colour[i] << choices[i] << "\n";
                    }
                    cout << "\033[1;0m";
                    printPadding();
                    cout << "use \"Up\" & \"Down\" arrow key to navigate\n";
                    cout << "press \"Enter\" to select\n";
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
                    cout << headerMessage;
                    printPadding();
                    for (int i=0; i<size; i++) {
                        cout << colour[i] << choices[i] << "\n";
                    }
                    cout << "\033[1;0m";
                    printPadding();
                    cout << "use \"Up\" & \"Down\" arrow key to navigate\n";
                    cout << "press \"Enter\" to select\n";
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
typedef struct 
{
    string userName;
    string password;
    string secureQuestionAns;
} USERMODEL;

class User {
    private:
        USERMODEL userModel;
        int userMenuIdx = 0;
    public:
        bool loggedIn = false;
        string userID;
        void menu();
        void login();
        void signUp();
        void forgotPass();
};

void User::menu() {
    system("cls");
    string headerMessage = "\tWelcome to the Login Page";
    string userAuthSelection[] = {"\tLogin\t\t\t--1--", "\tSign Up\t\t\t--2--", "\tForgot Password\t\t--3--", "\tExit\t\t\t--4--"};
    userMenuIdx = menuLinear(headerMessage, userAuthSelection, 4);
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

void User::login() {
    // reset info
    userModel.userName = "";
    userModel.password = "";

    // declare variables before clearing screen
    bool userExist = false;
    string line;
    vector<string> row;
    fstream file;
    file.open("userData.txt");

    // input
    system("cls");
    cout << "Enter user name: ";
    getline(cin, userModel.userName);
    cout << "Enter password: ";
    getline(cin, userModel.password);

    userModel.userName = space2underscore(userModel.userName);
    userModel.password = space2underscore(userModel.password);
    
    // check each line in file
    while(file>>line && !loggedIn) {
        row.clear();
        char* s = new char[line.length() + 1];
        strcpy(s, line.c_str());
        char * p;
        p = strtok(s, ",");
        while (p != NULL) {
            row.push_back(p);
            //cout << p << endl;
            p = strtok(NULL, ",");
        }
        if (row[1] == userModel.userName) {
            userExist = true;
            if (row[2] == userModel.password) {
                userID = row[0];
                loggedIn = true;
                file.close();
                break;
            } else {
                file.close();
                singleChoice("\t\tWrong Password\n\n", "Return");
                break;
            }
        }
    }
    if (!userExist) {
        singleChoice("\t\tInvalid User Name\n\n", "Return");
    }
    file.close();
}

void User::signUp() {
    // reset info
    userModel.userName = "";
    userModel.password = "";

    // declare variables before clearing screen
    bool userExist = false;
    int newUserIdx = 0;
    string line;
    vector<string> row;
    fstream file;
    file.open("userData.txt");

    // input
    system("cls");
    cout << "Enter user name: ";
    getline(cin, userModel.userName);
    cout << "Enter password: ";
    getline(cin, userModel.password);
    cout << "What is your favourite colour?: ";
    getline(cin, userModel.secureQuestionAns);

    userModel.userName = space2underscore(userModel.userName);
    userModel.password = space2underscore(userModel.password);
    userModel.secureQuestionAns = space2underscore(userModel.secureQuestionAns);

    // check each line in file
    while(file>>line && !loggedIn) {
        newUserIdx++;
        row.clear();
        char* s = new char[line.length() + 1];
        strcpy(s, line.c_str());
        char * p;
        p = strtok(s, ",");
        while (p != NULL) {
            row.push_back(p);
            //cout << p << endl;
            p = strtok(NULL, ",");
        }
        if (row[1] == userModel.userName) {
            userExist = true;
            break;
        }
    }
    if (userExist) {
        singleChoice("\t\tUser name already exist\n\n", "Return");
        file.close();
    } else {
        file.close();
        insert(to_string(newUserIdx) + "," + userModel.userName + "," + userModel.password + "," + userModel.secureQuestionAns, "userData.txt");
        singleChoice("\t\tUser added\n\n", "Return");
    }
}

void User::forgotPass() {
    // reset info
    userModel.userName = "";
    userModel.password = "";

    // declare variables before clearing screen
    bool userExist = false;
    string line;
    vector<string> row;
    fstream file;
    file.open("userData.txt");

    // input
    system("cls");
    cout << "Enter user name: ";
    getline(cin, userModel.userName);
    cout << "What is your favourite colour?: ";
    getline(cin, userModel.secureQuestionAns);

    userModel.userName = space2underscore(userModel.userName);
    userModel.secureQuestionAns = space2underscore(userModel.secureQuestionAns);

    ofstream fout;
    fout.open("userDataTemp.txt");

    // check each line in file
    while(file>>line && !loggedIn) {
        row.clear();
        char* s = new char[line.length() + 1];
        strcpy(s, line.c_str());
        char * p;
        p = strtok(s, ",");
        while (p != NULL) {
            row.push_back(p);
            //cout << p << endl;
            p = strtok(NULL, ",");
        }
        // check user name
        if (row[1] == userModel.userName) {
            userExist = true;
            // check secure phrase
            if (row[3] == userModel.secureQuestionAns) {
                // get new password
                cout << "Enter new password: ";
                getline(cin, userModel.password);
                userModel.password = space2underscore(userModel.password);
                // write new data to temporary file
                row[2] = userModel.password;
                line = row[0] + "," + row[1] + "," + row[2] + "," + row[3] + "\n";
                fout << line;
            } else {
                // write unchanged data to temporary file
                line += "\n";
                fout << line;
                singleChoice("\t\tWrong Answer\n\n", "Return");
            }
        } else {
            // write unchanged data to temporary file
            line += "\n";
            fout << line;
        }
    }
    if (!userExist) {
        singleChoice("\t\tInvalid User Name\n\n", "Return");
    }
    file.close();
    fout.close();
    // remove old file
    remove("userData.txt");
    rename("userDataTemp.txt", "userData.txt");
}
#pragma endregion User

// App
#pragma region App
typedef struct
{
    double price;
    string productName;
} PRODUCT;

class App {
    private:
        int appMainMenuIdx = 0;
    public:
        bool exitApp = false;
        string userID;
        void menu();
};

void App::menu() {
    system("cls");
    string headerMessage = "\tWelcome to the Main Menu";
    string appMainMenuSelection[] = 
    {
        "\tView Records\t\t--1--", 
        "\tSell Item\t\t--2--", 
        "\tBuy Item\t\t--3--", 
        "\tLogout\t\t\t--4--"
    };
    appMainMenuIdx = menuLinear(headerMessage, appMainMenuSelection, 4);
    switch (appMainMenuIdx) {
            case 0:
                //
                break;
            case 1:
                //
                break;
            case 2:
                //
                break;
            case 3:
                exitApp = true;
                break;
            default:
                cout << "\t\tInvalid Selection";
        }
}
#pragma endregion App

// main
int main(){
    User user;
    App app;
    while (!user.loggedIn) {
        user.menu();
        if (user.loggedIn) {
            app.exitApp = false;
            app.userID = user.userID;   // can use userID locally in app
        }
        while (user.loggedIn) {
            singleChoice("\t\tUser ID: " + app.userID + "\n", "Next");
            app.menu();
            if (app.exitApp) {
                user.loggedIn = false;
            }
        }
    }

    return 0;
}
