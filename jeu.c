#include "jeu.h"

#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "carte.h"
#include "enchere.h"
#include "pli.h"
#include "annonce.h"

Jeu creerJeu(Joueur joueurs[4], Equipe equipes[2],
             Carte paquet[TAILLE_PAQUET], int pointsObjectif) {
    Jeu j;
    j.joueurs = joueurs;
    j.nbPli = 0;
    j.nbRound = 0;
    j.entameur = 0;
    j.donneur = 1;

    j.equipes = equipes;

    resetPile(&j);

    j.paquet = paquet;

    j.carteMaitre = 0;
    j.joueurActuel = &joueurs[j.entameur];

    j.joueurPrincipal = &joueurs[0];

    j.atoutPose = NULL;
    j.entame = NULL;

    j.pointsObjectif = pointsObjectif;
    return j;
}

void resetPile(Jeu* jeu) {
    for (int i = 0; i < 4; i++) {
        jeu->pile[i] = NULL;
        jeu->nbCartes = 0;
    }
}

void afficherJeu(Jeu* jeu) { afficherPaquet(jeu->pile, 4); }

void afficherPile(Jeu* jeu) {
    printf("Pile : %d/4\n", jeu->nbCartes);
    for (int i = 0; i < 4; i++) {
        if (jeu->pile[i] != NULL) {
            Carte carte = *(jeu->pile[i]);

            char carteStr[16];
            carteToString(carte, carteStr);

            Joueur* joueur = poseurCarte(jeu, i);

            char indicateurEquipe[20] = "";

            if (joueur == jeu->joueurPrincipal) {
                strcpy(indicateurEquipe, "(vous)");
            } else if (isMemeEquipe(jeu->joueurPrincipal, joueur)) {
                strcpy(indicateurEquipe, "(coéquipier)");
            }

            printf("%d. %s%s %s\t(%d pts) <- %s %s\n", i, carteStr,
                   isAtout(jeu, carte) ? "*" : "", // Afiche un * si atout
                   jeu->carteMaitre == i? "+":"", // Affiche un + si maître
                   pointsCarte(carte, jeu->enchere.contrat),
                   joueur->nom,
                   indicateurEquipe
                );

        } else {
            printf("-. ---\n");
        }
    }
}

void lancerJeu(Jeu* jeu) {
    int i = 0;
    while (jeu->equipes[0].score < jeu->pointsObjectif && jeu->equipes[1].score < jeu->pointsObjectif) {
        printf("\nDonne #%d:\n", i+1);
        phaseRound(jeu);

        i++;
    }
}

void phaseRound(Jeu* jeu) {
    jeu->nbPli = 0;

    int nbRetry = 0;
    
    jeu->equipes[0].scoreRound = 0;
    jeu->equipes[1].scoreRound = 0;

    do {
        if (nbRetry > 0) {
            printf("Tout le monde a passé... Redistribution des cartes\n");
        }
        // Tant que personne n'a enchéri on redistribue les cartes
        distribuer(jeu->joueurs, jeu->paquet);
        afficherJoueur(jeu->joueurs[0]);
        phaseEnchere(jeu);

        nbRetry++;
    } while (!jeu->enchere.encheri);


    // Phase calcul d'annonce et de belote
    for (int i = 0; i < 4; i++) {
        jeu->joueurs[i].belote = hasBelote(jeu, &jeu->joueurs[i]);
        jeu->joueurs[i].annonce = hasAnnonce(jeu, &jeu->joueurs[i]);
    }

    for (int i = 0; i < 8; i++) {
        printf("\n------------ Contrat ------------\n");
        afficherContrat(jeu->enchere.contrat);
        printf("---------------------------------\n");
        phasePli(jeu);

        printf("Equipe %d : Round = %d pts (Total = %d pts)\n", jeu->equipes[0].id, jeu->equipes[0].scoreRound, jeu->equipes[0].score);
        printf("Equipe %d : Round = %d pts (Total = %d pts)\n", jeu->equipes[1].id, jeu->equipes[1].scoreRound, jeu->equipes[1].score);

        jeu->nbPli++;
    }

    printf("\nLes 8 plis ont été joués. Résultats de la donne :\n");
    calculerScoreDonne(jeu);
}

void calculerScoreDonne(Jeu *jeu) {
    Contrat contrat = jeu->enchere.contrat;

    // L'équipe qui a le contrat
    Equipe* preneurs = contrat.equipe;
    // L'équipe qui n'a pas le contrat (l'autre)
    Equipe* defenseurs = &jeu->equipes[(preneurs->id + 1) % 2];

    int valAnnonces[2] = {0, 0};
    int valBelotes[2] = {0, 0};

    for (int i = 0; i < 4; i++) {
        Joueur joueur = jeu->joueurs[i];

        Annonce annonce = joueur.annonce;
        Annonce belote = joueur.belote;

        valAnnonces[joueur.equipe->id] += scoreAnnonce(annonce);
        valBelotes[joueur.equipe->id] += scoreAnnonce(belote);

        if (belote.nom == BELOTE) {
            printf("%s (équipe %d) a une belote !", joueur.nom, joueur.equipe->id);
        }

        if (annonce.nom != RIEN) {
            printf("%s (équipe %d) avait un %s !", joueur.nom, joueur.equipe->id, annonceToString(annonce));
        }
    }

    int annoncesPreneurs = valAnnonces[preneurs->id];
    int annoncesDef = valAnnonces[(preneurs->id + 1) % 2];

    int belotePreneurs = valBelotes[preneurs->id];
    int beloteDef = valBelotes[(preneurs->id + 1) % 2];

    Equipe* dixDeDer = poseurCarte(jeu, jeu->carteMaitre)->equipe;

    int gainsPreneurs = 0;
    int gainsDefenseurs = 0;

    printf("L'équipe %d remporte le Dix de Der ! (+10pts)\n", dixDeDer->id);
    if (dixDeDer == preneurs) {
        gainsPreneurs += 10;
    } else {
        gainsDefenseurs += 10;
    }

    int gainCoinche = contrat.valeur + 160 + annoncesPreneurs + annoncesDef;

    if (contrat.equipe->scoreRound > contrat.valeur && contrat.equipe->scoreRound > defenseurs->scoreRound) {
        printf("L'équipe %d respecte le contrat (%d > %d)\n", preneurs->id, preneurs->scoreRound, contrat.valeur);
        if (jeu->enchere.surcoinche) {
            printf("L'équipe %d avait coinché mais les preneurs a surcoinché. x4 !\n", defenseurs->id);
            gainsPreneurs += (gainCoinche + belotePreneurs) * 4;
            gainsDefenseurs += beloteDef;
        } else if (jeu->enchere.coinche) {
            printf("L'équipe %d avait coinché. x2 !\n", defenseurs->id);
            gainsPreneurs += (gainCoinche + belotePreneurs) * 2;
            gainsDefenseurs += beloteDef;

        } else {    // Aucune coinche
            gainsPreneurs += contrat.valeur + preneurs->scoreRound + annoncesPreneurs + belotePreneurs;
            gainsDefenseurs += defenseurs->scoreRound + annoncesDef + beloteDef;
        }
    } else {
        printf("L'équipe %d ne respecte pas le contrat ou a moins de points que l'équipe adverse !\n", preneurs->id);
        if (jeu->enchere.surcoinche) {
            printf("L'équipe %d avait coinché mais les preneurs ont surcoinché. x4 !\n", defenseurs->id);
            gainsDefenseurs += (gainCoinche + beloteDef) * 4;
        } else if (jeu->enchere.coinche) {
            printf("L'équipe %d avait coinché. x2 !\n", defenseurs->id);
            gainsDefenseurs += (gainCoinche + beloteDef) * 2;
        } else {    // Aucune coinche
            gainsDefenseurs += (gainCoinche + belotePreneurs);
        }

        gainsPreneurs += belotePreneurs;
    }

    preneurs->score += gainsPreneurs;
    defenseurs->score += gainsDefenseurs;

    printf("\nL'équipe %d (preneurs) remporte au total %d points!\n", preneurs->id, gainsPreneurs);
    printf("L'équipe %d remporte au total %d points!\n\n", defenseurs->id, gainsDefenseurs);
}

bool isAtout(Jeu* jeu, Carte c) {
    return jeu->enchere.contrat.atout == c.couleur;
}

