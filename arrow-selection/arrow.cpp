#include <iostream>
#include <conio.h>//For _getch().


//https://stackoverflow.com/questions/24708700/c-detect-when-user-presses-arrow-key
#define KEY_LEFT 75       //Left arrow character
#define KEY_RIGHT 77    //Right arrow character
#define KEY_ENTER '\r'//Enter key charatcer

/*
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
*/

using namespace std;

int main(){
    int selected = 1;    //Keeps track of which option is selected.
    int numChoices = 2; //The number of choices we have.
    bool selecting = true;//True if we are still waiting for the user to press enter.

    //Output options
    cout << "\t\t--------------\n";
    cout << "\t\tMonthly Report\n";
    cout << "\t\tMoney: 123456\n";
    cout << "\t\tStuff: Fruit?\n";
    cout << "\t\t--------------\n";

    string mssg[2] = {"<---prev", "next--->"};
    cout << "\t" << mssg[0] << "\t\t";
    cout << "\033[1;36m" << mssg[1] << "\033[1;0m";

    char32_t c; //Store c outside of loop for efficiency.
    while (selecting) { //As long as we are selecting...
        switch ((c = _getch())) { //Check value of the last inputed character.
            case KEY_LEFT:
                if (selected > 0) { //Dont decrement if we are at the first option.
                    --selected;
                    cout << "\r";
                    cout << "\t" << "\033[1;36m" << mssg[0] << "\t\t";
                    cout << "\033[1;0m" << mssg[1]; 
                }
                break;
            case KEY_RIGHT:
                if (selected < numChoices - 1) { //Dont increment if we are at the last option.
                    ++selected;
                    cout << "\r";
                    cout << "\t" << "\033[1;0m" << mssg[0] << "\t\t";
                    cout << "\033[1;36m" << mssg[1] << "\033[1;0m"; 
                }
                break;
            case KEY_ENTER:
                //We are done selecting the option.
                selecting = false;
                break;
            default: break;
        }
    }
    //Lets us know what we ended up selecting.
    cout << "\n\t\t" << "Selected " << selected << '\n';
    return 0;
}