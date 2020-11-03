#include "Hachage.h"

int main()
{

    menu();
/*
//INITIALISATION DES ENCYCLOPEDIES
    Encyclopedie e, e1, e2;
    e = creer_encyclopedie();
    e1 = creer_encyclopedie();
    e2 = creer_encyclopedie();

    char * var_nulle = NULL;

//INITIALISATION DU FICHIER
    FILE * fichier = NULL;
    fichier = ouvrir_fichier(fichier, "B46_wikipedia_test.dat");
    e = initialisation_encyclopedie(fichier, e);
    //afficher_encyclopedie(e);

    printf("\n\n");

//INSERTIONS MANUELLES
    printf("INSERTION\n\n");
    e = inserer(e, 1, "Titre 1", "Contenu 1");
    e = inserer(e, 2, "Titre 2", "Contenu 2");
    //Doublon
    e = inserer(e, 1, "Titre 1-2", "Contenu 1-2");
    e = inserer(e, 6, "Titre 6", "Contenu 6");
    //Doublon
    e = inserer(e, 6, "Titre 6-2", "Contenu 6-2");
    e = inserer(e, 8, "Titre 8", "Contenu 8");
    e = inserer(e, 10, "Titre 10", var_nulle);
    e = inserer(e, 10, var_nulle, "Contenu 10");

    printf("\n\n");

//SUPRESSIONS
    printf("SUPPRESSION\n\n");
    e = supprimer(e, 25523);
    //afficher_encyclopedie(e);

    e = supprimer(e, 1);
    //afficher_encyclopedie(e);

    //1er suppression
    e = supprimer(e, 2);
    //afficher_encyclopedie(e);

    e = supprimer(e, 11908019);
    //afficher_encyclopedie(e);
    e = supprimer(e, 6747502);
    //afficher_encyclopedie(e);

    //Suppression d'un identifiant inconnu
    e = supprimer(e, 2);

    //Suppression dans une encyclopedie vide
    e2 = supprimer(e2, 6747502);

    printf("\n\n");

//RECHERCHE ARTICLE
    printf("RECHERCHE\n\n");
    printf("%s\n",rechercher_article(e, 5967677));
    printf("%s\n",rechercher_article(e, 8));
    printf("%s\n",rechercher_article(e, 1474691));
    printf("%s\n",rechercher_article(e, 1));
    printf("%s\n",rechercher_article(e, 10533691));
    printf("%s\n",rechercher_article(e, 4483743));
    printf("%s\n",rechercher_article(e, 2));
    printf("%s\n",rechercher_article(e2, 8));

    printf("\n\n");

//RECHERCHE ARTICLE PLEIN TEXTE
    printf("RECHERCHE PLEIN\n\n");
    e1 = rechercher_article_plein_texte(e, "Arbre binaire");
    //afficher_encyclopedie(e1);

    e1 = rechercher_article_plein_texte(e2, "Arbre binaire");
    //afficher_encyclopedie(e1);

    e1 = rechercher_article_plein_texte(e, "ddnsdnjsdjsd");
    //afficher_encyclopedie(e1);

    e1 = rechercher_article_plein_texte(e, "Laudon");
    //afficher_encyclopedie(e1);

    printf("\n\n");

//FERMETURE ET DESTRUCTION
    fclose(fichier);
    printf("DESTRUCTION\n\n");

    detruire_encyclopedie(e);
    e = NULL;

    detruire_encyclopedie(e1);
    e1 = NULL;
*/

    return 0;
}
