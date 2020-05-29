#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "carte.h"
#include "contrat.h"
#include "equipe.h"
#include "joueur.h"

int main() {
    srand(time(NULL));

    Carte paquet[TAILLE_PAQUET];
    initPaquetCarte(paquet);
    melanger(paquet, 150);

    Joueur joueurs[4];
    Equipe equipe[2];

    equipe[0] = creerEquipe(0);
    equipe[1] = creerEquipe(1);

    joueurs[0] = creerJoueur(0, "Somia", &equipe[0], false);
    joueurs[1] = creerJoueur(1, "Lionel", &equipe[0], true);
    joueurs[2] = creerJoueur(2, "Younesse", &equipe[1], true);
    joueurs[3] = creerJoueur(3, "Yacine", &equipe[1], true);

    distribuer(joueurs, paquet);

    afficherPaquet(joueurs[0].carte, 8);

    
    // contrat(&joueur[0], tabcarte[0]);

    /**


        int choixMenu;
        printf("****************************************\n");
        printf("*                                      *\n");
        printf("*           Belote coinch%ce            *\n",130);
        printf("*                                      *\n");
        printf("****************************************\n");
        printf("\nQue voulez vous faire ?\n\n");
        printf("1 : D%cmarer une nouvelle partie\n",130);
        printf("2 : Afficher le tableau des scores\n");
        printf("3 : Quitter\n\n");
        scanf("%d", &choixMenu);
        switch(choixMenu) {
            case 1:
                printf("Vous avez choisi de demarrer une partie\n");

                contrat(&joueur[0]);

               break;
            case 2:
                printf("Vous avez choisi d'afficher le tableau des scores\n");
                break;
            case 3:
                exit(1);
            default:
                printf("Vous devez choisir 1, 2 ou 3");
        }
    **/

    //    Carte carte_a;
    //    carte_a.couleur = CARREAU;
    //    carte_a.valeur = DAME;
    //    printf("Couleur: %d", carte_a.couleur);
    /**    Carte paquet[32] = {0};
        creerPaquetCarte(paquet);
        for (int i = 0; i < 32; ++i) {
            afficherCarte(paquet[i]);
        }
    **/
    /**
     // Equipe equipe;
        creerEquipe(&equipe, 0);
        creerEquipe(&equipe, 1);

        char nom[20];
        scanf("Entrer le nom du joueur %s", &nom);


        creerJoueur(&joueur[0], 0, 0, 0, nom);
        //scanf("Entrer le nom du joueur %s", joueur[0].name);
        creerJoueur(&joueur[1], 1, 1, 1, "Est");
        creerJoueur(&joueur[2], 1, 0, 2,"Nord" );
        creerJoueur(&joueur[3], 1, 1, 3, "Ouest");

    **/

    printf("\n\nDone \n");

    return 0;
}