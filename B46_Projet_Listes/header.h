#ifndef HEADER_LINKED_LIST_H_INCLUDED
#define HEADER_LINKED_LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct EncyclopedieSt{

    int clef;
    char * titre;
    char * contenu;
    struct EncyclopedieSt * suivant;
};
typedef struct EncyclopedieSt * Encyclopedie;

int est_vide(Encyclopedie e);
Encyclopedie creer_encyclopedie();
Encyclopedie inserer(Encyclopedie e, int identifiant, char * titre, char * contenu);
Encyclopedie supprimer(Encyclopedie e, int identifiant);
char * rechercher_article(Encyclopedie e, int identifiant);
Encyclopedie rechercher_article_plein_texte(Encyclopedie e, char * mot);
void detruire_encyclopedie(Encyclopedie e);

#endif // HEADER_LINKED_LIST_H_INCLUDED
