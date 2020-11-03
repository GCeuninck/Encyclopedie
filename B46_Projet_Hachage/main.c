#include "Hachage.h"

int main()
{
    Encyclopedie e, e1;

    e = creer_encyclopedie();
    printf("L'ENCYCLOPEDIE EST VIDE ? (1 = VRAI / 0 = FAUX) : %d\n",est_vide(e));

    e = inserer(e, 1, "Titre 1", "Contenu 1");
    e = inserer(e, 2, "Titre 2", "Contenu 2");
    e = inserer(e, 1, "Titre 1-2", "Contenu 1-2");
    e = inserer(e, 6, "Titre 6", "Contenu 6");
    e = inserer(e, 6, "Titre 6-2", "Contenu 6-2");

    afficher_encyclopedie(e);
    printf("L'ENCYCLOPEDIE EST VIDE ? (1 = VRAI / 0 = FAUX) : %d\n",est_vide(e));

    e = supprimer(e, 1);
    afficher_encyclopedie(e);

    e = supprimer(e, 3);
    afficher_encyclopedie(e);

    e = supprimer(e, 6);
    afficher_encyclopedie(e);

    e = supprimer(e, 2);
    afficher_encyclopedie(e);

    printf("\n");

    e = inserer(e, 8, "Titre 8", "Contenu 8");
    e = inserer(e, 10, "Titre 10", "Contenu 10");
    afficher_encyclopedie(e);

    printf("%s\n",rechercher_article(e, 1));

    printf("%s\n",rechercher_article(e, 8));

    printf("%s\n",rechercher_article(e, 10));

    e1 = rechercher_article_plein_texte(e, "Contenu");
    afficher_encyclopedie(e1);

    e1 = rechercher_article_plein_texte(e, "10");
    afficher_encyclopedie(e1);

    e1 = rechercher_article_plein_texte(e, "5");
    afficher_encyclopedie(e1);

    e1 = rechercher_article_plein_texte(e, "t");
    afficher_encyclopedie(e1);

    detruire_encyclopedie(e1);
    afficher_encyclopedie(e1);
    printf("L'ENCYCLOPEDIE EST VIDE ? (1 = VRAI / 0 = FAUX) : %d\n",est_vide(e1));
    e1 = NULL;


    return 0;
}
