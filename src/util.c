#include "util.h"
#include <math.h>
#include <sys/ioctl.h>
#include <stdio.h>

/*! \fn nbDigits
 *
 *  Retourne le nombre de chiffres de la représentation décimale d'un entier
 *  
 *  \param x : entier
 *  
*/
int nbDigits(int x)
{
    return (x != 0) ? (int) (log10 (abs (x))) + 1 : 1;
}

/*! \fn getWinSize
 * 
 *  Stock la hauteur et la largeur du terminal dans des variables
 *  
 *  \param *col : nombre de colonnes
 *  \param *row : nombre de lignes
 *  
*/
void getWinSize(int *col, int *row)
{
    struct winsize win;
    ioctl(0, TIOCGWINSZ, &win);
    *col = win.ws_col;
    *row = win.ws_row;
}

/*! \fn clearScreen
 *  
 *  Efface le terminal
 *  
*/


void clearScreen()
{
    int i, col, row;
    getWinSize(&col, &row);
    
    for (i = 0; i < row; i++)
    {
        printf("\n");
    }
}