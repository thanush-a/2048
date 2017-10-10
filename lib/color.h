#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>


// Couleurs du terminal
  typedef enum
  {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
  } COULEUR_TERMINAL;


/*
 * Fonction effaÃ§ant le terminal
 */
void clear_terminal();

/*
 * Printf en couleur. Les deux premiers paramÃ¨tres sont les couleurs d'Ã©criture et de fond (mettre une des valeurs parmi : 
 * BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN et WHITE).
 * Les parmÃ¨tres suivants sont comme le printf "normal" : chaÃ®ne de format puis toutes les valeurs Ã  afficher
 */
int color_printf(COULEUR_TERMINAL fg, COULEUR_TERMINAL bg, const char * format, ...);

#endif