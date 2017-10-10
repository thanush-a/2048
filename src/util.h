#ifndef UTIL_H
#define UTIL_H

#define CLEAR() printf("\e[1;1H\e[2J")

int nbDigits(int x);
void getWinSize(int *col, int *row);
void clearScreen();

#endif