#ifndef SAISIE_M_H
#define SAISIE_M_H



/*
 * Touches du clavier correspondant aux flèches (haut, bas, gauche, droite) + touche echap + autre touche
 */ 
typedef enum
{
	NO_KEY,
	KEY_ESCAPE,
	KEY_UP,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT
} Key;

/*
 * Début du mode saisie "sans retour chariot" : 
 * Il n'est pas nécessaire d'appuyer sur la touche entrée pour saisir une valeur.
 * La valeur saisie ne s'affiche pas.
 */
int debutTerminalSansR();

/*
 * Fin du mode saisie "sans retour chariot" : on revient à la normale
 */
void finTerminalSansR();

/*
 * Lecture d'une touche. La fonction renvoie :
 *   - KEY_UP, KEY_DOWN, KEY_LEFT ou KEY_RIGHT si l'utilisateur appuie sur une des flèches
 *   - KEY_ESCAPE si l'utilisateur appuie sur la touche Echap
 *   - NO_KEY si l'utilisateur appuie sur une autre touche
 */
Key lectureFleche();


#endif
