#ifndef PROJECTIFB_CARTE_H
#define PROJECTIFB_CARTE_H

#include "joueur.h"
#include "common.h"

static inline const char* couleurToString(Couleur c) {
    static const char* str_couleur[] = {"Trefle", "Carreau", "Coeur", "Pique"};
    return str_couleur[c];
}

static inline const char* valeurToString(Valeur v) {
    static const char* str_valeur[] = {"Sept",  "Huit", "Neuf", "Dix",
                                       "Valet", "Dame", "Roi",  "As"};
    return str_valeur[v];
}

Carte creerCarte(Couleur c, Valeur v);
void carteToString(Carte carte, char* output);

// Pose la carte idCarte du paquet de carte du joueur
int poserCarte(Joueur* joueur, int idCarte, Jeu* jeu);

void initPaquetCarte(Carte paquet[]);

// Retourne la valeur de la carte en fonction du contrat
int pointsCarte(Carte carte, Contrat contrat);

void afficherCarte(Carte carte);

void afficherPaquet(Carte** paquet, int nbCartes);

void permute(Carte* carte1, Carte* carte2);

void melanger(Carte* paquet, int nbMelange);

void distribuer(Joueur joueurs[4], Carte paquet[TAILLE_PAQUET]);

#endif  // PROJECTIFB_CARTE_H
