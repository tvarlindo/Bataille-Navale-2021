
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

#define GRILLE {{0,0,0,0,0,0,0,0,0,0},{0,0,0,211,211,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,311,311,311,0,0},{411,0,0,0,0,0,0,0,0,0},{411,0,0,0,0,0,0,0,0,0},{411,0,0,321,0,0,0,0,0,0},{411,0,0,321,0,0,0,0,0,0},{0,0,0,321,0,0,0,0,0,0},{0,0,0,0,0,511,511,511,511,511}}
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
            if (grille[ligneTableau][colonneTableau] % 10 == BATEAU != 0) {
                printf("   ║");
            } else {
                printf(" %c ║", affichageObjet[grille[ligneTableau][colonneTableau] % 10]);
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

int recupererNombreBateau(int grille[10][10], int referenceBateau) {
    int nombreBateau = 0;
    for (int ligne = 0; ligne < 10; ligne++) {
        for (int colonne = 0; colonne < 10; colonne++) {
            if (grille[ligne][colonne] == referenceBateau) {
                nombreBateau++;
            }
        }
    }
    //if (DEBUG != 0) {
       // printf("Nombre de bateaux %d : %d\n", referenceBateau, nombreBateau);
   // }
    return nombreBateau;
}

void coulerBateau(int grille[10][10], int referenceBateau) {
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

    printf("\n---");
    printf("\nChoisissez une option [1-4] : ");
    scanf("%d", &choixMenu);
    fflush(stdin);
return choixMenu;
}

int recupererGrille() {
    srand(time(NULL));
    int chiffre = (rand() % 5) + 1;
}

//Fonction qui contient le déroulement de la partie
void Jouer() {
    int grille[10][10] = GRILLE;
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

    do {

        if(estConnecte) {
            printf("Vous etes connecte en tant que %s\nVotre score sera enregistre.\n", joueurConnecte);
        }

    affichageGrille(grille);

    printf("Veuillez choisir les coordonéés de tir:\n");
    printf("lettre:");
    axeXLettre = getchar();
    colonne = recupererCoordoneeDepuisLettre(axeXLettre);
    printf("chiffre:");
    scanf("%d", &ligne);
    fflush(stdin);

    //fichierLog();

    ligne = ligne - 1;
    if (DEBUG != 0) {
        printf("Coordonnees dans le tableau x:%d, y:%d", colonne, ligne);
    }
    // TODO: Rajouter tous les types de case

    switch (grille[ligne][colonne] % 10) {
        case 0:
            printf("Tir Manqué, Rechargez les canons et tentez à nouveau...\n\n");
            grille[ligne][colonne] = RATE;
            score -= 200;
            if(score <= 0) {
                jeuFini = true;
            }
            break;

        case 1:
            printf("\n BRAVO!!! Vous avez touché un navire, continuez...\n\n\n");
            int referenceBateau = grille[ligne][colonne];
            victoire++;
            grille[ligne][colonne]++;

            if (recupererNombreBateau(grille, referenceBateau) == 0) {
                printf("\n BRAVO!!! Vous avez coulé un navire, continuez...\n\n\n");
                coulerBateau(grille, referenceBateau);
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
        printf("\nVOUS AVEZ PERDU. ESSAYEZ ENCORE...\n");

    }
    else {
        printf("\nVOUS AVEZ COULE TOUTE LA FLOTTE ADVERSE, VICTOIRE!!!\n");
        printf("\nVotre score est de %d points.\n", score);
    }


}

//

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


    do {
        // Affiche le titre et le menu du jeu
        affichageTitreMenu();

        // Récupère le choix du menu
        valeurChoix= choixMenu();

        switch (valeurChoix) {

            case 1:
                authentification();
                Jouer();
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
                printf("    _                             _      __  __       _       _       _   \n"
                       "   / \\  _   _ _ __ _____   _____ (_)_ __|  \\/  | __ _| |_ ___| | ___ | |_ \n"
                       "  / _ \\| | | | '__/ _ \\ \\ / / _ \\| | '__| |\\/| |/ _` | __/ _ \\ |/ _ \\| __|\n"
                       " / ___ \\ |_| | | |  __/\\ V / (_) | | |  | |  | | (_| | ||  __/ | (_) | |_ \n"
                       "/_/   \\_\\__,_|_|  \\___| \\_/ \\___/|_|_|  |_|  |_|\\__,_|\\__\\___|_|\\___/ \\__|\n"
                       "                                                                          ");
                return 0;

            default:
                break;

        }

    } while (valeurChoix <= 1 || valeurChoix >= 4);


    return 0;
}







/*

__     ___      _        _
\ \   / (_) ___| |_ ___ (_)_ __ ___
 \ \ / /| |/ __| __/ _ \| | '__/ _ \
  \ V / | | (__| || (_) | | | |  __/
   \_/  |_|\___|\__\___/|_|_|  \___|



 _____                _           ____            _
|_   _|__  _   _  ___| |__   ___ / ___|___  _   _| | ___
  | |/ _ \| | | |/ __| '_ \ / _ \ |   / _ \| | | | |/ _ \
  | | (_) | |_| | (__| | | |  __/ |__| (_) | |_| | |  __/
  |_|\___/ \__,_|\___|_| |_|\___|\____\___/ \__,_|_|\___|


 _______               _
|__   __|             | |
   | | ___  _   _  ___| |__   ___
   | |/ _ \| | | |/ __| '_ \ / _ \
   | | (_) | |_| | (__| | | |  __/
   |_|\___/ \__,_|\___|_| |_|\___|
                                  */
