/*
 * \Bataille Navale
 * \Autheur Arlindo Tavares Varela
 * \version 0.1
 * \date 02.03.2021
 */
#include <stdio.h>

#define TAILLEGRILLE 10
#define GRILLEAFFICHAGE

{\
{"", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"},\
{"A","","","","","","","","","",""},\
{"B","","","","","","","","","",""},\
{"C","","","","","","","","","",""},\
{"D","","","","","","","","","",""},\
{"E","","","","","","","","","",""},\
{"F","","","","","","","","","",""},\
{"G","","","","","","","","","",""},\
{"H","","","","","","","","","",""},\
{"I","","","","","","","","","",""},\
{"J","","","","","","","","","",""},\
}

char *table_grille_affichage[TAILLEGRILLE+1][TAILLEGRILLE+1] = GRILLEAFFICHAGE;


int main(){
    printf("%s", GRILLEAFFICHAGE);


    return 0;
}
