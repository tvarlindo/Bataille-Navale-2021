
/**
 * Arlindo Tavares Varela
 * Bataille navale
 * 04.03.2021
 * 23.03.2021
 * version 1.0
 * *23.03 15h
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#define AFFICHAGE_OBJETS {' ','B','X','O','C'}
#define DEBUG 0 // Changer à 1 pour afficher aussi les bateaux sur la grille
#define BATEAU 1
#define RATE 3
#define COULE 4
#define NOMBRE_JOUEURS 5

char joueurConnecte[20];
bool estConnecte = false;

/**
 * Cette fonction permet de convertir une lettre entrée par l'utilisateur en un
 * nombre utilisé par la suite comme coordonée verticale du tableau
 * @param lettre: Lettre entrée par l'utilisateur
 * @return coordonée numérique correspondante
 */
int **creerGrille() {
    int **tab = calloc(10, sizeof(int*));
    for(int i = 0; i < 10; i++) {
        tab[i] = calloc(10, sizeof(int));
    }
    return tab;
}

int **recupererGrille() {
    int chiffre = 1 + rand() % 5;
    FILE* ChoixDeGrille = NULL;
    int **tab = creerGrille();

    switch(chiffre){
        case 1: ChoixDeGrille = fopen("../grille1.txt","r");
            break;

        case 2: ChoixDeGrille = fopen("../grille2.txt","r");
            break;

        case 3: ChoixDeGrille = fopen("../grille3.txt","r");
            break;

        case 4: ChoixDeGrille = fopen("../grille4.txt","r");
            break;

        case 5: ChoixDeGrille = fopen("../grille5.txt","r");
            break;

        default:
            break;
    }
    for (int ligne = 0; ligne < 10; ++ligne) {
        for (int colonne = 0; colonne < 10; ++colonne) {
            fscanf(ChoixDeGrille,"%d,",&tab[ligne][colonne]);
        }
    }
    return tab;
}

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
 * @param grille mise à jour
 */

//Fonction pour affichage de la grille
void affichageGrille(int **tab) {
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
            if (tab[ligneTableau][colonneTableau] % 10 == BATEAU != 0) {
                printf("   ║");
            } else {
                printf(" %c ║", affichageObjet[tab[ligneTableau][colonneTableau] % 10]);
            }
        }
        printf("\n");
    }

    printf("   ╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n\n");
}

void aideDuJeu() {

printf("\t\t\t\t╔═════════════════════════╗\n");
printf("\t\t\t\t║ Voici les règles du jeu:║\n");
printf("\t\t\t\t╚═════════════════════════╝\n");
printf("\t ╔═════════════════════════════════════════════════════════════════════╗\n");
printf("\t ║ Le jeu de la bataille navale, consiste a faire couler tous les      ║\n");
printf("\t ║       bateaux de la flotte le plus rapidement possible.             ║\n");
printf("\t ╚═════════════════════════════════════════════════════════════════════╝\n");
printf("\t  ╔═══════════════════════════════════════════════════════════════════╗\n");
printf("\t  ║ Vous devez choisir une coordonnée sur l'axe horizontal. Par ex: c ║\n");
printf("\t  ║ \tpuis la coordonnée sur l'axe vertical: par ex. 4              ║\n");
printf("\t  ╚═══════════════════════════════════════════════════════════════════╝\n");
printf("    ╔════════════════════════════════════════════════════════════════════════════════╗\n");
printf("    ║ Si votre choix atteint un bateau, vous verrez apparaître un [x] dans la grille ║\n");
printf("    ║     Si votre choix ne touche aucun bateau, vous verrez apparaître un [O]       ║\n");
printf("    ╚════════════════════════════════════════════════════════════════════════════════╝\n");
printf("╔════════════════════════════════════════════════════════════════════════════════════════════╗\n");
printf("║ Lorsque vous aurez touché chaque case d'un même bateau, vous verrez apparaître des [C]     ║\n");
printf("║ en lieu et place des [x], indiquant que ce batiment est coulé ou qu'il n'y a plus de cases ║\n");
printf("║  à toucher pour ce bâtiment.                                                               ║\n");
printf("║ Lorsque tous les bateaux seront coulés ( [C] sur la grille) vous aurez terminé la partie.  ║\n");
printf("╚════════════════════════════════════════════════════════════════════════════════════════════╝\n");
printf("\t\t ╔═══════════════════════════════════════════════════════════╗\n");
printf("\t\t ║Pour rappel, les bateaux sont disposés soit à la verticale,║\n");
printf("\t\t ║\t soit à l'horizontale. Jamais en diagonale           ║\n");
printf("\t\t ║ \t\tBONNE CHANCE MATELOT!!!                      ║\n");
printf("\t\t ╚═══════════════════════════════════════════════════════════╝\n\n");


}

void authentification() {

    bool loginReussi = 0;
    char idJoueurValide[20];
    char motDePasseValide[20];
    char idJoueur[20];
    char motDePasse[20];
    FILE *fptr;

    if ((fptr = fopen("C:\\Users\\Arlindo.TAVARES-VARE\\Bataille-Navale-2021\\cmake-build-debug\\utilisateurs.txt","r")) == NULL) {
        printf("Error! opening file");
    }


    do {
        printf("Veuillez mettre votre nom d'utilisateur : ");
        scanf("%s", &idJoueur);
        printf("Veuillez insérer votre mot de passe : ");
        scanf("%s", &motDePasse);

        for (int i = 0; i < 2; i++) {

            fscanf(fptr, "%s", &idJoueurValide);
            fscanf(fptr, "%s", &motDePasseValide);
            fclose(fptr);

            if (strcmp(idJoueurValide, idJoueur) == 0 && strcmp(motDePasseValide, motDePasse) == 0) {
                loginReussi = 1;
                estConnecte = true;
                strcpy(joueurConnecte, idJoueur);
                break;
            }

        }

        if (!loginReussi) {
            printf("Le mot de passe est incorrect, veuillez réessayer\n");
        }

    } while (!loginReussi);

}

int recupererNombreBateau(int **grille, int referenceBateau) {
    int nombreBateau = 0;
    for (int ligne = 0; ligne < 10; ligne++) {
        for (int colonne = 0; colonne < 10; colonne++) {
            if (grille[ligne][colonne] == referenceBateau) {
                nombreBateau++;
            }
        }
    }

    return nombreBateau;
}

void coulerBateau(int **grille, int referenceBateau) {
    for (int ligne = 0; ligne < 10; ligne++) {
        for (int colonne = 0; colonne < 10; colonne++) {
            if (grille[ligne][colonne] == (referenceBateau + 1)) {
                grille[ligne][colonne] = COULE;
            }
        }
        printf("\n");
    }
}

//Fonction qui récupère le choix du menu
int choixMenu(){
    int choixMenu;

    printf("Que voulez-vous faire ?\n\n");
    printf("\t1\t S'authentifier \n");
    printf("\t2\t Jouer\n");
    printf("\t3\t Afficher aide du jeu\n");
    printf("\t4\t Quitter\n");
    printf("\n-------------------------------------------------------------------------------------------------------");
    printf("\nChoisissez une option [1-4] : ");
    scanf("%d", &choixMenu);
    fflush(stdin);
return choixMenu;
}



//Fonction qui contient le déroulement de la partie
void Jouer() {

    int score = 1000;
    char axeXLettre;
    int colonne = 0;
    int ligne = 0;
    int victoire = 0; // represente les cases touchées
    //char *MotDePasse;
    //bool LoginReussi = 0;
    bool jeuFini = false;
    char *Utilisateurs[NOMBRE_JOUEURS][2] = {{"Joueur1", "MdpJ1"},
                                             {"Joueur2", "MdpJ2"}};
    int **tab = recupererGrille();
    do {

        if(estConnecte) {
            printf("Vous etes connecte en tant que %s\nVotre score sera enregistre.\n", joueurConnecte);
        }
    affichageGrille(tab);

    printf("Veuillez choisir les coordonéés de tir:\n");
    printf("lettre:");
    axeXLettre = getchar();
    colonne = recupererCoordoneeDepuisLettre(axeXLettre);
    printf("chiffre:");
    scanf("%d", &ligne);
    fflush(stdin);

    ligne = ligne - 1;
    if (DEBUG != 0) {

    }

    switch (tab[ligne][colonne] % 10) {
        case 0:
            printf("Tir Manqué, Rechargez les canons et tentez à nouveau...\n\n");
            tab[ligne][colonne] = RATE;
            score -= 200;
            if(score <= 0) {
                jeuFini = true;
            }
            break;

        case 1:
            printf("\n BRAVO!!! Vous avez touché un navire, continuez...\n\n\n");
            int referenceBateau = tab[ligne][colonne];
            victoire++;
            tab[ligne][colonne]++;

            if (recupererNombreBateau(tab, referenceBateau) == 0) {
                printf("\n BRAVO!!! Vous avez coulé un navire, continuez...\n\n\n");
                coulerBateau(tab, referenceBateau);
                if(victoire == 17) {
                    jeuFini = true;
                }
            }
            break;

        case 2:
            printf("vous avez avez déjà tiré sur cette case!!\n");
            break;

        default:
            break;
    }

    } while (!jeuFini);

    if(score <= 0) {
        printf("\n _______                         __          \n"
                "/       \\                       /  |         \n"
                "$$$$$$$  |______   ______   ____$$ |__    __ \n"
                "$$ |__$$ /      \\ /      \\ /    $$ /  |  /  |\n"
                "$$    $$/$$$$$$  /$$$$$$  /$$$$$$$ $$ |  $$ |\n"
                "$$$$$$$/$$    $$ $$ |  $$/$$ |  $$ $$ |  $$ |\n"
                "$$ |    $$$$$$$$/$$ |     $$ \\__$$ $$ \\__$$ |\n"
                "$$ |    $$       $$ |     $$    $$ $$    $$/ \n"
                "$$/      $$$$$$$/$$/       $$$$$$$/ $$$$$$/  \n"
               "                                             \n"
               "                                             \n"
               "                                             \n\n"
               "VOUS AVEZ PERDU. ESSAYEZ ENCORE...\n");

    }
    else {
        printf(R"EOF(
                    /$$           /$$             /$$
                   |__/          | $$            |__/
          /$$    /$$/$$ /$$$$$$$/$$$$$$   /$$$$$$ /$$ /$$$$$$  /$$$$$$
         |  $$  /$$| $$/$$_____|_  $$_/  /$$__  $| $$/$$__  $$/$$__  $$
          \  $$/$$/| $| $$       | $$   | $$  \ $| $| $$  \__| $$$$$$$$
           \  $$$/ | $| $$       | $$ /$| $$  | $| $| $$     | $$_____/
            \  $/  | $|  $$$$$$$ |  $$$$|  $$$$$$| $| $$     |  $$$$$$$
             \_/   |__/\_______/  \___/  \______/|__|__/      \_______/
       )EOF");

        printf("\nVotre score est de %d points.\n", score);
    }


}

//Fonction pour affichage du titre

void affichageTitreMenu() {
    system("cls");

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
    int valeurChoix = 0;
    srand(time(NULL));


    do {
        // Affiche le titre et le menu du jeu
        affichageTitreMenu();

        // Récupère le choix du menu
        valeurChoix= choixMenu();

        switch (valeurChoix) {

            case 1:
                authentification();
                break;

            case 2:
                Jouer();
                choixMenu();
                break;

            case 3:
                aideDuJeu();
                choixMenu();
                break;

            case 4:
                printf("Quitter");
                return 0;

            default:
                break;

        }

    } while (valeurChoix <= 1 || valeurChoix >= 4);


    return 0;
}
