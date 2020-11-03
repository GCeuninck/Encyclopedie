#include "Hachage.h"

int hachage(int clef){

    int identifiant = clef % TAILLE_TAB;

    return identifiant;
}

void afficher_maillons(EncyclopedieMAILLON e){

    if(e!=NULL){
        printf("N %d : %s - %s\n",e->clef, e->titre, e->contenu);
        afficher_maillons(e->suivant);
    }
}

void afficher_encyclopedie(Encyclopedie e){

    int i;

    for(i=0;i<TAILLE_TAB;i++){
        printf("Indice : %d\n",i);
        afficher_maillons(e[i]);
        printf("\n");
    }
}

int est_vide(Encyclopedie e){

    int res=1, i;
    for(i=0;i<TAILLE_TAB;i++){
        if(e[i] != NULL){
            res=0;
        }
    }
    return res;
}

Encyclopedie creer_encyclopedie(){

    Encyclopedie e;
    e = (Encyclopedie)malloc(sizeof(struct EncyclopedieSt)*TAILLE_TAB);
    int i;

    for(i=0; i<TAILLE_TAB; i++){
        e[i] = NULL;
    }

    return e;
}

EncyclopedieMAILLON insererMAILLON(EncyclopedieMAILLON e, int identifiant, char * titre, char * contenu){

    if(e==NULL){
        e = (EncyclopedieMAILLON)malloc(sizeof(struct EncyclopedieSt));

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
        e->suivant = insererMAILLON(e->suivant, identifiant, titre, contenu);
    }

    return e;
}

Encyclopedie inserer(Encyclopedie e, int identifiant, char * titre, char * contenu){

    int ID_TABLE = hachage(identifiant);
    e[ID_TABLE] = insererMAILLON(e[ID_TABLE],identifiant,titre,contenu);

    return e;
}

EncyclopedieMAILLON supprimerMAILLON(EncyclopedieMAILLON e, int identifiant){

    EncyclopedieMAILLON suppr;

    if (e==NULL){
        printf("ENCYCLOPEDIE VIDE\n");
    }

    else if(e->suivant==NULL && e->clef != identifiant){
        printf("IDENTIFIANT INCONNU\n");
    }

    else if(identifiant == e->clef){
        suppr = e;
        e = e->suivant;
        free(suppr);
    }

    else if(e->suivant->clef == identifiant){

        suppr = e->suivant;
        e->suivant = e->suivant->suivant;
        free(suppr->titre);
        free(suppr->contenu);
        free(suppr);
    }

    else{
        e->suivant = supprimerMAILLON(e->suivant, identifiant);
    }

    return e;
}

Encyclopedie supprimer(Encyclopedie e, int identifiant){

    int ID_TABLE = hachage(identifiant);

    e[ID_TABLE] = supprimerMAILLON(e[ID_TABLE],identifiant);

    return e;
}


char * rechercher_articleMAILLON(EncyclopedieMAILLON e, int identifiant){

    char * res = NULL;

    if(e==NULL){
        printf("ENCYCLOPEDIE VIDE OU IDENTIFIANT INCONNU\n");
    }

    else if(e->clef == identifiant){
        res = e->contenu;
    }

    else{
        res = rechercher_articleMAILLON(e->suivant, identifiant);
    }

    return res;
}

char * rechercher_article(Encyclopedie e, int identifiant){

    int ID_TABLE = hachage(identifiant);

    char * res;

    res = rechercher_articleMAILLON(e[ID_TABLE],identifiant);

    return res;
}

EncyclopedieMAILLON rechercher_article_plein_texteMAILLON(EncyclopedieMAILLON e, char * mot){

    EncyclopedieMAILLON res = NULL;

    if(e!=NULL){

        if(strstr(e->contenu, mot)){
            res = insererMAILLON(res, e->clef, e->titre, e->contenu);
            res->suivant = rechercher_article_plein_texteMAILLON(e->suivant, mot);

        }

        else{
            res = rechercher_article_plein_texteMAILLON(e->suivant, mot);
        }
    }

    return res;
}

Encyclopedie rechercher_article_plein_texte(Encyclopedie e, char * mot){

    int i;

    Encyclopedie res = creer_encyclopedie();

    for(i=0;i<TAILLE_TAB;i++){
         res[i] = rechercher_article_plein_texteMAILLON(e[i], mot);
    }

    return res;
}


void detruire_encyclopedieMAILLON(EncyclopedieMAILLON e){

    EncyclopedieMAILLON suppr;

    while(e!=0){
        suppr = e;
        e = e->suivant;
        free(suppr->titre);
        free(suppr->contenu);
        free(suppr);
    }
}

void detruire_encyclopedie(Encyclopedie e){

    int i;

    for(i=0;i<TAILLE_TAB;i++){
        detruire_encyclopedieMAILLON(e[i]);
        e[i]=NULL;
    }
}

