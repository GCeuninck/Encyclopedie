#include "header.h"

int main()
{
    Encyclopedie e, e1;

    e = creer_encyclopedie();

    e = inserer(e, 1, "Titre 1", "Contenu 1");
    printf("N %d : %s - %s\n",e->clef, e->titre, e->contenu);

    e = inserer(e, 2, "Titre 2", "Contenu 2");
    printf("N %d : %s - %s\n",e->suivant->clef, e->suivant->titre, e->suivant->contenu);

    e = inserer(e, 1, "Autre Titre 1", "Autre Contenu 1");

    e = inserer(e, 3, "Titre 3", "Contenu 3");
    printf("N %d : %s - %s\n",e->suivant->suivant->clef, e->suivant->suivant->titre, e->suivant->suivant->contenu);

    e = inserer(e, 4, "Titre 4", "Contenu 4");
    printf("N %d : %s - %s\n",e->suivant->suivant->suivant->clef, e->suivant->suivant->suivant->titre, e->suivant->suivant->suivant->contenu);

    e = supprimer(e, 2);
    printf("N %d : %s - %s\n",e->suivant->clef, e->suivant->titre, e->suivant->contenu);

    e = supprimer(e, 4);
    if (est_vide(e->suivant->suivant)){
        printf("LE DERNIER ELEMENT A BIEN ETE SUPPRIME\n");
    }

    e = supprimer(e, 1);
    printf("N %d : %s - %s\n",e->clef, e->titre, e->contenu);

    printf("%s\n",rechercher_article(e, 3));

    printf("%s\n",rechercher_article(e, 1));

    printf("%s\n",rechercher_article(e, 7));

    e = inserer(e, 5, "Titre 5", "Contenu 5");

    e1 = rechercher_article_plein_texte(e, "Contenu");
    printf("N %d : %s - %s\n",e1->clef, e1->titre, e1->contenu);
    printf("N %d : %s - %s\n",e1->suivant->clef, e1->suivant->titre, e1->suivant->contenu);
    if(est_vide(e1->suivant->suivant)){
        printf("FIN\n");
    }

    e1 = rechercher_article_plein_texte(e, "3");
    printf("N %d : %s - %s\n",e1->clef, e1->titre, e1->contenu);
    if(est_vide(e1->suivant)){
        printf("FIN\n");
    }

    e1 = rechercher_article_plein_texte(e, "5");
    printf("N %d : %s - %s\n",e1->clef, e1->titre, e1->contenu);
    if(est_vide(e1->suivant)){
        printf("FIN\n");
    }

    e1 = rechercher_article_plein_texte(e, "t");
    printf("N %d : %s - %s\n",e1->clef, e1->titre, e1->contenu);
    printf("N %d : %s - %s\n",e1->suivant->clef, e1->suivant->titre, e1->suivant->contenu);

    detruire_encyclopedie(e1);
    e1 = NULL;

    return 0;
}
