#ifndef HEADER_LINKED_LIST_H_INCLUDED
#define HEADER_LINKED_LIST_H_INCLUDED 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_TAB 50000
#define TAILLE_MAX 100000


struct EncyclopedieSt{

    int clef;
    char * titre;
    char * contenu;
    struct EncyclopedieSt * suivant;
};
typedef struct EncyclopedieSt * EncyclopedieMAILLON;
typedef EncyclopedieMAILLON * Encyclopedie;


/*
FONCTION : ouvrir_fichier(FILE * fichier, char * choix) : FILE *
Permet d'ouvrir le fichier qui contient les articles pour être lu

PRE-CONDITION
- Une variable FILE* existe déjà
- Le fichier à lire existe

POST-CONDITION
- La variable FILE* n'est plus nulle (contient les infos du fichier)

INVARIANT
*/
FILE * ouvrir_fichier(FILE * fichier, char * choix);


/*
FONCTION : initialisation_encyclopedie(FILE * fichier, Encyclopedie e) : Encyclopedie
Permet de découper les informations de la variable FILE* en différents maillons dans l'arbre

PRE-CONDITION
- Une variable FILE* existe déjà
- Une variable Encyclopedie existe déjà

POST-CONDITION
- L'Encyclopedie n'est plus nulle

INVARIANT
*/
Encyclopedie initialisation_encyclopedie(FILE * fichier, Encyclopedie e);


/*
FONCTION : hachage(int clef) : int
Transforme la clef en indice

PRE-CONDITION
- La clef existe

POST-CONDITION
- La nouvelle clef retournee est un indice de la table de hachage

INVARIANT
*/
int hachage(int clef);


/*
FONCTION : afficher_encyclopedie(Encyclopedie e) : Void
Affiche l'encyclopedie

PRE-CONDITION
- L'encyclopedie existe et n'est pas vide, implémentée sous forme de tableau de listes chainees

POST-CONDITION

INVARIANT
*/
void afficher_encyclopedie(Encyclopedie e);


/*
FONCTION : est_vide(Encyclopedie e) : int
Renvoie "VRAI" si l'ensemble des listes chainees du tableau d'encyclopedie est vide

PRE-CONDITION
- L'encyclopedie existe et n'est pas vide

POST-CONDITION
- La variable retournée contient l'information si l'encyclopedie est vide ou non

INVARIANT
*/
int est_vide(Encyclopedie e);


/*
FONCTION : creer_encyclopedie() : Encyclopedie

PRE-CONDITION

POST-CONDITION
- La variable Encyclopédie existe et est vide

INVARIANT
*/
Encyclopedie creer_encyclopedie();


/*
FONCTION : insererMAILLON(EncyclopedieMAILLON e, int identifiant, char * titre, char * contenu : EncyclopedieMAILLON
Ajoute a la suite du dernier element de la liste chainee un nouvel article

PRE-CONDITION
- La liste chainee existe
- Les variables qui constituent l'article sont definies

POST-CONDITION
- Elle contient un nouvel élément en bout de chaine

INVARIANT
*/
EncyclopedieMAILLON insererMAILLON(EncyclopedieMAILLON e, int identifiant, char * titre, char * contenu);


/*
FONCTION : inserer(Encyclopedie e, int identifiant, char * titre, char * contenu) : Encyclopedie
Ajoute l'element a inserer dans le tableau d'encyclopedies a l'indice trouve par hachage

PRE-CONDITION
- La variable Encyclopédie existe
- Les variables qui constituent l'article sont definies

POST-CONDITION
- Elle contient un nouvel élément en bout de chaine

INVARIANT
*/
Encyclopedie inserer(Encyclopedie e, int identifiant, char * titre, char * contenu);


/*
FONCTION : supprimerMAILLON(EncyclopedieMAILLON e, int identifiant) : EncyclopedieMAILLON
Supprime un élément de la liste chainee

PRE-CONDITION
- La liste chainee existe et n'est pas vide
- La variable identifiant existe et est defini

POST-CONDITION
- La liste chainee possède un élément en moins

INVARIANT
*/
EncyclopedieMAILLON supprimerMAILLON(EncyclopedieMAILLON e, int identifiant);


/*
FONCTION : supprimer(Encyclopedie e, int identifiant) : Encyclopedie
Supprime un élément dans le tableau d'encyclopedies a l'indice trouve par hachage

PRE-CONDITION
- La variable Encyclopedie existe et n'est pas vide
- La variable identifiant existe et est defini

POST-CONDITION
- La liste chainee a l'indice trouve par hachage possède un élément en moins

INVARIANT
*/
Encyclopedie supprimer(Encyclopedie e, int identifiant);


/*
FONCTION : rechercher_articleMAILLON(EncyclopedieMAILLON e, int identifiant) : char *
Retourne l'article qui possède l'identifiant passé en paramètre

PRE-CONDITION
- La liste chainee existe et n'est pas vide
- La variable identifiant existe et est defini

POST-CONDITION
- La variable contient le contenu de l'article recherché

INVARIANT
*/
char * rechercher_articleMAILLON(EncyclopedieMAILLON e, int identifiant);


/*
FONCTION : rechercher_article(Encyclopedie e, int identifiant) : char *
Retourne l'article qui possède l'identifiant passé en paramètre avec la methode de hachage

PRE-CONDITION
- La variable Encyclopédie existe et n'est pas vide
- La variable identifiant existe et est defini

POST-CONDITION
- La variable contient le contenu de l'article recherché

INVARIANT
*/
char * rechercher_article(Encyclopedie e, int identifiant);


/*
FONCTION : rechercher_article_plein_texteMAILLON(EncyclopedieMAILLON e, char * mot) : EncyclopedieMAILLON
Retourne une nouvelle liste chainee dont les articles contiennent tous la variable "mot"

PRE-CONDITION
- Le mot recherché est defini
- La liste chainee existe et n'est pas vide

POST-CONDITION
- Une nouvelle liste chainee contient les articles issus de la recherche

INVARIANT
*/
EncyclopedieMAILLON rechercher_article_plein_texteMAILLON(EncyclopedieMAILLON e, char * mot);


/*
FONCTION : rechercher_article_plein_texte(Encyclopedie e, char * mot) : Encyclopedie
Retourne un nouveau tableau d'encyclopédies dont les articles contiennent tous la variable "mot"

PRE-CONDITION
- Le mot recherché est defini
- Le tableau d'encyclopedies existe et n'est pas vide

POST-CONDITION
- Un nouveau tableau d'encyclopedies contient les articles issus de la recherche

INVARIANT
*/
Encyclopedie rechercher_article_plein_texte(Encyclopedie e, char * mot);


/*
FONCTION : detruire_encyclopedieMAILLON(EncyclopedieMAILLON e) : Void
Libère chaque espace mémoire de la liste chainee en commençant par le premier maillon

PRE-CONDITION
- La liste chainee existe

POST-CONDITION
- La variable est vide

INVARIANT
*/
void detruire_encyclopedieMAILLON(EncyclopedieMAILLON e);


/*
FONCTION : detruire_encyclopedie(Encyclopedie e : Void
Libère chaque espace mémoire du tableau d'encyclopedies en commençant par le premier indice

PRE-CONDITION
- Le tableau de listes chainees existe

POST-CONDITION
- La variable est vide

INVARIANT
*/
void detruire_encyclopedie(Encyclopedie e);


/*
FONCTION : menu() : Void
Ouvre le menu pour choisir une version automatique ou manuelle

PRE-CONDITION

POST-CONDITION

INVARIANT
*/
void menu();


/*
FONCTION : menu_automatique(Encyclopedie e) : Void
Ouvre le menu automatique pour choisir quel fichier utiliser

PRE-CONDITION

POST-CONDITION

INVARIANT
*/
void menu_automatique(Encyclopedie e);


/*
FONCTION : menu_manuel(Encyclopedie e) : Void
Ouvre le menu manuel pour creer une encyclopedie manuellement

PRE-CONDITION

POST-CONDITION

INVARIANT
*/
void menu_manuel(Encyclopedie e);


/*
FONCTION : menu_principal(Encyclopedie e) : Void
Ouvre le menu principal pour choisir une fonction a effectuer

PRE-CONDITION

POST-CONDITION

INVARIANT
*/
void menu_principal(Encyclopedie e);


#endif // HEADER_LINKED_LIST_H_INCLUDED
