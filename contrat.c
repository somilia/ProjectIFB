#include "contrat.h"
#include "joueur.h"
#include "equipe.h"
#include "menuenchere.h"


void contrat(Joueur *joueur, Carte *tabcarte)
{
    int contrat=0;
    int couleur=0;
    int *Pcontrat=&contrat;
    int *Pcouleur=&couleur;

    joueur[0]=*joueur;       //Pour avoir accès à tout les joueurs
    joueur[1]=*(joueur+1);   //Je sais pas si pas si c'est la meilleure facon
    joueur[2]=*(joueur+2);
    joueur[3]=*(joueur+3);

    tabcarte[0]=*tabcarte;   //J'aurais aimé faire la meme chose mais je suis pas sur que ca marchera
    tabcarte[1]=*(tabcarte+1);
    tabcarte[2]=*(tabcarte+2);
    tabcarte[3]=*(tabcarte+3);
  //  tabcarte[0][0]=*tabcarte[0];

    for (int i=0; i<=3; i++)
    {

        if (joueur[i].bot == 0)
        {
            printf("\n ui\n");
          //  JoueurEnchere(&joueur[0], contrat, couleur, Pcontrat, Pcouleur);
        }
        else {
            //BotEnchere(&joueur[i]);
            printf("\n nn\n");
        }
       // printf("La proposition de contrat est de %d", *Pcontrat);

        afficherCarte(tabcarte[1]);
        printf("\n");
        afficherCarte(tabcarte[2]);
        printf("\n");
    }

}


void JoueurEnchere(Joueur *joueur, int contrat, int couleur, int *Pcontrat, int *Pcouleur)
{
    int choix = afficheMenuEnchere();

    int propositionContrat=0;
    int propositionCouleur=0;

    if (choix==2)
    {
        printf("Entrer une valeur de contrat \n");
        scanf("%d", &propositionContrat);

        printf("Vous avez choisi un contrat de %d\n", propositionContrat);

        while ((propositionContrat % 10 != 0) || (propositionContrat < contrat) || (propositionContrat < 80))
        {
            printf("\nLa valeur de contrat doit etre de minimum 80 ET doit etre un multiple de 10 ET doit etre superieur au contrat precedent, Reessayer: \n");
            scanf("%d", propositionContrat);
        }

        *Pcontrat = propositionContrat;
        printf("%d", propositionContrat);



        printf("Entrer une couleur: \nen choisissant une valeur entre 0 et 5 \n0: TREFLE, 1: CARREAU, 2: COEUR, 3: PIQUE, 4: SANS ATOUT, 5: TOUT ATOUT\n");
        scanf("%d", &propositionCouleur);
        while ((propositionCouleur < 0) || (propositionCouleur > 5))
        {
            printf("\nLa valeur de couleur doit etre comprise entre 1 et 4, Reessayer: \n");
            scanf("%d", propositionContrat);
        }


        *Pcouleur = propositionCouleur;


    }

}


void BotEnchere(Joueur *joueur[])
{

}

