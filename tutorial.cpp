#include <iostream>
#include <cstring>
#include <iomanip>
#include "tutorial.h"
using namespace std;

//print tutorial
void PrintTutorial()
{
    string userGrid[10][10], compGrid[10][10];

    cout << "Tutorial:" << endl << endl;
    cout << "Before the start of the game, you can enter the grid size you want to play (6-20). " << endl;
    cout << "The larger the grid size, the higher the difficulty to guess the right coordinates for the ship. " << endl;
    cout << "For demostration, assume the grid size is 10." << endl;

    ContinueTutorial();

    cout << "At the start of the game, you have to place 5 ships onto your grid by entering, " << endl;
    cout << "(1) the x, y coordinates" << endl;
    cout << "(2) the orientation of the ship (h for horizontal and v for vertical)" << endl << endl << endl;
    ShowInitGrid(userGrid);

    cout << endl;
    cout << endl;
    cout << "Please enter the ship Patrol Boat's coordination which has a size of 2, X & Y: " << "0 0" << endl;
    cout << "X = " << 0 << " Y = " << 0 << ", Please select the orientation (h - horizontal, v - vertical): " << "h" << endl;

    ContinueTutorial();

    StoreElements(userGrid, 0, 0, 'h', 2, "P.");
    cout << "After entering, you can see that (0,0) and (1,0) are filled with \"P.\" " << endl << endl;
    ShowGrid(userGrid);

    cout << endl;
    cout << endl;
    cout << "Please enter the ship Destroyer's coordination which has a size of 3, X & Y: " << "1 3" << endl;
    cout << "X = " << 1 << " Y = " << 3 << ", Please select the orientation (h - horizontal, v - vertical): " << "v" << endl;

    ContinueTutorial();

    cout << "After entering, you can see that (1,3), (1,4) and (1,5) are filled with \"D.\" " << endl << endl;
    StoreElements(userGrid, 1, 3, 'v', 3, "D.");
    ShowGrid(userGrid);

    ContinueTutorial();

    cout << "The remaining 3 ships are:" << endl;
    cout << "(1) Submarine of size 4, showed by \'S.\'. <-- entered: X & Y coordinates(4,0) and orientation(h)" << endl;
    cout << "(2) BattleShip of size 4, showed by \'B.\' <-- entered: X & Y coordinates(5,3) and orientation(v)" << endl;
    cout << "(3) Carrier of size 5, showed by \'C.\' <-- entered: X & Y coordinates(6,3) and orientation(v)" << endl;
    cout << endl;
    StoreElements(userGrid, 4, 0, 'h', 4, "S.");
    StoreElements(userGrid, 5, 3, 'v', 4, "B.");
    StoreElements(userGrid, 6, 3, 'v', 5, "C.");
    ShowGrid(userGrid);

    ContinueTutorial();

    cout << "After you and computer places all the ships, two grids will be shown: " << endl << endl;
    cout << "(1)Ocean Grid shows the ships you have placed and the hits (\"H.\") & misses (\"M.\") of the computer" << endl;
    cout << "(2)Tracking Grid marks down your hits (\"H.\") & misses (\"M.\") when you attack the computer's grid" << endl << endl;
    cout << "If you want to go back to the menu in the middle of the game, enter -1." << endl;
    cout << "If you want to save and exit the game, enter -2." << endl << endl;
    InitCompGrid(compGrid);
    ShowBothGrids(userGrid, compGrid);

    cout << endl << "Enter -1 back to menu or -2 save and exit." << endl;
    cout << "Please enter coordinates that you want to attack, X & Y: " << "2 3" << endl;

    ContinueTutorial();

    cout << "In this round, the X & Y coordinates you entered hit one of the ships on the computer's grid." << endl;
    cout << "Therefore, you could see (2,3) on the Tracking Grid is denoted as \"H.\"." << endl << endl;
    cout << "Then it is the computer's turn and it attack (3,3)." << endl;
    cout << "It did not hit any of your ships, which is shown by \"M.\" on the Ocean Grid." << endl << endl;
    StoreElements(compGrid, 2, 3, 'v', 1, "H.");
    StoreElements(userGrid, 3, 3, 'v', 1, "M.");
    ShowBothGrids(userGrid, compGrid);
    StatusBoard();

    ContinueTutorial();

//    if enter one number, by defaul x and y = number
    cout << "If you only enter one number for the coordinates, x and y coordinates of your attack will both be equal to the number you have entered." << endl << endl;
    ShowBothGrids(userGrid, compGrid);

    cout << endl << "Enter -1 back to menu or -2 save and exit." << endl;
    cout << "Please enter coordinates that you want to attack, X & Y: " << "5" << endl;

    ContinueTutorial();

    cout << "Therefore, you could see (5, 5) on the Tracking Grid is denoted as \"H.\"." << endl << endl;
    StoreElements(compGrid, 5, 5, 'v', 1, "H.");
    ShowBothGrids(userGrid, compGrid);

    ContinueTutorial();

    cout << "Description for each item on status board: " << endl << endl;
    cout << "(1) Total Target: total number of targets to be hit in order to win" << endl;
    cout << "(2) Target Hit: total number of targets hit" << endl;
    cout << "(3) Target Missed: total number of targets missed" << endl;
    cout << "(4) Last Attack: the status of last move (Hit / Miss)" << endl;

    StatusBoard();
    
    ContinueTutorial();
    cout << "In order to win, you have to hit all of the ships on computer's grid before the computer hit all of yours." << endl;
    cout << "For demonstation, assume that you have won this game." << endl;
    
    ContinueTutorial();
    
    cout << "You can see that in the status board shows that Total Target = 17 and Target Hit = 17." << endl;
    cout << "This shows you have hit all of the ships on computer's grid and won the game!" << endl;
    WinStatusBoard();
    
    ContinueTutorial();
}

//print initialized grid
void ShowInitGrid(string userGrid[10][10])
{
    cout << setw(4);
    for(int i = 0;i < 10;i++)
    {
        cout << "0" << i << " ";
    }

    cout << endl;

    for(int j = 0;j < 10;j++)
    {
        cout << "0" << j;
        for(int k = 0;k < 10;k++)
        {
            userGrid[j][k] = "--";
            cout << " " << userGrid[j][k];
        }
        cout << endl;
    }
}

//store grid elements for userGrid
void StoreElements(string Grid[10][10], int x, int y, char orientation, int ShipSize, string element)
{
    if (orientation == 'h')
    {
        for(int i = x; i < (x + ShipSize); i++)
        {
            Grid[y][i] = element;
        }
    }
    else
    {
        for(int j = y; j < (y + ShipSize); j++)
        {
            Grid[j][x] = element;
        }
    }

}

//print user grid with placed ships
void ShowGrid(string userGrid[][10])
{
    cout << setw(4);
    for(int i = 0;i < 10;i++)
    {
        cout << "0" << i << " ";
    }

    cout << endl;

    for(int j = 0;j < 10;j++)
    {
        cout << "0" << j;
        for(int k = 0;k < 10;k++)
        {
            cout << " " << userGrid[j][k];
        }
        cout << endl;
    }

}

//initialize all the grid elements as "--"
void InitCompGrid(string compGrid[][10])
{
    for(int j = 0;j < 10;j++)
    {
        for(int k = 0;k < 10;k++)
        {
            compGrid[j][k] = "--";
        }
    }
}

//print both user grid and computer grid, where the two are beside each other
void ShowBothGrids(string userGrid[][10], string compGrid[][10])
{
    int i = 0;
    cout << setw(20) << "Ocean Grid";
    cout << "\t\t\t\t\t";
    cout << setw(24) << "Tracking Grid" << endl;

    cout << setw(4);

    //print column number for userGrid
    for(i = 0;i < 10;i++)
    {
        cout << "0" << i << " ";
    }

    cout << "\t\t\t" << setw(4);
    //print column number for compGrid
    for(i = 0;i < 10;i++)
    {
        cout << "0" << i << " ";
    }

    cout << endl;

    for(i = 0;i < 10;i++)
    {
        //print row number for userGrid
        cout << "0" << i;

        //print row i in userGrid
        for(int j = 0;j < 10;j++)
        {
            cout << " " << userGrid[i][j];
        }

        //print row number for compGrid
        cout << "\t\t\t" << setw(1);
        cout << "0" << i;

        //print row i in compGrid
        for(int k = 0;k < 10;k++)
        {
            cout << " " << compGrid[i][k];
        }

        cout << endl;
    }
}

void StatusBoard()
{
    cout << endl << endl;
    cout << "Game Status: " << endl;
    cout << "------------" << endl;
    cout << setw(28) << "Computer" << setw(16) << "Player" << endl;

    // this variable is not corret, please clarify the total target number.
    cout << "Total Target:" << setw(12) << 17 << setw(17) << 17 << endl;


    cout << "Target Hit:" << setw(14) << 0 << setw(17) << 1 << endl;
    cout << "Target Missed:" << setw(11) << 1 << setw(17) << 0 << endl;
    cout << "Last Attack:" << setw(14) << "Miss" << setw(17) << "Hit" << endl;
}

void WinStatusBoard()
{
    cout << endl << endl;
    cout << "Game Status: " << endl;
    cout << "------------" << endl;
    cout << setw(28) << "Computer" << setw(16) << "Player" << endl;

    // this variable is not corret, please clarify the total target number.
    cout << "Total Target:" << setw(12) << 17 << setw(17) << 17 << endl;


    cout << "Target Hit:" << setw(14) << 13 << setw(17) << 17 << endl;
    cout << "Target Missed:" << setw(11) << 43 << setw(17) << 40 << endl;
    cout << "Last Attack:" << setw(14) << "Miss" << setw(17) << "Hit" << endl;
}

void ContinueTutorial()
{
    char cont;
    cout << endl << endl;
    //system("pause");    //for window
    //read -p "Press any key to continue..."        //for linux
    //cout << "Press any key to Continue...";
    //cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout << "Enter \"n\" to continue...";
    cin >> cont;
    while(cont != 'n')
    {
        cout << "Wrong input! Please enter \"n\" to continue...";
        cin >> cont;
    }
    cout << endl << "_______________________________________________________________________________________________________________________" << endl << endl;
}
