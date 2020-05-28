#ifndef PROJECTIFB_CARTE_H
#define PROJECTIFB_CARTE_H

typedef enum Couleur Couleur;
enum Couleur {
    TREFLE,
    CARREAU,
    COEUR,
    PIQUE
};

typedef enum Valeur Valeur;
enum Valeur {
    SEPT,
    HUIT,
    NEUF,
    DIX,
    VALET,
    DAME,
    ROI,
    AS,
};


/**
typedef enum Valeur Valeur;
enum Valeur {
    VALET=20,
    NEUF=14,
    AS=11,
    DIX=10,
    ROI=4,
    DAME=3,
    HUIT=0,
    SEPT=0
};**/
/**
typedef enum Valeur_HA Valeur_HA;
enum Valeur_HA {
    VALET=2,
    NEUF=0,
    AS=11,
    DIX=10,
    ROI=4,
    DAME=3,
    HUIT=0,
    SEPT=0
}; **/


typedef struct Carte Carte;
struct Carte {
    Couleur couleur;
    Valeur valeur;
};


void creerPaquetCarte(Carte paquet[]);


void affichecarte(Carte c);
void afficherCarte(Carte carte);
void permute(Carte *carte1, Carte *carte2);
void melange(Carte *paquet);
//void melangeTest(int *tab, int n);
void distribution(int *paquet, int *jeu, int *jeu1, int *jeu2, int *jeu3);




#endif //PROJECTIFB_CARTE_H
