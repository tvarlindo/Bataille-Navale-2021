
/**
 * Arlindo Tavares Varela
 * Bataille navale
 * 04.03.2021
 * version 0.1
 * *16.03 15h
 */

#include <stdio.h>
#include <windows.h>

#define GRILLE {{0,0,0,0,0,0,0,0,0,0},{0,0,0,211,211,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,311,311,311,0,0},{411,0,0,0,0,0,0,0,0,0},{411,0,0,0,0,0,0,0,0,0},{411,0,0,321,0,0,0,0,0,0},{411,0,0,321,0,0,0,0,0,0},{0,0,0,321,0,0,0,0,0,0},{0,0,0,0,0,511,511,511,511,511}}
#define AFFICHAGE_OBJETS {' ','B','X','O','C'}
#define DEBUG 1 // Changer à 1 pour afficher aussi les bateaux sur la grille
#define BATEAU 1
#define TOUCHE 2
#define RATE 3
#define COULE 4

//representation visuelle de la grille
/*{ {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,D,D,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,F,F,F,0,0},
    {W,0,0,0,0,0,0,0,0,0},
    {W,0,0,0,0,0,0,0,0,0},
    {W,0,0,S,0,0,0,0,0,0},
    {W,0,0,S,0,0,0,0,0,0},
    {0,0,0,S,0,0,0,0,0,0},
    {0,0,0,0,0,P,P,P,P,P}}*/


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

//Fonction pour affichage de la grille
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
            if (DEBUG == 0 && grille[ligneTableau][colonneTableau] % 10 == BATEAU)
            {
                printf("   ║");
            } else {
                printf(" %c ║", affichageObjet[grille[ligneTableau][colonneTableau] % 10]);
            }
        }
        printf("\n");
    }

    printf("   ╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n\n");
}

int recupererNombreBateau(int grille[10][10], int referenceBateau) {
    int nombreBateau = 0;
    for(int ligne = 0; ligne < 10; ligne++) {
        for(int colonne = 0; colonne < 10; colonne++) {
            if(grille[ligne][colonne] == referenceBateau) {
                nombreBateau++;
            }
        }
    }
    if(DEBUG != 0) {
        printf("Nombre de bateaux %d : %d\n", referenceBateau, nombreBateau);
    }
    return nombreBateau;
}

//Fonction pour affichage du titre

void affichageTitre() {
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
    int GrilleComp[10][10];
    char IdJoueur;


    affichageTitre();


    printf("Bienvenue dans la bataille navale...\n\n");

    do {
        printf("\tQue voulez-vous faire? :");
        printf("\t1 S'authentifier \n");
        printf("\t\t\t\t\t2 Jouer\n");
        printf("\t\t\t\t\t3 Afficher aide du jeu\n");
        printf("\t\t\t\t\t4 Quitter\n");

        scanf("%d", &choixMenu);
        fflush(stdin);


        /*if (choixMenu == 1) {
            printf("Veuillez entrer votre nom d'utilisateur ou pseudo");
            scanf("%s, &IdJoueur");*/


        /*else*/ if (choixMenu == 2) {
            while (victoire < 18) {
                // system("cls");

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
                // TODO: Rajouter tous les types de case
                //{{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}}



                switch (grille[ligne][colonne] % 10) {
                    case 0:
                        printf("Tir Manqué, Rechargez les canons et tentez à nouveau...\n\n");
                        grille[ligne][colonne] = RATE;

                        break;

                    case 1:
                        printf("\n BRAVO!!! Vous avez touché un navire, continuez...\n\n\n");
                        int referenceBateau = grille[ligne][colonne];
                        grille[ligne][colonne]++;

                        if(recupererNombreBateau(grille, referenceBateau) == 0) {
                            printf("\n BRAVO!!! Vous avez coulé un navire, continuez...\n\n\n");
                        }

                        break;

                    default:
                        break;
                }


            }
            //printf("\nVOUS AVEZ COULE TOUTE LA FLOTTE ADVERSE, VICTOIRE!!!\n");
            // TODO: Incrémenter victoire quand bateau touché
        } else if (choixMenu = 3) {
        // regles du jeu
        printf("\t\tVoici les règles du jeu:\n\n");
        printf("Le jeu de la bataille navale, consiste a faire couler tous les\nbateaux de la flotte le plus rapidement possible.\n\n");
        printf("Vous devez choisir une coordonnée sur l'axe horizontal. Par ex: c\n");
        printf("puis la coordonnée sur l'axe vertical: par ex. 4\n\n");
        printf("Si votre choix atteint un bateau, vous verrez apparaître un [x] dans la grille\n");
        printf("Si votre choix ne touche aucun bateau, vous verrez apparaître un [O]\n");
        printf("Lorsque vous aurez touché chaque case d'un même bateau, vous verrez apparaître des [C]\n");
        printf("en lieu et place des [x], indiquant que ce batiment est coulé ou qu'il n'y a plus de cases\n");
        printf("à toucher pour ce bâtiment.\n\n");
        printf("Lorsque tous les bateaux seront coulés ( [C] sur la grille) vous aurez terminé la partie.\n\n");
        printf("Pour rappel, les bateaux sont disposés soit à la verticale,\n");
        printf(" soit à l'horizontale. Jamais en diagonale\n\n");
        printf("BONNE CHANCE MATELOT!!!\n\n\n");

        choixMenu;

    } else {
        printf("Vous allez quitter le jeu, AUREVOIR MATELOT !!!");
    }

} while (choixMenu != 4);

return 0;
}










