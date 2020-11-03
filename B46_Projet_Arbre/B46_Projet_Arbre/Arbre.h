#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define TAILLE_MAX 500000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct EncyclopedieSt{
    int clef;
    char * contenu;
    char * titre;
    struct EncyclopedieSt * fils_gauche;
    struct EncyclopedieSt * fils_droit;
};
typedef struct EncyclopedieSt * Encyclopedie;


/*
FONCTION : ouvrir_fichier(FILE * fichier, char * choix) : FILE *
Permet d'ouvrir le fichier qui contient les articles pour etre lu

PRE-CONDITION
- Une variable FILE* existe deja
- Le fichier a lire existe

POST-CONDITION
- La variable FILE* n'est plus nulle (contient les infos du fichier)

INVARIANT
*/
FILE * ouvrir_fichier(FILE * fichier, char * choix);


/*
FONCTION : initialisation_encyclopedie(FILE * fichier, Encyclopedie e) : Encyclopedie
Permet de decouper les informations de la variable FILE* en différents maillons dans l'arbre

PRE-CONDITION
- Une variable FILE* existe déjà
- Une variable Encyclopedie existe déjà

POST-CONDITION
- L'Encyclopedie n'est plus nulle

INVARIANT
*/
Encyclopedie initialisation_encyclopedie(FILE * fichier, Encyclopedie e);


/*
FONCTION : afficher_arbre_infixe_rec( Encyclopedie a, int profondeur) : Void
Affiche l'encyclopedie contenue dans l'arbre

PRE-CONDITION
- L'encyclopedie existe, implémentée sous forme d'arbre

POST-CONDITION

INVARIANT
*/
void afficher_arbre_infixe_rec( Encyclopedie a, int profondeur);


/*
FONCTION : estFeuille(Encyclopedie e) : int
Retourne "vrai" si le noeud testé est en bout de l'arbre

PRE-CONDITION
- L'encyclopédie existe et est implémentée sous forme d'arbre non nul

POST-CONDITION

INVARIANT
*/
int estFeuille(Encyclopedie e);


/*
FONCTION : retourneMax(Encyclopedie e) : Encyclopedie
Renvoie le noeud qui contient le plus grand identifiant qui se trouve dans l'arbre considéré (le noeud le plus à droite dont le fils_droit est vide)

PRE-CONDITION
- Une variable Encyclopedie existe et est non nulle

POST-CONDITION

INVARIANT
*/
Encyclopedie retourneMax(Encyclopedie e);


/*
FONCTION : creer_encyclopedie() : Encyclopedie

PRE-CONDITION

POST-CONDITION
- La variable Encyclopédie existe et est vide

INVARIANT
*/
Encyclopedie creer_encyclopedie();


/*
FONCTION : inserer(Encyclopedie e, int identifiant, char* titre, char* contenu) : Encyclopedie
Ajoute dans l'arbre un nouvel article, en triant les identifiants avec les propriétés des ABR

PRE-CONDITION
- La variable Encyclopédie existe
- Les variables qui constituent l'article sont definies

POST-CONDITION
- Elle contient un nouvel élément

INVARIANT
*/
Encyclopedie inserer(Encyclopedie e, int identifiant, char* titre, char* contenu);


/*
FONCTION : supprimer(Encyclopedie e, int identifiant) : Encyclopedie
Supprime un élément de l'encyclopédie

PRE-CONDITION
- La variable Encyclopédie existe et n'est pas vide
- La variable identifiant existe

POST-CONDITION
- L'encyclopedie possède un élément en moins

INVARIANT
*/
Encyclopedie supprimer(Encyclopedie e, int identifiant);


/*
FONCTION : rechercher_article(Encyclopedie e, int identifiant) : char *
Retourne l'article qui possède l'identifiant passé en paramètre

PRE-CONDITION
- La variable Encyclopédie existe
- La variable identifiant existe

POST-CONDITION
- La variable contient le contenu de l'article recherché

INVARIANT
*/
char * rechercher_article(Encyclopedie e, int identifiant);


/*
FONCTION : rechercher_article_plein_texte(Encyclopedie e, char * mot) : Encyclopedie
Retourne une nouvelle encyclopédie dont les articles contiennent tous la variable "mot"

PRE-CONDITION
- Le mot recherché n'est pas "nul"
- L'Encyclopédie existe

POST-CONDITION
- Une nouvelle variable Encyclopédie contient les articles issus de la recherche

INVARIANT
*/
Encyclopedie rechercher_article_plein_texte(Encyclopedie e, char * mot);


/*
FONCTION : detruire_encyclopedie(Encyclopedie e) : Void
Libère chaque espace mémoire de l'arbre en commençant par les feuilles

PRE-CONDITION
- La variable Encyclopedie existe

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


#endif // HEADER_H_INCLUDED
