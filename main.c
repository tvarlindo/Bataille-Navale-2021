
/**
 * Arlindo Tavares Varela
 * Bataille navale
 * 04.03.2021
 * version 0.1
 */

#include <stdio.h>
#include <windows.h>

#define GRILLE {{0,0,0,0,0,0,0,0,0,0},{0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,1,1,1,0,0},{1,0,0,0,0,0,0,0,0,0},{1,0,0,0,0,0,0,0,0,0},{1,0,0,1,0,0,0,0,0,0},{1,0,0,1,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0,0},{0,0,0,0,0,1,1,1,1,1}}
#define AFFICHAGE_OBJETS {' ','B','X','O','C'}
#define DEBUG 0 // Changer à 1 pour afficher aussi les bateaux sur la grille
#define BATEAU 1
#define TOUCHE 2
#define RATE 3
#define COULE 4

int recupererCoordoneeDepuisLettre(char lettre) {
    int coordonnee = 0;
    switch (lettre) {
        case 'A':
        case 'a':
            coordonnee = 0;
            break;
        case 'B':
        case 'b':
            coordonnee = 1;
            break;
        case 'C':
        case 'c':
            coordonnee = 2;
            break;
        case 'D':
        case 'd':
            coordonnee = 3;
            break;
        case 'E':
        case 'e':
            coordonnee = 4;
            break;
        case 'F':
        case 'f':
            coordonnee = 5;
            break;
        case 'G':
        case 'g':
            coordonnee = 6;
            break;
        case 'H':
        case 'h':
            coordonnee = 7;
            break;
        case 'I':
        case 'i':
            coordonnee = 8;
            break;
        case 'J':
        case 'j':
            coordonnee = 9;
            break;
    }
    return coordonnee;
}

/**
 * Fonction qui gère l'affichage de la grille en fonction du jeu
 * @param grille la grille mise à jour
 */
void affichageGrille(int grille[10][10]) {
    char affichageObjet[5] = AFFICHAGE_OBJETS;
    printf("     A   B   C   D   E   F   G   H   I   J\n");
    printf("   ╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗\n");
    for (int ligneTableau = 0; ligneTableau < 10; ligneTableau++) {
        // Séparateur partout sauf à la première ligne
        if (ligneTableau != 0) {
            printf("   ╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n");
        }
        printf("%2d ║", ligneTableau + 1);
        for (int colonneTableau = 0; colonneTableau < 10; colonneTableau++) {
            // Affiche les bateaux que si debug à 1
            if (DEBUG == 0 && grille[ligneTableau][colonneTableau] == BATEAU) {
                printf("   ║");
            } else {
                printf(" %c ║", affichageObjet[grille[ligneTableau][colonneTableau]]);
            }
        }
        printf("\n");
    }

    printf("   ╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n\n");
}

int main() {
    SetConsoleOutputCP(65001);

    int choixMenu = 0;
    int grille[10][10] = GRILLE;
    // int LettreGrille=;
    // int i=1;
    char axeXLettre;
    int colonne = 0;
    int ligne = 0;
    int victoire = 0; // represente les cases touchées



    printf(R"EOF(
  __    __   ______   __     __   ______   __              _______    ______  ________  ________  __        ________
 |  \  |  \ /      \ |  \   |  \ /      \ |  \            |       \  /      \|        \|        \|  \      |        \
 | $$\ | $$|  $$$$$$\| $$   | $$|  $$$$$$\| $$            | $$$$$$$\|  $$$$$$\\$$$$$$$$ \$$$$$$$$| $$      | $$$$$$$$
 | $$$\| $$| $$__| $$| $$   | $$| $$__| $$| $$            | $$__/ $$| $$__| $$  | $$      | $$   | $$      | $$__
 | $$$$\ $$| $$    $$ \$$\ /  $$| $$    $$| $$            | $$    $$| $$    $$  | $$      | $$   | $$      | $$  \
 | $$\$$ $$| $$$$$$$$  \$$\  $$ | $$$$$$$$| $$            | $$$$$$$\| $$$$$$$$  | $$      | $$   | $$      | $$$$$
 | $$ \$$$$| $$  | $$   \$$ $$  | $$  | $$| $$_____       | $$__/ $$| $$  | $$  | $$      | $$   | $$_____ | $$_____
 | $$  \$$$| $$  | $$    \$$$   | $$  | $$| $$     \      | $$    $$| $$  | $$  | $$      | $$   | $$     \| $$     \
  \$$   \$$ \$$   \$$     \$     \$$   \$$ \$$$$$$$$       \$$$$$$$  \$$   \$$   \$$       \$$    \$$$$$$$$ \$$$$$$$$


     )EOF");


    printf("Bienvenue dans la bataille navale\n");
    printf("Que voulez-vous faire\n");
    printf("\t1 Jouer\n");
    printf("\t2 Afficher aide du jeu\n");

    scanf("%d", &choixMenu);
    fflush(stdin);


    if (choixMenu == 1) {
        while (victoire < 18) {
            //system("cls");


            affichageGrille(grille);
            printf("Veuillez choisir les coordonéés de tir:\n");
            printf("lettre:");
            axeXLettre = getchar();
            colonne = recupererCoordoneeDepuisLettre(axeXLettre);
            printf("chiffre:");
            scanf("%d", &ligne);
            fflush(stdin);
            ligne = ligne - 1;
            if (DEBUG != 0) {
                printf("Coordonnees dans le tableau x:%d, y:%d", colonne, ligne);
            }
        }
        // Juste exemple : A MODIFIER
        grille[ligne][colonne] = grille[ligne][colonne] == BATEAU ? TOUCHE : RATE;
        affichageGrille(grille);
    }

    else {
        printf("\t\tVoici les règles du jeu\n\n");

      //  printf("\t\t:");
//for(int i = 65; i < 75; i++)  {
// printf("%c |\n", i);
    }
    return 0;
}




// scanf("");


//{\
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


