//tutorial.h
//Created by Karen Pang on 21/11/2020

#ifndef tutorial
#define tutorial

void PrintTutorial();
void ShowInitGrid(std::string userGrid[10][10]);
void StoreElements(std::string userGrid[10][10], int x, int y, char orientation, int ShipSize, std::string element);
void ShowGrid(std::string userGrid[10][10]);
void InitCompGrid(std::string compGrid[10][10]);
void ShowBothGrids(std::string userGrid[10][10], std::string compGrid[10][10]);
void StatusBoard();
void WinStatusBoard();
void ContinueTutorial();

#endif
