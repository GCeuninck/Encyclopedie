#include "header.h"

int est_vide(Encyclopedie e){

    int res = 0;

    if(e == NULL){
        res = 1;
    }

    return res;
}


Encyclopedie creer_encyclopedie(){

    Encyclopedie e;
    e = NULL;

    return e;
}


Encyclopedie inserer(Encyclopedie e, int identifiant, char * titre, char * contenu){

    if(est_vide(e)){
        e = (Encyclopedie)malloc(sizeof(struct EncyclopedieSt));

        e->clef = identifiant;

        e->titre = (char *)malloc(sizeof(char)*strlen(titre)+1);
        strcpy(e->titre,titre);

        e->contenu = (char *)malloc(sizeof(char)*strlen(contenu)+1);
        strcpy(e->contenu,contenu);

        e->suivant = NULL;
    }

    else if(e->clef == identifiant){
        printf("IDENTIFIANT EXISTE DEJA\n");
    }

    else{
        e->suivant = inserer(e->suivant, identifiant, titre, contenu);
    }

    return e;
}


Encyclopedie supprimer(Encyclopedie e, int identifiant){

    Encyclopedie suppr;

    if (est_vide(e)){
        printf("ENCYCLOPEDIE VIDE\n");
    }

    else if(est_vide(e->suivant) && e->clef != identifiant){
        printf("IDENTIFIANT INCONNU\n");
    }

    else if(identifiant == e->clef){
        suppr = e;
        e = e->suivant;
        free(suppr->titre);
        free(suppr->contenu);
        free(suppr);
    }

    else if(e->suivant->clef == identifiant){

        suppr = e->suivant;
        e->suivant = e->suivant->suivant;
        free(suppr);
    }

    else{
        e->suivant = supprimer(e->suivant, identifiant);
    }

    return e;
}


char * rechercher_article(Encyclopedie e, int identifiant){

    char * res = NULL;

    if(est_vide(e)){
        printf("ENCYCLOPEDIE VIDE OU IDENTIFIANT INCONNU\n");
    }

    else if(e->clef == identifiant){
        res = e->contenu;
    }

    else{
        res = rechercher_article(e->suivant, identifiant);
    }

    return res;
}

Encyclopedie rechercher_article_plein_texte(Encyclopedie e, char * mot){

    Encyclopedie res = creer_encyclopedie();

    if(!est_vide(e)){

        if(strstr(e->contenu, mot)){
            res = inserer(res, e->clef, e->titre, e->contenu);
            res->suivant = rechercher_article_plein_texte(e->suivant, mot);

        }

        else{
            res = rechercher_article_plein_texte(e->suivant, mot);
        }
    }

    return res;
}

void detruire_encyclopedie(Encyclopedie e){

    Encyclopedie suppr;

    while(!est_vide(e)){
        suppr = e;
        e = e->suivant;
        free(suppr->titre);
        free(suppr->contenu);
        free(suppr);
    }
}
