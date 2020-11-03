#include "Arbre.h"

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

    //Initialisation des variables qui contiennent les informations de la ligne actuelle
    int identifiant;
    char * token_identifiant;
    char * token_titre;
    char * token_contenu;

    //Caractère qui permet la séparation de la la chaine de caractère
    const char separation[2] = "|";

    //Tant que les lignes ne sont pas vides / Informations séparées par changement de ligne
    while(fgets(ligne_actuelle, TAILLE_MAX, fichier) != NULL){

        //Respecte le format du fichier: Identifiant|Titre|Contenu
        token_identifiant = strtok(ligne_actuelle, separation);
        identifiant = atoi(token_identifiant);      //Conversion de l'identifiant char*->int
        token_titre = strtok(NULL, separation);
        token_contenu = strtok(NULL, separation);

        if((identifiant != NULL && token_titre != NULL) && token_contenu != NULL){
            //Ajouter le nouvel article si les informations ne sont pas vides
            e = inserer(e, identifiant, token_titre, token_contenu);
        }
    }
    return e;
}


//CODE RECUPERRE DU TP SUR LES ARBRES
void afficher_arbre_infixe_rec( Encyclopedie a, int profondeur ) {

	int i;
	if ( a != NULL ) {

		afficher_arbre_infixe_rec( a->fils_droit, profondeur + 1 );
		for ( i = 0 ; i < profondeur ; i++ ) {
			printf( "  " );
		}
		printf( "%d - %s\n", a->clef, a->titre);
		afficher_arbre_infixe_rec( a->fils_gauche, profondeur + 1 );
	}
}


int estFeuille(Encyclopedie e){
    int resultat = 0;
    if(e != NULL){
        //Si le fils droit et le fils gauche sont vide -> noeud considéré est une feuille
        if(e->fils_droit == NULL && e->fils_gauche == NULL){
            resultat = 1;
        }
    }else{
        printf("ARBRE NUL\n");
    }

    return resultat;
}


Encyclopedie retourneMax(Encyclopedie e){
    Encyclopedie Maximum = NULL;

    if(e != NULL){
        if(e->fils_droit == NULL){
            //Si le fils droit est vide on est en présence du maximum de l'arbre
            Maximum = e;
        }else{
            //Sinon appel à la droit pour trouver le maximum
            Maximum = retourneMax(e->fils_droit);
        }
    }else{
        printf("ARBRE NUL\n");
    }
    return Maximum;
}


Encyclopedie creer_encyclopedie(){
    //Creer Encyclopedie vide
    Encyclopedie e;
    e = NULL;

    return e;
}


Encyclopedie inserer(Encyclopedie e, int identifiant, char * titre, char * contenu){

    if(e == NULL && identifiant != NULL && titre != NULL && contenu != NULL){
        //Alloue la mémoire au nouveau noeud
        e = (Encyclopedie)malloc(sizeof(struct EncyclopedieSt));

        e->clef = identifiant;

        //Alloue de la mémoire pour la chaine de caractère de la taille de la chaine qui y sera rangée + le caractère qui indique la fin de la chaîne
        e->titre = (char *)malloc(sizeof(char)*strlen(titre) + 1);
        e->titre = strcpy(e->titre, titre);
        e->contenu = (char *)malloc(sizeof(char)*strlen(contenu) + 1);
        e->contenu = strcpy(e->contenu, contenu);

        //Permet d'indiquer la fin de l'arbre
        e->fils_gauche = NULL;
        e->fils_droit = NULL;

    }else if(e->clef == identifiant){
        printf("IDENTIFIANT EXISTE DEJA\n");

    }else if(identifiant != NULL && titre != NULL && contenu != NULL){
        //Ajoute un noeud en respectant les propriétés des ABR
        if(identifiant < e->clef){
            //Identifiants à gauche plus petits
            e->fils_gauche = inserer(e->fils_gauche, identifiant, titre, contenu);
        }else{
            //Identifiants à droite plus grands
            e->fils_droit = inserer(e->fils_droit, identifiant, titre, contenu);

        }
    }else{
        printf("INFORMATIONS NON DEFINIES\n");
    }
    return e;
}


Encyclopedie supprimer(Encyclopedie e, int identifiant){
    Encyclopedie temporaire = NULL;

    if(e != NULL){

        //Si on n'est pas sur le bon noeud on le retrouve grace au proprietes des ABR
        if(e->clef != identifiant){

            if(identifiant < e->clef){
                e->fils_gauche = supprimer(e->fils_gauche, identifiant);
            }else{
                e->fils_droit = supprimer(e->fils_droit, identifiant);
            }
        }else{
            if(e->fils_gauche != NULL && e->fils_droit != NULL){  //CAS 2 FILS

                //Copie du plus grand du sous arbre gauche dans le noeud a supprimer
                temporaire = retourneMax(e->fils_gauche);
                e->clef = temporaire->clef;
                e->contenu = temporaire->contenu;
                e->titre = temporaire->titre;

                //Relie le sous arbre gauche sans le point remonté au point changé ci-dessus
                e->fils_gauche = supprimer(e->fils_gauche, temporaire->clef);
            }
            //Pas de fils, on peut simplement vider le noeud
            else if(estFeuille(e)){  //CAS 0 FILS
                free(e);
                e = NULL;

            //Un fils à gauche, on le remonte d'un rang
            }else if(e->fils_gauche != NULL && e->fils_droit == NULL){ //CAS 1 FILS A DROITE
                temporaire = e;
                e = e->fils_gauche;
                free(temporaire);

            //Un fils à gauche, on le remonte d'un rang
            }else if(e->fils_gauche == NULL && e->fils_droit != NULL){ //CAS 1 FILS A GAUCHE
                temporaire = e;
                e = e->fils_droit;
                free(temporaire);
            }
        }
    }
    return e;
}


char * rechercher_article(Encyclopedie e, int identifiant){
    char * resultat = NULL;

    if(e != NULL && identifiant != NULL){
        if(identifiant == e->clef){
            //Retourne le contenu de l'article recherché
            resultat = e->contenu;

        //Rappel de la recherche en utilisant la propriétés de classement des ABR
        }else if(identifiant > e->clef){
            resultat = rechercher_article(e->fils_droit, identifiant);
        }else{
            resultat = rechercher_article(e->fils_gauche, identifiant);
        }
    }else{
        printf("ENCYCLOPEDIE NULLE OU IDENTIFIANT NON DEFINI\n");
    }
    return resultat;
}


Encyclopedie rechercher_article_plein_texte(Encyclopedie e, char * mot){
    //Initialisation de l'encyclopédie de sortie

    Encyclopedie res = creer_encyclopedie();
    Encyclopedie res_droit = creer_encyclopedie();
    Encyclopedie res_gauche = creer_encyclopedie();

    if(e != NULL && mot != NULL){
        //Si le contenu du noeud actuel contient le mot recherché
        if(strstr(e->contenu, mot)){

            //Ajoute l'article dans la nouvelle encyclopédie
            res = inserer(res, e->clef, e->titre, e->contenu);

            //Appel sur les fils pour continuer la recherche
            res_gauche = rechercher_article_plein_texte(e->fils_gauche, mot);
            res_droit = rechercher_article_plein_texte(e->fils_droit, mot);
        }else{
            //Appel sur les fils pour continuer la recherche
            res_gauche = rechercher_article_plein_texte(e->fils_gauche, mot);
            res_droit = rechercher_article_plein_texte(e->fils_droit, mot);
        }


        //Permet de faire le lien entre les arbres
        if(res != NULL){
            //Si la recherche courante a abouti, on la lie aux deux autres recherche
            res->fils_droit = res_droit;
            res->fils_gauche = res_gauche;
        }else if(res == NULL && res_gauche != NULL){
            //Si la recherche courante n'a pas abouti, mais la recherche à gauche oui
            //On lie alors la recherche à droite au maximum de la recherche à gauche
            res = res_gauche;
            Encyclopedie lien = retourneMax(res);
            lien->fils_droit = res_droit;
        }else{
            //Si la recherche courante et la recherche à gauche n'ont pas abouti, on ne garde que la recherche à droite
            res = res_droit;
        }
    }
    return res;
}


void detruire_encyclopedie(Encyclopedie e){
    if(e != NULL){
        detruire_encyclopedie(e->fils_gauche);
        detruire_encyclopedie(e->fils_droit);

        //Libère l'espace mémoire des variables attribuées par malloc
        free(e->contenu);
        free(e->titre);

        free(e);
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
                printf("\n\n");
                printf("%s", rechercher_article(e, choix));
                printf("\n\n");
                break;

            case 3:     //Recherche par mot
                printf("\t Debut recherche\n");
                printf("Mot a rechercher :\n");
                scanf("%s", &mot_clef);
                e1 = rechercher_article_plein_texte(e, mot_clef);
                afficher_arbre_infixe_rec(e1, 0);
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
                afficher_arbre_infixe_rec(e, 0);
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
