
/**
 * Arlindo Tavares Varela
 *project: Bataille navale
 *Date: 04.03.2021
 * version: 1.0
 * Dernière modif: 23.03 15h
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

//Todo: ajout de differentes grilles

#define GRILLE {{0,0,0,0,0,0,0,0,0,0},{0,0,0,211,211,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,311,311,311,0,0},{411,0,0,0,0,0,0,0,0,0},{411,0,0,0,0,0,0,0,0,0},{411,0,0,321,0,0,0,0,0,0},{411,0,0,321,0,0,0,0,0,0},{0,0,0,321,0,0,0,0,0,0},{0,0,0,0,0,511,511,511,511,511}}
#define AFFICHAGE_OBJETS {' ','B','X','O','C'}
#define DEBUG 0 // Changer à 1 pour afficher aussi les bateaux sur la grille
#define BATEAU 1
#define TOUCHE 2
#define RATE 3
#define COULE 4
#define NOMBRE_JOUEURS 5

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

//void fichierLog(char IdJoueur[30], int colonne, int ligne)  //fonction pour les fichiers log.

/**
 *
 * @param IdJoueur
 * @param colonne
 * @param ligne {
FILE *fichier = NULL;

fichier = fopen("log.txt", "a");
if (fichier != NULL)

{
}
else
{
printf("Impossible de creer le fichier log.txt \n");
}

fclose(fichier);

time_t now = time(NULL);
struct tm tm_now = *localtime(&now);
char s_now[sizeof "JJ/MM/AAAA HH:MM:SS"];
strftime (s_now,
sizeof s_now, "%d/%m/%Y %H:%M:%S", &tm_now);

fichier = fopen("log.txt", "a");
fprintf(fichier, "blabla"
}
*/

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
            if (DEBUG == 0 && grille[ligneTableau][colonneTableau] % 10 == BATEAU) {
                printf("   ║");
            } else {
                printf(" %c ║", affichageObjet[grille[ligneTableau][colonneTableau] % 10]);
            }
        }
        printf("\n");
    }

    printf("   ╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n\n");
}

/**
 * fonction permettant de récupérer la réference d'un bateau sur la grille
 * @param grille
 * @param referenceBateau
 * @return
 */

int recupererNombreBateau(int grille[10][10], int referenceBateau) {
    int nombreBateau = 0;
    for (int ligne = 0; ligne < 10; ligne++) {
        for (int colonne = 0; colonne < 10; colonne++) {
            if (grille[ligne][colonne] == referenceBateau) {
                nombreBateau++;
            }
        }
    }
    if (DEBUG != 0) {
        printf("Nombre de bateaux %d : %d\n", referenceBateau, nombreBateau);
    }
    return nombreBateau;
}

/**Fonction pour affichage du titre
 */

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

int fchoixmenu(char *IdJoueur, char *MotDePasse, char *Utilisateurs, int LoginReussi ) {
    do {
        
    }
        printf("Veuillez mettre votre nom d'utilisateur\n");
        scanf("%s", &IdJoueur);
        printf("Veuillez insérer votre mot de passe\n");
        scanf("%s", &MotDePasse);

        for (int i = 0; i < NOMBRE_JOUEURS; i++) {
            if (Utilisateurs[i][0] == IdJoueur && Utilisateurs[i][1] == MotDePasse) {
                LoginReussi = 1;
            } else {
                printf("Le mot de passe est incorrect, veuillez réessayer\n");
                break;
            }
        }
    } while (LoginReussi = !1);
}

void jouer(int grille[10][10], int ligne, int colonne, char axeXLettre) {
    affichageGrille(grille);
    printf("Veuillez choisir les coordonéés de tir:\n");
    printf("lettre:");
    axeXLettre = getchar();
    colonne = recupererCoordoneeDepuisLettre(axeXLettre);
    printf("chiffre:");
    scanf("%d", &ligne);

    //fichierLog();
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

            if (recupererNombreBateau(grille, referenceBateau) == 0) {
                printf("\n BRAVO!!! Vous avez coulé un navire, continuez...\n\n\n");
                //grille[ligne][colonne] = COULE;
            }
            break;

        default:
            break;
    }
}

int authentification() {}

void aideDuJeu() {
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
        char *IdJoueur;
        char *MotDePasse;
        bool LoginReussi = 0;
        char *Utilisateurs[NOMBRE_JOUEURS][2] = {{"Joueur1", "MdpJ1"},
                                                 {"Joueur2", "MdpJ2"}};

        affichageTitre();

        printf("\tQue voulez-vous faire? :");
        printf("\t1 S'authentifier \n");
        printf("\t\t\t\t\t2 Jouer\n");
        printf("\t\t\t\t\t3 Afficher aide du jeu\n");
        printf("\t\t\t\t\t4 Quitter\n");

        scanf("%d", &choixMenu);
        fflush(stdin);

        switch (choixMenu) {
            case 1:
                authentification();
                break;
            case 2;
                jouer();
                break;
            case 3:
                aideDuJeu();
                break;
            case 4:
                printf("Vous allez quitter le jeu, AUREVOIR MATELOT !!!");
                break;

            default:
                break;
                // TODO: Incrémenter victoire quand bateau touché
                return 0;
        }
    }















