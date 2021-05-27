#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

#include "menu.h"
#include "tutorial.h"

void printlogo(){

    string line1 =  " ____________________________________________________________________________________________________________________";
    string line2 =  "|  ________________________________________________________________________________________________________________  | ";
    string line3 =    "| |      ||||||     ||||      ||    ||||||  ||||||  ||      ||||||  ||||||  ||  ||  ||||||  ||||||      ||||||     | |";
    string line4 =  "| |      |||||||||| ||  ||  ||  ||    ||      ||    ||      ||      ||      ||  ||    ||    ||  ||  ||||||||||     | |";
    string line5 =    "| |  ____||||||____ ||||    ||||||    ||      ||    ||      |||||   ||||||  ||||||    ||    ||||||  ____||||||____ | |";
    string line6 =    "| |  \\            / ||  ||  ||  ||    ||      ||    ||      ||          ||  ||  ||    ||    ||      \\            / | |";
    string line7 =    "| |   \\__________/  ||||    ||  ||    ||      ||    ||||||  ||||||  ||||||  ||  ||  ||||||  ||       \\__________/  | |";
    string line8 =    "| |________________________________________________________________________________________________________________| |";
    string line9 =    "|____________________________________________________________________________________________________________________|";

    //system("cls");
    cout << endl << endl;
    cout << line1 << endl;
    cout << line2 << endl;
    cout << line3 << endl;
    cout << line4 << endl;
    cout << line5 << endl;
    cout << line6 << endl;
    cout << line7 << endl;
    cout << line8 << endl;
    cout << line9 << endl;

}

//to get a input line from player without function of cin.ignore(), By Horace
string MyGetline()
{
    string result;

    while (!getline(cin, result) || result.empty());

    return result;
}
char MenuCmd()
{
    char cmd;
    bool iscmd = true;
    printmenu(!iscmd);
    cin >> cmd;

  while(iscmd)
  {
      if (cmd == '1') {
          iscmd = false;
          //start the game
          //add function name for the game
      }else if (cmd == '2'){
          iscmd = false;
          //resume the game
          //file input and output?
      }else if (cmd == '3'){
          iscmd = false;
          //switch to tutorial video
          //add function name for the tutorial
      }else if (cmd == '4'){
          iscmd = false;
      }else{
          printmenu(iscmd);
          cin >> cmd;
      }

  }
  return cmd;

//     while(iscmd)
//     {
//         switch (cmd) {
//           case '1':
//             //system("cls");
//             //start the game
//                 NewGame();
//                 printmenu(!iscmd);
//                 cin >> cmd;
//             break;
//
//           case '2':
//             //system("cls");
//             //resume the game
//                 ResumeGame();
//                 printmenu(!iscmd);
//                 cin >> cmd;
//             break;
//
//           case '3':
//             //system("cls");
//             //switch to tutorial
//                 PrintTutorial();
//                 printmenu(!iscmd);
//                 cin >> cmd;
//             break;
//
//           case '4':
//             iscmd = false;
//             break;
//
//           default:
//               cout << "default:" << cmd << endl;
//                 printmenu(iscmd);
//                 cin >> cmd;
//         }
//
//     }
// return cmd;
}

void printmenu(bool bprtagain)
{

    printlogo();
    cout << setw(64) << "1. NEW GAME" << endl;
    cout << setw(67) << "2. RESUME GAME" << endl;
    cout << setw(64) << "3. TUTORIAL" << endl;
    cout << setw(60) << "4. QUIT" << endl << endl;
    if (bprtagain == false)
        cout << setw(55) <<"> ";
    else
        cout << "Please try again: " << setw(37) <<"> ";

}
