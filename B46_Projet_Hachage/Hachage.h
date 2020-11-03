#ifndef HEADER_LINKED_LIST_H_INCLUDED
#define HEADER_LINKED_LIST_H_INCLUDED 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_TAB 5


struct EncyclopedieSt{

    int clef;
    char * titre;
    char * contenu;
    struct EncyclopedieSt * suivant;
};
typedef struct EncyclopedieSt * EncyclopedieMAILLON;
typedef EncyclopedieMAILLON * Encyclopedie;



int hachage(int clef);
void afficher_encyclopedie(Encyclopedie e);
int est_vide(Encyclopedie e);
Encyclopedie creer_encyclopedie();
EncyclopedieMAILLON insererMAILLON(EncyclopedieMAILLON e, int identifiant, char * titre, char * contenu);
Encyclopedie inserer(Encyclopedie e, int identifiant, char * titre, char * contenu);
EncyclopedieMAILLON supprimerMAILLON(EncyclopedieMAILLON e, int identifiant);
Encyclopedie supprimer(Encyclopedie e, int identifiant);
char * rechercher_articleMAILLON(EncyclopedieMAILLON e, int identifiant);
char * rechercher_article(Encyclopedie e, int identifiant);
EncyclopedieMAILLON rechercher_article_plein_texteMAILLON(EncyclopedieMAILLON e, char * mot);
Encyclopedie rechercher_article_plein_texte(Encyclopedie e, char * mot);
void detruire_encyclopedieMAILLON(EncyclopedieMAILLON e);
void detruire_encyclopedie(Encyclopedie e);

#endif // HEADER_LINKED_LIST_H_INCLUDED
