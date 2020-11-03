#include "Liste.h"

FILE * ouvrir_fichier(FILE* fichier, char * choix){
    fichier = NULL;
    printf("%s\n", choix);

    if(fopen(choix, "r") != NULL){
        //Ajoute les informations du fichiers à la varible si l'ouverture a bien eu lieu
        fichier = fopen(choix, "r");
    }else{
        printf("ERREUR LORS DE L'OUVERTURE\n\n\n");
    }
    return fichier;
}


Encyclopedie initialisation_encyclopedie(FILE * fichier, Encyclopedie e){
    char ligne_actuelle[TAILLE_MAX];

    int identifiant;
    char * token_identifiant;
    char * token_titre;
    char * token_contenu;

    //Caractère en différentes informations
    const char separation[2] = "|";

    //Tant que les lignes ne sont pas vides / Informations séparées par changement de ligne
    while(fgets(ligne_actuelle, TAILLE_MAX, fichier) != NULL){

        //Respecte le format du fichier: Identifiant|Titre|Contenu
        token_identifiant = strtok(ligne_actuelle, separation);
        //Conversion de l'identifiant char*->int
        identifiant = atoi(token_identifiant);
        token_titre = strtok(NULL, separation);
        token_contenu = strtok(NULL, separation);

        if((identifiant != NULL && token_titre != NULL) && token_contenu != NULL){
            e = inserer(e, identifiant, token_titre, token_contenu);
        }
    }
    return e;
}

int est_vide(Encyclopedie e){

    int res = 0;

    //Si l'encyclopedie e est vide : res = VRAI
    if(e == NULL){
        res = 1;
    }

    return res;
}


void afficher_encyclopedie(Encyclopedie e){

    /*Si l'encyclopedie e n'est pas vide :
    on affiche l'identifiant, le titre et le contenu de chaque article de l'encyclopedie*/
    if(!est_vide(e)){
        printf("N %d : %s\n",e->clef, e->titre);
        afficher_encyclopedie(e->suivant);
    }
}


Encyclopedie creer_encyclopedie(){

    //On cree une encyclopedie vide
    Encyclopedie e;
    e = NULL;

    return e;
}


Encyclopedie inserer(Encyclopedie e, int identifiant, char * titre, char * contenu){
    Encyclopedie nouveau = creer_encyclopedie();
    nouveau = (Encyclopedie)malloc(sizeof(struct EncyclopedieSt));

    if(identifiant != 0 && titre != 0 && contenu != 0){
        nouveau->clef = identifiant;
        nouveau->titre = (char *)malloc(sizeof(char)*strlen(titre)+1);
        nouveau->titre = strcpy(nouveau->titre, titre);
        nouveau->contenu = (char *)malloc(sizeof(char)*strlen(contenu)+1);
        nouveau->contenu = strcpy(nouveau->contenu, contenu);

        nouveau->suivant = e;
    }else{
        nouveau = e;
    }
    return nouveau;
}


Encyclopedie supprimer(Encyclopedie e, int identifiant){

    Encyclopedie suppr;

    //Si l'encyclopedie e est vide ou que l'identifiant est non defini : Message d'erreur
    if (est_vide(e) || identifiant == NULL){
        printf("ENCYCLOPEDIE VIDE OU IDENTIFIANT NON DEFINI\n");
    }

    //Si le dernier element de la chaine n'est toujours pas l'article selectionne : Message d'erreur
    else if(est_vide(e->suivant) && e->clef != identifiant){
        printf("IDENTIFIANT INCONNU\n");
    }

    //Si le 1er maillon est celui a supprimer
    else if(identifiant == e->clef){

        //Le 1er maillon est remplace par le suivant puis on le supprime
        suppr = e;
        e = e->suivant;
        free(suppr->titre);
        free(suppr->contenu);
        free(suppr);
    }

    //Si le prochain maillon est celui a supprimer
    else if(e->suivant->clef == identifiant){

        //Le maillon suivant est remplace par son suivant puis on le supprime
        suppr = e->suivant;
        e->suivant = e->suivant->suivant;
        free(suppr->titre);
        free(suppr->contenu);
        free(suppr);
    }

    //Si le maillon n'est pas celui a supprimer : On recommence avec le maillon suivant
    else{
        e->suivant = supprimer(e->suivant, identifiant);
    }

    return e;
}


char * rechercher_article(Encyclopedie e, int identifiant){

    //Initialisation de la variable qui contiendra le contenu de l'article
    char * res = NULL;

    //Si l'encyclopedie e est vide ou que l'identifiant est non defini : Message d'erreur
    if(est_vide(e) || identifiant == NULL){
        printf("ENCYCLOPEDIE VIDE OU IDENTIFIANT INCONNU\n");
    }

    //Si le maillon est celui selectionne : res contient le contenu de cet article
    else if(e->clef == identifiant){
        res = e->contenu;
    }

    //Si le maillon n'est pas celui selectionne : On recommence avec le maillon suivant
    else{
        res = rechercher_article(e->suivant, identifiant);
    }

    return res;
}


Encyclopedie rechercher_article_plein_texte(Encyclopedie e, char * mot){

    //Creation d'une nouvelle encyclopedie qui contiendra les articles selectionnes par mot
    Encyclopedie res = creer_encyclopedie();

    while(e != NULL && mot != NULL){
        if(strstr(e->contenu, mot)){
            res = inserer(res, e->clef, e->titre, e->contenu);
        }
        e = e->suivant;
    }

    return res;
}


void detruire_encyclopedie(Encyclopedie e){

    Encyclopedie suppr;

    /*Tant qu'on a pas parcouru tout l'encyclopedie :
    Le maillon est remplace par son suivant puis on supprime ses informations*/
    while(!est_vide(e)){
        suppr = e;
        e = e->suivant;
        free(suppr->titre);
        free(suppr->contenu);
        free(suppr);
    }
}


void menu(){
    //CREATION DE L'ENCYCLOPEDIE
    Encyclopedie e = creer_encyclopedie();
    int menu = NULL;

    printf("----------------MENU--------------------\n");
    printf("\t Creation de l'encyclopedie\n");
    printf("1. Manuellement\n");
    printf("2. Par fichier externe\n");

    while(menu == NULL){
            printf("Votre choix : ");
            scanf("%d", &menu);

            switch(menu){
            case 1:
                menu_manuel(e);
                break;

            case 2:
                menu_automatique(e);
                break;

            default:
                printf("Entrer une valeur valide\n\n");
                break;
        }
    }
}


void menu_automatique(Encyclopedie e){
    FILE * fichier = NULL;
    char * choix = NULL;
    int menu;

    printf("----------------MENU--------------------\n");
    printf("\t Choisir le fichier\n");
    printf("1. Echantillons de 500 articles\n");
    printf("2. Articles tries\n");
    printf("3. Articles non tries\n\n");

    while(choix == NULL){
        printf("Votre choix : ");
        scanf("%d", &menu);

        switch(menu){
            case 1:
                choix = "B46_wikipedia_test.dat";
                break;

            case 2:
                choix = "B46_wikipedia_500K_sorted.dat";
                break;

            case 3:
                choix = "B46_wikipedia_500K_random.dat";
                break;

            default:
                printf("Entrer une valeur adaptee\n\n");
                break;
        }
    }

    fichier = ouvrir_fichier(fichier, choix);
    e = initialisation_encyclopedie(fichier, e);
    fclose(fichier);
    menu_principal(e);
}


void menu_manuel(Encyclopedie e){
    int nb_articles, i, identifiant;
    char titre[TAILLE_MAX];
    char contenu[TAILLE_MAX];

    printf("----------------MENU--------------------\n");
    printf("Saisir le nombre d'articles a ajouter : ");
    scanf("%d", &nb_articles);

    for(i = 0 ; i < nb_articles ; i++){

        printf("Identifiant : ");
        scanf("%d", &identifiant);
        fflush(stdin);  //Permet de vider le buffer d'entrée de stdin

        printf("Titre : ");
        fgets(titre, TAILLE_MAX, stdin);
        fflush(stdin);

        printf("Contenu : ");
        fgets(contenu, TAILLE_MAX, stdin);
        fflush(stdin);

        printf("\n");

        e = inserer(e, identifiant, titre, contenu);
    }
    menu_principal(e);
}


void menu_principal(Encyclopedie e){
    int menu = NULL;
    int sortie = 0;

    //Initialisation variables pour recherches/suppression
    int choix;
    char mot_clef[26];

    //Initialisation des variables pour l'ajout
    int identifiant;
    char titre[TAILLE_MAX];
    char contenu[TAILLE_MAX];

    Encyclopedie e1 = creer_encyclopedie();

    do{
            printf("----------------MENU--------------------\n");
            printf("\t Accueil\n");
            printf("1. Supprimer un article\n");
            printf("2. Rechercher par identifiant\n");
            printf("3. Rechercher par un mot\n");
            printf("4. Inserer un article\n");
            printf("5. Afficher encyclopedie\n\n");
            printf("6. Quitter\n\n");

            printf("Votre choix : ");
            scanf("%d", &menu);
            printf("\n");

            switch(menu){
            case 1:     //Supression d'article
                printf("Suppression\n");
                printf("Article a supprimer : ");
                scanf("%d", &choix);
                e = supprimer(e, choix);
                break;

            case 2:     //Recherche par identifiant
                printf("Debut recherche\n");
                printf("Article a rechercher : ");
                scanf("%d", &choix);
                printf("\n");
                printf("%s", rechercher_article(e, choix));
                printf("\n\n");
                break;

            case 3:     //Recherche par mot
                printf("Debut recherche\n");
                printf("Mot a rechercher :\n");
                scanf("%s", &mot_clef);
                e1 = rechercher_article_plein_texte(e, mot_clef);
                afficher_encyclopedie(e1);
                break;

             case 4:    // Insérer un article
                printf("Identifiant : ");
                scanf("%d", &identifiant);
                fflush(stdin);  //Permet de vider le buffer d'entrée de stdin

                printf("Titre : ");
                fgets(titre, TAILLE_MAX, stdin);
                fflush(stdin);

                printf("Contenu : ");
                fgets(contenu, TAILLE_MAX, stdin);
                fflush(stdin);

                printf("\n");

                e = inserer(e, identifiant, titre, contenu);
                break;

            case 5:     //Afficher arbre
                afficher_encyclopedie(e);
                printf("\n");
                break;

            case 6:     //Quitter
                detruire_encyclopedie(e1);
                detruire_encyclopedie(e);
                e = NULL;
                e1 = NULL;
                sortie = 1;
                break;

            default:
                printf("Entrer une valeur adaptee\n\n");
                break;
        }
    }while(sortie == 0);
    if(sortie != 1){
        menu_principal(e);
    }
}
