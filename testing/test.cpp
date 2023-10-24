#include <iostream>
#include <string>
#include <conio.h>      // _getch()
#include <windows.h>    // system("cls")
#include <fstream>      // file handing
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <sstream>
#include<limits>
using namespace std;

int main() {
    string str;
    for (int i=0; i<5; i++) {
        getline(cin, str);
        cout << str;
    }
}